#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void database_service()
{
    FILE *database;
    FILE *log;

    char buffer[256];


    printf("\n");
    printf("DATABASE SERVICE\n");
    printf("--------------------------------------------\n");


    /*
     * Create database file
     */

    database = fopen(
        "smartgym_database.txt",
        "w"
    );

    if (database == NULL)
    {
        perror("Unable to create database");
        exit(41);
    }


    printf("Creating database...\n");


    /*
     * INSERT records
     */

    printf("Inserting records...\n");


    fprintf(
        database,
        "1,Smith,85\n"
    );

    fprintf(
        database,
        "2,John,90\n"
    );

    fprintf(
        database,
        "3,David,75\n"
    );

    fprintf(
        database,
        "4,Alex,88\n"
    );


    fclose(database);


    printf("Records inserted successfully.\n");

    sleep(1);


    /*
     * READ records
     */

    database = fopen(
        "smartgym_database.txt",
        "r"
    );

    if (database == NULL)
    {
        perror("Unable to read database");
        exit(42);
    }


    printf("\nDATABASE RECORDS\n");
    printf("--------------------------------------------\n");


    while (fgets(
               buffer,
               sizeof(buffer),
               database) != NULL)
    {
        printf("%s", buffer);
    }


    fclose(database);


    /*
     * UPDATE database
     */

    printf("\nUpdating John record...\n");


    database = fopen(
        "smartgym_database.txt",
        "w"
    );

    if (database == NULL)
    {
        perror("Unable to update database");
        exit(43);
    }


    fprintf(
        database,
        "1,Smith,85\n"
    );

    fprintf(
        database,
        "2,John,95\n"
    );

    fprintf(
        database,
        "3,David,75\n"
    );

    fprintf(
        database,
        "4,Alex,88\n"
    );


    fclose(database);


    printf("Record updated successfully.\n");


    /*
     * VERIFY UPDATE
     */

    database = fopen(
        "smartgym_database.txt",
        "r"
    );

    if (database == NULL)
    {
        perror("Unable to verify database");
        exit(44);
    }


    printf("\nUPDATED DATABASE\n");
    printf("--------------------------------------------\n");


    while (fgets(
               buffer,
               sizeof(buffer),
               database) != NULL)
    {
        printf("%s", buffer);
    }


    fclose(database);


    /*
     * Create database log
     */

    log = fopen(
        "database_operation_log.txt",
        "w"
    );


    if (log != NULL)
    {
        fprintf(
            log,
            "DATABASE SERVICE REPORT\n"
        );

        fprintf(
            log,
            "=======================\n"
        );

        fprintf(
            log,
            "INSERT : SUCCESS\n"
        );

        fprintf(
            log,
            "READ   : SUCCESS\n"
        );

        fprintf(
            log,
            "UPDATE : SUCCESS\n"
        );

        fprintf(
            log,
            "VERIFY : SUCCESS\n"
        );

        fclose(log);
    }


    printf("\nCreated files:\n");
    printf("  smartgym_database.txt\n");
    printf("  database_operation_log.txt\n");


    printf(
        "\nDatabase operation completed successfully.\n"
    );


    exit(40);
}