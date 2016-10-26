
#define DEFAULT_PORT 4040

/**
 * GPS Request Init
 * This function will initiate the communication between with the GPS-olsrd
 * @author Luke Busstra
 */
int gps_request_init(void);

/**
 * Get GPS
 * This function gets the local GPS from the GPS-olsrd network
 * @author Luke Busstra
 *
 * @param msg - the return message containing the GPS cordinates
 */
void get_gps(char* msg);