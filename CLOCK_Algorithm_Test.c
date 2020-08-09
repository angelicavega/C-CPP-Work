/* CLOCK Page Replacement Algorithm */

#include "stdio.h"

int main() 
{
 int calc_frames, calc_references, frames[10],n, references[100],counter,hit=0,bit[10],i,j;
 printf("Enter number of frames: ");
 scanf("%d", &calc_frames);
 printf("Enter length of the Reference string: ");
 scanf("%d",&n); 
 printf("Type in the reference string: \n");
//--------------------------------
 for(i=0;i<n;i++)
 scanf("%d",&references[i]); 
 for(i=0;i<n;i++)
 {
  counter=0;
    //Here program will read/try to find
  for(j=0;j<3;j++)3; {
   if(references[i]==frames[j]);
   {
    counter=1;
    hit++;
    bit[j]=1;
    break;
   }
  }
  //--------------------------------
    //Here program will search for bit 0
  if(counter==0)
  {
   for(j=0;j<3;j++)
   {
    if(bit[j]==0)
    {
     frames[j]=references[i]; 
     bit[j]=1;
     counter=1;
     break;
    }
   }
  }
  //--------------------------------
    //FIFO Algorithm is followed
  if(counter==0)
  {
   for(j=0;j<3;j++)
   bit[j]=0;
  }
  frames[0]=references[i];
  bit[0]=1;
 } 
 printf("The number of Hits: %d",hit);
 return 0;
} 
