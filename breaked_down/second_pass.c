//second pass of the assembler 

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
char * getRegisterCode(char* temp)
{
    char *s;
    if (strcmp(temp,"R0") == 0)
    {
        s = "00000";
    }
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
    else if (strcmp(temp,"R6") == 0)
        s = "00110";
    else if (strcmp(temp,"R7") == 0)
        s = "00111";
    else if (strcmp(temp,"R8") == 0)
        s = "01000";
    else if (strcmp(temp,"R9") == 0)
        s = "01001";
    else if (strcmp(temp,"R10") == 0)
        s = "01010";
    else if (strcmp(temp,"R11") == 0)
        s = "01011";
    else if (strcmp(temp,"R12") == 0)
        s = "01100";
    else if (strcmp(temp,"R13") == 0)
        s = "01101";
    else if (strcmp(temp,"R14") == 0)
        s = "01110";
    else if (strcmp(temp,"R15") == 0)
        s = "01111";
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
char *getConstantCode(int temp)
{
    return convertTo5BitBinaryString(temp);
}

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
input_instructions = fopen("input_instructions.txt","r+");
   int * binary;
   char test[100];
   int count;
    
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
       if(op[l]==':')   //Its a label
       {
        	printf("Label Found!\n");
            fprintf(output_machine_code,"\n");
           //handle label
       }
       else
       {
           char temp[100];
           char temp2[100];
           char temp3[100];
           int temp4;
            //handle opcode and print corresponding machine code
            Opcode* current_node = getOpcodeNode(op);
            fprintf(output_machine_code,"%s",current_node->code);//print machine code of the opcode

            if (strcmp("z",getOpcodeFormat(current_node))==0)   //ZERO OPERAND INSTRUCTION
            {
                fprintf(output_machine_code,"\n");//Do nothing
            }
            else if(strcmp("r",getOpcodeFormat(current_node))==0)   //ONE OPERAND REGISTER OPERAND INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp); //read corresponding register code

                fprintf(output_machine_code,"%s",getRegisterCode(temp)); //write corresponding register code in binary
                fprintf(output_machine_code,"\n");
            }
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
            else if(strcmp("rr",getOpcodeFormat(current_node))==0)   //TWO OPERAND REGISTER REGISTER OPERAND INSTRUCTION
            {
                //printf("inside two");
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%s",temp2);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
                fprintf(output_machine_code,"%s",getRegisterCode(temp2));
                fprintf(output_machine_code,"\n");
            }
            else if(strcmp("ri",getOpcodeFormat(current_node))==0)   //TWO OPERAND REGISTER CONSTANT INSTRUCTION
            {
                k = fscanf(input_instructions,"%s",temp);
                k = fscanf(input_instructions,"%d",&temp4);
                fprintf(output_machine_code,"%s",getRegisterCode(temp));
              //  fprintf(output_machine_code,"%s",getConstantCode(temp4));
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

    }while(fgets(test, sizeof test, input_instructions)!=NULL);
    printf("\n\nSymbol Table\n\n");
    fclose(input_instructions);
    fclose(output_machine_code);
    fclose(input_opcode);
