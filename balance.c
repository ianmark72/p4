#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "tree.h"
#include "structs.h"

int checkSide(node* child, node* parent) {
	//0 = left, 1 = right, -1 = error
	int returnValue = -1;
	
	if(child == parent->left) {
		returnValue = 0;
	}else if(child == parent->right) {
		returnValue = 1;
	}

	return returnValue;
}

void leftleftcase(node* parent, node* grandparent) {
	if(grandparent->parent != NULL) {
		parent->parent = grandparent->parent;
	}else{
		parent->parent = NULL;
	}
	parent->right = grandparent;
        parent->color = 0;

	grandparent->parent = parent;
	grandparent->left = NULL;
	grandparent->color = 1;
}

void leftrightcase(node* child, node* parent, node* grandparent) {
	grandparent->left = child;
	child->parent = grandparent;

	parent->right = NULL;
	parent->parent = child;

	leftleftcase(child, grandparent);
}

void rightrightcase(node* parent, node* grandparent) {
	if(grandparent->parent != NULL) {
                parent->parent = grandparent->parent;
        }else{
                parent->parent = NULL;
        }
	parent->left = grandparent;
        parent->color = 0;

        grandparent->parent = parent;
	grandparent->right = NULL;
        grandparent->color = 1;
}

void rightleftcase(node* child, node* parent, node* grandparent) {
	grandparent->right = child;
        child->parent = grandparent;

        parent->left = NULL;
        parent->parent = child;

        rightrightcase(child, grandparent);
}

void balanceTree(node* rootNode) {
	//Path 0 = left-left, 1 = left-right, 2 = right-left, 3 = right-right 

    //  Case : A 
    //coloring needed

        /* Case : 1 
               The uncle of pt is also red 
               Only Recoloring required */

        /*  Case : 2 
                The uncle of pt is also red 
                Only Recoloring required */

        

    /* Case : B 
           //Rotation needed

        
        /* Case : 2 
                   pt is right child of its parent 
                   Left-rotation required */
        
        /* Case : 3 
                   pt is left child of its parent 
                   Right-rotation required */
        /* Case : 2 
                   pt is left child of its parent 
                   Right-rotation required */
        
         /* Case : 3 
                   pt is right child of its parent 
                   Left-rotation required */

}