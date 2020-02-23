/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // check if we're allowed to import string.h

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

        int count;
        char* arr = malloc(5 * sizeof(char *));
        int i;

        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                count = tokenize(fgets(buf, BUFFER_SIZE, stdin), args);

                if (strcmp(args[0],"i") == 0) {
                        if (count == 5) {
                                for (i = 0; i < count - 1; i++) {
                                        *(arr + i) = *(args)[i + 1];
                                }
                                tree_insert(root_ptr, &arr);
                        }

                        fprintf(stderr, "Invalid command.\n");
                }
                else if (strcmp(args[0], "q") == 0) {
                        if (count == 4) {
                                for (int i = 0; i < count - 1; i++) {
                                        *(arr + i) = *(args)[i + 1];
                                }
                                tree_search(root_ptr, &arr);
                        }

                        fprintf(stderr, "Invalid command.\n");
                }
                else if (strcmp(args[0], "p") == 0) {
                        tree_print(root_ptr);
                }
                else
                {
                        fprintf(stderr, "Invalid command.\n");
                }
                                
        }

        return 0;
}
