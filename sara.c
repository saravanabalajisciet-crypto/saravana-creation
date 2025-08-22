#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LEN 20
#define STATUS_LEN 10

typedef struct Attendance {
    int studentID;
    char date[DATE_LEN];
    char status[STATUS_LEN];  // "Present" or "Absent"
    struct Attendance* next;
} Attendance;

// Create new attendance record
Attendance* createRecord(int id, const char* date, const char* status) {
    Attendance* newNode = (Attendance*)malloc(sizeof(Attendance));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->studentID = id;
    strncpy(newNode->date, date, DATE_LEN);
    strncpy(newNode->status, status, STATUS_LEN);
    newNode->next = NULL;
    return newNode;
}

// Add attendance record
void addRecord(Attendance** head, int id, const char* date, const char* status) {
    Attendance* newNode = createRecord(id, date, status);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Attendance* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Delete record by student ID and date
void deleteRecord(Attendance** head, int id, const char* date) {
    if (*head == NULL) return;

    Attendance *temp = *head, *prev = NULL;

    while (temp && (temp->studentID != id || strcmp(temp->date, date) != 0)) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Record not found.\n");
        return;
    }

    if (!prev) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Record deleted successfully.\n");
}

// Search record by student ID and date
Attendance* searchRecord(Attendance* head, int id, const char* date) {
    while (head) {
        if (head->studentID == id && strcmp(head->date, date) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Display attendance for a specific date
void displayByDate(Attendance* head, const char* date) {
    int found = 0;
    while (head) {
        if (strcmp(head->date, date) == 0) {
            printf("ID: %d, Date: %s, Status: %s\n", head->studentID, head->date, head->status);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("No records found for date %s.\n", date);
}

// Display all records in reverse (recursively)
void displayReverse(Attendance* head) {
    if (head == NULL)
        return;
    displayReverse(head->next);
    printf("ID: %d, Date: %s, Status: %s\n", head->studentID, head->date, head->status);
}

// Clone attendance list
Attendance* cloneList(Attendance* head) {
    if (!head)
        return NULL;

    Attendance* newHead = createRecord(head->studentID, head->date, head->status);
    Attendance* curr = newHead;
    head = head->next;

    while (head) {
        curr->next = createRecord(head->studentID, head->date, head->status);
        curr = curr->next;
        head = head->next;
    }

    return newHead;
}

// Free entire list
void freeList(Attendance* head) {
    Attendance* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main menu
int main() {
    Attendance* attendanceList = NULL;
    Attendance* result = NULL;
    Attendance* cloned = NULL;

    int choice, id;
    char date[DATE_LEN], status[STATUS_LEN];

    while (1) {
        printf("\n===== Student Attendance Monitoring System =====\n");
        printf("1. Add Attendance Record\n");
        printf("2. Delete Record\n");
        printf("3. Search Record by ID and Date\n");
        printf("4. Display Attendance for a Date\n");
        printf("5. Reverse Display of Records\n");
        printf("6. Clone Attendance List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Date (YYYY-MM-DD): ");
                fgets(date, DATE_LEN, stdin);
                date[strcspn(date, "\n")] = 0;

                printf("Enter Status (Present/Absent): ");
                fgets(status, STATUS_LEN, stdin);
                status[strcspn(status, "\n")] = 0;

                addRecord(&attendanceList, id, date, status);
                printf("Record added successfully.\n");
                break;

            case 2:
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Date of record: ");
                fgets(date, DATE_LEN, stdin);
                date[strcspn(date, "\n")] = 0;

                deleteRecord(&attendanceList, id, date);
                break;

            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Date: ");
                fgets(date, DATE_LEN, stdin);
                date[strcspn(date, "\n")] = 0;

                result = searchRecord(attendanceList, id, date);
                if (result)
                    printf("Found: ID: %d, Date: %s, Status: %s\n", result->studentID, result->date, result->status);
                else
                    printf("Record not found.\n");
                break;

            case 4:
                printf("Enter Date to display attendance: ");
                fgets(date, DATE_LEN, stdin);
                date[strcspn(date, "\n")] = 0;
                displayByDate(attendanceList, date);
                break;

            case 5:
                printf("Attendance in Reverse Order:\n");
                displayReverse(attendanceList);
                break;

            case 6:
                cloned = cloneList(attendanceList);
                printf("Cloned List:\n");
                displayByDate(cloned, ""); // show all
                freeList(cloned);
                break;

            case 7:
                freeList(attendanceList);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
