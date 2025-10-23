#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int priority;
    char description[100];
    struct Task *next;
};

struct TaskList {
    struct Task *head;
    int count;
};

void initList(struct TaskList *list) {
    list->head = NULL;
    list->count = 0;
}

void insertTask(struct TaskList *list, int priority, char *desc) {
    struct Task *newNode = (struct Task *)malloc(sizeof(struct Task));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->priority = priority;
    strcpy(newNode->description, desc);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Task *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    list->count++;
    printf("Task added successfully.\n");
}

void displayTasks(struct TaskList *list) {
    if (list->head == NULL) {
        printf("No tasks available.\n");
        return;
    }

    struct Task *temp = list->head;
    printf("\nTask List (Total: %d):\n", list->count);
    while (temp != NULL) {
        printf("Priority: %d, Description: %s\n", temp->priority, temp->description);
        temp = temp->next;
    }
}

void deleteTask(struct TaskList *list, int priority) {
    struct Task *temp = list->head;
    struct Task *prev = NULL;

    while (temp != NULL) {
        if (temp->priority == priority) {
            if (prev == NULL) {
                list->head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            list->count--;
            printf("Task with priority %d deleted.\n", priority);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Task with priority %d not found.\n", priority);
}

void freeAll(struct TaskList *list) {
    struct Task *temp = list->head;
    while (temp != NULL) {
        struct Task *next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
    list->count = 0;
}

int main() {
    int choice, priority;
    char description[100];
    struct TaskList myList;

    initList(&myList);

    while (1) {
        printf("\nTask Manager Menu:\n");
        printf("1. Insert Task\n");
        printf("2. Display Tasks\n");
        printf("3. Delete Task by Priority\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter task priority: ");
                scanf("%d", &priority);
                getchar(); // clear newline

                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // remove newline

                insertTask(&myList, priority, description);
                break;

            case 2:
                displayTasks(&myList);
                break;

            case 3:
                printf("Enter priority to delete: ");
                scanf("%d", &priority);
                deleteTask(&myList, priority);
                break;

            case 4:
                freeAll(&myList);
                printf("Exiting and freeing memory.\n");
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }
}
