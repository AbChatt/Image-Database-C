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

	struct TreeNode *new_node = (struct TreeNode *)malloc(1, sizeof(struct TreeNode));

	new_node->value = value;
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

	p = root;


}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {

	struct TreeNode *p = NULL;
	int level = 0;

	p = root;

	// loop for finding files with these attributes

	while (p->child != NULL) {
		if (strcmp(p->value, values[level]) == 0) {
			p = p->child;
			level++;
		}
		else if (strcmp(p->value, values[level]) > 0) {
			p = p->sibling;
		}
		else if (strcmp(p->value, values[level]) < 0) {
			// values does not exist
			break;
		}
	}

	// loop for printing out files with these attributes
	if (p->child == NULL) {
		while (p->sibling != NULL) {
			printf("%s", p->value);
			p = p->sibling;
		}
	}
	
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
	
}
