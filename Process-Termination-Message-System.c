#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void create_child(int choice)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        // Child process
        printf("\nChild Process Created\n");
        printf("Child PID: %d\n", getpid());

        if (choice == 1)
        {
            printf("Child is performing a normal task...\n");
            sleep(2);

            printf("Child terminating normally.\n");
            exit(10);
        }
        else if (choice == 2)
        {
            printf("Child is performing another task...\n");
            sleep(2);

            printf("Child terminating using SIGTERM.\n");
            raise(SIGTERM);
        }
        else if (choice == 3)
        {
            printf("Child is performing Task 3...\n");
            sleep(2);

            printf("Child terminating normally.\n");
            exit(20);
        }
    }
    else
    {
        // Parent process
        printf("Parent is waiting for child PID %d...\n", pid);

        waitpid(pid, &status, 0);

        printf("\n========== TERMINATION INFORMATION ==========\n");
        printf("Terminated Child PID : %d\n", pid);

        if (WIFEXITED(status))
        {
            printf("Termination Type     : Normal\n");
            printf("Exit Status          : %d\n",
                   WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Termination Type     : Signal\n");
            printf("Signal Number        : %d\n",
                   WTERMSIG(status));
        }

        printf("=============================================\n");
    }
}

int main()
{
    int choice;

    printf("=============================================\n");
    printf("       PROCESS TERMINATION MONITOR\n");
    printf("=============================================\n");

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Create Child - Normal Termination\n");
        printf("2. Create Child - Signal Termination\n");
        printf("3. Create Child - Normal Termination 2\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                create_child(1);
                break;

            case 2:
                create_child(2);
                break;

            case 3:
                create_child(3);
                break;

            case 4:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
