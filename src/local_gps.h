//
// Created by pi on 27/08/16.
//

#ifndef OLSRD_LOCAL_GPS_H
#define OLSRD_LOCAL_GPS_H

struct gps_data_t mygps_data;
unsigned short last_lati;
unsigned short last_long;


bool Init_GPS(void);
bool GPS_ready(void);
unsigned short Get_Latitude(void);
unsigned short Get_Longitude(void);

#endif //OLSRD_LOCAL_GPS_H
