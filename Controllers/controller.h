#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// #include "utils.h" // Di Comment sementara karena tidak ada library chrono di compiler ku
#include "LinkedList.h"
#include "HashTable.h"

char OS[15];
int terminated = 0;

const char* getOS() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}

void cls(void) {
    for (int i = 0; i < 50; i++) {
        puts("");
    }
}

void printTime(void) {
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("%s", asctime (timeinfo) );
}

void AddDish(void) {
    cls();
    char name[50];
    int nFlag = 0;
    do {
        nFlag = 1;
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", name);
        getchar();

        curr = head;
        int found = 0;

        int capital = 0;
        for (int i = 0; i < strlen(name); i++) {
            if(name[i] >= 'A' && name[i] <= 'Z') {
                capital = 1;
            }
        }

        while (curr) {
            if (strcmp(curr->dish.name, name) == 0) {
                found = 1;
                break;
            }
            curr = curr->next;
        } 

        if (found || capital) {
            nFlag = 0;
        }
    } while (nFlag == 0);

    int price = 0, pFlag = 0;
    do {
        pFlag = 1;
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();
        if (price < 1000 || price > 50000) {
            pFlag = 0;
        }
    } while (pFlag == 0);

    int quantity, qFlag = 0;
    do {
        qFlag = 1;
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity);
        getchar();
        if (quantity < 1 || quantity > 999) {
            qFlag = 0;
        }
    } while (qFlag == 0);

    pushMid(name, price, quantity);

    printf("The dish has been added!\n");
    printf("Press enter to continue...");
    getchar();

    curr = head;
    while (curr) {
        printf("%s %d %d\n", curr->dish.name, curr->dish.price, curr->dish.quantity);
        curr = curr->next;
    }
}

void RemoveDish(void) {
    cls();
    curr = head;
    if (curr) {
        printf("    Bude's Menu\n");
        printf("=====================================\n");
        printf("No.     Name       Quantity    Price\n");

        int ctr = 1;
        while (curr) {
            int len = strlen(curr->dish.name);
            printf("%2d. %-16s %-03d       %-5d\n", ctr, curr->dish.name, curr->dish.quantity, curr->dish.price);
            curr = curr->next;
            ctr++;
        }

        printf("=====================================\n");
        printf("Insert dish's name to be deleted: ");
        char dishName[50];
        scanf("%[^\n]", dishName);
        getchar();
        
        curr = head;
        int found = 0;
        while (curr) {
            if (strcmp(curr->dish.name, dishName) == 0) {
                found = 1;
                break;
            } else {
                curr = curr->next;
            }
        }

        if (found) {
            popMid((char *)dishName);
            printf("The dish has been removed!\n");
        } else {
            printf("The dish was not found!\n");
        }
    } else {
        printf("There are no dishes!\n");
    }
    printf("Press enter to continue...");
    getchar();
}

// Not Done
void AddCustomer(void) {
    cls();
    char name[50];
    int nFlag = 1;
    do {
        nFlag = 1;
        printf("Insert the  customer's name [Without space]: ");
        scanf("%[^\n]", name);
        getchar();
        int space = 0;
        for (int i = 0; i < strlen(name); i++) {
            if (name[i] == ' ') {
                space = 1;
            }
        }

        if (space) {
            nFlag = 0;
        }
    } while (nFlag == 0);

    printf("Customer has been added!\n");
    printf("Press enter to continue...");
    insert(name);
    getchar();

}

void SearchCustomer(void) {
    cls();
    char name[50];
    int nFlag = 1;
    do {
        nFlag = 1;
        printf("Insert the customer's name to be searched: ");
        scanf("%[^\n]", name);
        getchar();

        for (int i = 0; i < strlen(name); i++) {
            if (name[i] >= '0' && name[i] <= '9') {
                nFlag = 0;
            }
        }
    } while (nFlag == 0);
    
    int found = search(name);

    if (found == -1) {
        printf("%s is not present!\n", name);
    } else {
        printf("%s is present\n");
    }
    printf("Press enter to continue...");
    getchar();
}

