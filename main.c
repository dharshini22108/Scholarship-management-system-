#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Scholarship
{
    int applicationID;
    char studentName[50];
    char department[30];
    int year;
    char scholarshipName[50];
    float percentage;
    float familyIncome;
    char status[20];
};

void addApplication()
{
    struct Scholarship s;
    FILE *fp;

    fp = fopen("scholarship_records.txt", "a");

    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    printf("\n--- Add Scholarship Application ---\n");

    printf("Application ID: ");
    scanf("%d", &s.applicationID);

    printf("Student Name: ");
    scanf(" %[^\n]", s.studentName);

    printf("Department: ");
    scanf(" %[^\n]", s.department);

    printf("Year: ");
    scanf("%d", &s.year);

    printf("Scholarship Name: ");
    scanf(" %[^\n]", s.scholarshipName);

    printf("Academic Percentage: ");
    scanf("%f", &s.percentage);

    printf("Family Income: ");
    scanf("%f", &s.familyIncome);

    strcpy(s.status, "Pending");

    fprintf(fp, "%d|%s|%s|%d|%s|%.2f|%.2f|%s\n",
            s.applicationID,
            s.studentName,
            s.department,
            s.year,
            s.scholarshipName,
            s.percentage,
            s.familyIncome,
            s.status);

    fclose(fp);

    printf("\nApplication added successfully!\n");
}

void viewApplications()
{
    struct Scholarship s;
    FILE *fp;

    fp = fopen("scholarship_records.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n========== Scholarship Applications ==========\n");

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%d|%49[^|]|%f|%f|%19[^\n]\n",
                  &s.applicationID,
                  s.studentName,
                  s.department,
                  &s.year,
                  s.scholarshipName,
                  &s.percentage,
                  &s.familyIncome,
                  s.status) == 8)
    {
        printf("\nApplication ID : %d", s.applicationID);
        printf("\nStudent Name   : %s", s.studentName);
        printf("\nDepartment     : %s", s.department);
        printf("\nYear           : %d", s.year);
        printf("\nScholarship    : %s", s.scholarshipName);
        printf("\nPercentage     : %.2f", s.percentage);
        printf("\nFamily Income  : %.2f", s.familyIncome);
        printf("\nStatus         : %s\n", s.status);
        printf("---------------------------------------------\n");
    }

    fclose(fp);
}

void searchApplication()
{
    struct Scholarship s;
    FILE *fp;
    int id;
    int found = 0;

    fp = fopen("scholarship_records.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Application ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%d|%49[^|]|%f|%f|%19[^\n]\n",
                  &s.applicationID,
                  s.studentName,
                  s.department,
                  &s.year,
                  s.scholarshipName,
                  &s.percentage,
                  &s.familyIncome,
                  s.status) == 8)
    {
        if (s.applicationID == id)
        {
            printf("\n--- Application Found ---\n");
            printf("Student Name  : %s\n", s.studentName);
            printf("Department    : %s\n", s.department);
            printf("Year          : %d\n", s.year);
            printf("Scholarship   : %s\n", s.scholarshipName);
            printf("Percentage    : %.2f\n", s.percentage);
            printf("Family Income : %.2f\n", s.familyIncome);
            printf("Status        : %s\n", s.status);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nApplication not found.\n");
    }

    fclose(fp);
}

void checkEligibility()
{
    float percentage;
    float income;

    printf("\n--- Scholarship Eligibility Check ---\n");

    printf("Enter Academic Percentage: ");
    scanf("%f", &percentage);

    printf("Enter Family Income: ");
    scanf("%f", &income);

    if (percentage >= 60 && income <= 300000)
    {
        printf("\nEligible for the scholarship.\n");
    }
    else
    {
        printf("\nNot eligible based on the given criteria.\n");
    }
}

void updateStatus()
{
    struct Scholarship s;
    FILE *fp;
    FILE *temp;
    int id;
    int found = 0;
    int choice;

    fp = fopen("scholarship_records.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\nUnable to open file.\n");
        return;
    }

    printf("\nEnter Application ID: ");
    scanf("%d", &id);

    printf("\n1. Approved");
    printf("\n2. Rejected");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%d|%49[^|]|%f|%f|%19[^\n]\n",
                  &s.applicationID,
                  s.studentName,
                  s.department,
                  &s.year,
                  s.scholarshipName,
                  &s.percentage,
                  &s.familyIncome,
                  s.status) == 8)
    {
        if (s.applicationID == id)
        {
            if (choice == 1)
            {
                strcpy(s.status, "Approved");
            }
            else if (choice == 2)
            {
                strcpy(s.status, "Rejected");
            }

            found = 1;
        }

        fprintf(temp, "%d|%s|%s|%d|%s|%.2f|%.2f|%s\n",
                s.applicationID,
                s.studentName,
                s.department,
                s.year,
                s.scholarshipName,
                s.percentage,
                s.familyIncome,
                s.status);
    }

    fclose(fp);
    fclose(temp);

    remove("scholarship_records.txt");
    rename("temp.txt", "scholarship_records.txt");

    if (found)
    {
        printf("\nApplication status updated successfully.\n");
    }
    else
    {
        printf("\nApplication not found.\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n========================================");
        printf("\n     SCHOLARSHIP MANAGEMENT SYSTEM");
        printf("\n========================================");
        printf("\n1. Add Scholarship Application");
        printf("\n2. View All Applications");
        printf("\n3. Search Application");
        printf("\n4. Check Eligibility");
        printf("\n5. Update Application Status");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addApplication();
                break;

            case 2:
                viewApplications();
                break;

            case 3:
                searchApplication();
                break;

            case 4:
                checkEligibility();
                break;

            case 5:
                updateStatus();
                break;

            case 6:
                printf("\nThank you for using Scholarship Management System!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
