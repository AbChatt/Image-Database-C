/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>     // not allowed to import string.h

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

        // Add your code below:

        int count = 0;

        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                count = tokenize(buf, args);    // fgets populates buf with the next line from the stream during the while loop condition check

                if (*(*(args)) == 'i') {        // comparing first string to i
                        if (count == INPUT_ARG_MAX_NUM) {
                                tree_insert(root_ptr, args);    // not compiling as before with ./name arg 1 so args does not include ./name
                        }
                        else
                        {
                                fprintf(stderr, "Invalid command.\n");
                        }
                }
                else if (*(*(args)) == 'q') {
                        if (count == INPUT_ARG_MAX_NUM - 1) {
                                tree_search(root_ptr, args);
                        }
                        else
                        {
                                fprintf(stderr, "Invalid command.\n");
                        }
                }
                else if (*(*(args)) == 'p') {
                        if (count == 1) {
                                tree_print(root_ptr);
                        }
                        else
                        {
                                fprintf(stderr, "Invalid command.\n");
                        }
                }
                else
                {
                        fprintf(stderr, "Invalid command.\n");
                }
                                
        }

        return 0;
}
