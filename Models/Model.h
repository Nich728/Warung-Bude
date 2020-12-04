struct Dish {
    char name[50];
    int price;
    int quantity;
};

struct Node {
    Dish dish;
    Node *next; 
    Node *prev;
} *head, *tail, *curr;
