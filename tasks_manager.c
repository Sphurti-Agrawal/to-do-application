#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TASK_LENGTH 100
#define FILE_NAME "to-do-list.txt"

// Defining task structure
typedef struct{
    char priority; // H for High, M for Medium, L for Low
    char description[MAX_TASK_LENGTH];
    int status; // 1 for completed & 0 for incomplete
} Task;

//Functions
void addtasks();
void deletetasks();
void viewtasks();
void clearbuffer();
void marktaskcompleted();

int main(){
    int choice;
    while (1) {
        printf("TO-DO LIST APPLICATION \n");
        printf("1. Add tasks \n");
        printf("2. View tasks \n");
        printf("3. Delete tasks \n");
        printf("4. Mark tasks Completed\n");
        printf("5. Exit\n");
        printf("Enter your choice : \n");
        scanf("%d", &choice );
        clearbuffer();

        switch (choice)
        {
        case 1:
            addtasks();
            break;
        case 2:
            viewtasks();
            break;
        case 3:
            deletetasks();
            break;
        case 4:
            marktaskcompleted();
            break;
        case 5:
            printf("Exiting.....\n");
            exit(0);
        default:
            printf("Invalid Choice . Please enter a valid option :) ");
        }
    }
    return 0;
}

void addtasks(){
    FILE *file= fopen(FILE_NAME ,"a");
    if (file== NULL){
        printf("Error in opening the file . \n");
        return;
    }

    Task task;
    printf("Enter the task description : \n");
    fgets(task.description, sizeof(task.description), stdin);
    task.description[strcspn(task.description, "\n")] = '\0'; // Remove newline character

    //Assigning priority
    printf("Enter priority (H for High , M for Medium , L for Low) : ");
    task.priority=getchar();
    clearbuffer(); // clear newline left in buffer

    task.status=0;
    fprintf(file ,"%s|%c|%d\n",task.description , task.priority , task.status);
    fclose(file);
    printf("Task added successfully\n");
}

void viewtasks() {
    FILE *file = fopen(FILE_NAME,"r");
    if (file==NULL){
        printf("Error in opening the file \n");
        return;
    }

    Task task;
    char line[MAX_TASK_LENGTH +10];
    printf("Your Tasks:\n");
    while (fgets( line, sizeof(line), file)){
        sscanf(line, "%[^|]|%c|%d\n", task.description, &task.priority, &task.status);
        printf("- %s [Priority: %c] [%s] \n" , task.description , task.priority, task.status ? "Completed": "Not Completed");
    }
    fclose(file);
}

void deletetasks(){
    FILE *file = fopen(FILE_NAME,"r");
    if (file==NULL){
        printf("Error in opening the file\n");
        return;
    }

    char tempfilename[]= "temp.txt";
    FILE *tempfile = fopen(tempfilename, "w");
    if (tempfile==NULL){
        printf("Error creating temp file\n");
        fclose(file);
        return;
    }
    Task task;

    char line[MAX_TASK_LENGTH+10];
    int tasknumber =1;
    int deleteindex;
    printf("Enter the task number to be deleted : ");
    scanf("%d", &deleteindex);
    clearbuffer(); //clear newline left in buffer

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%c|%d\n", task.description, &task.priority, &task.status);
        if (tasknumber != deleteindex) {
            fprintf(tempfile, "%s|%c|%d\n", task.description, task.priority, task.status);
        }
        tasknumber++;
    }
    fclose(file);
    fclose(tempfile);
    remove(FILE_NAME);
    rename(tempfilename, FILE_NAME);
    printf("Task deleted successfully. \n");
}

void marktaskcompleted(){
    FILE *file= fopen(FILE_NAME,"r");
    if (file==NULL){
        printf("Error in opening the file\n");
        return;
    }
    char tempfilename[]="temp.txt";
    FILE *tempfile = fopen(tempfilename,"w");
    if (tempfile==NULL){
        printf("Error in creating temp file\n");
        fclose(file);
        return;
    }

    Task task;
    char line[MAX_TASK_LENGTH+10];
    int tasknumber=1;
    int completeindex;
    printf("Enter the task number which has been completed: \n");
    scanf("%d", &completeindex);
    clearbuffer(); // clear newline left in buffer
    while (fgets(line, sizeof(line), file)){
        sscanf(line, "%[^|]|%c|%d\n", task.description, &task.priority, &task.status);
        if (tasknumber == completeindex){
            task.status=1;
        }
        fprintf(tempfile, "%s|%c|%d\n",task.description, task.priority, task.status);
        tasknumber++;
    }
    fclose(file);
    fclose(tempfile);
    remove(FILE_NAME);
    rename(tempfilename , FILE_NAME);
    printf("Task marked as complete.\n");
}

void clearbuffer(){
    int c;
    while ((c=getchar()) != '\n' && (c != EOF));
}





