#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Order {
  char dishName[50];
  int quantity;
  Order *next;
} *newOrder, *currOrder;

struct Customer {
    char name[50];
    Customer *next;
    int checkOut;
    Order *headOrder, *tailOrder;
} *currCustomer;

Customer *table[200];

// Order *createFood(char *name, int quantity, int index) {
//   Order *temp = (Order *)malloc(sizeof(Order));
//   strcpy(temp->dishName)

// }

unsigned long hashFunction(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
  return hash % 200;
}

void insert(char *name) {
  Customer * newNode = (Customer *) malloc(sizeof(Customer));
  strcpy(newNode->name, name);
  newNode->next = NULL;
  newNode->checkOut = 0;

  int index = hashFunction(name);

  if (table[index] == NULL) {
    table[index] = newNode;
  } else {
      Customer *curr = table[index];
      while (curr->next != NULL) {
        curr = curr->next;
      }
      curr->next = newNode;
  }

  table[index] = newNode;
}

int search(char *name) {
    int index = hashFunction(name);

    if (table[index] != NULL) {
      Customer *curr = table[index];

      while (curr != NULL && strcmp(curr->name, name) != 0) {
          curr = curr->next;
      }

      if (curr != NULL) {
        return index;
      } else {
        return -1;
      }
    } else {
      return -1;
    }
}