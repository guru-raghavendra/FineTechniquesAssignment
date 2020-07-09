#include<stdio.h>
#include <stdlib.h>
#include"assignment_4.h"




int insert(FILE *fp,int key)         // to find the position where to insert
{
	tree_t h;
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(tree_t), 1, fp);
	int prev=-1; int pres = h.root;
	node_t pres_node; node_t prev_node;
	while (pres!= -1) //traversing till leaf
	{
	
		prev = pres;
		prev_node = pres_node;  
		if(pres!= -1)         
		{
			fseek(fp, pres, SEEK_SET);
			fread(&pres_node, sizeof(node_t), 1, fp);
			if(pres_node.key==key) //if the key already exists
			{
				return prev;
			}
			else if(pres_node.key>key) //move left
			{
				pres=pres_node.left_offset;
			}
			else                     //move right
			{
				pres=pres_node.right_offset;
			}
			
		}

	}
	return prev;       //returning the the parent node to insert
}




void inorder(FILE *fp, int pres)  // to print inorder
{
	if(pres== -1)
	{
		return;
	}
	node_t pres_node;
	fseek(fp, pres, SEEK_SET);	fread(&pres_node, sizeof(node_t), 1, fp);
	
	inorder(fp,pres_node.left_offset);
	printf("%d ",pres_node.key);
	inorder(fp,pres_node.right_offset);
}




void preorder(FILE *fp, int pres)  // to print preorder
{
	if(pres== -1)
	{
		return;
	}
	node_t pres_node;
	fseek(fp, pres, SEEK_SET);	fread(&pres_node, sizeof(node_t), 1, fp);
	
	printf("%d ",pres_node.key);
	preorder(fp,pres_node.left_offset);
	preorder(fp,pres_node.right_offset);
}







// create a file with the filename and initialize the header with tree_t structure
// if the file already exists, just return the file ptr
FILE* init_tree(const char* filename)
{
	tree_t h;
	FILE* fp = fopen(filename, "r+");
	if(fp == NULL)                   //if the file does not exist create new file
	{
		//printf("empty file\n");
		fp = fopen(filename, "w");
		h.free_head=-1;
		h.root=-1;
		fwrite(&h, sizeof(tree_t), 1, fp);  //creating new file 
		fclose(fp); 
		fp = fopen(filename, "r+");    
	}
	fread(&h, sizeof(tree_t), 1, fp);
	return fp;	

}






// insert the key into the tree in the file
// if the key already exists just return
void insert_key(int key, FILE *fp)
{
	node_t temp_node;
	int temp;
	tree_t h;
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(tree_t), 1, fp);


	

	if(h.free_head == -1)      //no free head 
	{
		fseek(fp, 0, SEEK_END); // seek to the end
		temp = ftell(fp);
	
		
	}
	else                       // free head exists
	{
		temp = h.free_head;
		fseek(fp, temp, SEEK_SET);
		fread(&temp_node, sizeof(node_t), 1, fp);
	
		h.free_head = temp_node.left_offset;   //since only attaching to the left side of the node after deleting 
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(tree_t), 1, fp);
	}

	temp_node.key = key;
	temp_node.left_offset=-1;
	temp_node.right_offset=-1;

	if(h.root == -1)          //tree is empty
	{
		
		h.root=temp;
		temp_node.left_offset=-1;
		temp_node.right_offset=-1;
		fseek(fp, 0, SEEK_SET); fwrite(&h, sizeof(tree_t), 1, fp);
		fseek(fp, temp, SEEK_SET); fwrite(&temp_node, sizeof(node_t), 1, fp);
	}
	else                  //non empty tree
	{
		
		int prev; int pres = h.root;

		prev=insert(fp,key);      //find where to insert
	
		//node_t pres_node;
		node_t prev_node;
		fseek(fp, prev, SEEK_SET);
		fread(&prev_node, sizeof(node_t), 1, fp);
		if(prev_node.key==key)    //key already exists
		{
			return;
		}
		else if (prev_node.key>key) //insert left
		{
			prev_node.left_offset=temp;
		}
		else                       //insert right
		{
			prev_node.right_offset=temp;
		}
		fseek(fp, prev, SEEK_SET); fwrite(&prev_node, sizeof(node_t), 1, fp); // prev is the parent of the key to insert
		
		fseek(fp, temp, SEEK_SET); fwrite(&temp_node, sizeof(node_t), 1, fp); // temp is having the value of key
	}

}


// close the file pointed by fp
void close_tree(FILE *fp)
{
	fclose(fp);
}

// Space separated keys. Last key followed by '\n'
void display_inorder(FILE *fp)
{
	tree_t h;
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(tree_t), 1, fp);
	inorder(fp,h.root); //calls the recursive inorder funtion to print the inorder 
	printf("\n");
	

}

// Space separated keys. Last key followed by '\n'
void display_preorder(FILE *fp)
{
	tree_t h;
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(tree_t), 1, fp);
	preorder(fp,h.root); //calls the recursive preorder funtion to print the preorder 
	printf("\n");
}



