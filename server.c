#include "server.h"

int kv_set(int key, int value){
    kv_current->key = key; //set current element key to key
    kv_current->value = value; //set current element value to value
    kv_current->next = malloc(sizeof(struct kv_elem)); //create new empty element
    kv_current = kv_current->next; //new current element is a new element
    kv_current->next = 0; //set current element next to 0
    return 0;
}

int kv_get(int key){
    struct kv_elem *iter = kv_first;
    if(iter->next != 0){
        do{
            if (iter->key == key){
                return iter->value;
            }  
            else{
                iter = iter->next;
            }
        } while(iter->next != 0);
    }
    else{
        if (iter->key == key){
            return key;
        }
    }
    return 0;
}

int kv_update(int key, int value){
    struct kv_elem *iter = kv_first;
    if(iter->next !=0){
        do{
            if(iter->key == key){
                 iter->value = value;
                 return 1;
            }
            else{
                iter = iter->next;
            }

          } while(iter->next != 0);
   } 
   else{
       if(iter->key == key){
           iter->key = value;
           return 1;
       } 
   }
   return 0;
}

int kv_exist(int key){
    struct kv_elem *iter = kv_first;
    if(iter->next !=0){
        do{
            if(iter->key == key){
                return 1;
            }
            else{
                iter = iter->next;
            }
        } while (iter->next != 0);
    } 
    else{
        if(iter->key == key){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    struct kv_elem *kv_first = malloc(sizeof(struct kv_elem)); //initialize first kv_elem
    kv_first->next=0;
    struct kv_elem *kv_current = kv_first;
    int port = (int) argv[1]; //port to listen on
    char str[1024]; //buffer string
    char* ok_answer = "OK"; //ok answer
    int ok_answer_len = strlen(ok_answer)+1; //ok answer
    char* fail_answer = "fail"; //fail answer
    int fail_answer_len = strlen(fail_answer)+1; //ok answer
    int listen_fd, comm_fd; //file descriptors
    struct sockaddr_in servaddr; //struct to hold ip and port
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    bzero( &servaddr, sizeof(servaddr)); //write zeros to servaddr
    servaddr.sin_family = AF_INET; //set socket type to IP
    servaddr.sin_addr.s_addr = htons(INADDR_ANY); //allow any ip to connect
    servaddr.sin_port = htons(port); //listen on port
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)); //prepate to listen to connections on sockaddr
    listen(listen_fd, 1024); //listen to connections on listen_fd, max 1024 connection requests waiting. more will return an error
    while(1){ //start waiting for connections forever
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); //accept connection if there is a connect request. if there is none, wait
        while(1){ //accept connect and wait for actions
            bzero(str, 1024); //fill str with zeros
            read(comm_fd, str, 1024); //read 1024 bytes from socket
            printf("%s", str); //print received string
            char* command = strok(str, " ");
            char* key = strok(NULL, " ");
            if (command == "set"){
                char* value = strok(NULL, " ");
                kv_set(key, value);
                write(comm_fd, ok_answer, ok_answer_len);
            }
            else if (command == "get"){
                write(comm_fd, kv_get(key), fail_answer_len);
            }
            else if (command == "update"){
                char* value = strok(NULL, " ");
                kv_set(key, value); 
                write(comm_fd, ok_answer, ok_answer_len);
            }
            else if (command == "exist"){
                write(comm_fd, kv_exist(key), 2);
            }
            else{
                write(comm_fd, fail_answer, fail_answer_len);
            }
        }
    }
}
