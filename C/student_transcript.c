#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_UNITS 7
#define MAX_NAME 100
#define MAX_STRING 50

// Structure to store student details
struct Student {
    char institution[MAX_STRING];
    char school[MAX_STRING];
    char department[MAX_STRING];
    int year_of_study;
    int current_semester;
    char full_name[MAX_NAME];
    char reg_number[20];
};

// Structure to store unit information
struct Unit {
    char code[20];
    char name[100];
    int marks;
};

// Function to get student details
void getStudentDetails(struct Student *student) {
    printf("\n========== STUDENT INFORMATION ==========\n");
    
    // Pre-filled information
    strcpy(student->institution, "DeKUT");
    strcpy(student->school, "School of CS & IT");
    strcpy(student->department, "IT");
    
    printf("1. Institution: %s\n", student->institution);
    printf("2. School: %s\n", student->school);
    printf("3. Department: %s\n", student->department);
    
    // Get user input for other details
    printf("4. Year of study (e.g., 1 for First Year): ");
    while(scanf("%d", &student->year_of_study) != 1 || student->year_of_study < 1 || student->year_of_study > 5) {
        printf("Invalid input! Please enter a valid year (1-5): ");
        while(getchar() != '\n'); // Clear input buffer
    }
    
    printf("5. Current semester (e.g., 1 or 2): ");
    while(scanf("%d", &student->current_semester) != 1 || student->current_semester < 1 || student->current_semester > 2) {
        printf("Invalid input! Please enter 1 or 2: ");
        while(getchar() != '\n');
    }
    
    getchar(); // Clear newline character
    
    printf("6. Full name of student: ");
    fgets(student->full_name, MAX_NAME, stdin);
    student->full_name[strcspn(student->full_name, "\n")] = '\0'; // Remove newline
    
    printf("7. Registration number: ");
    fgets(student->reg_number, 20, stdin);
    student->reg_number[strcspn(student->reg_number, "\n")] = '\0';
}

// Function to get marks for units
void getUnitMarks(struct Unit units[]) {
    printf("\n========== ENTER UNIT MARKS (0-100) ==========\n");
    
    // Initialize unit codes and names
    char *unit_codes[MAX_UNITS] = {
        "CIT 1101", "CIT 1102", "CIT 1103", 
        "SMA 2100", "SMA 1103", 
        "IGS 1104", "HNS 1100"
    };
    
    char *unit_names[MAX_UNITS] = {
        "IT Essentials",
        "Introduction to Programming",
        "Computer Architecture and Organization",
        "Discrete Mathematics",
        "Mathematics for Science",
        "Introduction to Philosophy and Critical Thinking",
        "HIV & Aids"
    };
    
    for(int i = 0; i < MAX_UNITS; i++) {
        strcpy(units[i].code, unit_codes[i]);
        strcpy(units[i].name, unit_names[i]);
        
        printf("\n%d. %s: %s\n", i+1, units[i].code, units[i].name);
        printf("   Enter marks: ");
        
        while(scanf("%d", &units[i].marks) != 1 || units[i].marks < 0 || units[i].marks > 100) {
            printf("   Invalid marks! Please enter marks between 0-100: ");
            while(getchar() != '\n');
        }
    }
}

// Function to calculate average
float calculateAverage(struct Unit units[]) {
    int total = 0;
    for(int i = 0; i < MAX_UNITS; i++) {
        total += units[i].marks;
    }
    return (float)total / MAX_UNITS;
}

// Function to determine grade
char determineGrade(float average) {
    if(average >= 70 && average <= 100) return 'A';
    else if(average >= 60 && average <= 69) return 'B';
    else if(average >= 50 && average <= 59) return 'C';
    else if(average >= 40 && average <= 49) return 'D';
    else if(average >= 1 && average <= 39) return 'E';
    else return 'F'; // For invalid averages
}

// Function to display the report
void displayReport(struct Student student, struct Unit units[], float average, char grade) {
    printf("\n\n========== STUDENT ACADEMIC REPORT ==========\n");
    printf("=============================================\n");
    printf("INSTITUTION: %s\n", student.institution);
    printf("SCHOOL: %s\n", student.school);
    printf("DEPARTMENT: %s\n", student.department);
    printf("YEAR OF STUDY: %d\n", student.year_of_study);
    printf("CURRENT SEMESTER: %d\n", student.current_semester);
    printf("FULL NAME: %s\n", student.full_name);
    printf("REGISTRATION NUMBER: %s\n", student.reg_number);
    
    printf("\n========== UNIT MARKS ==========\n");
    printf("No. UNIT CODE      UNIT NAME                                MARKS\n");
    printf("-----------------------------------------------------------------\n");
    
    for(int i = 0; i < MAX_UNITS; i++) {
        printf("%d.  %-10s    %-40s    %3d\n", 
               i+1, units[i].code, units[i].name, units[i].marks);
    }
    
    printf("\n========== FINAL RESULT ==========\n");
    printf("AVERAGE MARK: %.2f\n", average);
    printf("GRADE: %c\n", grade);
    
    // Additional grade interpretation
    printf("\nGrade Interpretation:\n");
    switch(grade) {
        case 'A': printf("Excellent Performance\n"); break;
        case 'B': printf("Good Performance\n"); break;
        case 'C': printf("Average Performance\n"); break;
        case 'D': printf("Below Average\n"); break;
        case 'E': printf("Fail\n"); break;
        default: printf("Invalid Grade\n");
    }
    printf("=============================================\n");
}

int main() {
    struct Student student;
    struct Unit units[MAX_UNITS];
    float average;
    char grade;
    char choice;
    
    printf("=============================================\n");
    printf("    STUDENT ACADEMIC RECORD SYSTEM\n");
    printf("    DeKUT - School of CS & IT - IT Department\n");
    printf("=============================================\n");
    
    do {
        // Get student details
        getStudentDetails(&student);
        
        // Get unit marks
        getUnitMarks(units);
        
        // Calculate average and grade
        average = calculateAverage(units);
        grade = determineGrade(average);
        
        // Display the complete report
        displayReport(student, units, average, grade);
        
        // Ask if user wants to enter another record
        printf("\nDo you want to enter another student record? (Y/N): ");
        scanf(" %c", &choice);
        getchar(); // Clear newline
        
        // Convert to uppercase for comparison
        choice = toupper(choice);
        
    } while(choice == 'Y');
    
    printf("\nThank you for using the Student Academic Record System!\n");
    printf("=============================================\n");
    
    return 0;
}