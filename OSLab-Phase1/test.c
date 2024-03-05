
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Opcode               //This node is used for Hashing using Chaining
{
    char name[10];
    char code[35];
    char format[5];
    struct Opcode *next;
};

struct Symbol               //Symbol Table is made using Linked List to save space
{
    char name[50];
    int add;
    struct Symbol *next;
};

typedef struct Symbol Symbol;
Symbol *head=NULL;

typedef struct Opcode Opcode;
Opcode* hash_table[13] = {NULL};

int getHashIndex(char name[])
{
    int sum=0,i=0;
    while(name[i]!='\0')
    {
        sum+=name[i++];
    }
    return sum%13;
}
void insertAtIndex(Opcode *Node,int index)
{
    if(hash_table[index] == NULL) //boundary condition
    {
        hash_table[index] = Node;
        Node->next = NULL;
    }
    else
    {
        Opcode* temp = hash_table[index];
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = Node;
        Node->next=NULL;
    }
}
void insertIntoHashMap(Opcode *Node)
{
    int index = getHashIndex(Node->name);
    insertAtIndex(Node,index);
}

int main()
{
    FILE *input_opcode;
    FILE *output_machine_code;
    FILE *input_instructions;
    int ilc=0;  //Instruction Location Counter
    int base = 0;
    char c,c2,c3,temp;
    char opcode[100];
    char machine_code[100];
    char format[5];
  
    
    input_opcode = fopen("input_opcode.txt","r+");  //input_opcode contains a list of opcodes followed by their format and mac.code
    if (input_opcode == NULL)
        printf("FILE OPENING PROBLEM");
    char test1[50];
    do
    {
        c = fscanf(input_opcode,"%s",opcode);//Assuming to get opcode as a string in opcode array
        c2= fscanf(input_opcode,"%s",machine_code);//Assuming to get a the integer as a string in machine_code array
        c3= fscanf(input_opcode,"%s",format);
        //now we will create node of each string
        struct Opcode* Node = (struct Opcode *) malloc(sizeof(Opcode));

        strcpy(Node->name,opcode);
        //Name of the opcode is fed
        strcpy(Node->code,machine_code);
        //Machine code of the opcode is fed
        strcpy(Node->format,format);
        //Format of the opcode is fed
      //  printf("BEFORE INSERTING NAME:: %s ,CODE:: %s and format",Node->name,Node->code,Node->format);
        insertIntoHashMap(Node);


    }while(fgets(test1, sizeof test1, input_opcode)!=NULL);

        //At this point we have a hash-map of Opcodes


    printf("Hash-map Created Successfully!\n");
    /*TEST:: PRINTING HASHTABLE with hashcode*/
    int i=0;
    for(i=0;i<13;i++)
    {

        if(hash_table[i]!=NULL)
        {

            Opcode* temp = hash_table[i];

            while(temp!=NULL)
            {
                printf("NAME:: %s and CODE:: %s and format:: %s \n",temp->name,temp->code,temp->format);
                temp = temp->next;
            }
            printf("\n");

        }
    }

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

     /*PRINT SYMBOL TABLE*/
    Symbol *p;
    p=head;
    FILE *f = fopen("symbol_table.txt","w+");
    while(p!=NULL)
    {
        printf("%s :: ",p->name);
        fprintf(f,"%s :: ",p->name);
        printf("%d\n",p->add);
        fprintf(f,"%d\n",p->add);
        p = p->next;
    }

    return 0;
}