// delete the key from the tree in the file
// the key may or may not existsss
void delete_key(int key, FILE *fp)
{
	tree_t h;	
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(tree_t), 1, fp);
	if(h.root==-1)  //empty tree
	{
		return;
	}
		
	int prev=-1; int pres = h.root;
	node_t pres_node; node_t prev_node;
	fseek(fp, pres, SEEK_SET);
	fread(&pres_node, sizeof(node_t), 1, fp);
	while (pres!= -1 && pres_node.key!=key) //pres is the node to delete  and traversing till the end 
	{
		
		prev = pres;
		prev_node = pres_node;  
		if(pres!= -1)        
		{
			
			if(pres_node.key==key)
			{
				break;
			}
			else if(pres_node.key>key) //move left
			{
				pres=pres_node.left_offset;
			}
			else                     //move right
			{
				
				pres=pres_node.right_offset;
			}
			fseek(fp, pres, SEEK_SET);
			fread(&pres_node, sizeof(node_t), 1, fp);
		}
	}
	if(pres != -1  && pres_node.key==key ) // found key
	{
		if(prev==-1)//delete root
		{
			
			
			if(pres_node.left_offset==-1) //only right node or only root
			{
				
				h.root=pres_node.right_offset;
				
				pres_node.left_offset=h.free_head;  //adding the deleted node to free head
				h.free_head=pres;

				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);

                fseek(fp, 0, SEEK_SET);
			    fwrite(&h, sizeof(tree_t), 1, fp);
			}
			else if(pres_node.right_offset==-1)//only left node 
			{
				
				h.root=pres_node.left_offset;
				pres_node.left_offset=h.free_head;  //adding the deleted node to free head
				h.free_head=pres;

				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);

                fseek(fp, 0, SEEK_SET);
			    fwrite(&h, sizeof(tree_t), 1, fp);
			}
			else //has both left and right childs
			{
				
				int temp=pres_node.right_offset;
				//read the right offset and then then delete the inorder successor;

				node_t temp_node;
				fseek(fp, temp , SEEK_SET);
				fread(&temp_node, sizeof(node_t), 1, fp);
				while(temp_node.left_offset!=-1)
				{
					temp=temp_node.left_offset;
					fseek(fp, temp , SEEK_SET);
					fread(&temp_node, sizeof(node_t), 1, fp);
				}

				delete_key(temp_node.key,fp); //delete the inorder successor of the key and replacing key with inorder successor

				fseek(fp, pres , SEEK_SET);
				fread(&pres_node, sizeof(node_t), 1, fp);
				pres_node.key=temp_node.key;//replacing key with inorder successor
				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);
				
				
			}
			
		}
		else //deleting other than root
		{

			if(pres_node.left_offset==-1) //only right node or leaf node
			{
				
				if(prev_node.key > pres_node.key) //pres is on the left of prev
				{
					prev_node.left_offset=pres_node.right_offset;
					
				}
				else   //pres is on the right of prev
				{
					prev_node.right_offset=pres_node.right_offset;
					
				}
				fseek(fp, prev , SEEK_SET);
				fwrite(&prev_node, sizeof(node_t), 1, fp);
				
				pres_node.left_offset=h.free_head; //adding the deleted node to free head
				h.free_head=pres;

				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);


				fseek(fp, 0 , SEEK_SET);
				fwrite(&h, sizeof(tree_t), 1, fp);

			}
			else if(pres_node.right_offset==-1) //only left node
			{
				
				if(prev_node.key > pres_node.key) //pres is on the left of prev
				{
					
					prev_node.left_offset=pres_node.left_offset;
				}
				else   //pres is on the right of prev
				{
					
					prev_node.right_offset=pres_node.left_offset;
				}
				fseek(fp, prev , SEEK_SET);
				fwrite(&prev_node, sizeof(node_t), 1, fp);

				
				pres_node.left_offset=h.free_head;  //adding the deleted node to free head
				h.free_head=pres;

				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);

				fseek(fp, 0 , SEEK_SET);
				fwrite(&h, sizeof(tree_t), 1, fp);

			}
			else //has both left and right childs
			{
				
		
				int temp=pres_node.right_offset;
				//read the right offset and then then delete the inorder succssor;

				node_t temp_node;
				fseek(fp, temp , SEEK_SET);
				fread(&temp_node, sizeof(node_t), 1, fp);
				while(temp_node.left_offset!=-1)
				{
					temp=temp_node.left_offset;
					fseek(fp, temp , SEEK_SET);
					fread(&temp_node, sizeof(node_t), 1, fp);
				}
				
				delete_key(temp_node.key,fp);  //delete the inorder successor of the key and replacing key with inorder successor
				fseek(fp, pres , SEEK_SET);
				fread(&pres_node, sizeof(node_t), 1, fp);
				pres_node.key=temp_node.key; //replacing key with inorder successor
				fseek(fp, pres , SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);
				
				
			}
		}	
	}
	
}
