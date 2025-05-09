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
    {30.06575420, 31.27833720, 8}   // "Fountain"
};

const int landmarkCount = sizeof(landmarks) / sizeof(Landmark);

char* name[5] = {"Hall A", "Lupan", "Civil", "Fountain", "Error"};

// ------ Function Definitions ------

// Reads the relevant part of the GPRMC sentence from UART
void GPS_READ() {
    char flag; // Will be used in logname check
    char counter = 0; // Used in filling gps_input_array
    char recieved_char; // For readability
    char i; // Counter

    // Check for the GPRMC log name
    do {
        flag = 1;
        for (i = 0; i < 7; i++) { // 7 is strlen("$GPRMC,")
            if (UART2_ReadChar() != GPS_LOGNAME[i]) {
                flag = 0;
                break;
            }
        }
    } while (flag == 0);

    // Clear GPS_input_array (ensure null termination if expecting string functions later)
    // strcpy(GPS_input_array, "");
    // More robust: memset(GPS_input_array, 0, sizeof(GPS_input_array));
    memset(GPS_input_array, 0, sizeof(GPS_input_array));


    // Read data until 'E' (East designator for longitude) or end of buffer
    counter = 0; // Reset counter for GPS_input_array
    do {
        recieved_char = UART2_ReadChar();
        if (counter < sizeof(GPS_input_array) - 1) { // Prevent buffer overflow
            GPS_input_array[counter] = recieved_char;
            counter++;
        } else {
            // Buffer full, handle error or break
            break;
        }
    } while (recieved_char != 'E' && recieved_char != '\n' && recieved_char != '*');
    GPS_input_array[counter] = '\0';
}


// Parses the GPRMC sentence data stored in GPS_input_array
void GPS_format() {
    char counter_of_token_strings = 0;
    char temp_input[sizeof(GPS_input_array)]; // Create a mutable copy for strtok

    // GPS_input_array = "UTC_Time,Status,Latitude,N/S,Longitude,E"
    strcpy(temp_input, GPS_input_array); // Use a copy for strtok

    token = strtok(temp_input, ",");

    // $GPRMC, [0]=UTC, [1]=Status, [2]=Lat, [3]=N/S, [4]=Lon, [5]=E/W ...
    while (token != NULL && counter_of_token_strings < 12) {
        strcpy(GPS_2D[counter_of_token_strings], token);
        token = strtok(NULL, ",");
        counter_of_token_strings++;
    }

    // Check data validity: GPS_2D[1] should be "A"
    if (counter_of_token_strings > 5 && strcmp(GPS_2D[1], "A") == 0) {
        // Latitude: GPS_2D[2], N/S: GPS_2D[3]
        if (strlen(GPS_2D[2]) > 0) {
            rawLat = atof(GPS_2D[2]);
            deg = (int)(rawLat / 100);
            min = rawLat - (float)(deg * 100);
            latitude = deg + (min / 60.0);
            if (strcmp(GPS_2D[3], "S") == 0) {
                latitude = -latitude;
            }
        } else {
            latitude = 0.0; // Invalid or missing data
        }

        // Longitude: GPS_2D[4], E/W: GPS_2D[5]
        if (strlen(GPS_2D[4]) > 0) {
            rawLon = atof(GPS_2D[4]);
            deg = (int)(rawLon / 100);
            min = rawLon - (float)(deg * 100);
            longitude = deg + (min / 60.0);
            if (strcmp(GPS_2D[5], "W") == 0) {
                longitude = -longitude;
            }
        } else {
            longitude = 0.0; // Invalid or missing data
        }
    } else {
        // Data is not valid or not enough tokens
        latitude = 0.0;
        longitude = 0.0;
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
