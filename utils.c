/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
        // returning 0 for now, so the compiler does not complain
	int count = 0;
        //char *segment;
        char *segment = strtok_r(cmd, DELIMITERS, &cmd);        // first call to strtok_r returns pointer to first segment

        while (segment != NULL) {
                cmd_argv[count] = segment;
                count++;
                segment = strtok_r(cmd, DELIMITERS, &cmd);      // subsequent calls return pointers to following segments
        }

        return count;
}
