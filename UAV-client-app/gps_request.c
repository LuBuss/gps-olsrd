#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "gps_request.h"

pthread_mutex_t write_data;
pthread_cond_t cv;
char message[128];
bool ready;

/**
 * GPS Request
 * This function is the thread the keeps the socket open and responsing accepts requests from get GPS
 * @author Luke Busstra
 *
 * @param client_sock - the socket Id
 */
void gps_request(int client_sock);


/**
 * This is an example code
 *
 *int main(int argc, char *argv[]) {
 *   gps_request_init();
 *
 *   sleep(2);
 *   char msg[128];
 *   get_gps(msg);
 *   printf("%s\n", msg);
 *
 *   sleep(2);
 *   get_gps(msg);
 *   printf("%s\n", msg);
 *
 *   return 0;
 *}
 */

/**
 * GPS Request Init
 * This function will initiate the communication between with the GPS-olsrd
 * @author Luke Busstra
 */
int gps_request_init(){
    //Thread to socket
    pthread_t thread1;

    pthread_mutex_init(&write_data, NULL);
    pthread_cond_init (&cv, NULL);
    int sock;

    struct sockaddr_in server;
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket\n");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(DEFAULT_PORT);

    //Connect to remote server
    int counter = 0;
    while (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        if(counter++ % 10 == 0){
            printf("\nWaiting for connection...\n");
        }
        sleep(1);
    }

    //Create thread for socket process
    pthread_create(&thread1, NULL, gps_request, (void*)sock);

    return 1;
};

/**
 * Get GPS
 * This function gets the local GPS from the GPS-olsrd network
 * @author Luke Busstra
 *
 * @param msg - the return message containing the GPS cordinates
 */
void get_gps(char* msg){
    //send message
    pthread_mutex_lock(&write_data);
    {
        sprintf(message, "%s", "local");
        ready = true;
        pthread_cond_signal(&cv);
    }
    pthread_mutex_unlock(&write_data);
    //wait response
    pthread_mutex_lock(&write_data);
    {
        while (ready)
        {
            pthread_cond_wait(&cv, &write_data);
        }
        sprintf(msg, "%s", message);
    }
    pthread_mutex_unlock(&write_data);
}

/**
 * GPS Request
 * This function is the thread the keeps the socket open and responsing accepts requests from get GPS
 * @author Luke Busstra
 *
 * @param client_sock - the socket Id
 */
void gps_request(int client_sock){
    ready = false;
    while(1){
        char buff[128];
        int len = 128;

        pthread_mutex_lock(&write_data);
        while (!ready)
        {
            printf("%d", ready);
            pthread_cond_wait(&cv, &write_data);
        }

        //Send data back to client
        sprintf(buff, "local");
        send(client_sock, buff, strlen(buff), 0);

        //Receive request from sock
        memset(buff, '\0', len);
        recv(client_sock, buff, len, 0);
        sprintf(message, "%s", buff);
        ready = false;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&write_data);
    }
}