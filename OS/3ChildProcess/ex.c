#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int execLeaf()
{
    pid_t pid;
    char file_name[32];
    FILE *fp;

    pid = getpid();

    sprintf(file_name, "%d.txt", pid); // child process pid

    fp = fopen(file_name, "w");
    
    srand(pid);
    fprintf(file_name, "%d", (1+rand()%100));

    fclose(fp);

    return 0;
}


int execParent(pid_t leftPID, pid_t rightPID)
{
    wait(NULL);

    int leftRandom, rightRandom;
    pid_t parentPID;
    char left_file_name[32], right_file_name[32], parent_file_name[32];
    FILE *lfp, *rfp, *pfp;

    parentPID = getpid();

    sprintf(left_file_name, "%d.txt", leftPID);
    sprintf(right_file_name, "%d.txt", rightPID);
    sprintf(parent_file_name, "%d.txt", parentPID);

    lfp = fopen(left_file_name, "r");
    rfp = fopen(right_file_name, "r");
    pfp = fopen(parent_file_name, "w");

    fscanf(lfp, "%d", &leftRandom);
    fscanf(rfp, "%d", &rightRandom);

    fprintf(pfp, "%d", leftRandom+rightRandom);


    fclose(lfp);
    fclose(rfp);
    fclose(pfp);

    return 0;
}


int createProcessTree(int height)
{
    if (height == 0) {
        execLeaf();
        return;
    }

    pid_t leftPID, rightPID;

    leftPID = fork();
    if (leftPID > 0) {
        rightPID = fork();
        if (rightPID > 0) {
            // parent process
            wait(NULL);
            printf("parent pid: %d\tleft pid: %d\tright pid: %d\n", getpid(), leftPID, rightPID);
            fflush(stdout);
            execParent(leftPID, rightPID);
        } else if (rightPID == 0) {
            createProcessTree(--height);
        }
    } else if (leftPID == 0) {
        createProcessTree(--height);
    }

    return 0;
}

int main()
{
    createProcessTree(3);

    return 0;
}
