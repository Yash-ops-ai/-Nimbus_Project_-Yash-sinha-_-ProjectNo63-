#include <stdio.h>
#include <string.h>

// ==================== STRUCTURES ====================
struct Train {
    int number;
    char name[50];
    char source[30];
    char destination[30];
    int total_seats;
    int available_seats;
};

struct Passenger {
    int pnr;
    char name[50];
    int age;
    char gender;
    int train_number;
    int seat_number;
    char status[20];
    float fare;
};

// ==================== GLOBAL VARIABLES ====================
struct Train trains[10];
struct Passenger passengers[100];
int train_count = 0;
int passenger_count = 0;
int pnr_counter = 10001;

// ==================== FUNCTION DECLARATIONS ====================
void displayMenu();
void manageTrains();
void bookTicket();
void cancelTicket();
void showReports();
void saveData();
void loadData();

// ==================== MAIN FUNCTION ====================
int main() {
    printf("=========================================\n");
    printf("    RAILWAY BOOKING SYSTEM - PROJECT 63\n");
    printf("=========================================\n");
    
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: manageTrains(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: showReports(); break;
            case 5: saveData(); break;
            case 6: printf("Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 6);
    
    return 0;
}

void displayMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Manage Trains\n");
    printf("2. Book Ticket\n");
    printf("3. Cancel Ticket\n");
    printf("4. Show Reports\n");
    printf("5. Save Data\n");
    printf("6. Exit\n");
    printf("===============================\n");
}

// TEMPLATE FUNCTIONS - WILL BE FILLED BY TEAM MEMBERS
void manageTrains() {
    printf("Train management - To be implemented by Member 1\n");
}

void bookTicket() {
    printf("Ticket booking - To be implemented by Member 2\n");
}

void cancelTicket() {
    printf("Ticket cancellation - To be implemented by Member 3\n");
}

void showReports() {
    printf("Reports - To be implemented by Member 4\n");
}

void saveData() {
    printf("Data saving - To be implemented by Member 4\n");
}

void loadData() {
    // Will be implemented later
}
