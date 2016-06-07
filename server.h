#ifndef SERVER
#define SERVER

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct kv_elem{ //linked list
    int key;
    int value;
    struct kv_elem *next;
};
struct kv_elem *kv_first, *kv_current; //first and current element of linked list

int kv_set(int key, int value);
int kv_get(int key);
int kv_update(int key, int value);
int kv_exist(int key);

#endif // SERVER

