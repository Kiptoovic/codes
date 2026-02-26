Asignment 1


// Student Management System.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define MAX_NAME_LEN 50
#define MAX_DEPT_LEN 30

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
    char department[MAX_DEPT_LEN];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void displayMenu();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateGPA();
void findTopStudent();
void calculateAverageGPA();
void sortStudentsByGPA();
void deleteStudent();
void saveToFile();
void loadFromFile();

int main() {
    int choice;
    
    printf("===================================\n");
    printf("   STUDENT MANAGEMENT SYSTEM\n");
    printf("===================================\n");
    
    // Load existing data from file
    loadFromFile();
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateGPA();
                break;
            case 5:
                findTopStudent();
                break;
            case 6:
                calculateAverageGPA();
                break;
            case 7:
                sortStudentsByGPA();
                break;
            case 8:
                deleteStudent();
                break;
            case 9:
                saveToFile();
                printf("Data saved successfully!\n");
                break;
            case 10:
                printf("Exiting program...\n");
                saveToFile();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while(choice != 10);
    
    return 0;
}

void displayMenu() {
    printf("\n===== MAIN MENU =====\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Update Student GPA\n");
    printf("5. Find Top Student (Highest GPA)\n");
    printf("6. Calculate Average GPA\n");
    printf("7. Sort Students by GPA\n");
    printf("8. Delete Student\n");
    printf("9. Save Data to File\n");
    printf("10. Exit\n");
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Error: Maximum student limit reached (%d students)\n", MAX_STUDENTS);
        return;
    }
    
    Student newStudent;
    
    printf("\n--- Add New Student ---\n");
    
    // Get student ID with validation
    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);
    
    // Check if ID already exists
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id) {
            printf("Error: Student ID %d already exists!\n", newStudent.id);
            return;
        }
    }
    
    // Clear input buffer
    while(getchar() != '\n');
    
    // Get student name
    printf("Enter Name: ");
    fgets(newStudent.name, MAX_NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline
    
    // Get age with validation
    do {
        printf("Enter Age (16-50): ");
        scanf("%d", &newStudent.age);
    } while(newStudent.age < 16 || newStudent.age > 50);
    
    // Get GPA with validation
    do {
        printf("Enter GPA (0.0-4.0): ");
        scanf("%f", &newStudent.gpa);
    } while(newStudent.gpa < 0.0 || newStudent.gpa > 4.0);
    
    // Clear input buffer
    while(getchar() != '\n');
    
    // Get department
    printf("Enter Department: ");
    fgets(newStudent.department, MAX_DEPT_LEN, stdin);
    newStudent.department[strcspn(newStudent.department, "\n")] = 0;
    
    // Add to array
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("Student added successfully!\n");
    printf("Total students: %d\n", studentCount);
}

void displayAllStudents() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    printf("\n======================================================================================\n");
    printf("                                     ALL STUDENTS                                     \n");
    printf("======================================================================================\n");
    printf("%-10s %-25s %-6s %-8s %-20s\n", 
           "ID", "Name", "Age", "GPA", "Department");
    printf("--------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%-10d %-25s %-6d %-8.2f %-20s\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gpa,
               students[i].department);
    }
    printf("======================================================================================\n");
    printf("Total Students: %d\n", studentCount);
}

void searchStudent() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    int searchId;
    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            printf("\n=== Student Found ===\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("Department: %s\n", students[i].department);
            return;
        }
    }
    
    printf("Student with ID %d not found.\n", searchId);
}

void updateGPA() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    int searchId;
    float newGPA;
    
    printf("Enter Student ID to update GPA: ");
    scanf("%d", &searchId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            printf("Current GPA: %.2f\n", students[i].gpa);
            
            do {
                printf("Enter new GPA (0.0-4.0): ");
                scanf("%f", &newGPA);
            } while(newGPA < 0.0 || newGPA > 4.0);
            
            students[i].gpa = newGPA;
            printf("GPA updated successfully!\n");
            return;
        }
    }
    
    printf("Student with ID %d not found.\n", searchId);
}

void findTopStudent() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    int topIndex = 0;
    for (int i = 1; i < studentCount; i++) {
        if (students[i].gpa > students[topIndex].gpa) {
            topIndex = i;
        }
    }
    
    printf("\n=== TOP STUDENT (Highest GPA) ===\n");
    printf("ID: %d\n", students[topIndex].id);
    printf("Name: %s\n", students[topIndex].name);
    printf("Age: %d\n", students[topIndex].age);
    printf("GPA: %.2f\n", students[topIndex].gpa);
    printf("Department: %s\n", students[topIndex].department);
}

void calculateAverageGPA() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    float totalGPA = 0;
    for (int i = 0; i < studentCount; i++) {
        totalGPA += students[i].gpa;
    }
    
    float averageGPA = totalGPA / studentCount;
    printf("\n=== GPA STATISTICS ===\n");
    printf("Total Students: %d\n", studentCount);
    printf("Total GPA: %.2f\n", totalGPA);
    printf("Average GPA: %.2f\n", averageGPA);
    
    // Count students by GPA range
    int excellent = 0, good = 0, average = 0, poor = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].gpa >= 3.5) excellent++;
        else if (students[i].gpa >= 3.0) good++;
        else if (students[i].gpa >= 2.0) average++;
        else poor++;
    }
    
    printf("\nGPA Distribution:\n");
    printf("Excellent (3.5-4.0): %d students\n", excellent);
    printf("Good (3.0-3.49): %d students\n", good);
    printf("Average (2.0-2.99): %d students\n", average);
    printf("Poor (<2.0): %d students\n", poor);
}

void sortStudentsByGPA() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    // Bubble sort in descending order by GPA
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                // Swap students
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("Students sorted by GPA (highest to lowest).\n");
    displayAllStudents();
}

void deleteStudent() {
    if (studentCount == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    int deleteId, foundIndex = -1;
    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteId);
    
    // Find student index
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == deleteId) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("Student with ID %d not found.\n", deleteId);
        return;
    }
    
    // Display student to be deleted
    printf("\n=== Student to Delete ===\n");
    printf("ID: %d, Name: %s, GPA: %.2f\n", 
           students[foundIndex].id, 
           students[foundIndex].name, 
           students[foundIndex].gpa);
    
    char confirm;
    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // Shift elements left
        for (int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("Student deleted successfully!\n");
        printf("Remaining students: %d\n", studentCount);
    } else {
        printf("Deletion cancelled.\n");
    }
}

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    
    // Write student count
    fwrite(&studentCount, sizeof(int), 1, file);
    
    // Write student data
    for (int i = 0; i < studentCount; i++) {
        fwrite(&students[i], sizeof(Student), 1, file);
    }
    
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }
    
    // Read student count
    fread(&studentCount, sizeof(int), 1, file);
    
    // Read student data
    for (int i = 0; i < studentCount; i++) {
        fread(&students[i], sizeof(Student), 1, file);
    }
    
    fclose(file);
    printf("Loaded %d students from file.\n", studentCount);
}