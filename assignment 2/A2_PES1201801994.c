#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "assignment_2.h"


 typedef struct node
{
    int data;
    int first;
    struct node *next;
    

}node;


node* create_Node(int data)    //for creating new struct for a given element of element of  array
{
	node* new = (node*)malloc(sizeof(node));
	new -> data = data;
	new -> next= NULL;
	new->first = 1;

	return new;
}
	
void display_pre(node* temp)  //for sisplaying the both parts of array 
{
	node *t=(node*)malloc(sizeof(node));
	t=temp;
	printf("%d ",t->data);
	t=t->next;
	 while(t->first!=1)
	 {
		 printf("%d ",t->data);
		 t=t->next;
	 }
	printf("x ");
	while(t!=NULL)
	{
		 printf("%d ",t->data);
		 t=t->next;
	}
	printf("= ");

}


void display_post(node* temp) //for displaying the result of the two parts of the array
{
	node *t=(node*)malloc(sizeof(node));
	t=temp;
	while(t!=NULL)
	{
		 printf("%d ",t->data);
		 t=t->next;
	}
	printf("\n");
}


void move(node* arr[], int index)  //for a given index of the adjency list, it sorts and puts the result to the next index
{
	
	int i=index;
	node *final=(node*)malloc(sizeof(node));
	node *t=(node*)malloc(sizeof(node));
	node *t1=(node*)malloc(sizeof(node));
	node *temp1=(node*)malloc(sizeof(node));
	node *temp2=(node*)malloc(sizeof(node));
	node *prev=(node*)malloc(sizeof(node));
	node *pres=(node*)malloc(sizeof(node));

    temp1=arr[i];
    prev=arr[i];
    pres=arr[i]->next;
    while(pres!=NULL && pres->first!=1) //reasons for exiting 1.pres=NULL (only element ) , 2.pres->first=1 ,
    {
        prev=pres;
        pres=pres->next;
    }
    if(pres==NULL)  //prev=temp1;    //when only one element
    {
        t=arr[index+1];
		t1=NULL;
		while(t!=NULL)
		{
			t1=t;
			t=t->next;	
		}

		if(t1==NULL)
		{
			arr[index+1]=arr[i];
		}
		else
		{
			t1->next=arr[i];
			move(arr,i+1);
			arr[i]=NULL;
		}


		//prev->next=arr[0];
		//free(arr[i]);
		
    }
    else if(pres->first==1)     //when there are two parts of  adjency list to be sorted.  
    {
        display_pre(arr[i]);
         temp2=pres;

         if(temp1->data > temp2->data)  //checks which part of the  adjency list is grater
         {
             final=temp2;
             t=temp1;//free everything after temp2
             while(t->next->first!=1)
			 {
				final->next=t->next;
				t=t->next;
				final=final->next;
			 }
            final->next=NULL;
			temp1->next=temp2;	
			final=temp1;
         }
         else
         {
             final=temp1;
             t=temp2;
             while(t->next!=NULL)
			{
				final->next=t->next;
				t=t->next;
				final=final->next;
			}
			final->next=NULL;
            temp2->next=temp1;	
			final=temp2;
         }
		display_post(final);
         pres=final->next;
         while(pres)        //marking all the elements except the first element's to first flag to zero
         {
             pres->first=0;
             pres=pres->next;
         }
		t=arr[i+1];   
        t1=NULL;
        while(t!=NULL)  //attaching the final sorted array to the next index of the  adjency list
        {
            t1=t;
            t=t->next;
        }
        if(t1==NULL)
        {
            arr[i+1]=final;
			arr[i]=NULL;
        }
        else
        {
            t1->next=final;
			
			move(arr,i+1);
			arr[i]=NULL;
        }    
    }    
}
void update(int n , node*arr[])  //attaches the new element to the adjency list
{
    node *new; 
	new=create_Node(n);
    if(arr[0]==NULL)   //if the adjency list has no elements the just attach
    {
        arr[0]=new;
    }
    else               //if the adjency list has any elements the attach the new element and then sort it using the more() 
    {
        node *temp=(node*)malloc(sizeof(node));
	    temp=arr[0];
        while(temp->next)
        { 	
            temp=temp->next;
        }
        temp->next=new;
        move(arr,0);
		arr[0]=NULL;  //check
        //free(arr[0]); 
    }
}





void find_second_greatest(int *numbers, int length)     //finds the second largest number 
{
	if(length>1)
	{
		/*for(int k=0;k<length;k++)
		{
			printf("%d \n",numbers[k]);
		}*/

		node *pres=(node*)malloc(sizeof(node));
		node *temp;
		int len=ceil(log(length)/log(2))+1;  //  creating the  adjency list of log n +1 size
		node *arr[len];
		for(int z=0;z<len;z++)
		{
			arr[z]=(node*)malloc(sizeof(node));
			arr[z]=NULL;
		}
		for(int i=0;i<length;i++)
		{
			update(numbers[i],arr);
			/*printf("\n%d  line 195\n",numbers[i]);
			for(int j=0;j<len;j++)
			{
				printf("\n%d  line 196\n",j);
				temp=arr[j];
				while(temp!=NULL)
				{
					printf("%d  202 \t",temp->data);
					temp=temp->next;
				}
			}*/
		}
		

		//printf("done \n");
		int count=0;
		int flag=0;
		int j;
	/*	for(int j=0;j<len;j++)
			{
				printf("\n%d  line 222\n",j);
				temp=arr[j];
				while(temp!=NULL)
				{
					printf("%d  226  \t",temp->data);
					temp=temp->next;
				}
			}*/
		for(int i=0;i<len;i++)     //checks if there is no nore than one non NULL in the adjacency list
		{
			//printf("%d     line 220\n",i);
			if(arr[i]!=NULL)
			{
				//printf("%d  line 223\n",arr[i]->data);
				count++;
				//printf("%d  count\n",count);
				if(count>1)
				{
					//printf("\n inside count grater than 1 \n");
					//printf("%d  count\n",j);
					move(arr,j);

					for(int z=0;z<len;z++)
					{
						//printf("\n%d  line 222\n",z);
						temp=arr[z];
						while(temp!=NULL)
						{
							//printf("%d  226  \t",temp->data);
							temp=temp->next;
						}
					}

					i=j;
					count=0;
					flag=0;
				}
				else if(count==1&& (!flag))
				{
					//printf("\n inside else if \n");
					j=i;
					flag=1;
				}
			}
		}
		int sec; //minimum 2  elements required
		pres=arr[j]->next;
		sec=pres->data;
		while(pres)
		{
			if(pres->data > sec)
				sec=pres->data;
			pres=pres->next;
		}
		printf("%d \n",sec);   //displays the second largest 
	}
}




int main()
{
   	int length=33;
	int numbers[length];
	for(int i=0;i<length;i++)
	{
		numbers[i]=i;
	}
	find_second_greatest(numbers, length);
	
}



