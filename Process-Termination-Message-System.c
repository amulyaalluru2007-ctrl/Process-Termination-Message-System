#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int pid[3];
    int status;
    int completed = 0;

    printf("\n");
    printf("====================================================\n");
    printf("          PROCESS TERMINATION MONITOR\n");
    printf("====================================================\n");

    // Create 3 child processes
    for(int i = 0; i < 3; i++)
    {
    pid[i] = fork();
    if(pid[i] < 0)
    {
    printf("Fork failed\n");
    exit(1);
    }
    if(pid[i] == 0)
    {
    if(i == 0)
    {
    // Child 1
    sleep(2);
    exit(0);
    }

    else if(i == 1)
    {
     // Child 2
    sleep(4);
    exit(5);
    }

    else
    {
    // Child 3
    sleep(3);
    kill(getpid(), SIGTERM);
    }
    }
    }

    // Display all created children
    printf("\n");
    printf("----------------------------------------------------\n");
    printf("             CHILD PROCESSES CREATED\n");
    printf("----------------------------------------------------\n");

    printf("Child 1  | PID = %d | Task = Data Processing\n", pid[0]);
    printf("Child 2  | PID = %d | Task = File Processing\n", pid[1]);
    printf("Child 3  | PID = %d | Task = Network Monitoring\n", pid[2]);

    // Parent monitoring section
    printf("\n");
    printf("====================================================\n");
    printf("             PARENT PROCESS MONITORING\n");
    printf("====================================================\n");

    while(completed < 3)
    {
    int child_pid = wait(&status);

    printf("\n");
    printf("****************************************************\n");
    printf("              TERMINATION REPORT\n");
    printf("****************************************************\n");

    // Identify which child terminated
    if(child_pid == pid[0])
    {
    printf("Child Number         : Child 1\n");
     printf("Task                 : Data Processing\n");
     }

     else if(child_pid == pid[1])
    {
    printf("Child Number         : Child 2\n");
    printf("Task                 : File Processing\n");
     }
    else if(child_pid == pid[2])
    {
    printf("Child Number         : Child 3\n");
    printf("Task                 : Network Monitoring\n");
    }

    printf("Process PID          : %d\n", child_pid);
    if(WIFEXITED(status))
    {
    printf("Termination Type     : Normal\n");
    printf("Exit Status          : %d\n",WEXITSTATUS(status));
    if(WEXITSTATUS(status) == 0)
    {
    printf("Result               : Successful Completion\n");
    }
    else
    {
    printf("Result               : Completed with Status %d\n",WEXITSTATUS(status));
    }
    }
    else if(WIFSIGNALED(status))
    {
    printf("Termination Type     : Signal\n");
    printf("Signal Number        : %d\n",WTERMSIG(status));
    if(WTERMSIG(status) == SIGTERM)
    {
    printf("Signal               : SIGTERM\n");
     }
     }

    printf("****************************************************\n");

    completed++;
    }

    printf("\n");
    printf("====================================================\n");
    printf("              FINAL MONITORING REPORT\n");
    printf("====================================================\n");
    printf("All child processes have been collected.\n");
    printf("Termination status successfully received.\n");
    printf("Zombie processes prevented using wait().\n");
    printf("====================================================\n");

    return 0;
}