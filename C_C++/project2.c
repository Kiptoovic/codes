#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COURSES 10

// Structure to hold course information
typedef struct {
    char code[10];
    char title[50];
    int units;
    int mark;
    char grade[3];
} Course;

// Structure to hold student information
typedef struct {
    char name[50];
    char regNo[20];
    char program[100];
    char academicYear[30];
    Course courses[MAX_COURSES];
    int courseCount;
    float gpa;
    float avgMark;
    char avgGrade[3];
    char classification[30];
    char remark[50];
} Student;

// Function to determine grade based on mark
void determineGrade(int mark, char* grade) {
    if (mark >= 70) strcpy(grade, "A");
    else if (mark >= 60) strcpy(grade, "B");
    else if (mark >= 50) strcpy(grade, "C");
    else if (mark >= 40) strcpy(grade, "D");
    else strcpy(grade, "F");
}

// Function to calculate GPA
float calculateGPA(Course courses[], int count) {
    float totalPoints = 0;
    int totalUnits = 0;
    
    for (int i = 0; i < count; i++) {
        int points;
        if (strcmp(courses[i].grade, "A") == 0) points = 4;
        else if (strcmp(courses[i].grade, "B") == 0) points = 3;
        else if (strcmp(courses[i].grade, "C") == 0) points = 2;
        else if (strcmp(courses[i].grade, "D") == 0) points = 1;
        else points = 0;
        
        totalPoints += points * courses[i].units;
        totalUnits += courses[i].units;
    }
    
    return totalUnits > 0 ? totalPoints / totalUnits : 0;
}

// Function to calculate average mark
float calculateAvgMark(Course courses[], int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += courses[i].mark;
    }
    return count > 0 ? (float)total / count : 0;
}

// Function to create PDF transcript file
void createPDFTranscript(Student *student, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("ERROR: Cannot create file %s\n", filename);
        return;
    }
    
    // Write content as formatted text that can be printed/converted to PDF
    fprintf(file, "===========================================================================\n");
    fprintf(file, "%30s DEDAN KIMATHI UNIVERSITY OF TECHNOLOGY\n", "");
    fprintf(file, "===========================================================================\n\n");
    fprintf(file, "%35s OFFICIAL TRANSCRIPT\n\n", "");
    
    fprintf(file, "STUDENT NAME:      %s\n", student->name);
    fprintf(file, "REGISTRATION NO:   %s\n", student->regNo);
    fprintf(file, "PROGRAM:           %s\n", student->program);
    fprintf(file, "ACADEMIC YEAR:     %s\n\n", student->academicYear);
    
    fprintf(file, "===========================================================================\n");
    fprintf(file, "%-10s %-40s %-6s %-6s\n", "CODE", "UNIT TITLE", "MARK", "GRADE");
    fprintf(file, "===========================================================================\n");
    
    for (int i = 0; i < student->courseCount; i++) {
        fprintf(file, "%-10s %-40s %-6d %-6s\n",
               student->courses[i].code,
               student->courses[i].title,
               student->courses[i].mark,
               student->courses[i].grade);
    }
    
    fprintf(file, "===========================================================================\n");
    fprintf(file, "\nACADEMIC PERFORMANCE\n");
    fprintf(file, "===========================================================================\n");
    fprintf(file, "GPA: %.2f / 4.00                  Average Mark: %.1f%%\n", 
           student->gpa, student->avgMark);
    fprintf(file, "Average Grade: %s                  Classification: %s\n", 
           student->avgGrade, student->classification);
    fprintf(file, "Remark: %s\n", student->remark);
    fprintf(file, "===========================================================================\n");
    
    fprintf(file, "\nGRADING SYSTEM\n");
    fprintf(file, "A = 70-100%%  Excellent  4.0\n");
    fprintf(file, "B = 60-69%%   Very Good  3.0\n");
    fprintf(file, "C = 50-59%%   Good       2.0\n");
    fprintf(file, "D = 40-49%%   Pass       1.0\n");
    fprintf(file, "F = 0-39%%    Fail       0.0\n");
    fprintf(file, "===========================================================================\n");
    
    fclose(file);
    
    printf("\n========================================\n");
    printf("✓ Transcript successfully saved to:\n");
    printf("  %s\n", filename);
    printf("========================================\n");
}

