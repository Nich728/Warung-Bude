#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Models/Model.h"

Node *createNode(char *name, int price, int quantity){
    Node *temp = (Node *)malloc(sizeof(Node));
    strcpy(temp->dish.name, name);
    temp->dish.price = price;
    temp->dish.quantity = quantity;
    temp->prev = temp->next = NULL;   
    return temp;
}

void pushHead(char *name, int price, int quantity) {
    Node *temp = createNode(name, price, quantity);

    if (!head) {
        head = tail = temp;
    } else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail (char *name, int price, int quantity) {
    Node * temp = createNode(name, price, quantity);

    if (!head) {
        head = tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(char *name, int price, int quantity) {
    Node *temp = createNode(name, price, quantity);

    if (!head) {
        head = tail = temp;
    } else if (strcmp(head->dish.name, name) > 0) {
        pushHead(name, price, quantity);
    } else if (strcmp(tail->dish.name, name) < 0) {
        pushTail(name, price, quantity);
    } else {
        curr = head;
        while (curr && strcmp(curr->dish.name, name) < 0) {
            curr = curr->next;
        } 

        temp->prev = curr->prev; 
        temp->next = curr; 

        curr->prev->next = temp; 
        curr->prev = temp;
    }
}

void popHead() {
    if (head && head == tail) {
        head = tail = NULL;
        free(head);
    } else {
        Node *newHead = head->next;
        head->next = newHead->prev = NULL;
        free(head);
        head = newHead;
    }
}

void popTail() {
    if (head && head == tail) {
        head = tail = NULL;
        free(head);
    } else {
        Node *newTail = tail->prev;
        tail->prev = newTail->next = NULL;
        free(tail);
        tail - newTail;
    }
}

void popMid(char *name) {
    if (!head) {
        return;
    } else if (strcmp(head->dish.name, name) == 0) {
        popHead();
    } else if (strcmp(head->dish.name, name) == 0) {
        popTail();
    } else {
        curr = head;
        while (curr && strcmp(curr->dish.name, name) != 0) {
            curr = curr->next;
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr->prev = curr->next = NULL;
        free(curr);
    }
}