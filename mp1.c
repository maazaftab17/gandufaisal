#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an item in the bakery
struct Item {
    int serialNumber;
    char name[50];
    char category[20];
    float price;
    int quantity;
};

// Function to display the menu by category
void displayMenu(struct Item menu[], int itemCount) {
    printf("Menu:\n");
    printf("-------------------------------------------------\n");
    printf("| %-10s | %-30s | %-20s | %-10s | %-10s |\n", "Serial", "Item", "Category", "Price", "Quantity");
    printf("-------------------------------------------------\n");

    // Iterate over unique categories
    for (int i = 0; i < itemCount; i++) {
        printf("| %-10d | %-30s | %-20s | %-10.2f | %-10d |\n", menu[i].serialNumber, menu[i].name, menu[i].category, menu[i].price, menu[i].quantity);
    }

    printf("-------------------------------------------------\n");
}

// Function to take customer order and generate bill
void takeOrder(struct Item menu[], int itemCount) {
    int choice, quantity;
    float totalBill = 0.0;
    char continueOrder;

    do {
        printf("Enter the item number (serial) you want to order (1-%d): ", itemCount);
        scanf("%d", &choice);

        if (choice < 1 || choice > itemCount) {
            printf("Invalid choice.\n");
            return;
        }

        printf("Enter the quantity: ");
        scanf("%d", &quantity);

        if (quantity <= 0 || quantity > menu[choice - 1].quantity) {
            printf("Invalid quantity.\n");
            return;
        }

        totalBill += quantity * menu[choice - 1].price;

        // Update inventory
        menu[choice - 1].quantity -= quantity;

        printf("Do you want to add more items to your order? (Y/N): ");
        scanf(" %c", &continueOrder);
    } while (continueOrder == 'Y' || continueOrder == 'y');

    printf("Your total bill for the order: %.2f\n", totalBill);
    printf("Order successfully placed!\n");
}

// Function to check the password
int authenticate() {
    int choice;
    char password[20];

    printf("Menu:\n");
    printf("1. Login\n");
    printf("2. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 2) {
        printf("Login canceled. Exiting...\n");
        return 0;
    } else if (choice != 1) {
        printf("Invalid choice. Exiting...\n");
        return 0;
    }

    printf("Enter the password: ");
    scanf("%s", password);

    // You can replace the password with a more secure authentication method
    if (strcmp(password, "admin") == 0) {
        printf("Authentication successful.\n");
        return 1; // Authentication successful
    } else {
        printf("Authentication failed. Exiting...\n");
        return 0; // Authentication failed
    }
}

int main() {
    // Sample menu items with categories
    struct Item menu[] = {
        {1, "Chocolate Cake", "Cake", 200, 20},
        {2, "Black Forest Cake", "Cake", 300, 20},
        {3, "Vanilla Cake", "Cake", 200, 25},
        {4, "Red Velvet", "Cake", 350, 20},
        {5, "White Bread", "Bread", 20, 50},
        {6, "Whole Wheat Bread", "Bread", 50, 40},
        {7, "Banana Bread", "Bread", 50, 50},
        {8, "French Bread", "Bread", 60, 50},
        {9, "Chocolate Chip Cookies", "Cookies",40, 30},
        {10, "Oatmeal Cookies", "Cookies", 30, 35},
        {11, "Confitte", "Cookies", 40, 30},
        {12, "Macaron", "Cookies", 50, 30},
        {13, "Chocolate Muffin", "Cup Cakes", 50, 20},
        {14, "Blueberry Cup Cake", "Cup Cakes", 50, 20},
        {15, "Apple Juice", "Drinks", 70, 35},
        {16, "Mix-Fruit Shake", "Drinks", 80, 35},
        {17, "Orange Juice", "Drinks", 50, 35},
        // Add more items as needed
    };

    int itemCount = sizeof(menu) / sizeof(menu[0]);
    char adminChoice;

    // Authenticate before displaying the menu and taking orders
    if (authenticate()) {
        do {
            displayMenu(menu, itemCount);
            takeOrder(menu, itemCount);

           

            printf("Press 'E' to exit or any other key to continue: ");
            scanf(" %c", &adminChoice);
        } while (adminChoice != 'E' && adminChoice != 'e');
         // Display updated inventory after order
            printf("Updated Inventory:\n");
            displayMenu(menu, itemCount);
    }

    return 0;
}