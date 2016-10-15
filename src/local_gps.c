//
// Created by pi on 27/08/16.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "local_gps.h"
#include "defs.h"

#define GEO_ACCURACY 10000

uint16_t shortLati = 0;
uint16_t shortLong = 0;
double longitude = 0;
double latitude = 0;
uint8_t first = 1;

/**
 *Initizes the GPS module
 *
 *@return {int} -1 setup failed
 *              1 setup successful
 */
int
Init_GPS(double lat, double lon){

    latitude = lat;
    longitude = lon;

    shortLati = Geo_To_Short(latitude);
    shortLong = Geo_To_Short(longitude);

    //No GPS so return valid
    return 1;

    /*
    int rc;
    //Opening gpsd daemon and checking for connection
    if((rc = gps_open("localhost", "2947", &mygps_data)) == -1){
        //Print error connection
        printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
        return -1;
    } else {
        //Starts a stream of geo data
        gps_stream(&mygps_data, WATCH_ENABLE | WATCH_JSON, NULL);

        return 1;
    }
     */
}

/**
 * GEO_TO_SHORT
 * Converts a geo position (longitude or Latitude) into a uint16_t equialent.
 *
 * @param {double} geo_position - A geo positions (longitude or Latitude) value
 * @return {uint16_t} the geo position in the compressed short version
 */
uint16_t
Geo_To_Short(double geo_position){
    int geo_int_form = geo_position * GEO_ACCURACY;
    return geo_int_form % USHRT_MAX;
}

/**
 * SHORT_TO_GEO
 * Converts a geo position (longitude or Latitude) into its original form by using the current gps position and finding
 * the losts possible match to this position.
 *
 * @param short_geo {uint16_t} - A compressed geo position gather from a communication message
 * @param current_geo {double} - The current geo position gather from this device
 * @return {double} - The full geo position of the short_geo position entered
 */
double
Short_To_Geo(uint16_t short_geo, uint8_t type){
    //declaring variables
    double geo1;
    double geo2;

    double current_geo;
    if (latitude == 0){
        OLSR_PRINTF(1, "Current GPS not working");
    } else if(type == 1){
        current_geo = latitude;
    } else {
        current_geo = longitude;
    }

    //finds the multipler that has been removed in compression
    int multipler1 = floor((current_geo * GEO_ACCURACY) / USHRT_MAX) ;  //23
    int multipler2 = floor(((current_geo * GEO_ACCURACY) / USHRT_MAX) + 0.5); //22

    //finds the two possible multiplers are same
    if(multipler1 == multipler2){
        //deincrement one of the multiplers
        multipler2 -= 1;
    }

    //Gets the two possible Geo Positions
    geo1 = (double)((USHRT_MAX * multipler1) + short_geo) / GEO_ACCURACY;
    geo2 = (double)((USHRT_MAX * multipler2) + short_geo) / GEO_ACCURACY;

    //Find the closest Geo Position and returns results
    return (abs(geo1 - current_geo) <= abs(geo2 - current_geo)) ? geo1 : geo2;
}

/**
 * GET_LATITUDE
 * uses the gps stream, to get the current latitude value and convert to the a short_geo
 *
 * return {uint16_t} the Latitude in the short form
 */
uint16_t
Get_Latitude(void){

    return shortLati;
    /*
    if (gps_read(&mygps_data) == -1){
        //unable to get gps data
        #ifdef DEBUG
                OLSR_PRINTF(1, "Not able to read GPS\n");
        #endif
        //return last stored latitude
        return shortLati;
    } else {
        if (mygps_data.status == STATUS_FIX) {
            //Get latitude from mygps
            latitude = mygps_data.fix.latitude;
            //convert geo to short
            shortLati = Geo_To_Short(latitude);
            return shortLati;
        } else {
            //unable to get gps fixed
            #ifdef DEBUG
                        OLSR_PRINTF(1, "Unable to get a GPS FIX\n");
            #endif
            //return the last stored shortLati
            return shortLati;
        }
    }
     */
}

/**
 * GET_LONGITUDE
 * uses the gps stream, to get the current longitude value and convert to the a short_geo, if gps gets a fixed status
 * the Longitude and shortLong global variables are updated.
 *
 * return {uint16_t} the Longitude in the short form
 */
uint16_t
Get_Longitude(void){

    return shortLong;
    /*
    if (gps_read(&mygps_data) == -1){
    #ifdef DEBUG
        OLSR_PRINTF(1, "Not able to read GPS\n");
    #endif
        return shortLong;
    } else {
        if (mygps_data.status == STATUS_FIX){
            //Get latitude from mygps
            longitude = mygps_data.fix.longitude;
            //convert geo to short
            shortLong = Geo_To_Short(longitude);
            return shortLong;
        } else {
            #ifdef DEBUG
                OLSR_PRINTF(1, "Unable to get a GPS FIX\n");
            #endif
            return shortLong;
        }
    }*/
}

