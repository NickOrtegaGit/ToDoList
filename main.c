#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//limit to length of task description
#define MAXTASKLEN 100

//define the struct
typedef struct Task{
    int id;
    char description[MAXTASKLEN];
    char time[80];
    struct Task* next;
} Task;


Task* head = NULL;
int next_id = 1;

void viewdelete();
void viewToDo();
void addToDo();
void reorder();
void checkOff();
void wipe();
int main(){

    //main menu
    int choice;
    while(1){
        printf("\n--- WELCOME TO YOUR TO-DO LIST! ---\n");
        printf("------ Let's get productive! ------\n");

        printf("------ 1. view To-Do's ------------\n");
        printf("------ 2. add To-Do's -------------\n");
        printf("------ 3. finish To-Do's ----------\n");
        printf("------ 4. delete all To-Do's ------\n");
        printf("------ 0. Exit --------------------\n");
        scanf("%d", &choice);
        getchar();

    switch(choice){
        case 1: viewToDo(); break;
        case 2: addToDo(); break;
        case 3: checkOff(); break;
        case 4: wipe(); break;
        case 0: exit(0);

        default: printf("please choose from valid options.\n");
    }
    }

}

//goes through list and prints each one with the time it was added
void viewToDo(){
    int i=1;
    Task* temp = head;
    if(temp==NULL){
        printf("Your To-Do List is empty!\n");
        printf("--- enter any key to return ---\n");
        getchar();
        return;
    }

    printf("--- Current To-Do's ---\n");
   while(temp!=NULL) {
       printf("%d- %s - added on %s \n", i,temp->description,temp->time);
       temp = temp->next;
       i++;
   }
   printf("--- enter any key to return ---\n");
   getchar();

}

//adds to list as well as the time it was added
void addToDo(){
   Task* newTask = malloc(sizeof(Task));
    if(newTask==NULL) {
        printf("You have way too many To-Do's left! complete some before adding more!\n");
        return;
    }
    printf("Let's do it! What should we name this task?\n");
    fgets(newTask->description, MAXTASKLEN, stdin);
    newTask->description[strcspn(newTask->description, "\n")] = '\0';

    //fill out struct
    newTask-> next = NULL;
    newTask->id= next_id++;

    //time of addition
    time_t now = time(NULL);
    struct tm* local = localtime(&now);
    strftime(newTask->time, sizeof(newTask->time), "%Y-%m-%d %H:%M:%S", local);


    //navigate through linked list and add to end of list
    if(head==NULL)
        head= newTask;
    else {
        Task *temp = head;
        while (temp->next != NULL)
            temp=temp->next;
        temp->next = newTask;
        newTask->next = NULL;
    }

    printf("--- Task was added to your To-Do list! ---\n");
    printf("--- enter any key to return ---\n");

    getchar();

}
//shows list without text above
void viewdelete(){
    int i=1;
    Task* temp = head;
    while(temp!=NULL) {
        printf("%d- %s \n", i,temp->description);
        temp = temp->next;
        i++;
    }
}
//reorder the id to fit the number in list to be able to keep deleting
void reorder(){
    int newid = 1;
    Task*temp=head;
    while(temp!=NULL){
        temp->id=newid++;
        temp=temp->next;
    }
}

void checkOff(){
    //check if list is empty
if(head==NULL){
    printf("Your list is empty! Let's change that!\n");
    printf("--- enter any key to return ---\n");
    getchar();
    return;
}
//show the list
viewdelete();

//we are deleting the To-Do by struct id i.e. the number in the list
printf("Which task number are we checking off?\n");
int num;
scanf("%d", &num);

//check if list is only 1 item long
if(head->id==NULL) {
    Task*delete = head;
    head=head->next;
    free(delete);
    reorder();
    return;
}

//otherwise, set up walker variables
Task* temp = head;
Task* delete;

//walk through list to get to target
while(temp->next!=NULL && temp->next->id!=num) {
    temp = temp->next;
}
//if input is 0 or any other invalid number
if(temp->next==NULL) {
    printf("invalid To-Do number!\n");
    return;
}
//keeps list linked during deletion and frees afterwards
delete= temp->next;
temp->next = delete->next;
free(delete);
reorder();
}

//frees entire list
void wipe(){
    if(head==NULL) {
        printf("your list is already empty!\n");
        return;
    }
    while(head!=NULL){
        Task*temp=head;
        head=head->next;
        free(temp);
    }
    printf("List is now empty. Let's change that!\n");
    printf("--- enter any key to return ---\n");
    getchar();
}



