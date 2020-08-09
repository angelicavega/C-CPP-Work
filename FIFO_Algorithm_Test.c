/* FIFO Page Replacement Algorithm */

#include "stdio.h"
#include "curses.h"
#include "stdlib.h"

struct node
  {
  int data;
  struct node *next;
  }*ava,*nnode,*current,*start=NULL,*temp,*last;

int hits[100],count,fault,di;
//--------------------------------
void follow()
 {
 int i;
   
   for(i=0;i< di;i++)
   {
   nnode=(struct node *)malloc(sizeof(struct node));
   nnode->data = -99;     // NULL Declaration
   nnode->next=NULL;
    
   if(start==NULL)
     {
     start=nnode;
     current=nnode;
     }
   else
     {
     current->next=nnode;
     current=nnode;
     }
   }
 current->next = start;
 }
//--------------------------------
void display()
{
struct node *temp;
temp=start;
  do
   {
   if(temp->data == -99)
       printf("-t",temp->data);
   else
       printf("%dt",temp->data);
   temp=temp->next;
   }while(temp!=start);
}
//--------------------------------
int search(int number)
{
int flag;
struct node *temp;
temp=start;
  do
   {
   if(temp->data==number)
         return(1);
   else
         flag = 0;
   temp=temp->next;
   }while(temp!=start);

if(flag ==0)
   return(0);
}
//FIFO 
void fifo()
{
int res,i;
temp = start;  //Temp 
last = start;  //Repl 
ava = start;  //Ava 

for(i=0;i< count;i++)
  {
  res = search(hits[i]);

   if(res == 0)
     {
     fault++;
     if(ava->data == -99)
        {
        ava->data = hits[i];
        ava = ava->next;
        }
     else
        {
        last ->data = hits[i];
        last = last->next;
        }
     }//end outer if

  printf("After Inserting (%d)  :: ",hits[i]);
  display();
  printf("    Fault : %d",fault);
  }//end for


  printf(" Total Number of Faults = %d ",fault);


}
//Printing Section
void accept()
{
int i;
printf("Enter the number of Frames : ");
scanf("%d",&di);

printf("Enter the number of References : ");
scanf("%d",&count);

printf("Enter the String : ");
for(i=0;i< count;i++)
    scanf("%d",&hits[i]);
}
//Satisfying #Include Functions
void main()
{
char ch;



accept();
follow();
fifo();


}