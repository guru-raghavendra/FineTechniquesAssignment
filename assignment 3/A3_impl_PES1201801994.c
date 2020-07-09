#include <stdio.h>
#include <stdlib.h>
#include "A3_header_PES1201801994.h"






void set_state(state* ptr_state, int A, int B, int C)
{
    ptr_state->A=A;
    ptr_state->B=B;
    ptr_state->C=C;
    ptr_state->fn_index=0;

}


void disp_state(const state* ptr_state)
{
    printf("%d %d %d\n",ptr_state->A,ptr_state->B,ptr_state->C);
}


void moveA2B(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_B - src->B;//required by dest
    int pos=src->A;         //possible by source
    int min;              //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A - min;
    dst->B=src->B + min;
    dst->C=src->C;
}

void moveA2C(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_C - src->C;//required by dest
    int pos=src->A;         //possible transfer by source
    int min;              //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A - min; 
    dst->B=src->B ;
    dst->C=src->C + min;
}

void moveB2A(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_A - src->A;//required by dest
    int pos=src->B;         //possible transfer by source
    int min;               //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A + min;
    dst->B=src->B - min ;
    dst->C=src->C;
}

void moveB2C(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_C - src->C;//required by dest
    int pos=src->B;         //possible transfer by source
    int min;               //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A;
    dst->B=src->B - min ;
    dst->C=src->C + min;
}

void moveC2A(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_A - src->A;//required by dest
    int pos=src->C;         //possible transfer by source
    int min;               //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A + min;
    dst->B=src->B;
    dst->C=src->C - min;
}

void moveC2B(const state* src, state *dst,const int size_A,const int size_B,const int size_C)
{
    int req=size_B - src->B;//required by dest
    int pos=src->C;         //possible transfer by source
    int min;               //possible transfer
    if (req<pos)
        min=req;
    else
        min=pos;
    dst->A=src->A;
    dst->B=src->B + min;
    dst->C=src->C - min;
}



int are_same(const state* lhs, const state* rhs)
{
    return (lhs->A==rhs->A) && (lhs->B==rhs->B) && (lhs->C==rhs->C);
}

int is_valid(const state* ptr_state,const int size_A,const int size_B,const int size_C)
{
    return ( ptr_state->A>=0 ) && ( ptr_state->B>=0 ) && 
            ( ptr_state->C >=0 ) && ( ptr_state->A<=size_A ) && 
            ( ptr_state->B<=size_B ) && ( ptr_state->C<=size_C );

            // check for the sum of the 3 
}


void init_list(list *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}


void add_at_end(list *ptr_list, const state *ptr_state)
{
	node* temp = (node*)malloc(sizeof(node));
	temp->st = *ptr_state;
	// empty list
	if(ptr_list->head == NULL)
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->head = temp;
		ptr_list->tail = temp;
	}
	// non-empty list
	else
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->tail->next = temp;
		ptr_list->tail = temp;
	}
}

void remove_at_end(list *ptr_list)
{
	// empty list
	if(ptr_list->head == NULL)
	{
		printf("empty list\n");
	}
	// one node list
	else if(ptr_list->head == ptr_list->tail)
	{
		node* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->head = NULL;
		free(temp);
	}
	// multi node list
	else
	{
		node* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}    
}

void disp_list(const list *ptr_list)
{
	node* temp = ptr_list->head;
	while(temp)
	{	
		disp_state(&temp->st);
		temp = temp->next;
	}
}

int is_repeated(const list *ptr_list, const state *ptr_state)
{
	node* temp = ptr_list->head;
	while(temp)
	{	
		if (are_same(&temp->st, ptr_state))
			return 1;
		temp = temp->next;
	}
	return 0;
}
