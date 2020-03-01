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
	new_node->value = malloc(BUFFER_SIZE * sizeof(char));		// need space to store value
	
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
	struct TreeNode *q = NULL;

	int i = 1;
	int current_level = i;
	int p_level = 0;
	int q_level = 0;

	// insertion code for when tree is empty

	if (root->child == NULL) {
		for (int j = 1; j < INPUT_ARG_MAX_NUM; j++) {
		new_node = allocate_node(*(values + j));
		root->child = new_node;
		root = root->child;
		}

		return;
	}

	q = root->child;		// skip root node containing empty string as value
	q_level++;

	// only handles insertion along a level somewhere in the middle, not at start or end

	while (i < INPUT_ARG_MAX_NUM) {
		while (q != NULL) {

			// haven't found spot to insert into, keep traversing along level

			if (strcmp(q->value, *(values + i)) < 0) {
				p = q;
				p_level = q_level;
				q = q->sibling;
			}

			// handles insertion at starting of level when other nodes are already present on level

			else if (strcmp(q->value, *(values + i)) > 0 && p_level < q_level) {
				if (p == NULL) {
					p = root;
				}
				new_node = allocate_node(*(values + i));
				new_node->sibling = q;
				p->child = new_node;
				q = new_node->child;
				p = new_node;
				p_level = q_level;
				q_level++;
				i++;
			}

			// insertion spot is somewhere in the middle of the level
			else if (strcmp(q->value, *(values + i)) > 0 && p_level == q_level) {
				if (strcmp(q->value, *(values + i)) > 0 && strcmp(p->value, *(values + i)) < 0) {
					new_node = allocate_node(*(values) + i);
					new_node->sibling = q;
					p->sibling = new_node;
					q = new_node->child;
					q_level++;
					i++;
				}
			}

			// node to be inserted already exists in database

			else if (strcmp(q->value, *(values + i)) == 0) {
				p = q;
				p_level = q_level;
				q = q->child;
				q_level++;
				i++;
			}
		}

		// handles insertion at ending of level / if level is empty
		
		if (i == current_level) {

			// case 1: traversed all nodes in this level i.e. adding a new ending node

			if (p_level == q_level) {
				new_node = allocate_node(*(values + i));
				p->sibling = new_node;
				q = new_node->child;
				p = new_node;
				i++;
				q_level++;
			}

			// case 2: no nodes in this level, i.e. adding a new starting node

			else if (p_level < q_level) {
				new_node = allocate_node(*(values + i));
				p->child = new_node;
				q = new_node->child;
				p = new_node;
				i++;
				p_level = q_level;
				q_level++;
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
			// value does not exist
			break;
		}
		else if (strcmp(root->value, values[level]) < 0) {
			if (root->sibling == NULL) {	// if there are no more siblings and current node is not what we are looking for
				printf("(NULL)\n");
				return;
			}
			root = root->sibling;
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
		printf("(NULL)\n");
	}

}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
	struct TreeNode *level_1 = NULL;
	struct TreeNode *level_2 = NULL;
	struct TreeNode *level_3 = NULL;
	struct TreeNode *level_4 = NULL;

	if (tree->child == NULL) {
		printf("(NULL)\n");
		return;
	}

	level_1 = tree->child;
	level_2 = level_1->child;
	level_3 = level_2->child;
	level_4 = level_3->child;
		
	while (level_1 != NULL) {
		while (level_2 != NULL) {
			while (level_3 != NULL) {
				while (level_4 != NULL) {
					printf("%s %s %s %s\n", level_1->value, level_2->value, level_3->value, level_4->value);
					level_4 = level_4->sibling;
				}

				level_3 = level_3->sibling;

				if (level_3 != NULL) {
					level_4 = level_3->child;
				}
			}

			level_2 = level_2->sibling;
			
			if (level_2 != NULL) {
				level_3 = level_2->child;

				if (level_3 != NULL) {
					level_4 = level_3->child;
				}
			}
		}

		level_1 = level_1->sibling;

		if (level_1 != NULL) {
			level_2 = level_1->child;

			if (level_2 != NULL) {
				level_3 = level_2->child;

				if (level_3 != NULL) {
					level_4 = level_3->child;
				}
			}
		}
		
	}
	
}
