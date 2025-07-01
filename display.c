#include <stdio.h>
#include <stdlib.h>
// #include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 100
#define DEBUG 1

// void err_exit(int var, int fail_val, char* err_msg, int exit_code);

int main(int argc, char *argv[]){
    /**** Debug ****/
    int retval;

    // Create debug_file to write info to when testing the program
    int fd_debug;
    char msg[BUFSIZE];
    char* debug_file = ".info";
    if (DEBUG){
        fd_debug = open(debug_file, O_CREAT|O_WRONLY|O_TRUNC, 0777);
        if (fd_debug == -1) {
            printf("ERROR: Failed to open %s\n", debug_file);
            exit(EXIT_FAILURE);
        }
    }

    /**** File Checking ****/

    // Not proper args
    if (argc < 2) {
        printf("Ussage: ./display file [, char delimiter]\n");
        exit(EXIT_FAILURE);
    }
    
    // TODO: Check for normal file

    // If optional delimiter was give set that as new delimiter
    char delim = ',';
    if (argc > 2) {
        delim = argv[2][0];
        if (DEBUG) {
            int size = sprintf(msg, "Delimiter:\t'%c'\n", delim);
            retval = write(fd_debug, msg, size);
            // If write failed
            if (retval == -1) {
                printf("ERROR: Failed to write %s", debug_file);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Open give file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Failed to open '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /**** Output ****/
    char buf[BUFSIZE];
  
    // Read and Write each character
    int quote_Count = 0;
    while ( (retval = read(fd, buf, 1)) ) {
        if (retval == -1) {
            printf("ERROR: Failed to read '%s'", argv[1]);
            exit(EXIT_FAILURE);
        }

        // Each " in a csv or tsv is a double quote so when you see a delimiter
        // and the quotes are at an odd count you are still inside a cell
        if (buf[0] == '\"') quote_Count++;
        if ( (buf[0] == delim) && ((quote_Count % 2) == 0 )){
            printf("\t");
        }
        printf("%c", buf[0]);
    }

    printf("\n");
    return 0;
}

// void err_exit(int var, int fail_val, char* err_msg, int exit_code){
//     if (var == fail_val) {
//         printf("%s", err_msg);
//         exit(exit_code);
//     }
// }
