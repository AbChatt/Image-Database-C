/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>

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
        FILE *file;
        char arr[5];

        while (fgets(buf, BUFFER_SIZE, stdin) != EOF) {
                count = tokenize(fgets(buf, BUFFER_SIZE, stdin), args);

                if (args[0] == 'i') {
                        if (strlen(args) == 5) {
                                arr = {args[1], args[2], args[3], args[4], '\0'};
                                if (!(args[1].isdigit())) {
                                        if (!(args[2].isdigit())) {
                                                if (!(args[3].isdigit())) {
                                                        if (file = fopen(args[4], "r") {
                                                                tree_insert(root_ptr, arr);
                                                        }
                                                }
                                        }
                                }
                        }

                        print("Invalid command.");
                }
                else if (args[0] == 'q') {
                        if (strlen(args) == 4) {
                                arr = {args[1], args[2], args[3], '\0'};
                                if (!(args[1].isdigit())) {
                                        if (!(args[2].isdigit())) {
                                                if (!(args[3].isdigit())) {
                                                        tree_search(root_ptr, arr);
                                                }
                                        }
                                }
                        }

                        print("Invalid command.");
                }
                else if (args[0] == 'p') {
                        tree_print(root_ptr);
                }
                else
                {
                        print("Invalid command.");
                }
                                
        }

        return 0;
}
