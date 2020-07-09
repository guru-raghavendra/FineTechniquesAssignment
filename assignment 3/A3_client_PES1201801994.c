#include <stdio.h>
#include <stdlib.h>
#include "A3_header_PES1201801994.h"


#define DEBUG 1
int main()
{
	int total=0;
	state start;
	state goal;
	void (*move[])(const state*, state*,const int, const int , const int) = {
		moveA2B,
        moveA2C,
        moveB2A,
        moveB2C,
        moveC2A,
        moveC2B
	};
    int size_A,size_B,size_C,s_A,s_B,s_C,f_A,f_B,f_C;
    scanf("%d",&size_A);
	//printf("%d size of A\n",size_A);
	scanf("%d",&size_B);
	//printf("%d size of B\n",size_B);
	scanf("%d",&size_C);
	//printf("%d size of C\n",size_C);
	//printf("line22\n");

    scanf("%d",&s_A);
	//printf("%d sOURCE A\n",s_A);
	scanf("%d",&s_B);
	//printf("%d sOURCE b\n",s_B);
	scanf("%d",&s_C);
	//printf("%d sOURCE c\n",s_C);
	//printf("line24\n");

    scanf("%d",&f_A);
	//printf("%d FINAL A\n",f_A);
	scanf("%d",&f_B);
	//printf("%d FINAL B\n",f_B);
	scanf("%d",&f_C);
	//printf("%d FINAL C\n",f_C);
	//printf("line26\n");

//int size_A=8,size_B=5,size_C=3,s_A=8,s_B=0,s_C=0,f_A=4,f_B=4,f_C=0;
//int size_A=10,size_B=7,size_C=3,s_A=10,s_B=0,s_C=0,f_A=5,f_B=5,f_C=0;
//int size_A=12,size_B=8,size_C=5,s_A=12,s_B=0,s_C=0,f_A=6,f_B=6,f_C=0;

	set_state(&start, s_A,s_B,s_C);
	//printf("line30\n");
	set_state(&goal, f_A,f_B,f_C);
	list mylist;
	init_list(&mylist);
	add_at_end(&mylist, &start);
	int is_soln = 0;
	state* temp;
	temp = (state*)malloc(sizeof(state));
	int fn_index;
	while(mylist.tail!=NULL)
	{
		fn_index = mylist.tail->st.fn_index;
		/*if(DEBUG)
		{
			printf("trying transition %d on\n", fn_index);
			disp_state(&mylist.tail->st);
			
		}	*/
		move[fn_index](&mylist.tail->st, temp , size_A,size_B,size_C);
		if(is_valid(temp,size_A,size_B,size_C) && ! is_repeated(&mylist, temp))
		{
			/*if(DEBUG)
			{
				printf("adding : ");
				disp_state(temp);
			}*/
			add_at_end(&mylist, temp);
			is_soln = are_same(temp, &goal);
			if(is_soln)
			{
				disp_list(&mylist);
				//remove_at_end(&mylist);
    			while(mylist.tail && ++mylist.tail->st.fn_index == 6)
    			{
    				remove_at_end(&mylist);
    			}
    			total += 1;
    			printf("\n");
			}
		}
		else
		{
			// not checking for all solutions
			while(mylist.tail && ++mylist.tail->st.fn_index == 6)
    		{
    			remove_at_end(&mylist);
			}
		}
	}
	printf("%d", total);		// total number of solutions
}
