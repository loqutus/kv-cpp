#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
    int port = (int) argv[1]; //port to listen on
    char str[1024]; //buffer string
    int listen_fd, comm_fd; //file descriptors
    struct sockaddr_in servaddr; //struct to hold ip and port
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    bzero( &servaddr, sizeof(servaddr)); //write zeros to servaddr
    servaddr.sin_family = AF_INET; //set socket type to IP
    servaddr.sin_addr.s_addr = htons(INADDR_ANY); //allow any ip to connect
    servaddr.sin_port = htons(port); //listen on port
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)); //prepate to listen to connections on sockaddr
    listen(listen_fd, 1024); //listen to connections on listen_fd, max 1024 connection requests waiting. more will return an error
    while(true){ //start waiting for connections forever
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); //accept connection if there is a connect request. if there is none, wait
        while(true){ //accept connect and wait for actions
            bzero(str, 1024); //fill str with zeros
            read(comm_fd, str, 1024); //read 1024 bytes from socket
            printf("%s", str);
            write(comm_fd, str, strlen(str)+1);
        }
    }
}
