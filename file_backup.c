#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void file_backup_service()
{
    FILE *source;
    FILE *backup;

    char buffer[256];

    size_t bytes;


    printf("\n");
    printf("FILE BACKUP SERVICE\n");
    printf("--------------------------------------------\n");


    /*
     * Create actual source file
     */

    printf("Creating service_data.txt...\n");


    source = fopen("service_data.txt", "w");

    if (source == NULL)
    {
        perror("Unable to create source file");
        exit(21);
    }


    fprintf(source, "SmartGym Process Monitoring Project\n");
    fprintf(source, "Service Data Record 1\n");
    fprintf(source, "Service Data Record 2\n");
    fprintf(source, "Backup operation test data\n");


    fclose(source);


    printf("Source file created successfully.\n");

    sleep(1);


    /*
     * Open source for reading
     */

    source = fopen("service_data.txt", "r");

    if (source == NULL)
    {
        perror("Unable to open source file");
        exit(22);
    }


    /*
     * Create backup
     */

    printf("Creating service_data_backup.txt...\n");


    backup = fopen("service_data_backup.txt", "w");

    if (backup == NULL)
    {
        perror("Unable to create backup");
        fclose(source);
        exit(23);
    }


    /*
     * Actual file copying
     */

    printf("Copying source file...\n");


    while ((bytes = fread(
                buffer,
                1,
                sizeof(buffer),
                source)) > 0)
    {
        fwrite(
            buffer,
            1,
            bytes,
            backup
        );
    }


    fclose(source);
    fclose(backup);


    printf("Backup file created successfully.\n");

    sleep(1);


    /*
     * Verify backup
     */

    backup = fopen(
        "service_data_backup.txt",
        "r"
    );

    if (backup == NULL)
    {
        perror("Unable to verify backup");
        exit(24);
    }


    printf("\nBACKUP CONTENT\n");
    printf("--------------------------------------------\n");


    while (fgets(
               buffer,
               sizeof(buffer),
               backup) != NULL)
    {
        printf("%s", buffer);
    }


    fclose(backup);


    /*
     * Create backup log
     */

    backup = fopen(
        "backup_operation_log.txt",
        "w"
    );

    if (backup != NULL)
    {
        fprintf(
            backup,
            "FILE BACKUP SERVICE REPORT\n"
        );

        fprintf(
            backup,
            "===========================\n"
        );

        fprintf(
            backup,
            "Source      : service_data.txt\n"
        );

        fprintf(
            backup,
            "Backup      : service_data_backup.txt\n"
        );

        fprintf(
            backup,
            "Status      : SUCCESS\n"
        );

        fclose(backup);
    }


    printf("\nCreated files:\n");
    printf("  service_data.txt\n");
    printf("  service_data_backup.txt\n");
    printf("  backup_operation_log.txt\n");

    printf("\nFile backup completed successfully.\n");


    exit(20);
}