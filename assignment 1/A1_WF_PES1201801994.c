#include <stdio.h>
#include <stdlib.h>
#include "assignment_1.h"

char *p;
extern char *p;
int size;
extern int size;

typedef struct book
{
    int S;      //book size i.e size of each block
    int fl;    //flag to show if its fl
    struct book *next; //link to the next book

}book;


void fre()            //to join the free blocks if there is any.
{
    book *temp = (book*)p;    
    while(temp!=NULL && temp->next!=NULL)   //traverse till the end to merge the free blocks
    {
       if(temp->fl==0 && temp->next->fl==0)
       {
           temp->S=temp->S + sizeof(book)+ temp->next->S;
           temp->next=temp->next->next;
       }
       temp=temp->next;
   }
}



void allocate(int n)  //function to allocate memory for the global array p, n number of bytes long.
{
    p=(void *)malloc(n * sizeof(char)); 
    
    size =n;
    book *temp=(book*)p;
    temp->S=n-sizeof(book);   
    temp->next=NULL;
    temp->fl=0;    // 0:free     1:allocated
    
}


void print_book() // prints bytes used by the bookkeeping structure
{
    printf("%d\n", sizeof(book));
}


void* mymalloc(int SIZE) //function to allocate a block of size "size" from p
{
    if(SIZE<0 || SIZE >size)  //size to be inserted must be between 0 and max size
    {
        return NULL;
    }
    int max=-100;
    book *alloc=NULL;
    book *temp=(book*)p;
    while(temp!=NULL)
    {
       
        if(temp->S - SIZE > max && (temp->fl==0))  //traverse and find the maximum free block available 
        {
            max=temp->S - SIZE;      //max is the maximum space available after allocating SIZE
            if(max>=0)
                alloc=temp;
               
        }
        temp=temp->next;
       
    }
    
    if(alloc!=NULL  )    //if the block to allocate is available, then allocate
    {

        if(max > sizeof(book)  ) // space available is more than  SIZE and bookkeeping
        {
            book *temp1=alloc + 1 + SIZE ;
            temp1->S = max - sizeof(book);
            temp1->fl=0;
            temp1->next=alloc->next;
            alloc->S=SIZE;
            alloc->fl=1;
            alloc->next=temp1;
            return alloc  + 1;  
        } 
        else if(max>=0) // no space available for next bookkeeping
        {
            alloc->S=max + SIZE;
            alloc->fl=1;
            return alloc  + 1;
        }
        else
        {
            return NULL; //if no block is available to allocate, return NULL
        }
        
       
    }
    return NULL; //if no block is available to allocate, return NULL

}


void display_mem_map() // print the memory array p in the following format:     start_addr   block_in_bytes  status
{
    int addr=0;
    book *temp =(book*)p;
    while(temp!=NULL )
    {
        printf("%d   %d   book\n" , addr ,sizeof(book));

        if(temp->fl)
            printf("%d   %d   allocated\n" , addr+sizeof(book) ,temp->S);  
        
        else
           printf("%d   %d   free\n" , addr+sizeof(book) ,temp->S); 
        
        addr += sizeof(book);
        addr += temp->S;
        temp=temp->next;


    }


}


void myfree(void *b) //free the block pointed to by the parameter
{
   if(b!=NULL)
   {
       book *temp = (book*)p;
       book *temp1=(book*)b - 1;
       temp1->fl=0; 
       while(temp!=NULL && temp->next!=NULL) //traverse till the end to merge the free blocks
       {
           if(temp->fl==0 && temp->next->fl==0) 
           {
               temp->S=temp->S + sizeof(book)+ temp->next->S;
               temp->next=temp->next->next;
           }
           temp=temp->next;
       }
   }
   fre(); //to join the free blocks if there is any.
}