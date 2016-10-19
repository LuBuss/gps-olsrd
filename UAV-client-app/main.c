 #include <stdlib.h>
 #include <stdio.h>
 #include "gps_request.h"
 
 int main(int argc, char *argv[]) {
    gps_request_init();
 
    sleep(2);
    char msg[128];
    get_gps(msg);
    printf("%s\n", msg);
 
    sleep(2);
    get_gps(msg);
    printf("%s\n", msg);
 
 }   