#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void security_monitoring_service()
{
    DIR *directory;

    struct dirent *entry;

    FILE *report;

    FILE *process_file;

    char process_path[256];

    char process_name[256];

    int process_count = 0;

    int pid_number;


    printf("\n");
    printf("SECURITY MONITORING SERVICE\n");
    printf("--------------------------------------------\n");


    /*
     * Open Linux /proc filesystem
     */

    directory = opendir("/proc");

    if (directory == NULL)
    {
        perror("Unable to open /proc");
        exit(51);
    }


    printf(
        "Scanning active processes...\n"
    );


    /*
     * Count actual running processes
     */

    while ((entry = readdir(directory)) != NULL)
    {
        if (sscanf(
                entry->d_name,
                "%d",
                &pid_number) == 1)
        {
            process_count++;
        }
    }


    closedir(directory);


    printf(
        "Active processes detected : %d\n",
        process_count
    );


    /*
     * Get current process information
     */

    snprintf(
        process_path,
        sizeof(process_path),
        "/proc/%d/comm",
        getpid()
    );


    process_file = fopen(
        process_path,
        "r"
    );


    printf("\nCURRENT PROCESS\n");
    printf("--------------------------------------------\n");


    printf(
        "PID        : %d\n",
        getpid()
    );


    printf(
        "Parent PID : %d\n",
        getppid()
    );


    if (process_file != NULL)
    {
        if (fgets(
                process_name,
                sizeof(process_name),
                process_file) != NULL)
        {
            printf(
                "Name       : %s",
                process_name
            );
        }

        fclose(process_file);
    }


    /*
     * Create actual security report
     */

    report = fopen(
        "security_monitoring_report.txt",
        "w"
    );


    if (report == NULL)
    {
        perror(
            "Unable to create security report"
        );

        exit(52);
    }


    fprintf(
        report,
        "SECURITY MONITORING REPORT\n"
    );

    fprintf(
        report,
        "===========================\n"
    );

    fprintf(
        report,
        "Current PID       : %d\n",
        getpid()
    );

    fprintf(
        report,
        "Parent PID        : %d\n",
        getppid()
    );

    fprintf(
        report,
        "Active Processes  : %d\n",
        process_count
    );

    fprintf(
        report,
        "Process Scan      : COMPLETED\n"
    );

    fprintf(
        report,
        "Monitoring Status : NORMAL\n"
    );


    fclose(report);


    printf("\n");
    printf(
        "Security process scan completed.\n"
    );


    printf("\nCreated file:\n");
    printf(
        "  security_monitoring_report.txt\n"
    );


    printf(
        "\nSecurity monitoring completed successfully.\n"
    );


    exit(50);
}