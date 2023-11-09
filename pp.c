#include <stdio.h>
#include <string.h>

struct Product {
    char name[50];
    int id;
    float price;
    int quantity;
};

void viewInventory(struct Product inventory[], int count) {
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    
    printf("Inventory:\n");
    for (int i = 0; i < count; i++) {
        printf("Product Name: %s\n", inventory[i].name);
        printf("Product ID: %d\n", inventory[i].id);
        printf("Product Price: %.2f\n", inventory[i].price);
        printf("Product Quantity: %d\n", inventory[i].quantity);
        printf("------------------------\n");
    }
}

int findProductIndex(struct Product inventory[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1; // Product not found
}

void deleteProduct(struct Product inventory[], int *count, int id) {
    int index = findProductIndex(inventory, *count, id);
    if (index != -1) {
        for (int i = index; i < *count - 1; i++) {
            inventory[i] = inventory[i + 1];
        }
        (*count)--;
        printf("Product deleted from inventory.\n");
    } else {
        printf("Product not found in inventory.\n");
    }
}

void saveInventory(struct Product inventory[], int count) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%d\n%.2f\n%d\n", inventory[i].name, inventory[i].id, inventory[i].price, inventory[i].quantity);
    }

    fclose(file);
    printf("Inventory data saved to file.\n");
}

void loadInventory(struct Product inventory[], int *count) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening file for loading.\n");
        return;
    }

    *count = 0;
    while (fscanf(file, " %[^\n]s", inventory[*count].name) != EOF) {
        fscanf(file, "%d%f%d", &inventory[*count].id, &inventory[*count].price, &inventory[*count].quantity);
        (*count)++;
    }

    fclose(file);
    printf("Inventory data loaded from file.\n");
}

void sortInventoryByName(struct Product inventory[], int count) {
    int i, j;
    struct Product temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (strcmp(inventory[j].name, inventory[j + 1].name) > 0) {
                // Swap the products if they are out of order
                temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }

    printf("Inventory sorted by product name.\n");
}

void searchProduct(struct Product inventory[], int count, int id) {
    int index = findProductIndex(inventory, count, id);
    if (index != -1) {
        printf("Product Found:\n");
        printf("Product Name: %s\n", inventory[index].name);
        printf("Product ID: %d\n", inventory[index].id);
        printf("Product Price: %.2f\n", inventory[index].price);
        printf("Product Quantity: %d\n", inventory[index].quantity);
    } else {
        printf("Product not found in inventory.\n");
    }
}

int isProductValid(struct Product product,struct Product inventory[],int count) {
    for(int i=0;i<count;i++){
        int iD = inventory[i].id;
        if(product.id== iD){
            return 0;
        }
    }
    if (product.id <= 0 || product.price < 0 || product.quantity < 0 || strlen(product.name) == 0) {
        return 0; // Invalid product
    }
    return 1; // Valid product
}

void addProduct(struct Product inventory[], int *count) {
    int c = *count;
    if (*count < 100) {
        struct Product newProduct;
        printf("Enter product name: ");
        scanf(" %[^\n]s", newProduct.name);
        printf("Enter product ID: ");
        scanf("%d", &newProduct.id);
        printf("Enter product price: ");
        scanf("%f", &newProduct.price);
        printf("Enter product quantity: ");
        scanf("%d", &newProduct.quantity);

        if (isProductValid(newProduct,inventory,c)) {
            inventory[*count] = newProduct;
            (*count)++;
            printf("Product added to inventory.\n");
        } else {
            printf("Invalid product data. Please check and try again.\n");
        }
    } else {
        printf("Maximum inventory capacity reached.\n");
    }
}

void updateProduct(struct Product inventory[], int count, int id) {
    int index = findProductIndex(inventory, count, id);
    if (index != -1) {
        printf("Enter updated product quantity: ");
        int newQuantity;
        scanf("%d", &newQuantity);
        
        if (newQuantity >= 0) {
            inventory[index].quantity = newQuantity;
            printf("Product quantity updated.\n");
        } else {
            printf("Invalid quantity. Please enter a non-negative value.\n");
        }
    } else {
        printf("Product not found in inventory.\n");
    }
}

int main() {
    struct Product inventory[100];
    int count = 0;
    int choice, id;

    printf("Inventory Management System\n");

    loadInventory(inventory, &count);

    do {
        printf("\nMenu:\n");
        printf("1. Add Product\n");
        printf("2. View Inventory\n");
        printf("3. Update Product Quantity\n");
        printf("4. Delete Product\n");
        printf("5. Sort Inventory by Name\n");
        printf("6. Search for Product\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(inventory, &count);
                break;
            case 2:
                viewInventory(inventory, count);
                break;
            case 3:
                printf("Enter the product ID to update: ");
                scanf("%d", &id);
                updateProduct(inventory, count, id);
                break;
            case 4:
                printf("Enter the product ID to delete: ");
                scanf("%d", &id);
                deleteProduct(inventory, &count, id);
                break;
            case 5:
                sortInventoryByName(inventory, count);
                break;
            case 6:
                printf("Enter the product ID to search: ");
                scanf("%d", &id);
                searchProduct(inventory, count, id);
                break;
            case 7:
                saveInventory(inventory, count);
                printf("data saved!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}