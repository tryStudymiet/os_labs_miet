#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t child_pid = fork();
    //If this process is parent.
    if (child_pid > 0){
        sleep(60);
    }
    else{
        //It child.
        exit(0);
    }

    return 0;
}