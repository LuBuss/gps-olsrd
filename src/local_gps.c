//
// Created by pi on 27/08/16.
//

#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "local_gps.h"
#include "defs.h"


/**
 *Initizes the GPS module
 *
 *@param
 *@return status of GPS setup
 */
bool
Init_GPS(void){
    int rc;
    if((rc = gps_open("localhost", "2947", &mygps_data)) == -1){
        printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
        return false;
    }

    gps_stream(&mygps_data, WATCH_ENABLE | WATCH_JSON, NULL);
    return true;
}

/**
 * Checks that the GPS is ready
 *
 * @return state of the GPS
 */
bool
GPS_ready(void){
    int rc;
    if((rc = gps_read(&mygps_data)) == -1){
        #ifdef DEBUG
            OLSR_PRINTF(1, "Error Reading GPS data\n");
            OLSR_PRINTF(1, "code: %d reason: %s\n", rc, gps_errstr(rc));
        #endif
        return false;
    } else {
        return true;
    }

};

/**
 *
 */
unsigned short
Get_Latitude(void){

    if (gps_read(&mygps_data) == -1){
        #ifdef DEBUG
            OLSR_PRINTF(1, "Not able to read GPS\n");
        #endif
        return last_lati;
    } else {
        if (mygps_data.status == STATUS_FIX){
            double full_lati = mygps_data.fix.latitude;
            int int_lati = abs(full_lati * 100000);
            unsigned short lati = int_lati % USHRT_MAX;
            last_lati = lati;
            return lati;
        } else {
            #ifdef DEBUG
                OLSR_PRINTF(1, "Unable to get a GPS FIX\n");
            #endif
            return last_lati;
        }
    }
}

/**
 *
 */
unsigned short
Get_Longitude(void){

    if (gps_read(&mygps_data) == -1){
    #ifdef DEBUG
        OLSR_PRINTF(1, "Not able to read GPS\n");
    #endif
        return last_long;
    } else {
        if (mygps_data.status == STATUS_FIX){
            double full_long = mygps_data.fix.longitude;
            int int_long = abs(full_long * 100000);
            unsigned short lng = int_long % USHRT_MAX;
            last_long = lng;
            return lng;
        } else {
            #ifdef DEBUG
                OLSR_PRINTF(1, "Unable to get a GPS FIX\n");
            #endif
            return last_long;
        }
    }
}


