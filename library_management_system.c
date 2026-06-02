#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
    char author[50];
    int quantity;
};

void addBook() {
    FILE *fp = fopen("library.txt", "ab");
    struct Book b;

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.name);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nBook Added Successfully!\n");
}

void displayBooks() {
    FILE *fp = fopen("library.txt", "rb");
    struct Book b;

    printf("\n--- Book List ---\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d\nName: %s\nAuthor: %s\nQuantity: %d\n",
               b.id, b.name, b.author, b.quantity);
    }

    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("library.txt", "rb");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found!\n");
            printf("Name: %s\nAuthor: %s\nQuantity: %d\n",
                   b.name, b.author, b.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook Not Found!\n");

    fclose(fp);
}

void issueBook() {
    FILE *fp = fopen("library.txt", "rb+");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id && b.quantity > 0) {
            b.quantity--;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("\nBook Issued Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook not available!\n");

    fclose(fp);
}

void returnBook() {
    FILE *fp = fopen("library.txt", "rb+");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            b.quantity++;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("\nBook Returned Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nInvalid Book ID!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
