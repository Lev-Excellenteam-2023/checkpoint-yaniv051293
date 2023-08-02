#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

char* strndup(const char* s, size_t n) {
    size_t len = strnlen(s, n);
    char* copy = (char*)malloc(len + 1);
    if (copy != NULL) {
        memcpy(copy, s, len);
        copy[len] = '\0';
    }
    return copy;
}

struct Student {
    char* firstName;
    char* lastName;
    char* cellphone;
    int grade;
    int classroom;
    int grades[10];
    struct Student* next; // Pointer to the next node in the list
};

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

void insertNewStudent(struct Student* school[12][10]);
void printAllStudents(struct Student* school[12][10]);
void deleteStudent(struct Student* school[12][10]);
void editStudentGrade(struct Student* school[12][10]);
void searchStudent(struct Student* school[12][10]);
void printTopNStudentsPerCourse(struct Student* school[12][10]);
void printAverage(struct Student* school[12][10]);
void exportDatabase(struct Student* school[12][10]);
void printUnderperformedStudents(struct Student* school[12][10]);
void handleClosing(struct Student* school[12][10]);

void menu(struct Student* school[12][10]) {
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
        case Insert:
           insertNewStudent(school);
            break;
        case Delete:
            deleteStudent(school);
            break;
        case Edit:
            editStudentGrade(school);
            break;
        case Search:
            searchStudent(school);
            break;
        case Showall:
            printAllStudents(school);
            break;
        case Top10:
            printTopNStudentsPerCourse(school);
            break;
        case UnderperformedStudents:
            printUnderperformedStudents(school);
            break;
        case Average:
            printAverage(school);
            break;
        case Export:
            exportDatabase(school);
            break;
        case Exit:
            handleClosing(school);
            break;
        default:
            printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                input);
            getc(stdin);
           // getc(stdin);
            break;
        }
    } while (input != Exit);
}

void insertNewStudent(struct Student* school[12][10])
{
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed for the new student.\n");
        return;
    }

    char buffer[50]; // Buffer to store user input temporarily

    // Get first name from the user
    printf("Enter the first name: ");
    scanf("%49s", buffer);
    newStudent->firstName = strndup(buffer, 50);

    // Get last name from the user
    printf("Enter the last name: ");
    scanf("%49s", buffer);
    newStudent->lastName = strndup(buffer, 50);

    // Get cellphone from the user
    printf("Enter the cellphone: ");
    scanf("%10s", buffer);
    newStudent->cellphone = strndup(buffer, 10);

    // Get grade from the user
    printf("Enter the grade: ");
    scanf("%d", &(newStudent->grade));

    // Get classroom from the user
    printf("Enter the classroom: ");
    scanf("%d", &(newStudent->classroom));

    // Get grades array from the user
    printf("Enter the grades (10 integers separated by spaces): ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &(newStudent->grades[i]));
    }

    newStudent->next = NULL;
    insertStudentToList(&(school[newStudent->grade][newStudent->classroom]), &newStudent);
}

void printAllStudents(struct Student* school[12][10]) {
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                printf("First Name: %s\n", current->firstName);
                printf("Last Name: %s\n", current->lastName);
                printf("cellphone: %s\n", current->cellphone);
                printf("Grade: %d\n", current->grade);
                printf("Classroom: %d\n", current->classroom);
                printf("Grades: ");
                for (int k = 0; k < 10; k++) {
                    printf("%d ", current->grades[k]);
                }
                printf("\n\n");
                current = current->next;
            }
        }
    }
}

void deleteStudent(struct Student* school[12][10]) {
    // Get cellphone from the user
    char cellphone[50];
    printf("Enter the cellphone: ");
    scanf("%10s", cellphone);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            struct Student* previous = NULL;
            while (current != NULL) {
                if (strcmp(current->cellphone, cellphone) == 0)
                {
                    if (previous == NULL)
                        // If the node to be deleted is the head node
                        school[i][j] = current->next;
                    else
                        // If the node to be deleted is not the head node
                        previous->next = current->next;

                    // Free memory occupied by the node
                    free(current->firstName);
                    free(current->lastName);
                    free(current);
                    return;
                }
                previous = current;
                current = current->next;
            }
        }
    }
}

void editStudentGrade(struct Student* school[12][10]) {
    char cellphone[50];
    printf("Enter the cellphone: ");
    scanf("%10s", cellphone);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                if (strcmp(current->cellphone, cellphone) == 0)
                {

                    int courseNumber;
                    printf("Enter the course number you want to update: (between 1-10) ");
                    scanf("%d", &(courseNumber));

                    // Get classroom from the user
                    printf("Enter the new grade: ");
                    scanf("%d", &(current->grades[courseNumber+1]));
                    printf("edit succussfully");
                    return;
                }
                current = current->next;
            }
        }
    }        
    printf("student not found");
}

