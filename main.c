#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTASKLEN 100

typedef struct Task{
    int id;
    int completed; //flag, 0 incomplete, 1 complete
    char description[MAXTASKLEN];
    struct Task* next;
} Task;

//int taskcount = 0;
Task* head = NULL;
int next_id = 1;

void viewdelete();
void viewToDo();
void addToDo();
void reorder();
void checkOff();
void wipe();
//int load();
//int exit();
int main(){

    //main menu
    int choice;
    while(1){
        printf("\n--- WELCOME TO YOUR TO-DO LIST! ---\n");
        printf("--- Let's get productive! --\n");
        //printf("---- choose your option below: ---\n\n");
        printf("------ 1. view To-Do's ------\n");
        printf("------ 2. add To-Do's ------\n");
        printf("------ 3. check off To-Do's ------\n");
        printf("------ 4. delete all tasks ------\n");
        printf("------ 5. Load from File ------\n");
        printf("------ 0. Exit ------\n");
        scanf("%d", &choice);
        getchar();

    switch(choice){
        case 1: viewToDo(); break;
        case 2: addToDo(); break;
        case 3: checkOff(); break;
        case 4: wipe(); break;
        //case 5: load(); break;
        case 0: exit(0);

        default: printf("please choose from valid options.\n");
    }
    }

}

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
       printf("%d- %s \n", i,temp->description);
       temp = temp->next;
       i++;
   }
   printf("--- enter any key to return ---\n");
   getchar();

}

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
    newTask->completed = 0;
    newTask-> next = NULL;
    newTask->id= next_id++;


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

    //taskcount++;

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
printf("test");
//walk thru list to get to
while(temp->next!=NULL && temp->next->id!=num) {
    temp = temp->next;
    printf("test");
}
if(temp->next==NULL) {
    printf("you don't have that many To-Do's!");
    return;
}
delete= temp->next;
temp->next = delete->next;
free(delete);
reorder();
}

//frees entire list
void wipe(){
    if(head==NULL) {
        printf("your list is already empty!");
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



