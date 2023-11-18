// QUESTION 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char email[50];
    char phoneNumber[20];
};

int main() {
    struct Contact* addressBook = NULL;
    int numContacts = 0;

    while (1) {
        printf("\nAddress Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. View Address Book\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                numContacts++;
                if (numContacts == 1) {
                    addressBook = (struct Contact*)malloc(numContacts * sizeof(struct Contact));
                } else {
                    addressBook = (struct Contact*)realloc(addressBook, numContacts * sizeof(struct Contact));
                }

                if (addressBook == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }

                printf("Enter Contact Details: \n");
                printf("Name: ");
                scanf("%s", addressBook[numContacts - 1].name);

                printf("Email: ");
                scanf("%s", addressBook[numContacts - 1].email);

                printf("Phone Number: ");
                scanf("%s", addressBook[numContacts - 1].phoneNumber);
                break;

            case 2:
                if (numContacts > 0) {
                    int contactIndex;
                    printf("Enter the index of the contact to delete (0-%d): ", numContacts - 1);
                    scanf("%d", &contactIndex);

                    if (contactIndex >= 0 && contactIndex < numContacts) {
                        for (int i = contactIndex; i < numContacts - 1; i++) {
                            addressBook[i] = addressBook[i + 1];
                        }

                        numContacts--;
                        addressBook = (struct Contact*)realloc(addressBook, numContacts * sizeof(struct Contact));
                    } else {
                        printf("Invalid contact index.\n");
                    }
                } else {
                    printf("Address book is empty.\n");
                }
                break;

            case 3:
                printf("Address Book:\n");
                for (int i = 0; i < numContacts; i++) {
                    printf("%d. Name: %s, Email: %s, Phone Number: %s\n", i + 1, addressBook[i].name,
                           addressBook[i].email, addressBook[i].phoneNumber);
                }
                break;

            case 4:
                free(addressBook);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}


// QUESTION 2
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* mergedList = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            insertAtEnd(&mergedList, list1->data);
            list1 = list1->next;
        } else {
            insertAtEnd(&mergedList, list2->data);
            list2 = list2->next;
        }
    }
    while (list1 != NULL) {
        insertAtEnd(&mergedList, list1->data);
        list1 = list1->next;
    }
    while (list2 != NULL) {
        insertAtEnd(&mergedList, list2->data);
        list2 = list2->next;
    }
    return mergedList;
}
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    insertAtEnd(&list1, 1);
    insertAtEnd(&list1, 3);
    insertAtEnd(&list1, 5);
    insertAtEnd(&list2, 2);
    insertAtEnd(&list2, 4);
    insertAtEnd(&list2, 6);

    printf("List 1: ");
    printList(list1);

    printf("List 2: ");
    printList(list2);

    struct Node* mergedList = mergeSortedLists(list1, list2);

    printf("Merged List: ");
    printList(mergedList);

    freeList(list1);
    freeList(list2);
    freeList(mergedList);

    return 0;
}



// Question 03
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* head = NULL;
    for (int i = 5; i > 0; i--) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = i;
        newNode->next = head;
        head = newNode;
    }

    printf("Singly linked list before conversion: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");

    int size = 0;
    current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    current = head;
    for (int i = 0; i < size; i++) {
        array[i] = current->data;
        current = current->next;
    }

    printf("Converted Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(array);
    current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

// Question 04

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void printLinkedList(struct Node* head) {
    printf("Linked list: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void removeOddIndices(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* prev = NULL;
    int index = 0;

    while (current != NULL) {
        if (index % 2 != 0) {
            if (prev != NULL) {
                prev->next = current->next;
                free(current);
                current = prev->next;
            } else {
                *head = current->next;
                free(current);
                current = *head;
            }
        } else {
            prev = current;
            current = current->next;
        }
        index++;
    }
}