void ViewWarteg(void) {
    cls();
    int exist = 0;
    for (int i = 0; i < 200; i++) {
        if (table[i]) {
            exist = 1;
            currCustomer = table[i];
            while (currCustomer) {
                printf("%d. %s\n", i, currCustomer->name);
                currCustomer = currCustomer->next;
            }
        }
    }

    if (!exist) {
        printf("There are no customers!\n");
    }
    printf("Press enter to continue...");
    getchar();
}

void Order(void) {
    char name[50];
    int nFlag = 1;
    nFlag = 1;
    printf("Enter the customer's name: ");
    scanf("%[^\n]", name);
    getchar();

    int found = search(name);

    if (found == -1) {
        printf("Customer not found!\n");
    } else {
        currCustomer = table[found];
        while (currCustomer && strcmp(currCustomer->name, name) != 0) {
            currCustomer = currCustomer->next;
        }

        int amount = 0;
        printf("Insert the amount of dish: ");
        scanf("%d", &amount);
        for (int i = 1; i <= amount; i++) {
            char food[50];
            int quantity;
            printf("[%d] Insert the dish's name and quantity: ", i);
            scanf("%[^X]X %d", food, &quantity, found);
            getchar();
            // currCustomer->headOrders
        }

        printf("Order Success!\n");
    }

    printf("Press enter to continue...");
    getchar();
}

void Payment(void) {
    int index;
    printf("Insert the customer's index: ");
    scanf("%d", &index);

    if (!table[index]) {
        printf("Customer not found!\n");
    } else {
        char name[50];
        scanf("%[^\n]", name);
        getchar();
        currCustomer = table[index];
        while (currCustomer && strcmp(currCustomer->name, name) != 0) {
            currCustomer = currCustomer->next;
        }

        // GetFood and count total
    }

    printf("Press enter to continue...");
    getchar();
}

void Quit() {
    terminated = 1;
    FILE *fp = fopen("splash-screen.txt", "r");
    char string[500];
    if (!fp) {
        printf("NULL\n");
    }
    while (fscanf(fp, "%[^\n]\n", string) != EOF) {
        printf("%s\n", string);
    }
    getchar();
    fclose(fp);
 }

void printStart(void) {
    int cFlag = 1;
    char choice[20];
    do {
        cFlag = 1;
        printTime();
        printf("1. Add Dish\n");
        printf("2. Remove Dish\n");
        printf("3. Add Customer\n");
        printf("4. Search Customer\n");
        printf("5. View Warteg\n");
        printf("6. Order\n");
        printf("7. Paymenr\n");
        printf("8. Exit Warteg\n");
        printf(">> ");

        scanf("%s", choice);
        getchar();
        if (strlen(choice) > 1) {
            int alpha = 0;
            for (int i = 0; i < strlen(choice); i++) {
                if (choice[i] >= 'A' && choice[i] <= 'Z' || choice[i] >= 'a' && choice[i] <= 'z') {
                    alpha = 1;
                }
            }
            if (alpha) printf("Input must be numeric!\n");
            else printf("Input must be in range 1 - 8!\n");
            cFlag = 0;
            getchar();
        } else if (choice[0] < '1' || choice[0] > '8') {
            printf("Input must be in range 1 - 8!\n");
            getchar();
            cFlag = 0;
        } 
    } while (cFlag == 0);

    if (choice[0] == '1') {
        AddDish();
    } else if (choice[0] == '2') {
        RemoveDish();
    } else if (choice[0] == '3') {
        AddCustomer();
    } else if (choice[0] == '4') {
        SearchCustomer();
    } else if (choice[0] == '5') {
        ViewWarteg();
    } else if (choice[0] == '6') {
        Order();
    } else if (choice[0] == '7') {
        Payment();
    } else if (choice[0] == '8') {
        Quit();
    }
}
