#include <stdio.h>
#include <stdlib.h>
#include "proj3B_deque.h"
#include <string.h>

Node *newNode(void *data, size_t dataSize)
{
    Node *node = malloc(sizeof(Node));
    node->data = malloc(dataSize);
    size_t x = 0;

    if (dataSize == sizeof(int long))
    {
        *(long *)node->data = *(int long *)data;
    } else
    {
        for (x = 0; x < dataSize; x++)
        {
            ((char *)node->data)[x] = ((char *)data)[x];
        }
    }
    node->next = NULL;
    node->prev = NULL;

    return node;
}

Deque *createDeque()
{
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->back = NULL;
    deque->count = 0;
    return deque;
}

void insertFront(Deque *deque, void *data, size_t dataSize)
{
    Node *node = newNode(data, dataSize);

    if (deque->front == NULL)
    {
        deque->front = node;
        deque->back = node;

    } else
    {
        node->next = deque->front;
        deque->front->prev = node;
        deque->front = node;
    }
    deque->count++;
}

void insertBack(Deque *deque, void *data, size_t dataSize)
{
    //CREATES A NEW NODE
    Node *node = newNode(data, dataSize);

    if (deque->back == NULL) {
        deque->back = node;
        deque->front = node;
    } else {
        node->prev = deque->back;
        deque->back->next = node;
        deque->back = node;
    }
    deque->count++;
}

void printLong(void *data) 
{
    printf("%ld", *(long *)data);
}

void printChar(void *data) {
    char *str = (char *)data;
    int x = 0;
    int Number_present = 0;
    while (str[x + 1] != '\0')
    {
        if ((str[x] >= '0' && str[x] <= '9') || str[x] == 'U')
        {
            Number_present++;
        }
        x++;
    }
    x = 0;
    if (Number_present > 0)
    {
        while (str[x] != '\0')
        {
            printf("%c",str[x]);
            x++;
        }
    } else
    {
        while (str[x + 1] != '\0')
        {
            printf("%c",str[x]);
            x++;
        }
    }

}

void printDeque(Deque *deque, void (*print)(void *)) {
    Node *current = deque->front;
    int x = 0;
    while (current != NULL) {
        print(current->data);
        current = current->next;
        x++;
        printf(" ");
    }
}

void removeFront(Deque *deque, void *data, size_t dataSize) {
    if (!deque || !deque->front) {
        fprintf(stderr, "Deque is empty or NULL.\n");
        return;
    }

    Node *nodeToRemove = deque->front;

    deque->front = nodeToRemove->next;
    if (deque->front) {
        deque->front->prev = NULL;
    } else {
        deque->back = NULL;
    }

    if (data && nodeToRemove->data) {
        if (dataSize == sizeof(long)) {
            *(long *)data = *(long *)nodeToRemove->data;
        } else {
            char *src = (char *)nodeToRemove->data;
            char *dest = (char *)data;
            size_t i = 0;
            for (; i < dataSize - 1 && src[i] != '\0'; i++) {
                dest[i] = src[i];
            }
            dest[i] = '\0'; // Null-terminate
        }
    }

    // Free node memory
    free(nodeToRemove->data);
    free(nodeToRemove);
    deque->count--;
}


void removeBack(Deque *deque, void *data, size_t dataSize) {
    if (!deque || !deque->back) {
        fprintf(stderr, "Deque is empty or NULL.\n");
        return;
    }

    Node *nodeToRemove = deque->back;

    deque->back = nodeToRemove->prev;
    if (deque->back) {
        deque->back->next = NULL;
    } else {
        deque->front = NULL;
    }

    if (data && nodeToRemove->data) {
        if (dataSize == sizeof(long)) {
            *(long *)data = *(long *)nodeToRemove->data;
        } else {
            char *src = (char *)nodeToRemove->data;
            char *dest = (char *)data;
            size_t i = 0;
            for (; i < dataSize - 1 && src[i] != '\0'; i++) {
                dest[i] = src[i];
            }
            dest[i] = '\0';
        }
    }
    free(nodeToRemove->data);
    free(nodeToRemove);
    deque->count--;
}


void freeDeque(Deque *deque)
{
    Node *current = deque->front;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;

        free(current->data);
        free(current);

        current = nextNode;
    }
    free(deque);
}