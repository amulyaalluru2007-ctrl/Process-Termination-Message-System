#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_EVENTS 5

typedef struct
{
    int event_no;
    pid_t pid;
    pid_t parent_pid;

    int termination_type;
    int exit_status;
    int signal_no;

    int executed;
    int reaped;
} EventReport;

EventReport reports[MAX_EVENTS];


/* Display event name */
void display_event_name(int event)
{
    switch (event)
    {
        case 1:
            printf("Data Processing Service");
            break;

        case 2:
            printf("File Backup Service");
            break;

        case 3:
            printf("Network Service Failure");
            break;

        case 4:
            printf("Database Service");
            break;

        case 5:
            printf("Security Monitoring Service");
            break;
    }
}


/* Initialize report data */
void initialize_reports()
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        reports[i].event_no = i + 1;
        reports[i].pid = 0;
        reports[i].parent_pid = 0;
        reports[i].termination_type = 0;
        reports[i].exit_status = 0;
        reports[i].signal_no = 0;
        reports[i].executed = 0;
        reports[i].reaped = 0;
    }
}


/* Execute selected process event */
void execute_event(int event)
{
    pid_t pid;
    pid_t terminated_pid;
    int status;

    printf("\n");
    printf("============================================================\n");
    printf("              EVENT %d : ", event);
    display_event_name(event);
    printf("\n");
    printf("============================================================\n");

    printf("\n");
    printf("PROCESS CREATION\n");
    printf("------------------------------------------------------------\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }


    /* Child process */
    if (pid == 0)
    {
        printf("Child process created.\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("\n");
        printf("TASK EXECUTION\n");
        printf("------------------------------------------------------------\n");


        /* Event 1 */
        if (event == 1)
        {
            printf("Initializing data processing...\n");
            sleep(1);

            printf("Reading records...\n");
            sleep(1);

            printf("Processing 1000 records...\n");
            sleep(1);

            printf("Data processing completed.\n");

            exit(10);
        }


        /* Event 2 */
        else if (event == 2)
        {
            printf("Initializing backup service...\n");
            sleep(1);

            printf("Scanning files...\n");
            sleep(1);

            printf("Creating backup...\n");
            sleep(1);

            printf("Backup completed successfully.\n");

            exit(20);
        }


        /* Event 3 */
        else if (event == 3)
        {
            printf("Starting network service...\n");
            sleep(1);

            printf("Establishing connection...\n");
            sleep(1);

            printf("Processing network requests...\n");
            sleep(1);

            printf("\n");
            printf("[!] Simulating network service failure...\n");

            raise(SIGTERM);
        }


        /* Event 4 */
        else if (event == 4)
        {
            printf("Starting database service...\n");
            sleep(1);

            printf("Connecting to database...\n");
            sleep(1);

            printf("Executing database operation...\n");
            sleep(1);

            printf("Updating records...\n");
            sleep(1);

            printf("Database operation completed.\n");

            exit(40);
        }


        /* Event 5 */
        else if (event == 5)
        {
            printf("Starting security monitor...\n");
            sleep(1);

            printf("Scanning active processes...\n");
            sleep(1);

            printf("Checking system activity...\n");
            sleep(1);

            printf("Security scan completed.\n");

            exit(50);
        }

        exit(0);
    }


    /* Parent process */
    printf("Child PID created : %d\n", pid);
    printf("Parent PID        : %d\n", getpid());

    printf("\n");
    printf("PARENT MONITOR\n");
    printf("------------------------------------------------------------\n");
    printf("Waiting for child process termination...\n");


    /* Parent waits for child */
    terminated_pid = waitpid(pid, &status, 0);

    if (terminated_pid == -1)
    {
        perror("waitpid failed");
        return;
    }


    /* Store process information */
    reports[event - 1].event_no = event;
    reports[event - 1].pid = pid;
    reports[event - 1].parent_pid = getpid();
    reports[event - 1].executed = 1;
    reports[event - 1].reaped = 1;


    printf("\n");
    printf("============================================================\n");
    printf("                 TERMINATION ANALYSIS\n");
    printf("============================================================\n");


    /* Normal termination */
    if (WIFEXITED(status))
    {
        reports[event - 1].termination_type = 1;

        reports[event - 1].exit_status =
            WEXITSTATUS(status);

        printf("Termination Type : NORMAL\n");
        printf("Exit Status      : %d\n",
               reports[event - 1].exit_status);

        printf("\n");
        printf("WIFEXITED()      : TRUE\n");
        printf("WEXITSTATUS()    : %d\n",
               reports[event - 1].exit_status);
    }


    /* Signal termination */
    else if (WIFSIGNALED(status))
    {
        reports[event - 1].termination_type = 2;

        reports[event - 1].signal_no =
            WTERMSIG(status);

        printf("Termination Type : ABNORMAL\n");
        printf("Signal           : SIGTERM\n");
        printf("Signal Number    : %d\n",
               reports[event - 1].signal_no);

        printf("\n");
        printf("WIFSIGNALED()    : TRUE\n");
        printf("WTERMSIG()       : %d\n",
               reports[event - 1].signal_no);
    }


    /* Process cleanup */
    printf("\n");
    printf("PROCESS CLEANUP\n");
    printf("------------------------------------------------------------\n");

    printf("waitpid()        : SUCCESS\n");
    printf("Process Reaped   : YES\n");
    printf("Zombie Process   : NO\n");


    /* Final result */
    printf("\n");
    printf("EVENT RESULT\n");
    printf("------------------------------------------------------------\n");

    if (reports[event - 1].termination_type == 1)
    {
        printf("[SUCCESS] ");
        display_event_name(event);
        printf(" completed normally.\n");
    }
    else
    {
        printf("[ALERT] ");
        display_event_name(event);
        printf(" terminated by SIGTERM.\n");
    }

    printf("[SUCCESS] Parent collected the termination status.\n");
}


/* Display latest event */
void latest_report()
{
    int found = -1;
    int i;

    for (i = MAX_EVENTS - 1; i >= 0; i--)
    {
        if (reports[i].executed)
        {
            found = i;
            break;
        }
    }


    if (found == -1)
    {
        printf("\nNo events have been executed yet.\n");
        return;
    }


    printf("\n");
    printf("============================================================\n");
    printf("                  LATEST EVENT REPORT\n");
    printf("============================================================\n");

    printf("Event           : %d\n",
           reports[found].event_no);

    printf("Service         : ");
    display_event_name(reports[found].event_no);
    printf("\n");

    printf("Child PID       : %d\n",
           reports[found].pid);

    printf("Parent PID      : %d\n",
           reports[found].parent_pid);


    if (reports[found].termination_type == 1)
    {
        printf("Termination     : NORMAL\n");

        printf("Exit Status     : %d\n",
               reports[found].exit_status);
    }
    else
    {
        printf("Termination     : ABNORMAL\n");

        printf("Signal          : SIGTERM\n");

        printf("Signal Number   : %d\n",
               reports[found].signal_no);
    }

    printf("Process Reaped  : YES\n");
    printf("Zombie Process  : NO\n");

    printf("============================================================\n");
}


/* Display all executed events */
void all_events_report()
{
    int count = 0;
    int i;

    printf("\n");
    printf("============================================================\n");
    printf("                   EVENT HISTORY\n");
    printf("============================================================\n");


    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (reports[i].executed)
        {
            count++;

            printf("\nEvent %d : ",
                   reports[i].event_no);

            display_event_name(reports[i].event_no);

            printf("\n");

            printf("PID          : %d\n",
                   reports[i].pid);


            if (reports[i].termination_type == 1)
            {
                printf("Result       : NORMAL\n");

                printf("Exit Code    : %d\n",
                       reports[i].exit_status);
            }
            else
            {
                printf("Result       : SIGNAL\n");

                printf("Signal       : SIGTERM (%d)\n",
                       reports[i].signal_no);
            }

            printf("Reaped       : YES\n");
        }
    }


    if (count == 0)
    {
        printf("\nNo events have been executed yet.\n");
    }

    printf("\n============================================================\n");
}


/* Display process statistics */
void process_statistics()
{
    int executed = 0;
    int normal = 0;
    int abnormal = 0;
    int reaped = 0;

    int i;


    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (reports[i].executed)
        {
            executed++;

            if (reports[i].termination_type == 1)
                normal++;

            else if (reports[i].termination_type == 2)
                abnormal++;


            if (reports[i].reaped)
                reaped++;
        }
    }


    printf("\n");
    printf("============================================================\n");
    printf("                  PROCESS STATISTICS\n");
    printf("============================================================\n");

    printf("Events Executed       : %d\n", executed);
    printf("Normal Terminations   : %d\n", normal);
    printf("Signal Terminations   : %d\n", abnormal);
    printf("Processes Reaped      : %d\n", reaped);
    printf("Zombie Processes      : 0\n");

    printf("\n");


    if (executed == 0)
        printf("Monitoring Status     : READY\n");
    else
        printf("Monitoring Status     : ACTIVE\n");

    printf("============================================================\n");
}


