#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    char* firstName;
    char* lastName;
    char* cellphone;
    int grade;
    int classroom;
    int grades[10];
    struct Student* next; // Pointer to the next node in the list
};


void parseStudent(struct Student* student, const char* input_string) {
    student->firstName = (char*)malloc(50);
    student->lastName = (char*)malloc(50);
    student->cellphone = (char*)malloc(11);

    int result = sscanf(input_string, "%49s %49s %10s %d %d %d %d %d %d %d %d %d %d %d %d",
        student->firstName,
        student->lastName,
        student->cellphone,
        &student->grade,
        &student->classroom,
        &student->grades[0], &student->grades[1], &student->grades[2], &student->grades[3], &student->grades[4],
        &student->grades[5], &student->grades[6], &student->grades[7], &student->grades[8], &student->grades[9]);
}


struct Student* createStudentNode( char* input_string) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    if (newNode == NULL) {
        printf("Memory allocation failed for the new node.\n");
        exit(1);
    }
    parseStudent(newNode, input_string);
    newNode->next = NULL;
    return newNode;
}


void freeStudentList(struct Student* school[12][10]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            struct Student* current = school[i][j];
            while (current != NULL) {
                struct Student* next = current->next;
                free(current->firstName);
                free(current->lastName);
                free(current);
                current = next;
            }
        }
    }
}


int main() {
    FILE* file;
    char line[256];

    // Open the file in read mode
    file = fopen( "students_with_class.txt", "r");
    if (!file) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    struct Student* school[12][10] ; 
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            school[i][j] = NULL;
        }
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        // Create a new node for the student and insert it into the list
        struct Student* newNode = createStudentNode(line);
        int g=newNode->grade;
        int c=newNode->classroom;
        
        //insertStudentToList
        newNode->next = school[g][c];
        school[g][c]=newNode;
    }

    // Close the file
    fclose(file);

    // Print the list
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            struct Student* current = school[i][j];
            while (current != NULL) {
                printf("First Name: %s\n", current->firstName);
                printf("Last Name: %s\n", current->lastName);
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

    // Free the memory allocated for the linked list
    freeStudentList(school);
    return 0;
}
