#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void data_processing_service()
{
    FILE *file;
    FILE *report;

    int data[10] =
    {
        10, 25, 40, 55, 70,
        15, 30, 65, 100, 140
    };

    int value;
    int count = 0;
    int total = 0;
    int maximum = 0;
    int minimum = 0;

    double average;


    printf("\n");
    printf("DATA PROCESSING SERVICE\n");
    printf("--------------------------------------------\n");


    /*
     * Create actual data file
     */

    file = fopen("data_records.txt", "w");

    if (file == NULL)
    {
        perror("Unable to create data_records.txt");
        exit(11);
    }


    printf("Creating data_records.txt...\n");


    for (int i = 0; i < 10; i++)
    {
        fprintf(file, "%d\n", data[i]);
    }


    fclose(file);


    printf("Data records created successfully.\n");

    sleep(1);


    /*
     * Open the actual file and read the records
     */

    file = fopen("data_records.txt", "r");

    if (file == NULL)
    {
        perror("Unable to open data_records.txt");
        exit(12);
    }


    printf("\nReading records from data_records.txt...\n");

    while (fscanf(file, "%d", &value) == 1)
    {
        printf("Record %d : %d\n",
               count + 1,
               value);

        if (count == 0)
        {
            maximum = value;
            minimum = value;
        }

        if (value > maximum)
            maximum = value;

        if (value < minimum)
            minimum = value;

        total += value;

        count++;
    }


    fclose(file);


    if (count == 0)
    {
        printf("No records found.\n");
        exit(13);
    }


    average = (double)total / count;


    /*
     * Create actual processing report
     */

    report = fopen("data_processing_report.txt", "w");

    if (report == NULL)
    {
        perror("Unable to create processing report");
        exit(14);
    }


    fprintf(report, "DATA PROCESSING REPORT\n");
    fprintf(report, "======================\n");
    fprintf(report, "Total Records : %d\n", count);
    fprintf(report, "Total Value   : %d\n", total);
    fprintf(report, "Average       : %.2f\n", average);
    fprintf(report, "Maximum       : %d\n", maximum);
    fprintf(report, "Minimum       : %d\n", minimum);


    fclose(report);


    printf("\n");
    printf("DATA PROCESSING RESULT\n");
    printf("--------------------------------------------\n");

    printf("Total Records : %d\n", count);
    printf("Total Value   : %d\n", total);
    printf("Average       : %.2f\n", average);
    printf("Maximum       : %d\n", maximum);
    printf("Minimum       : %d\n", minimum);

    printf("\n");
    printf("Created files:\n");
    printf("  data_records.txt\n");
    printf("  data_processing_report.txt\n");

    printf("\nData processing completed successfully.\n");


    exit(10);
}