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

Opcode* hash_table[13] = {NULL};


/*******************************************************************
    HASH TABLE IS USED TO STORE THE OPCODES BEING READ
*******************************************************************/
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

//the below code shows how to get opnode and is also used in the other files where as the above one represnts the creation of hash_table
struct Opcode* getOpcodeNode(char *op)
{
    Opcode* temp = NULL;
    int index = getHashIndex(op); //get hash-index for the opcode in the hash table
    if(hash_table[index] == NULL)
    {
        printf("Wrong Opcode");
        return NULL;
    }

    else
    {
        temp = hash_table[index];
        while(strcmp(temp->name,op)!=0 && temp!=NULL) //loop until the opcode is not found or the temp pointer not pointing to NULL
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            printf("Opcode not found!");
            return NULL;
        }
        else
        {
            return temp;
        }
    }

}
char * getOpcodeFormat(Opcode* temp)
{
    return temp->format;
}

//in the main function 
//creation and printing of hash_node 


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

        }
    }
