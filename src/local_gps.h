//
// Created by pi on 27/08/16.
//

#ifndef OLSRD_LOCAL_GPS_H
#define OLSRD_LOCAL_GPS_H
#include <gps.h>


struct gps_data_t mygps_data;
uint16_t shortLati;
uint16_t shortLong;
double longitude;
double latitude;

/**
 *Initizes the GPS module
 *
 *@return {int} -1 setup failed
 *              1 setup successful
 */
int Init_GPS(void);

/**
 * GEO_TO_SHORT
 * Converts a geo position (longitude or Latitude) into a uint16_t equialent.
 *
 * @param {double} geo_position - A geo positions (longitude or Latitude) value
 * @return {uint16_t} the geo position in the compressed short version
 */
uint16_t Geo_To_Short(double geo_position);

/**
 * SHORT_TO_GEO
 * Converts a geo position (longitude or Latitude) into its original form by using the current gps position and finding
 * the losts possible match to this position.
 *
 * @param short_geo {uint16_t} - A compressed geo position gather from a communication message
 * @param current_geo {double} - The current geo position gather from this device
 * @return {double} - The full geo position of the short_geo position entered
 */
double Short_To_Geo(uint16_t short_geo, double current_geo);

/**
 * GET_LATITUDE
 * uses the gps stream, to get the current latitude value and convert to the a short_geo, if gps gets a fixed status
 * the Latitude and shortLati global variables are updated.
 *
 * return {uint16_t} the Latitude in the short form
 */
uint16_t Get_Latitude(void);

/**
 * GET_LONGITUDE
 * uses the gps stream, to get the current longitude value and convert to the a short_geo, if gps gets a fixed status
 * the Longitude and shortLong global variables are updated.
 *
 * return {uint16_t} the Longitude in the short form
 */
uint16_t Get_Longitude(void);

#endif //OLSRD_LOCAL_GPS_H
