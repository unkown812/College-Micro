/*Shop System using Datastructures like queue , linked list, stack*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>

//Structure for items
struct Item {
    char name[30];
    float price;
    int quantity;
    struct Item *next;
}*cartHead = NULL;

//Structure for previous items
struct HistoryNode {
    char product[30];
    struct HistoryNode *next;
}*historyFront = NULL, *historyRear = NULL;

//Structure
struct UndoNode {
    struct Item *item;
    struct UndoNode *next;
}*undoTop = NULL;

struct Item* createItem(char name[], float price, int quantity) {
    struct Item *newItem = malloc(sizeof(struct Item));
    if (newItem != NULL) {
        strcpy(newItem->name, name);
        newItem->price = price;
        newItem->quantity = quantity;
        newItem->next = NULL;
    }
    return newItem;
}

void addItemToCart(char name[], float price, int quantity) {
    struct Item *newItem = createItem(name, price, quantity);
    if (newItem == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    if (cartHead == NULL) {
        cartHead = newItem;
    } else {
        struct Item *temp = cartHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }

    struct UndoNode *undoNode = malloc(sizeof(struct UndoNode));
    if (undoNode != NULL) {
        undoNode->item = newItem;
        undoNode->next = undoTop;
        undoTop = undoNode;
    }

    struct HistoryNode *historyNode = malloc(sizeof(struct HistoryNode));
    if (historyNode != NULL) {
        strcpy(historyNode->product, name);
        historyNode->next = NULL;
        if (historyFront == NULL) {
            historyFront = historyNode;
            historyRear = historyNode;
        } else {
            historyRear->next = historyNode;
            historyRear = historyNode;
        }
    }
}

void viewCart() {
    struct Item *temp = cartHead;
    system("Color 02");
    if (temp == NULL) {
        printf("\nYour cart is empty.\n");
        return;
    }
    printf("\nItems in your cart:\n");
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s - Price: $%.2f, Quantity: %d\n", i++, temp->name, temp->price, temp->quantity);
        temp = temp->next;
    }
}

float calculateTotal() {
    float total = 0;
    struct Item *temp = cartHead;
    while (temp != NULL) {
        total += temp->price * temp->quantity;
        temp = temp->next;
    }
    return total;
}

void displayHistory() {
    struct HistoryNode *temp = historyFront;
    if (temp == NULL) {
        printf("\nNo product selection history.\n");
        return;
    }
    printf("\nProduct selection history:\n");
    while (temp != NULL) {
        printf("%s\n", temp->product);
        temp = temp->next;
    }
}

void undoLastAddition() {
    if (undoTop == NULL) {
        printf("\nNo items to undo.\n");
        return;
    }

    struct UndoNode *undoNode = undoTop;
    undoTop = undoTop->next;

    struct Item *item = undoNode->item;
    if (cartHead == item) {
        cartHead = cartHead->next;
    } else {
        struct Item *temp = cartHead;
        while (temp->next != item) {
            temp = temp->next;
        }
        temp->next = item->next;
    }

    free(item);
    free(undoNode);
    printf("\nLast added item removed from cart.\n");
}

void displayCategories() {
    system("Color 0A");
    printf("\nAvailable Categories:\n");
    printf("1. Electronics\n");
    printf("2. Groceries\n");
    printf("3. Clothing\n");
}

void displayProducts(int category) {
    system("Color 0D");
    switch (category) {
        case 1:
            printf("\nElectronics:\n");
            printf("1. Laptop - $1000.00\n");
            printf("2. Smartphone - $600.00\n");
            printf("3. Headphones - $100.00\n");
            printf("3. Speakers - $80.00\n");
            printf("3. Charger - $10.00\n");
            break;
        case 2:
            printf("\nGroceries:\n");
            printf("1. Rice (1kg) - $2.00\n");
            printf("2. Sugar (1kg) - $1.50\n");
            printf("3. Milk (1L) - $1.20\n");
            printf("4. Salt(1kg) - $1.50\n");
            break;
        case 3:
            printf("\nClothing:\n");
            printf("1. T-Shirt - $20.00\n");
            printf("2. Jeans - $50.00\n");
            printf("3. Jacket - $100.00\n");
            break;
        default:
            printf("Invalid category.\n");
            break;
    }
}

void addItem(int category, int product) {
    char name[30];
    float price = 0;
    int quantity;
    system("Color 09");
    switch (category) {
        case 1:
            if (product == 1) {
                strcpy(name, "Laptop");
                price = 1000.00;
            } else if (product == 2) {
                strcpy(name, "Smartphone");
                price = 600.00;
            } else if (product == 3) {
                strcpy(name, "Headphones");
                price = 50.00;
            }else if (product == 4) {
                strcpy(name, "Speakers");
                price = 80.00;
            }else if (product == 5) {
                strcpy(name, "Charger");
                price = 10.00;
            }
            break;
        case 2:
            if (product == 1) {
                strcpy(name, "Rice (1kg)");
                price = 2.00;
            } else if (product == 2) {
                strcpy(name, "Sugar (1kg)");
                price = 1.50;
            } else if (product == 3) {
                strcpy(name, "Milk (1L)");
                price = 1.20;
            }
             else if (product == 4) {
                strcpy(name, "Salt(1kg)");
                price = 1.50;
            }
             else if (product == 5) {
                strcpy(name, "Jaggery(1kg)");
                price = 1.0;
            }
            break;
        case 3:
            if (product == 1) {
                strcpy(name, "T-Shirt");
                price = 20.00;
            } else if (product == 2) {
                strcpy(name, "Jeans");
                price = 50.00;
            } else if (product == 3) {
                strcpy(name, "Jacket");
                price = 100.00;
            }else if (product == 3) {
                strcpy(name, "Trousers");
                price = 120.00;
            }else if (product == 3) {
                strcpy(name, "Tuxedo");
                price = 100.00;
            }
            break;
        default:
            printf("Invalid category or product.\n");
            return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    addItemToCart(name, price, quantity);
}

int main() {
    int choice, category, product,i;
    float total;    
    system("Color 0B");
    do {
        printf("\nOnline Shopping System Menu:\n");
        printf("1. Browse Categories\n");
        printf("2. View Cart\n");
        printf("3. Calculate Total\n");
        printf("4. Undo Last Addition\n");
        printf("5. View Product Selection History\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCategories();
                printf("\nEnter category number: ");
                scanf("%d", &category);
                displayProducts(category);
                printf("\nEnter product number to add to cart: ");
                scanf("%d", &product);
                addItem(category, product);
                break;
            case 2:
                viewCart();
                break;
            case 3:
                total = calculateTotal();
                printf("\nTotal Amount: $%.2f\n", total);
                break;
            case 4:
                undoLastAddition();
                break;
            case 5:
                displayHistory();
                break;
            case 6:
                printf("\nThank you for shopping!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}