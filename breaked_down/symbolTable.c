//first pass of the assembler - symbol table creation and adding nodes 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Symbol               //Symbol Table is made using Linked List to save space
{
    char name[50];
    int add;
    struct Symbol *next;
};
typedef struct Opcode Opcode;
typedef struct Symbol Symbol;

Symbol *head=NULL;

//in the main program

printf("Now reading Opcodes and Converting them to machine codes\n");

    input_instructions = fopen("input_instructions.txt","r+");
    output_machine_code = fopen("output_machine_code.txt","w+");
    char k;
    char op[100];

    /***********************************************************************************************/
	/*First pass for generation of symbol table*/
	
    while ( fgets ( op, sizeof op, input_instructions ) != NULL ) /* read a line */
    {
       int l=0;

       while(op[l+1]!='\0')
       {
        if(op[l]==':')   //Its a label
        {
        	Symbol *t;
        	struct Symbol *temp = (struct Symbol*) malloc(sizeof(Symbol)); //dynamic memory allocation for a node of symbol
        	int i=0;
        	for(;i<l;i++)
                temp->name[i] = op[i];
            temp->name[i] = '\0';
            temp->add = ilc + 1 + base;
            temp->next = NULL;
        	if(head == NULL) //boundary condition for implementing symbol table using linked list
                head = temp;
        	else  //adding new symbol node to existing table of nodes
        	{
                t = head;
                while(t->next!=NULL)
                    t= t->next;
                t->next = temp;
        	}
           //handle label
       }
       l++;
     }
     ilc++;
 }
   fclose(input_instructions);
   
