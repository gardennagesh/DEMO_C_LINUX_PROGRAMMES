/*******************************************

Programme:  This is not how shell works or a demo for shell. But, shell calls fork plus exec.
Programme: This programme mainly to demo execvp.
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