int main() {
    Student student;
    
    // Get student information from user
    printf("\n===== STUDENT TRANSCRIPT SYSTEM =====\n");
    printf("\nEnter Student Information:\n");
    
    printf("Student Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = 0;
    
    printf("Registration Number: ");
    fgets(student.regNo, sizeof(student.regNo), stdin);
    student.regNo[strcspn(student.regNo, "\n")] = 0;
    
    printf("Program: ");
    fgets(student.program, sizeof(student.program), stdin);
    student.program[strcspn(student.program, "\n")] = 0;
    
    printf("Academic Year: ");
    fgets(student.academicYear, sizeof(student.academicYear), stdin);
    student.academicYear[strcspn(student.academicYear, "\n")] = 0;
    
    // Get number of courses
    printf("\nHow many units did you take? ");
    scanf("%d", &student.courseCount);
    getchar();  // Clear the newline from input buffer
    
    if (student.courseCount > MAX_COURSES) {
        printf("Maximum units allowed: %d\n", MAX_COURSES);
        student.courseCount = MAX_COURSES;
    }
    
    // Get course information from user
    printf("\nEnter Units Details:\n");
    for (int i = 0; i < student.courseCount; i++) {
        printf("\n--- Unit %d ---\n", i + 1);
        
        printf("Unit Code: ");
        fgets(student.courses[i].code, sizeof(student.courses[i].code), stdin);
        student.courses[i].code[strcspn(student.courses[i].code, "\n")] = 0;
        
        printf("Unit Title: ");
        fgets(student.courses[i].title, sizeof(student.courses[i].title), stdin);
        student.courses[i].title[strcspn(student.courses[i].title, "\n")] = 0;
        
        printf("Points: ");

        scanf("%d", &student.courses[i].units);
        
        printf("Mark (0-100): ");
        scanf("%d", &student.courses[i].mark);
        getchar();  // Clear the newline from input buffer
    }
    
    // Determine grades for all courses
    for (int i = 0; i < student.courseCount; i++) {
        determineGrade(student.courses[i].mark, student.courses[i].grade);
    }
    
    // Calculate academic performance
    student.gpa = calculateGPA(student.courses, student.courseCount);
    student.avgMark = calculateAvgMark(student.courses, student.courseCount);
    determineGrade((int)student.avgMark, student.avgGrade);
    
    // Determine classification and remark based on GPA
    if (student.gpa >= 3.6) {
        strcpy(student.classification, "First Class Honours");
        strcpy(student.remark, "EXCELLENT PERFORMANCE");
    } else if (student.gpa >= 3.0) {
        strcpy(student.classification, "Upper Second Class Honours");
        strcpy(student.remark, "VERY GOOD PERFORMANCE");
    } else if (student.gpa >= 2.4) {
        strcpy(student.classification, "Lower Second Class Honours");
        strcpy(student.remark, "GOOD PERFORMANCE");
    } else if (student.gpa >= 1.6) {
        strcpy(student.classification, "Third Class Honours");
        strcpy(student.remark, "SATISFACTORY PERFORMANCE");
    } else {
        strcpy(student.classification, "Pass");
        strcpy(student.remark, "MINIMUM PERFORMANCE");
    }
    
    // Ask user for PDF filename
    char filename[256];
    printf("\n========================================\n");
    printf("Enter filename to save PDF transcript\n");
    printf("(Do not include .pdf extension): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    // Validate and create full filename with .pdf extension
    if (strlen(filename) == 0) {
        printf("ERROR: Filename cannot be empty\n");
        return 1;
    }
    
    char fullpath[300];
    sprintf(fullpath, "%s.pdf", filename);
    
    // Create PDF transcript
    createPDFTranscript(&student, fullpath);
    
    return 0;
}