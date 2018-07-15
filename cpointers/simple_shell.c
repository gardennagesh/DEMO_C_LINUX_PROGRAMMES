/*******************************************

Programme:  basic_shell.c
Programmer: Nagesh Nanjundachari 
Usage:      RUN as   ./a.out ls -ltr


********************************************/

#include<unistd.h>

int main (int argc, char **argv) {
       
        if (!fork()) {
                argv++;
                execvp(argv[0], argv);
        }
}
