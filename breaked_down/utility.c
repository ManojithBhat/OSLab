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
int* conBin(int num) //function to convert in binary
{
    int t;
    int i, j;
    int *bin;
    bin=(int*)malloc(10*sizeof(int));
    for(i=0; i<10; i++)
    {
        bin[i]=0;
    }
    i=9;
    t = num;
    while(t!=0)
    {
         bin[i--]= t % 2;
         t = t / 2;
    }
    return bin;
}

char* convertTo5BitBinaryString(int decimal)    //This decimal is between 0 and 31
{
    printf("bitbinary function receives %d\n",decimal);
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

//in the main function 
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
