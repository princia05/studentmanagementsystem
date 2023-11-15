#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

#define USERNAME "admin"
#define MAX_PASSWORD_LENGTH 50

struct Student 
{
    int rollNumber;
    char name[50];
    float marks;
    long long int mb_no;
    struct Student* next;
};

char PASSWORD[MAX_PASSWORD_LENGTH] = "password";

struct Student* createStudent(int rollNumber, const char* name,long long int mob_no, float marks);

int addStudent(struct Student** head, int rollNumber, const char* name,long long int mb_no, float marks);
void read_file(char str[50], struct Student** head) ;
void displayStudents(struct Student* head);

void modifyStudent(struct Student* head, int rollNumber);
void deleteStudent(struct Student** head, int rollNumber);
void calculateStatistics(struct Student* head);

int searchStudent(struct Student* head, int rollNumber);
void searchStudentByMobile(struct Student* head,long long int mb_no);
void searchStudentByName(struct Student* head, const char* searchName);

int compareStudents(const struct Student* student1, const struct Student* student2);
int compareStudentsByName(const struct Student* student1, const struct Student* student2);
int compareStudentsByMarks(const struct Student* student1, const struct Student* student2);

void sortStudents(const struct Student* head);
void sortStudentsByName(const struct Student* head);
struct Student* sortStudentsByMarks(const struct Student* head);

struct Student* copyStudents(const struct Student* head);
struct Student* reverseStudents(struct Student* head);
void filterTopStudents(struct Student* head, int n);
void filterBottomStudents(struct Student* head, int n);

void savePassword(const char* password);
void loadPassword(char* password);
int login();
void modifyPassword();
int verifyPassword();

void downloadToFile(struct Student* head, const char* filename);
void freeStudents(struct Student* head);



struct Student* createStudent(int rollNumber, const char* name,long long int mob_no, float marks) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->rollNumber = rollNumber;
    newStudent->mb_no = mob_no; 
    strncpy(newStudent->name, name, sizeof(newStudent->name));
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}

int addStudent(struct Student** head, int rollNumber, const char* name,long long int mb_no, float marks) {
    if (rollNumber<0) {
        printf("Invalid input. Roll Number must be non-negative\n"); 
        return 1;
    }
    if (!(marks >= 0 && marks <= 100)) {
        printf("Invalid input. Marks must be in the range of 0 to 100.\n");
        return 1;
    }

    struct Student* newStudent = createStudent(rollNumber, name, mb_no, marks);
    struct Student* temp = *head;
    int flag = searchStudent(*head, rollNumber);

    if (flag == 1) {
        printf("Student roll number is used. Cannot add a new student for this roll number.\n");
        return 1;
    } 
    else 
    {
        if (*head == NULL) {
            *head = newStudent;
        } else {
            while (temp->next != NULL)
                temp = temp->next;
              temp->next = newStudent;
        }
        return 0;
    }
}

void read_file(char str[50], struct Student** head) {
    FILE *fp = fopen(str, "r");
    char line[500];
    if (fp == NULL) {
        printf("Error in opening the file\n");
    } else {
        int count = 0;
        char *rno, *name, *mbno, *marks;
        fgets(line, 500, fp) != NULL;
        while (fgets(line, 500, fp) != NULL) {
            strtok(line, ","); 

            rno = strtok(NULL, ",");
            int rollNumber = atoi(rno); 

            name = strtok(NULL, ",");
            mbno = strtok(NULL, ",");
            long long int mobileNumber = atoll(mbno); 

            marks = strtok(NULL, ",");
            float studentMarks = atof(marks); 
            addStudent(head, rollNumber, name, mobileNumber, studentMarks);
        }
        fclose(fp); 
        printf("Records uploaded to list from file\n");
    }
}

// Function to display all student records
void displayStudents(struct Student* head) {
    if(head==NULL)
	    printf("No students in records.\n");
    else
    {
    	printf("Student Records:\n");
   	while (head != NULL) {
        	printf("Roll Number: %d\n", head->rollNumber);
        	printf("Name: %s\n", head->name);
       		printf("Mobile Number: %lld\n", head->mb_no);
        	printf("Marks: %.2f\n", head->marks);
        	printf("-------------------------\n");
        	head = head->next;
    	}
    }
}

