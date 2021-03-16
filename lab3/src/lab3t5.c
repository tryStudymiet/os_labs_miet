#include <unistd.h>
#include <stdio.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 3)
        printf("Invlid arguments amount.");

    pid_t pid = fork();
    if(pid == 0){
        printf("sequential_min_maxMF process.\n");
        execv("sequential_min_maxMF.out", argv);
    }

    printf("Waiting...\n");
    wait(NULL);
    return 0;
}