void searchStudent(struct Student* school[12][10])
{
    // Get first name from the user and last name
    char firstName[50], lastName[50];
    printf("Enter the first name: ");
    scanf("%49s", firstName);
    printf("Enter the last name: ");
    scanf("%49s", lastName);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                if ((strcmp(current->lastName, lastName) == 0) && (strcmp(current->firstName, firstName) == 0))
                {
                    printf("First Name: %s\n", current->firstName);
                    printf("Last Name: %s\n", current->lastName);
                    printf("cellphone: %s\n", current->cellphone);
                    printf("Grade: %d\n", current->grade);
                    printf("Classroom: %d\n", current->classroom);
                    printf("Grades: ");
                    for (int k = 0; k < 10; k++) {
                        printf("%d ", current->grades[k]);
                    }
                    return;
                }
                current = current->next;
            }
        }
    }
    printf("student not found");
}

void printTopNStudentsPerCourse(struct Student* school[12][10])
{
    // Get the grade
    int grade, course;
    printf("Enter the grade: (between 1 to 12)");
    scanf("%d", &(grade));
    printf("Enter the course: (between 1 to 10)");
    scanf("%d", &(course));
    grade--;
    course--;

    struct Student* topTen[10];
    int i = 0;
    for (int j = 0; j < 10; j++)
    {
        struct Student* current = school[grade][j];
        while (current != NULL) {
            if (i < 10)
                topTen[i++] = current;
            else
            {
                int lowestGrade = findlowIndex(topTen, course);
                if (topTen[lowestGrade]->grades[course] < current->grades[course])
                    topTen[lowestGrade] = current;
            }
            current = current->next;
        }
    }

    for (int j = 0; j < i; j++)
    {
        struct Student* current = topTen[j];
            printf("First Name: %s\n", current->firstName);
            printf("Last Name: %s\n", current->lastName);
            printf("cellphone: %s\n", current->cellphone);
            printf("Grade: %d\n", current->grade);
            printf("Classroom: %d\n", current->classroom);
            printf("Grades: ");
            for (int k = 0; k < 10; k++) {
                printf("%d ", current->grades[k]);
            }
            printf("\n\n");
    }
}

int findlowIndex(struct Student* arr[10],int course)
// return the index of the low grade
{
    int temp = 100, tempIndex=0;
    for (int i = 0; i < 10; i++)
    {
        if (arr[i]->grades[course] < temp)
        {
            temp = arr[i]->grades[course];
            tempIndex = i;
        }
    }
    return tempIndex;
}

void printAverage(struct Student* school[12][10]) {
    int grade, course;
    printf("Enter the grade: (between 1 to 12) ");
    scanf("%d", &(grade));
    printf("Enter the course: (between 1 to 10) ");
    scanf("%d", &(course));
    grade--;
    course--;

    int sum = 0, count = 0;
    for (int j = 0; j < 10; j++)
    {
        struct Student* current = school[grade][j];
        while (current != NULL) {
            sum += current->grades[course];
            count++;
            current = current->next;
        }
    }
    int avg = sum / count;
    printf("the avarge is %d\n", avg);
}

void printUnderperformedStudents(struct Student* school[12][10]) {
    // print all studets with avg <65
    printf("print all studets with avg lower than 65:\n");
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                int sum = 0;
                for (int k = 0; k < 10; k++) {
                    sum += current->grades[k];
                }
                if (sum / 10 < 65)
                {
                    printf("Name: %s %s\n", current->firstName, current->lastName);
                }
                current = current->next;
            }
        }
    }
    printf("\n\n");
}

void exportDatabase(struct Student* school[12][10]) {
    // Function to export student information to a file
    FILE* file;
    file = fopen( "students_with_class.txt", "w");
    if (!file) {
        printf("Error opening the file.\n");
        return;
    }
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                fprintf(file, "%s %s %s %d %d", current->firstName, current->lastName, current->cellphone,
                    current->grade, current->classroom);
                for (int i = 0; i < 10; i++) {
                    fprintf(file, " %d", current->grades[i]);
                }
                fprintf(file, "\n");
                current = current->next;
            }
        }
    }
    fclose(file);
    printf("Export Successfully.\n");
}

void handleClosing(struct Student* school[12][10]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            struct Student* current = school[i][j];
            while (current != NULL) {
                struct Student* next = current->next;
                free(current->firstName);
                free(current->lastName);
                free(current->cellphone);
                free(current);
                current = next;
            }
        }
    }
}





