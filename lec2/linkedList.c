#include <stdio.h>
#include <stdlib.h>

struct student{
    char *name;
    int gpa;
    struct student *next;

};

typedef struct student student;

student* addToList(student *start, char* n, int grade){
    //Create start of linked list if nothing is there

    //If something is there, connect them 

    if(start == NULL){
        start = (student*) malloc(sizeof(student*));

        start -> name = n;
        //start.name = name;
        start -> gpa = grade;
        start -> next = NULL;
        return start;
    }
    else{
        //if l to r, loop until linked list node-> next == NULL
        
        //adding to front

        student *node = (student *)malloc(sizeof(student *));
        if (node == NULL){
            //return error
        }
        node -> name = n;
        node -> gpa = grade;

        node -> next = start;
        return node;
    }
}

void printList(student *start){
    while(start != NULL){
        printf("Name: %s GPA: %d \n", start->name, start->gpa);
        start = start -> next;
    }
}

int main(){
    student *start = NULL;

    start = addToList(start, "Jake", 4);
    start = addToList(start, "Sam", 2);

    printList(start);
    return 0;

}
//