// Function to free memory allocated for the linked list
void freeStudents(struct Student* head) {
    while (head != NULL) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to modify a student's record
void modifyStudent(struct Student* head, int rollNumber) {
    int choice;
    while (head != NULL) {
        if (head->rollNumber == rollNumber) {
            do {
                printf("Modify Student Record Menu:\n");
                printf("1. Change Name\n");
                printf("2. Change Mobile Number\n");
                printf("3. Change Marks\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Enter new Name: ");
                        scanf("%s", head->name);
                        printf("Name modified\n");
                        break;
                    case 2:
                        printf("Enter new Mobile Number: ");
                        scanf("%lld", &head->mb_no);
                        printf("Mobile number modified\n");
                        break;
                    case 3:
                        printf("Enter new Marks: ");
                        scanf("%f", &head->marks);
                        printf("Marks modifie\n");
                        break;
                    case 4:
                        printf("Student record modified successfully!\n");
                        return; // Exit the modification loop
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 4); // Continue the loop until the user chooses to exit
            return;
        }
        head = head->next;
    }
    printf("Student with Roll Number %d not found.\n", rollNumber);
}


// Function to delete a student by roll number
void deleteStudent(struct Student** head, int rollNumber) {
    struct Student* current = *head;
    struct Student* previous = NULL;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            printf("Student with Roll Number %d deleted successfully!\n", rollNumber);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Student with Roll Number %d not found.\n", rollNumber);
}

// Function to calculate statistics (average, highest, and lowest marks)
void calculateStatistics(struct Student* h) {
    struct Student* head=sortStudentsByMarks(h);
    float sum = 0.0;
    float highestMarks = 0.0;
    float lowestMarks = 100.0;
    int count = 0;
    float marksArray[100]; // Array to store student marks for various statistics
    while (head != NULL) {
        float marks = head->marks;
        sum += marks;
        if (marks > highestMarks) {
            highestMarks = marks;
        }
        if (marks < lowestMarks) {
            lowestMarks = marks;
        }
        marksArray[count] = marks;//in an array we are storing the studnt marks
        count++;
        head = head->next;
    }

    if (count > 0) {
        printf("Statistics:\n");
        printf("Average Marks: %.2f\n", sum / count);
        printf("Highest Marks: %.2f\n", highestMarks);
        printf("Lowest Marks: %.2f\n", lowestMarks);

        // Calculate and display the median
        if (count % 2 == 0) {
            float median = (marksArray[(count / 2) - 1] + marksArray[count / 2]) / 2.0;
            printf("Median Marks: %.2f\n", median);
        } else {
            float median = marksArray[(count)/ 2];
            printf("Median Marks: %.2f\n", median);
        }
// Calculate and display the standard deviation
        float sumSquaredDiff = 0.0;
        for (int i = 0; i < count; i++) {
            float diff = marksArray[i] - (sum / count);
            sumSquaredDiff += diff * diff;
        }
        float stdDeviation = sqrt(sumSquaredDiff / count);
        printf("Standard Deviation: %.2f\n", stdDeviation);

        // Calculate and display count of students in grade ranges
        int gradeA = 0, gradeB = 0, gradeC = 0,gradeD = 0, gradeE = 0, gradeF = 0;
        for (int i = 0; i < count; i++) {
            if (marksArray[i] >= 90) {
                gradeA++;
            } 
            else if (marksArray[i] >= 80) {
                gradeB++;
            } 
             else if (marksArray[i] >= 70) {
                gradeC++;
            } 
             else if (marksArray[i] >= 60) {
                gradeD++;
            } 
             else if (marksArray[i] >= 40) {
                gradeE++;
            } 
            else {
                gradeF++;
            }
        }
 printf("Number of Students in Grade A : %d\n", gradeA);
      printf("Number of Students in Grade B : %d\n", gradeB);
      printf("Number of Students in Grade C : %d\n", gradeC);
      printf("Number of Students in Grade D : %d\n", gradeD);
      printf("Number of Students in Grade E : %d\n", gradeE);
      printf("Number of Students in Grade F : %d\n", gradeF);
        // Calculate and display the mode (most frequent value)
        int mode = 0;
        int maxCount = 0;
        for (int i = 0; i < count; i++) {
            int currentCount = 1;
            for (int j = i + 1; j < count; j++) {
                if (marksArray[i] == marksArray[j]) {
                    currentCount++;
                }
            }
            if (currentCount > maxCount) {
                mode = marksArray[i];
                maxCount = currentCount;
            }
        }
        printf("Mode: %d\n", mode);

        // Calculate and display the variance
        float variance = sumSquaredDiff / (count - 1); // Sample variance
        printf("Variance: %.2f\n", variance);

        // Calculate and display the interquartile range (IQR)
        int quartile25 = (int)(0.25 * count);
        int quartile75 = (int)(0.75 * count);
        float iqr = marksArray[quartile75] - marksArray[quartile25];
        printf("Interquartile Range (IQR): %.2f\n", iqr);
    } else {
        printf("No students in the records.\n");
    }
}
// Function to search for a student by roll number
int searchStudent(struct Student* head, int rollNumber) {
    while (head != NULL) {
        if (head->rollNumber == rollNumber) {
            printf("Roll Number: %d\n", head->rollNumber);
            printf("Name: %s\n", head->name);
            printf("Mobile Number: %lld\n", head->mb_no);
            printf("Marks: %.2f\n", head->marks);
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void searchStudentByMobile(struct Student* head, long long int mb_no) {
    int found = 0;
    while (head != NULL) {
        if (head->mb_no == mb_no) {
            printf("Student Found:\n");
            printf("Roll Number: %d\n", head->rollNumber);
            printf("Name: %s\n", head->name);
            printf("Mobile Number: %lld\n", head->mb_no);
            printf("Marks: %.2f\n", head->marks);
            found = 1;
        }
        head = head->next;
    }

    if (!found) {
        printf("No student with Mobile Number %d found.\n", mb_no);
    }
}

void searchStudentByName(struct Student* head, const char* searchName) {
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->name, searchName) == 0) {
            printf("Student Found:\n");
            printf("Roll Number: %d\n", head->rollNumber);
            printf("Name: %s\n", head->name);
            printf("Mobile Number: %lld\n", head->mb_no);
            printf("Marks: %.2f\n", head->marks);
            found = 1;
        }
        head = head->next;
    }

    if (!found) {
        printf("No student with the name '%s' found.\n", searchName);
    }
}

// Function to compare two students for sorting
int compareStudents(const struct Student* student1, const struct Student* student2) {
    return student1->rollNumber - student2->rollNumber;
}

void sortStudents(const struct Student* head) {
    struct Student* sorted = NULL;

    while (head != NULL) {
        struct Student* current = createStudent(head->rollNumber, head->name, head->mb_no, head->marks);
        struct Student* temp = sorted;
        struct Student* prev = NULL;

        if (sorted == NULL || compareStudents(current, sorted) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            while (temp != NULL && compareStudents(current, temp) >= 0) {
                prev = temp;
                temp = temp->next;
            }
            current->next = temp;
            if (prev != NULL) {
                prev->next = current;
            } else {
                sorted = current;
            }
        }
        head = head->next;
    }

    displayStudents(sorted);
}

// Function to compare two students for sorting by name
int compareStudentsByName(const struct Student* student1, const struct Student* student2) {
    return strcmp(student1->name, student2->name);
}

// Function to sort students by name (ascending) and create a new sorted list
void sortStudentsByName(const struct Student* head) {
    struct Student* sorted = NULL;

    while (head != NULL) {
        struct Student* current = createStudent(head->rollNumber, head->name, head->mb_no, head->marks);
        struct Student* temp = sorted;
        struct Student* prev = NULL;

        if (sorted == NULL || compareStudentsByName(current, sorted) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            while (temp != NULL && compareStudentsByName(current, temp) >= 0) {
                prev = temp;
                temp = temp->next;
            }
            current->next = temp;
            if (prev != NULL) {
                prev->next = current;
            } else {
                sorted = current;
            }
        }

        head = head->next;
    }

    displayStudents(sorted);
}

// Function to compare two students for sorting by marks
int compareStudentsByMarks(const struct Student* student1, const struct Student* student2) {
    return (int)(student1->marks - student2->marks);
}

struct Student* sortStudentsByMarks(const struct Student* head) {
    struct Student* sorted = NULL;

    while (head != NULL) {
        struct Student* current = createStudent(head->rollNumber, head->name, head->mb_no, head->marks);
        struct Student* temp = sorted;
        struct Student* prev = NULL;

        if (sorted == NULL || compareStudentsByMarks(current, sorted) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            while (temp != NULL && compareStudentsByMarks(current, temp) >= 0) {
                prev = temp;
                temp = temp->next;
            }
            current->next = temp;
            if (prev != NULL) {
                prev->next = current;
            } else {
                sorted = current;
            }
        }

        head = head->next;
    }

    //displayStudents(sorted);
    return sorted;
}

struct Student* reverseStudents(struct Student* head) {
    struct Student* prev = NULL;
    struct Student* current = head;
    struct Student* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev; // Update the head to point to the new first node (previously the last node)

    return head;
}

// Function to create a copy of the linked list
struct Student* copyStudents(const struct Student* head) {
    struct Student* copied = NULL;
    struct Student* tail = NULL;

    while (head != NULL) {
        struct Student* newStudent = createStudent(head->rollNumber, head->name, head->mb_no, head->marks);
        if (copied == NULL) {
            copied = newStudent;
            tail = newStudent;
        } else {
            tail->next = newStudent;
            tail = newStudent;
        }
        head = head->next;
    }

    return copied;
}

void filterBottomStudents(struct Student* head, int n) {
    struct Student* copiedHead = copyStudents(head);

    // Sort the copied list by marks (ascending order)
    copiedHead=sortStudentsByMarks(copiedHead);

    int count = 0;
    printf("Bottom %d Students with Lowest Marks:\n", n);
    while (copiedHead != NULL && count < n) {
        printf("Roll Number: %d\n", copiedHead->rollNumber);
        printf("Name: %s\n", copiedHead->name);
        printf("Marks: %.2f\n", copiedHead->marks);
        printf("Mobile Number: %lld\n", head->mb_no);
        printf("-------------------------\n");
        copiedHead = copiedHead->next;
        count++;
    }

    // Free the memory allocated for the copied list
    freeStudents(copiedHead);
}

void filterTopStudents(struct Student* head, int n) {
    struct Student* copiedHead = copyStudents(head);
    
    // Sort the copied list by marks in descending order
    copiedHead=sortStudentsByMarks(copiedHead);
    
    // Reverse the sorted list to get the top students with the highest marks
    copiedHead = reverseStudents(copiedHead);

    int count = 0;
    printf("Top %d Students with Highest Marks:\n", n);
    while (copiedHead != NULL && count < n) {
        printf("Roll Number: %d\n", copiedHead->rollNumber);
        printf("Name: %s\n", copiedHead->name);
        printf("Marks: %.2f\n", copiedHead->marks);
        printf("Mobile Number: %lld\n", head->mb_no);
        printf("-------------------------\n");
        copiedHead = copiedHead->next;
        count++;
    }

    // Free the memory allocated for the copied list
    freeStudents(copiedHead);
}

void savePassword(const char* password) {
  FILE *file = fopen("password.txt", "w");
  if (file != NULL) {
    fprintf(file, "%s", password);
    fclose(file);
  } 
  else {
    printf("Failed to save password to the file.\n");
  }
}

void loadPassword(char* password) {
  FILE *file = fopen("password.txt", "r");
  if (file != NULL) {
    fscanf(file, "%s", password);
    fclose(file);
  } else {
    printf("Password file not found. Using default password.\n");
  }
}

int login() {
    char enteredUsername[50];
    char enteredPassword[50];
    printf("Username: ");
    scanf("%s", enteredUsername);
    printf("Password: ");
    scanf("%s", enteredPassword);
    if (strcmp(enteredUsername, USERNAME) == 0 && strcmp(enteredPassword, PASSWORD) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

int verifyPassword() {
    char enteredPassword[MAX_PASSWORD_LENGTH];
    printf("Enter the current password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, PASSWORD) == 0) {
        return 1; // Password verification successful
    } else {
        printf("Incorrect current password. Password modification failed.\n");
        return 0; // Password verification failed
    }
}

void modifyPassword() {
    if (verifyPassword()) {
        char newPassword[MAX_PASSWORD_LENGTH];
        char confirmPassword[MAX_PASSWORD_LENGTH];

        printf("Enter the new password: ");
        scanf("%s", newPassword); 
        printf("Confirm the new password: ");
        scanf("%s", confirmPassword);

        if (strcmp(newPassword, confirmPassword) == 0) {
            strncpy(PASSWORD, newPassword, MAX_PASSWORD_LENGTH);
            savePassword(newPassword);  // Save the new password
            printf("Password has been modified successfully.\n");
        } else {
            printf("Passwords do not match. Password modification failed.\n");
        }
    }
}

void downloadToFile(struct Student* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error in opening the file for writing.\n");
        return;
    }
    int choice;
        printf("Download:\n");
        printf("1. All fields\n");
        printf("2. Roll number and name\n");
        printf("3. Name and marks\n");
        printf("4. Name and mobile number\n");
        printf("5. Name, roll number, and marks\n");
        printf("6. Name, roll number, and mobile number\n");
        printf("7. Cancel\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        struct Student* temp = head;
        switch (choice) {
            case 1:
              fprintf(fp, "Roll Number,Name,Mobile Number,Marks\n");
                while (temp != NULL) {
                  
                    fprintf(fp, "%d,%s,%lld,%.2f\n", temp->rollNumber, temp->name, temp->mb_no, temp->marks);
                    temp = temp->next;
                }
                break;
            case 2:
              fprintf(fp, "Roll Number,Name\n");
                while (temp != NULL) {
                  
                    fprintf(fp, "%d,%s\n", temp->rollNumber, temp->name);
                    temp = temp->next;
                }
                break;
            case 3:
                fprintf(fp, "Name,Marks\n");
                while (temp != NULL) {
                
                    fprintf(fp, "%s,%.2f\n", temp->name, temp->marks);
                    temp = temp->next;
                }
                break;
            case 4:
            fprintf(fp, "Name,Mobile Number\n");
                while (temp != NULL) {
                    
                    fprintf(fp, "%s,%lld\n", temp->name, temp->mb_no);
                    temp = temp->next;
                }
                break;
            case 5:
              fprintf(fp, "Roll Number,Name,Marks\n");
                while (temp != NULL) {
                    
                    fprintf(fp, "%d,%s,%.2f\n", temp->rollNumber, temp->name, temp->marks);
                    temp = temp->next;
                }
                break;
            case 6:
                fprintf(fp, "Roll Number,Name,Mobile Number\n");
                while (temp != NULL) {
                
                    fprintf(fp, "%d,%s,%lld\n", temp->rollNumber, temp->name, temp->mb_no);
                    temp = temp->next;
                }
                break;
            case 7:
                printf("No downloads\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    fclose(fp);
    printf("Student records have been written to %s successfully.\n", filename);
}

int main() 
{
  loadPassword(PASSWORD);
  if (!login()) {
    printf("Authentication failed. Exiting...\n");
    return 1;
  }
  struct Student *head = NULL,*temp;
  int choice;
  int rollNumber;
  char name[50] ,str[50];;
  long long int mb_no;
  float marks;
  int n,v;

  while (1) {
    printf("\nStudent Management System\n");
    printf("1. Add Student\n");
    printf("2. Upload from file\n");
    printf("3. Display Students\n");
    printf("4. Modify Student Record\n");
    printf("5. Delete Student\n");
    printf("6. Calculate Statistics\n");
    printf("7. Search Student by roll number\n");
    printf("8. Search Student by mobile number\n");
    printf("9. Search Student by name\n");
    printf("10. Sort Students by Roll Number\n");
    printf("11. Sort Students by name\n");
    printf("12. Sort Students by marks\n");
    printf("13. Display n students with highest marks\n");
    printf("14. Display n students with lowest marks\n");
    printf("15. Change Password\n");
    printf("16. Download report\n");
    printf("17. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter Roll Number: ");
        scanf("%d", &rollNumber);
        printf("Enter Name: ");
        scanf("%s", name);
        printf("Enter Mobile number: ");
        scanf("%lld", &mb_no);
        printf("Enter Marks: ");
        scanf("%f", &marks);
        v=addStudent(&head, rollNumber, name, mb_no, marks);
        if(v==0)
          printf("Student added successfully!\n");
        break;
      case 2: 
        printf("Enter filename: ");
        scanf("%s", str);
        read_file(str, &head); 
        break;
      case 3:
        displayStudents(head);
        break;
      case 4:
        printf("Enter Roll Number to modify: ");
        scanf("%d", &rollNumber);
        modifyStudent(head, rollNumber);
        break;
      case 5:
        printf("Enter Roll Number to delete: ");
        scanf("%d", &rollNumber);
        deleteStudent(&head, rollNumber);
        break;
      case 6:
        calculateStatistics(head);
        break;
      case 7:
        printf("Enter Roll Number to search: ");
        scanf("%d", &rollNumber);
        int res=searchStudent(head, rollNumber);
        if(res==0)
          printf("Student with Roll Number %d not found.\n", rollNumber);
        break;
      case 8:
        printf("Enter Mobile Number to search: ");
        scanf("%lld", &mb_no);
        searchStudentByMobile(head, mb_no);
        break;
      case 9:
        printf("Enter Name to search: ");
        char searchName[50];
        scanf("%s", searchName);
        searchStudentByName(head, searchName);
        break;
      case 10:
        sortStudents(head);
        break;
      case 11:
        sortStudentsByName(head);
        break;
      case 12:
        temp=sortStudentsByMarks(head);
        displayStudents(temp);
        break;
      case 13:
        printf("Enter n: ");
        scanf("%d", &n);
        filterTopStudents(head, n);
        break;
      case 14:
        printf("Enter n: ");
        scanf("%d", &n);
        filterBottomStudents(head, n);
        break;
      case 15:
        modifyPassword();
        break; 
      case 16: 
        printf("Enter filename: ");
        scanf("%s", str);
        downloadToFile( head,str); 
        break;
      case 17:
        freeStudents(head);
        exit(0);
        default:
        printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}
