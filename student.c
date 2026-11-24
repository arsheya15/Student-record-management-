#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    char course[30];
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File error!");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks (out of 100): ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n------ STUDENT RECORDS ------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll Number: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nCourse: %s", s.course);
        printf("\nMarks: %.2f", s.marks);
        printf("\nPercentage: %.2f%%", s.marks);
        
        if (s.marks >= 90)
            printf("\nGrade: A+");
        else if (s.marks >= 80)
            printf("\nGrade: A");
        else if (s.marks >= 70)
            printf("\nGrade: B");
        else if (s.marks >= 60)
            printf("\nGrade: C");
        else if (s.marks >= 40)
            printf("\nGrade: D");
        else
            printf("\nGrade: F");

        printf("\n---------------------------\n");
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo Records Found!");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found!");
            printf("\nName: %s", s.name);
            printf("\nCourse: %s", s.course);
            printf("\nMarks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent Not Found!");

    fclose(fp);
}

void updateStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("\nFile Error!");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            found = 1;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Updated Successfully!");
    else
        printf("\nStudent Not Found!");
}

void deleteStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("\nFile Error!");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Deleted Successfully!");
    else
        printf("\nStudent Not Found!");
}

int main() {
    int choice;

    do {
        printf("\n\n================================");
        printf("\n   STUDENT RECORD MANAGEMENT");
        printf("\n================================");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n================================");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank You!");
                break;

            default:
                printf("\nInvalid Choice!");
        }

    } while (choice != 6);

    return 0;
}