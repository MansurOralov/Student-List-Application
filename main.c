     // Assignment N3 Mansur Oralov
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 100

typedef struct node {
    char *name;
    float gpa;
    size_t id;
    struct node* next;
} student_t;


student_t* createNode(); // function to create the node
student_t* createList(); // function to create the list
void displayList(student_t*);      // function to display the list
void insertNode(student_t *head);// inserting the node
void removeList(student_t **head);  // function to delete the linked list

int id=1000; // declaring counters on the register is better 

// -------------------------------------- MAIN STARTS HERE-------------------------------------------------------------------------
int main() {
    
    student_t* head = createList();
    printf("\n===============List of students==================\n");
    printf("No          GPA            ID           Name\n");// Head of the table
    displayList(head);
    removeList(&head);
    return 0;
}
//--------------------------------------------------------MAIN ENDS HERE------------------------------------------------------------

//------------------------------------------------ CREATE NODE STARTS HERE----------------------------------------------------------
student_t* createNode(){
    //Getting the inputs from the user
    char tmp[MAX_LEN] ={0};
    char gpa[MAX_LEN] = {0};
    student_t* node = NULL; 
    printf("Insert student's name (id = %d): ", id);
    fgets(tmp,MAX_LEN,stdin);
    tmp[strcspn(tmp, "\n")] = 0;
    // if there is something in the input - memory will get allocated
    
    if (strlen(tmp)  > 1) {
        node = (student_t*) malloc( sizeof(student_t) );
        // GPA input has to be greater than -1 and smaller than 101
        printf("Insert student's GPA (0-100): ");
        fgets(gpa,sizeof(float)+1,stdin);
        printf("\n");
        gpa[strcspn(gpa, "\n")] = 0;
        // The name pointer is allocated on the heap
        node->name = (char*) calloc(strlen(tmp)+1, sizeof(char));
        strcpy(node->name, tmp);
        node->gpa = (float) strtof(gpa,NULL);
        if(strtof(gpa, NULL) > 100  || strtof(gpa,NULL) < 0 || strlen(gpa) < 1 ){ 
            node->gpa = 0;
            printf("Incorrect value of GPA! Ignore student input!\n\n");
            // Recursive call if the input doesn't pass the validation
            node = createNode();
        }
        
        node->next=NULL; 
        FLUSH;
    }
    return node;
}
//---------------------------------------------- CREATE NODE ENDS HERE--------------------------------------------------

// -------------------------------------------- CREATE LIST STARTS HERE-------------------------------------------------

student_t* createList(){
    // Forming the list here
    student_t *new_node=NULL, *current=NULL, *head=NULL;
    
    printf("Creating list of students:\n");
    // Loop is going to break only if the input is going to be NULL
    while ((new_node = createNode()) != NULL) {
        
        id++;
        
        if(current==NULL) {
            head=new_node;
        }
        else {  
            current->next=new_node;    
        }
        current=new_node;
        
    };
    //Calling insertNode to sort the list and insert the structure on the fly while console input
    insertNode(head);
    return head;
}
//--------------------------------------------CREATE LIST ENDS HERE-----------------------------------------------------


//-------------------------------------------INSERT NODE STARTS HERE---------------------------------------------------------------
void insertNode(student_t *head) {  
    //algorithm to sort the list and insert the node
    student_t *current = head, *index = NULL;  
    float temp;
    char *temp_name;
    
    if(head == NULL) {  
        exit(1);  
    }  
    else {  
        while(current != NULL) {  
            
            index = current->next;  
            // Honestly said My brain was to dumm to make the entire structures swap. I just swapped names and GPAs, but it works well
            while(index != NULL) {  
                if(current->gpa <  index->gpa) {  
                    temp = current->gpa;
                    temp_name = current->name;
                    current->gpa = index->gpa; 
                    current->name = index->name;
                    index->gpa = temp;
                    index->name = temp_name;
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }  
} 
//----------------------------------------------------- INSERT NODE ENDS HERE ----------------------------------------------------------------------

//-----------------------------------------------------DISPLAY LIST STARTS HERE --------------------------------------------------------------------
void displayList(student_t* head){
    // Displaying sorted (descending ) linked list.
    register int number=1; // declaring counter on the register is better for counters
    register int id1 = 1000;
    if(head == NULL) {
        printf("Linked List is empty.\n");
    } // end of if
    else  {
        student_t* current=head;
        while(current != NULL)  {
            printf("%d.         %.2f           %d          %s\n",number,current->gpa,id1,current->name);
            current = current->next; 
            number++;
            id1++;
            
        } 
        printf("\n");
    }
} 
//--------------------------------------------------DISPLAY LIST ENDS HERE ------------------------------------------------------------------------
//--------------------------------------------------REMOVE LIST STARTS HERE------------------------------------------------------------------------
void removeList(student_t **head){
    student_t* current = *head;
    student_t* next;
    
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    
}
//-------------------------------------------------REMOVE LIST ENDS HERE---------------------------------------------------------------------------
