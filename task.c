#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 100
#define FILENAME "todolist.txt"

// Task structure
typedef struct {
    char description[MAX_TASK_LENGTH];
    char priority; // 'H' for high, 'M' for medium, 'L' for low
    int completed; // 1 for completed, 0 for not completed
} Task;

// Function prototypes
void addTask();
void viewTasks();
void deleteTask();
void clearBuffer();
void markTaskComplete();

int main() {
    int choice;

    while (1) {
        printf("To-Do List Application\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Mark Task Complete\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer(); // Clear newline left in buffer

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                markTaskComplete();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addTask() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Task task;
    printf("Enter the task description: ");
    fgets(task.description, sizeof(task.description), stdin);

    // Remove newline character if present
    size_t len = strlen(task.description);
    if (len > 0 && task.description[len-1] == '\n') {
        task.description[len-1] = '\0';
    }

    printf("Enter priority (H for high, M for medium, L for low): ");
    task.priority = getchar();
    clearBuffer(); // Clear newline left in buffer

    task.completed = 0; // Default to not completed

    fprintf(file, "%s|%c|%d\n", task.description, task.priority, task.completed);
    fclose(file);
    printf("Task added successfully.\n");
}

void viewTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Task task;
    char line[MAX_TASK_LENGTH + 10];
    printf("Your tasks:\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%c|%d\n", task.description, &task.priority, &task.completed);
        printf(" - %s [Priority: %c] [%s]\n", task.description, task.priority, task.completed ? "Completed" : "Not Completed");
    }

    fclose(file);
}

void deleteTask() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char tempFilename[] = "temp.txt";
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Error creating temp file.\n");
        fclose(file);
        return;
    }

    char line[MAX_TASK_LENGTH + 10];
    int taskNumber = 1;
    int deleteIndex;
    printf("Enter the task number to delete: ");
    scanf("%d", &deleteIndex);
    clearBuffer(); // Clear newline left in buffer

    while (fgets(line, sizeof(line), file)) {
        if (taskNumber != deleteIndex) {
            fprintf(tempFile, "%s", line);
        }
        taskNumber++;
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename(tempFilename, FILENAME);

    printf("Task deleted successfully.\n");
}

void markTaskComplete() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char tempFilename[] = "temp.txt";
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Error creating temp file.\n");
        fclose(file);
        return;
    }

    Task task;
    char line[MAX_TASK_LENGTH + 10];
    int taskNumber = 1;
    int completeIndex;
    printf("Enter the task number to mark as complete: ");
    scanf("%d", &completeIndex);
    clearBuffer(); // Clear newline left in buffer

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%c|%d\n", task.description, &task.priority, &task.completed);
        if (taskNumber == completeIndex) {
            task.completed = 1;
        }
        fprintf(tempFile, "%s|%c|%d\n", task.description, task.priority, task.completed);
        taskNumber++;
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename(tempFilename, FILENAME);

    printf("Task marked as complete.\n");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
