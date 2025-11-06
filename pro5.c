#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
    char url[100];
    struct page *prev;
    struct page *next;
};


void newPage(struct page **head, struct page **current, const char *url) {
    struct page *newNode = (struct page *)malloc(sizeof(struct page));
    strcpy(newNode->url, url);
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        *current = newNode;
    } else {
        
        struct page *temp = *current;
        while (temp->next != NULL) {
            struct page *toFree = temp->next;
            temp->next = toFree->next;
            free(toFree);
        }

        newNode->prev = *current;
        (*current)->next = newNode;
        *current = newNode;
    }

    printf("Visited: %s\n", url);
}


void back(struct page **current) {
    if (*current == NULL) {
        printf("No current page.\n");
        return;
    }
    if ((*current)->prev == NULL) {
        printf("No previous page to go back to.\n");
    } else {
        *current = (*current)->prev;
        printf("Went back to: %s\n", (*current)->url);
    }
}


void forward(struct page **current) {
    if (*current == NULL) {
        printf("No current page.\n");
        return;
    }
    if ((*current)->next == NULL) {
        printf("No next page to go forward to.\n");
    } else {
        *current = (*current)->next;
        printf("Went forward to: %s\n", (*current)->url);
    }
}


void freeAll(struct page *head) {
    while (head != NULL) {
        struct page *next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    struct page *head = NULL;
    struct page *current = NULL;
    int choice;
    char url[100];

    while (1) {
        printf("\nBrowser History Menu:\n");
        printf("1. Visit new page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                fgets(url, sizeof(url), stdin);
                url[strcspn(url, "\n")] = '\0';
                newPage(&head, &current, url);
                break;

            case 2:
                back(&current);
                break;

            case 3:
                forward(&current);
                break;

            case 4:
                freeAll(head);
                printf("Exiting browser and freeing history.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
