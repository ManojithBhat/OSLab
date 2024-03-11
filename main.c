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

/*
This structure stores the opcode, which is a mnemonic in assembly language. The opcode is used to denote what operation is to be performed. An opcode is short for 'Operation Code'.
An opcode is a single instruction that can be executed by the CPU.
In assembly language mnemonic form an opcode is a command such as MOV or ADD or JMP.
*/

struct Symbol               //Symbol Table is made using Linked List to save space
{
    char name[50];
    int add;
    struct Symbol *next;
};

//This table stores all the encountered labels and their corresponding memory addresses.
typedef struct Opcode Opcode;
typedef struct Symbol Symbol;

Symbol *head=NULL;

Opcode* hash_table[13] = {NULL};
void reverseArray(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

//The array must be reversed in order to convert it to a binary string
int* conBin(int num) 
{
    int t;
    int i, j;
    int *bin;
    bin=(int*)malloc(10*sizeof(int));
    for(i=0; i<10; i++) bin[i]=0;
    i=9;
    t = num;
    while(t!=0)
    {
         bin[i--]= t % 2;
         t = t / 2;
    }
    return bin;
}

//Function to convert the decimal value of a symbol (which has been mapped) to binary
char* convertTo5BitBinaryString(int decimal)   
{
    char *str = (char *)malloc(5*sizeof(char));
    int d[5]={0};
    int i=0,j=0;
    while(decimal>0)
    {
       d[i]=decimal%2;
       i++;
       decimal=decimal/2;
    }
    int size = i;
    int k=0;
    int s=0;

    reverseArray(d,0,4);
    for(s=0;s<5;s++)
	{
        printf("%d",d[s]);
        str[s] = d[s] + '0';
    }
      printf("\n");

     printf("%s",str);
     return str;
}
//This function converts the decimal value to a 5-bit binary string

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

/*This is the hash function used to get the index at which the opcode must be stored in the hash table.
The function takes in the name of the opcode as input, calculates the sum of the ascii values of all the characters
in the opcode and computes the remainder when divided by the size of the hash table, to get the index.*/

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

//After having calculated the index, the opcode is inserted at the index in the hash table.
void insertIntoHashMap(Opcode *Node)
{
    int index = getHashIndex(Node->name);
    insertAtIndex(Node,index);
}

//This function is used to get the hash index and insert the opcode at the index calculated.
int *getAddressCode(char* temp)
{
    Symbol * t = head;
    int * val;
    int num;
    while(t != NULL)
    {
        if(!strcmp(temp,t->name))
        {
            num = t->add;
            break;
        }
        t = t->next;
    }
    val = conBin(num);
    return val;
}

/*This function takes a symbol (presumably a label or address) as input and searches for it in the symbol table.
If found, it retrieves the associated address and converts it to a 10-bit binary array using the conBin function.*/

char * getRegisterCode(char* temp)
{
    char *s;
    if (strcmp(temp,"R0") == 0)
        s = "00000";
    else if (strcmp(temp,"R1") == 0)
        s = "00001";
    else if (strcmp(temp,"R2") == 0)
        s = "00010";
    else if (strcmp(temp,"R3") == 0)
        s = "00011";
    else if (strcmp(temp,"R4") == 0)
        s = "00100";
    else if (strcmp(temp,"R5") == 0)
        s = "00101";
    else if (strcmp(temp,"R10") == 0)
        s = "01010";
    else if (strcmp(temp,"A1") == 0)
        s = "10000";
    else if (strcmp(temp,"A2") == 0)
        s = "10001";
    else if (strcmp(temp,"A3") == 0)
        s = "10010";
    else if (strcmp(temp,"A4") == 0)
        s = "10011";
    else if (strcmp(temp,"port0") == 0)
        s = "10100";
    else if (strcmp(temp,"port1") == 0)
        s = "10101";
    return s;
}

//This function maps the registers to binary strings
char *getConstantCode(int temp)
{
    return convertTo5BitBinaryString(temp);
}

//This function calls the 5-bit binary string function to retreieve the 5 bit binary string value.
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

/*This function retrieves an opcode node from the hash table based on the opcode name.
It calculates the hash index using the getHashIndex function, then searches for the opcode in the corresponding hash chain.
If found, it returns a pointer to the Opcode structure; otherwise, it returns NULL.*/

char * getOpcodeFormat(Opcode* temp)
{
    return temp->format;
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
	//Reading each opcode and inserting its binary codes intp the hash map

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
    printf("Now reading Opcodes and Converting them to machine codes\n");

    input_instructions = fopen("input_instructions.txt","r+");
    output_machine_code = fopen("output_machine_code.txt","w+");
    char k;
    char op[100];

/***********************************************************************************************/
/*First pass for generation of symbol table*/
/***********************************************************************************************/
	
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
    printf("\n\nSymbol Table\n\n");
    FILE *f = fopen("symbol_table.txt","w+");
    while(p!=NULL)
    {
        printf("%s :: ",p->name);
        fprintf(f,"%s :: ",p->name);
        printf("%d\n",p->add);
        fprintf(f,"%d\n",p->add);
        p = p->next;
    }
   fclose(f);
	
/***********************************************************************************************/
/*Second pass for generation of binary codes*/
/***********************************************************************************************/
	
   input_instructions = fopen("input_instructions.txt","r+");
   int * binary;
   char test[100];
   int count;
    // The code reads the first word on the line, which is assumed to be the opcode (operation code) of the instruction.
    do
    {
       k=fscanf(input_instructions,"%s",op);
       printf("WORD SCANNED IS %s  \n",op);
        /*check if opcode or label*/
       int l=0;
       while(op[l+1]!='\0')
       {
           l++;
       }
	// It checks if the opcode ends with a colon (':'). If it does, it is considered a label,
       if(op[l]==':')   //Its a label
       {
            printf("Label Found!\n");
            fprintf(output_machine_code,"\n");
           //handle label
       }
       else
       {
	  /*Handles opcode: If the opcode is not a label, the code performs the following steps:
	  Gets opcode information: It calls a function getOpcodeNode(op) to retrieve information about the opcode.
          This function returns a node containing the opcode, machine code representation and the format of its operands (e.g., zero operands, one register operand, etc.).
	  Prints machine code: The code then prints the machine code of the opcode to the output file.*/
	  
           char temp[100];
           char temp2[100];
           char temp3[100];
           int temp4;
	       
            //handle opcode and print corresponding machine code
            Opcode* current_node = getOpcodeNode(op);
            fprintf(output_machine_code,"%s",current_node->code);//print machine code of the opcode

	   /* Handles operands: Based on the format of the operands retrieved from getOpcodeNode(op), the code reads
   	    the operands from the input file and performs the following:*/
	   // Zero operands: If the opcode has no operands (format "z"), the code does nothing.
	       
            if (strcmp("z",getOpcodeFormat(current_node))==0)   //ZERO OPERAND INSTRUCTION
            {
                fprintf(output_machine_code,"\n");//Do nothing
            }
	    /*One register operand: If the opcode has one register operand (format "r"), the code reads the register name from the input file, 
	    calls a function getRegisterCode(temp) to get the binary code for the register, and prints the binary code to the output file.*/
		    
            else if(strcmp("r",getOpcodeFormat(current_node))==0)   //ONE OPERAND REGISTER OPERAND INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp); //read corresponding register code

                fprintf(output_machine_code,"%s",getRegisterCode(temp)); //write corresponding register code in binary
                fprintf(output_machine_code,"\n");
            }

	    /*One address operand: If the opcode has one address operand (format "a"), the code reads the address from the input file,
            calls a function getAddressCode(temp) to get the binary code for the address (likely an integer value), and prints the binary code
            to the output file.*/
		    
            else if(strcmp("a",getOpcodeFormat(current_node))==0)   //ONE OPERAND ADDRESS OPERAND INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp);
                binary = getAddressCode(temp); //write corresponding address in binary
                for(count=0;count<10;count++)
                {
                    fprintf(output_machine_code,"%d",binary[count]);
                }
                fprintf(output_machine_code,"\n");
            }

	    /*Two register operands: If the opcode has two register operands (format "rr"), the code reads the two register names from the 
     	     input file,calls getRegisterCode(temp) for each register to get their binary codes, and prints the binary codes to the output file.*/
		    
            else if(strcmp("rr",getOpcodeFormat(current_node))==0)   //TWO OPERAND REGISTER REGISTER OPERAND INSTRUCTION
            {
                //printf("inside two");
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%s",temp2);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
                fprintf(output_machine_code,"%s",getRegisterCode(temp2));
                fprintf(output_machine_code,"\n");
            }

	    /*Two operands: register and constant: If the opcode has one register operand and one constant operand (format "ri"), the code reads the
     register name and the constant value from the input file. It then calls getRegisterCode(temp) to get the binary code for the register. For the
     constant operand, it converts the decimal value to binary using a function conBin(temp4). It then prints the binary codes for the
     register and the constant to the output file.*/
            
            else if(strcmp("ri",getOpcodeFormat(current_node))==0)   //TWO OPERAND REGISTER CONSTANT INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%d",&temp4);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
                binary = conBin(temp4);
                for(count=0;count<10;count++)
                {
                    fprintf(output_machine_code,"%d",binary[count]);
                }
                fprintf(output_machine_code,"\n");
            }
		    
	    else if(strcmp("rrr",getOpcodeFormat(current_node))==0)   //THREE OPERAND REGISTER-REGISTER-REGISTER INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%s",temp2);
                k = fscanf(input_instructions,"%s",temp3);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
                fprintf(output_machine_code,"%s",getRegisterCode(temp2));
                fprintf(output_machine_code,"%s",getRegisterCode(temp3));
                fprintf(output_machine_code,"\n");
            }

           /*Three operands: register-register-immediate: If the opcode has three operands (one register, one register, and one immediate value) 
	   (format "rri"), the code reads the two register names and the constant value from the input file. It then performs similar steps as 
    	   the two-operand (register and constant) case  to get the binary codes for the register operands and the constant operand. Finally, 
	    it prints the binary codes to the output file.*/
		    
            else if(strcmp("rri",getOpcodeFormat(current_node))==0)   //THREE OPERAND REGISTER-REGISTER-INTERMEDIATE INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%s",temp2);
                k = fscanf(input_instructions,"%d",&temp4);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
                fprintf(output_machine_code,"%s",getRegisterCode(temp2));
                binary = conBin(temp4);
                for(count=0;count<10;count++)
                {
                    fprintf(output_machine_code,"%d",binary[count]);
                }
                fprintf(output_machine_code,"\n");
            }
       }

    }
    while(fgets(test, sizeof test, input_instructions)!=NULL);
   
    fclose(input_instructions);
    fclose(output_machine_code);
    fclose(input_opcode);
 
    return 0;
}
