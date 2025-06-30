#include <stdio.h>
#include <stdlib.h>
// #include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1

int main(int argc, char *argv[]){
    /**** File Checking ****/

    if (argc < 2) {
        printf("Ussage: ./display file\n");
        exit(EXIT_FAILURE);
    }
    
    // TODO: Check for normal file
    // TODO: Check for supported file type???? or leavel that onto the user?


    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Failed to open '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /**** Output ****/
    char buf[BUFSIZE];
    int retval;
   
    while ( (retval = read(fd, buf, 1)) ) {
        if (retval == -1) {
            printf("ERROR: Failed to read '%s'", argv[1]);
            exit(EXIT_FAILURE);
        }
        printf("%c", buf[0]);
    }


    return 0;
}
