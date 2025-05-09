#ifndef GPS_H
#define GPS_H

#include <stdio.h>

// ------ Macros ------
#define PI 3.14159265359
#define EARTH_RADIUS_KM 6371.0

// ------ Structure Definition ------
typedef struct {
    float latitude;
    float longitude;
    int len;
} Landmark;

// ------ Extern Variable Declarations ------

// For GPS_READ and GPS_format
extern char *token;
extern char GPS_input_array[50];
extern char GPS_LOGNAME[];
extern char GPS_2D[12][20];

// For storing final converted latitude and longitude
extern float latitude;
extern float longitude;

// For storing raw latitude and longitude
extern float minDist;
extern int deg;
extern float min;
extern float rawLat;
extern float rawLon;

// Landmark data (name array needs to be accessed by main.c)
extern char* name[5];
extern const int landmarkCount;

// ------ Function Prototypes ------

// Reads the GPRMC sentence from UART
void GPS_READ(void);

// Parses the GPRMC sentence stored in GPS_input_array and populates latitude and longitude
void GPS_format(void);

// Convert degrees to radians
float toRadians(float degree);

// Calculates the Haversine distance
float CalculateDistance(float lat1, float lon1, float lat2, float lon2);

// Finds the index of the nearest landmark
int FindNearestLandmark(float lat, float lon);

#endif // GPS_H