/* Termination report menu */
void reports_menu()
{
    int choice;


    while (1)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                  TERMINATION REPORT CENTER\n");
        printf("============================================================\n");

        printf("1. Latest Event Report\n");
        printf("2. All Executed Events\n");
        printf("3. Process Statistics\n");
        printf("4. Back to Main Menu\n");

        printf("------------------------------------------------------------\n");
        printf("Enter choice: ");

        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                latest_report();
                break;

            case 2:
                all_events_report();
                break;

            case 3:
                process_statistics();
                break;

            case 4:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* Process event menu */
void event_menu()
{
    int choice;


    while (1)
    {
        printf("\n");
        printf("============================================================\n");
        printf("                  PROCESS EVENT SIMULATOR\n");
        printf("============================================================\n");

        printf("1. Data Processing Service\n");
        printf("2. File Backup Service\n");
        printf("3. Network Service Failure\n");
        printf("4. Database Service\n");
        printf("5. Security Monitoring Service\n");
        printf("6. Back to Main Menu\n");

        printf("------------------------------------------------------------\n");
        printf("Select Event: ");

        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                execute_event(choice);
                break;

            case 6:
                return;

            default:
                printf("\nInvalid choice.\n");
        }
    }
}


/* Main function */
int main()
{
    int choice;


    initialize_reports();


    printf("\n");
    printf("============================================================\n");
    printf("             PROCESS TERMINATION COMMAND CENTER\n");
    printf("============================================================\n");

    printf("Operating System Process Monitoring Project\n");
    printf("Parent Monitor : ACTIVE\n");


    while (1)
    {
        printf("\n");

        printf("╔════════════════════════════════════════════════════════════╗\n");
        printf("║                       MAIN MENU                           ║\n");
        printf("╠════════════════════════════════════════════════════════════╣\n");
        printf("║  1. Process Event Simulator                               ║\n");
        printf("║  2. Termination Report Center                             ║\n");
        printf("║  3. Exit                                                  ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");

        printf("Enter choice: ");

        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                event_menu();
                break;

            case 2:
                reports_menu();
                break;

            case 3:
                printf("\n");
                printf("Shutting down Process Termination Command Center...\n");
                printf("Program terminated successfully.\n");

                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }


    return 0;
}
