/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
struct TreeNode *allocate_node(const char *value) {

	struct TreeNode *new_node = malloc(1 * sizeof(struct TreeNode));
	new_node->value = malloc(INPUT_ARG_MAX_NUM * sizeof(char));		// need space to store value
	
	strcpy(new_node->value, value);
	new_node->child = NULL;
	new_node->sibling = NULL;

	return new_node;
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {

	struct TreeNode *p = NULL;
	struct TreeNode *new_node = NULL;

	int i = 1;
	int current_level = i;
	int p_level = 0;
	int root_level = 0;

	// insertion code for when tree is empty

	if (root->child == NULL) {
		for (int j = 1; j < 5; j++) {
		new_node = allocate_node(*(values + j));
		root->child = new_node;
		root = root->child;
		}

		return;
	}

	root = root->child;		// skip root node containing empty string as value
	root_level++;

	// only handles insertion along a level somewhere in the middle, not at start or end

	while (i < 5) {
		while (root != NULL) {

			// haven't found spot to insert into, keep traversing along level

			if (strcmp(root->value, *(values + i)) < 0) {
				p = root;
				p_level = root_level;
				root = root->sibling;
			}

			// insertion spot is somewhere in the middle of the level

			else if (strcmp(root->value, *(values + i)) > 0 && strcmp(p->value, *(values + i)) < 0) {
				new_node = allocate_node(*(values) + i);
				new_node->sibling = root;
				p->sibling = new_node;
				root = new_node->child;
				root_level++;
				i++;
			}

			// node to be inserted already exists in database

			else if (strcmp(root->value, *(values + i)) == 0) {
				p = root;
				p_level = root_level;
				root = root->child;
				root_level++;
				i++;
			}

			// handles insertion at starting of level when other nodes are already present on level

			else if (strcmp(root->value, *(values + i)) > 0) {
				new_node = allocate_node(*(values + i));
				new_node->sibling = root;
				p->child = new_node;
				root = new_node->child;
				p = new_node;
				p_level = root_level;
				root_level++;
				i++;
			}
		}

		// handles insertion at ending of level / if level is empty
		
		if (i == current_level) {

			// case 1: traversed all nodes in this level i.e. adding a new ending node

			if (p_level == root_level) {		// this condition doesn't work - need a new one
				new_node = allocate_node(*(values + i));
				p->sibling = new_node;
				root = new_node->child;
				p = new_node;
				i++;
				root_level++;
			}

			// case 2: no nodes in this level, i.e. adding a new starting node

			else if (p_level < root_level) {
				new_node = allocate_node(*(values + i));
				p->child = new_node;
				root = new_node->child;
				p = new_node;
				i++;
				p_level = root_level;
				root_level++;
			}
		}

		current_level++;
	}

}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {

	//struct TreeNode *p = NULL;
	int level = 1;

	root = root->child;

	// loop for finding files with these attributes

	while (root->child != NULL) {
		if (strcmp(root->value, values[level]) == 0) {
			root = root->child;
			level++;
		}
		else if (strcmp(root->value, values[level]) > 0) {
			root = root->sibling;
		}
		else if (strcmp(root->value, values[level]) < 0) {
			// values does not exist
			break;
		}
	}

	// loop for printing out files with these attributes
	if (root->child == NULL) {
		while (root != NULL) {
			printf("%s ", root->value);
			root = root->sibling;
		}

		printf("\n");
	}
	else
	{
		printf("(NULL)\n\n");
	}
	
	
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {

}
