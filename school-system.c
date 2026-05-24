#include <stdio.h>
#include <string.h>

struct Student {
    int student_id;
    char name[50];
    float grades[5];
    int has_grades;
};

struct Student class_Students[50];
int total_students = 0;
int next_id = 1;

void display_menu() {
    printf("\n--- School Management System ---\n");
    printf("1. Add New Student\n");
    printf("2. Enter Grades for a Student\n");
    printf("3. Search for a Student by Name\n");
    printf("4. View Class Report (All Students)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void add_student() {
    if (total_students >= 50) {
        printf("\nClass is full! Cannot add more students.\n");
        return;
    }
    
    printf("\nEnter student name: ");
    getchar();
    fgets(class_Students[total_students].name, 50, stdin);
    
    int i;
    for (i = 0; i < 50; i = i + 1) {
        if (class_Students[total_students].name[i] == '\n') {
            class_Students[total_students].name[i] = '\0';
            break;
        }
    }
    
    class_Students[total_students].student_id = next_id;
    class_Students[total_students].has_grades = 0;
    
    printf("Student added successfully!\n");
    printf("Student ID: %d\n", next_id);
    
    next_id = next_id + 1;
    total_students = total_students + 1;
}

void enter_grades() {
    int id;
    int found = 0;
    int i;
    int j;
    
    printf("\nEnter Student ID: ");
    scanf("%d", &id);
    
    for (i = 0; i < total_students; i = i + 1) {
        if (class_Students[i].student_id == id) {
            found = 1;
            printf("\nEntering grades for: %s (ID: %d)\n", 
                   class_Students[i].name, id);
            
            for (j = 0; j < 5; j = j + 1) {
                printf("Enter grade for Subject %d: ", j + 1);
                scanf("%f", &class_Students[i].grades[j]);
            }
            
            class_Students[i].has_grades = 1;
            printf("\nGrades saved successfully!\n");
            break;
        }
    }
    
    if (found == 0) {
        printf("\nStudent with ID %d not found!\n", id);
    }
}

float calculate_average(int student_index) {
    float sum = 0;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        sum = sum + class_Students[student_index].grades[i];
    }
    
    float average = sum / 5;
    return average;
}

void search_by_name() {
    char search_name[50];
    int found = 0;
    int i;
    int j;
    
    printf("\nEnter student name: ");
    getchar();
    fgets(search_name, 50, stdin);
    
    for (i = 0; i < 50; i = i + 1) {
        if (search_name[i] == '\n') {
            search_name[i] = '\0';
            break;
        }
    }
    
    for (i = 0; i < total_students; i = i + 1) {
        if (strcmp(class_Students[i].name, search_name) == 0) {
            found = 1;
            
            printf("\nStudent ID: %d\n", class_Students[i].student_id);
            printf("Name: %s\n", class_Students[i].name);
            
            if (class_Students[i].has_grades == 1) {
                printf("Grades: ");
                for (j = 0; j < 5; j = j + 1) {
                    printf("%.1f  ", class_Students[i].grades[j]);
                }
                printf("\nAverage: %.2f\n", calculate_average(i));
            } else {
                printf("No grades recorded yet.\n");
            }
            break;
        }
    }
    
    if (found == 0) {
        printf("\nStudent not found!\n");
    }
}

void view_class_report() {
    int i;
    
    if (total_students == 0) {
        printf("\nNo students in the class yet!\n");
        return;
    }
    
    printf("\n--- Class Report ---\n");
    printf("ID\tName\t\t\tAverage\n");
    
    for (i = 0; i < total_students; i = i + 1) {
        printf("%d\t%-20s\t", 
               class_Students[i].student_id, 
               class_Students[i].name);
        
        if (class_Students[i].has_grades == 1) {
            printf("%.2f\n", calculate_average(i));
        } else {
            printf("No grades\n");
        }
    }
    
    printf("Total students: %d\n", total_students);
}

int main() {
    int choice;
    
    printf("\nWelcome to School Management System\n");
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        
        if (choice == 1) {
            add_student();
        } 
        else if (choice == 2) {
            enter_grades();
        } 
        else if (choice == 3) {
            search_by_name();
        } 
        else if (choice == 4) {
            view_class_report();
        } 
        else if (choice == 5) {
            printf("\nThank you for using the system!\n");
            printf("Goodbye!\n");
            break;
        } 
        else {
            printf("\nInvalid choice! Please choose from 1 to 5\n");
        }
    }
    
    return 0;
}