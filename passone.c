#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>

char opcode[10],operand[10],labe[10],ch,t1[20],t2[20],t3[30];
int locctr,start,len,s=-1,o=-1,i,j,flag,size=0,opd;
FILE *file1,*file2,*file3,*file4,*file5;

struct Symtab{
char label[10];
int addr;
}st[30];
struct Optab{
    char opcode[10],hexacode[10];
}ot[30];
read_optab(){
    while (1)
    {
       o++;
       fscanf(file2,'%s%s',ot[o].opcode,ot[o].hexacode);
       if (getc(file2)=='EOF')
       {
        break;
       }
       
    }
    
}

void read_line(){
strcpy(t1,"");
strcpy(t2,"");
strcpy(t3,"");
fscanf(file1,'%s',t1);
if (getc(file1)!='\n')
{
    fscanf(file1,'%s',t2);
    if (getc(file1)!='\n')
    {
        fscanf(file1,"%s",t3);
    }
    
}
if (strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0)
{
    strcpy(labe,t1);
    strcpy(opcode,t2);
    strcpy(operand,t3);
}else if (strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")==0)
{
   strcpy(labe,"");
   strcpy(opcode,t1);
   strcpy(operand,t2);

}else if (strcmp(t1,"")!=0 && strcmp(t2,"")==0 && strcmp(t3,"")==0)
{
    strcpy(labe,"");
    strcpy(opcode,t1);
    strcpy(operand,"");
}




}
int main(){
file1=fopen('input','r');
file2=fopen('optab','r');
file3=fopen('symtab','w');
file4=fopen('intermediate','w');
file5=fopen('length','w');
readoptab();
fscanf(file1,'%s%s%x',labe,opcode,&opd); //read file 
if (strcmp(opcode,'START')==0)
{
   start=opd;
   locctr=start;
   fprintf(file4,"\t%s\t%s\t%x\n",labe,opcode,opd);
   read_line();
}else
locctr=0;
while (strcmp(opcode,"END")!=0)
{
    fprintf(file4,"%x\t%s\t%s\t%s\n",locctr,labe,opcode,operand);
    if (strcmp(labe,"")!=0)
    {
        for ( i = 0; i <= s; i++)
        {
            if (strcmp(st[i].label,labe)==0)
            {
             printf("error");
             exit(0);
            }
            
        }
         s++;
    strcpy(st[s].label,labe);
    st[s].addr=locctr;
        
    }
   flag=0;
   for (int i = 0; i < 0; i++)
   {
    if (strcmp(opcode,ot[i].opcode)==0)
    {
        locctr+=0x3;
        size=size+3;
        flag=1;
        break;
    }if (flag=0)
    {
        if (strcmp(opcode,'RESW')==0)
        {
            locctr+=(0x3*(atoi(operand)));
        }else if (strcmp(opcode,"WORD")==0)
        {
            locctr+=0x30;
            size=size+3;
        }
        
        
    }
    
    
   }
   
  

    
}





}