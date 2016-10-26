//
// Created by Luke Busstra on 19/10/16.
//
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include "local_gps.h"
#include "gps_socket.h"

#define DEFAULT_PORT 4040

/**
 * Init Socket
 * This function sets up the socket and contiueously listens for requests from a client
 */
void *init_socket(void);

/**
 * GPS Request
 * This function takes the socket request accepts the type of data the user is wanting and return the geo poistion for
 * the specification of the message
 *
 * @param client_sock - the sock number
 */
void gps_request(int client_sock);


/**
 * gps socket init
 * This function starts a thread that is then initiates the socket and listens for requests.
 */
void gps_socket_init() {
    pthread_t thread1;

    //Create thread for socket process
    pthread_create(&thread1, NULL, init_socket, NULL);
}


/**
 * Init Socket
 * This function sets up the socket and contiueously listens for requests from a client
 */
void *init_socket(){
    int c, client_sock, socket_desc;
    struct sockaddr_in server , client;

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    printf("Socket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    //No argument use Default
    server.sin_port = htons(DEFAULT_PORT);


    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
    }
    printf("bind done");

    listen(socket_desc , 10);

    printf("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        gps_request(client_sock);
    }
}

/**
 * GPS Request
 * This function takes the socket request accepts the type of data the user is wanting and return the geo poistion for
 * the specification of the message
 */
void gps_request(int client_sock) {
    char buff[128];
    double lat, lon;
    int len = 128;

    printf("Waiting for communication");
    while (1) {
        //Receive request from sock
        memset(buff, '\0', len);
        recv(client_sock, buff, len, 0);

        //Check buff is a valid IP address or local
        if (strcmp(buff, "local") >= 0) {
            lat = latitude;
            lon = longitude;
        } else {
            //get information from routing table
            lat = 0;
            lon = 0;
        }

        //Send data back to client
        sprintf(buff, "%.6f %.6f", lat, lon);
        send(client_sock, buff, strlen(buff), 0);
    }
}