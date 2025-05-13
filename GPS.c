#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "GPS.h"
#include "UART.h"

// Global Variable Definitions (declared as extern in GPS.h)
char *token;
char GPS_input_array[50];
char GPS_LOGNAME[]="$GPRMC,";
char GPS_2D[12][20];
float latitude = 0.0;
float longitude = 0.0;

// Global intermediate variables for calculations
float minDist = 1e9;
int deg;
float min;
float rawLat;
float rawLon;


// ------ Landmark Data ------
Landmark landmarks[] = {
    {30.064242, 31.280137, 6},  // "Hall A"
    {30.063459, 31.279696, 5},  // "Lupan"
    {30.0642569, 31.2778623, 5},  // "Civil"
    {30.06575420, 31.27833720, 8},   // "Fountain"
    {30.065153, -31.280037, 7} //"Library"
};

const int landmarkCount = sizeof(landmarks) / sizeof(Landmark);

char* name[6] = {"Hall A", "Lupan", "Civil", "Fountain", "Library", "Error"};

// ------ Function Definitions ------

// Reads the relevant part of the GPRMC sentence from UART
void GPS_ReadData(void) {
    enum State { SEARCHING, HEADER, DATA } state = SEARCHING;
    char buffer[80] = {0}; // Local buffer to avoid modifying global directly
    char ch;
    int index = 0;
    const char *header = "$GPRMC,";
    int headerIndex = 0;

    // State machine to read GPS data
    while (index < sizeof(buffer) - 1) {
        ch = UART2_ReadChar(); // Assume this blocks until data is available

        switch (state) {
            case SEARCHING:
                if (ch == header[headerIndex]) {
                    headerIndex++;
                    if (headerIndex == strlen(header)) {
                        state = HEADER;
                        headerIndex = 0; // Reset for next check if needed
                    }
                } else {
                    headerIndex = 0; // Reset if mismatch
                }
                break;

            case HEADER:
                if (ch == ',') {
                    state = DATA;
                }
                buffer[index++] = ch;
                break;

            case DATA:
                buffer[index++] = ch;
                if (ch == '*' || ch == '\n') {
                    buffer[index] = '\0'; // Null terminate
                    // Copy to global array if needed
                    strncpy(GPS_input_array, buffer, sizeof(GPS_input_array) - 1);
                    GPS_input_array[sizeof(GPS_input_array) - 1] = '\0';
                    return;
                }
                break;
        }
    }
    // Buffer overflow, null terminate anyway
    GPS_input_array[0] = '\0';
}


// Parses the GPRMC sentence data stored in GPS_input_array
void GPS_ProcessData(void) {
    float lat = 0.0f, lon = 0.0f;
    int field = 0;
    char *ptr = GPS_input_array;
    char temp[20];
    float rawValue;
    int degrees;
    float minutes;
    char direction;

    // Skip initial $GPRMC,
    while (*ptr && field < 2) {
        if (*ptr++ == ',') field++;
    }

    // Parse fields: [2]=Latitude, [3]=N/S, [4]=Longitude, [5]=E/W
    while (*ptr && field < 6) {
        if (*ptr == ',') {
            field++;
            ptr++;
            continue;
        }
        if (field == 2 || field == 4) { // Latitude or Longitude
            char *end = temp;
            while (*ptr && *ptr != ',' && (end - temp) < sizeof(temp) - 1) {
                *end++ = *ptr++;
            }
            *end = '\0';
            rawValue = atof(temp);
            degrees = (int)(rawValue / 100);
            minutes = rawValue - (degrees * 100);
            if (field == 2) lat = degrees + (minutes / 60.0f);
            else if (field == 4) lon = degrees + (minutes / 60.0f);
        } else if (field == 3 || field == 5) { // Direction
            direction = *ptr;
            if (field == 3 && direction == 'S') lat = -lat;
            else if (field == 5 && direction == 'W') lon = -lon;
            ptr++;
        }
        while (*ptr && *ptr != ',') ptr++; // Skip to next field
        field++;
    }

    // Validate status (field 1 should be 'A' for valid data)
    char *status = GPS_input_array;
    while (*status && *status != ',') status++;
    if (*++status == 'A') {
        latitude = lat;
        longitude = lon;
    } else {
        latitude = 0.0f;
        longitude = 0.0f; // Invalid fix
    }
}


// --- Convert degrees to radians ---
float toRadians(float degree) {
    return degree * (PI / 180.0);
}

// --- Haversine Distance Function ---
float CalculateDistance(float lat1, float lon1, float lat2, float lon2) {
    float dLat = toRadians(lat2 - lat1);
    float dLon = toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    float a, c;
    a = sin(dLat / 2) * sin(dLat / 2) +
        cos(lat1) * cos(lat2) *
        sin(dLon / 2) * sin(dLon / 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

// --- Find Nearest Landmark ---
int FindNearestLandmark(float lat, float lon) {
    int idx = landmarkCount;
    int i;

    if (lat == 0.0 && lon == 0.0) {
        return idx;
    }

    for (i = 0; i < landmarkCount; i++) {
        float dist = CalculateDistance(lat, lon, landmarks[i].latitude, landmarks[i].longitude);
        if (dist < minDist) {
            minDist = dist;
            idx = i;
        }
    }
    return idx;
}
