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
    int choice;
    do {
        printf("\n=== TRAIN MANAGEMENT ===\n");
        printf("1. Add New Train\n");
        printf("2. View All Trains\n");
        printf("3. Check Seat Availability\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(train_count < 10) {
                    printf("Enter Train Number: ");
                    scanf("%d", &trains[train_count].number);
                    printf("Enter Train Name: ");
                    scanf(" %[^\n]", trains[train_count].name);
                    printf("Enter Source Station: ");
                    scanf(" %[^\n]", trains[train_count].source);
                    printf("Enter Destination Station: ");
                    scanf(" %[^\n]", trains[train_count].destination);
                    printf("Enter Total Seats: ");
                    scanf("%d", &trains[train_count].total_seats);
                    trains[train_count].available_seats = trains[train_count].total_seats;
                    
                    train_count++;
                    printf("✅ Train added successfully!\n");
                } else {
                    printf("❌ Maximum train limit reached! Cannot add more trains.\n");
                }
                break;
                
            case 2:
                if(train_count == 0) {
                    printf("❌ No trains available! Please add trains first.\n");
                } else {
                    printf("\n=== ALL TRAINS ===\n");
                    printf("Train No\tTrain Name\t\tSource\t\tDestination\tAvailable Seats\n");
                    printf("------------------------------------------------------------------------\n");
                    for(int i = 0; i < train_count; i++) {
                        printf("%d\t\t%-15s\t%-10s\t%-12s\t%d/%d\n",
                               trains[i].number,
                               trains[i].name,
                               trains[i].source,
                               trains[i].destination,
                               trains[i].available_seats,
                               trains[i].total_seats);
                    }
                }
                break;
                
            case 3:
                if(train_count == 0) {
                    printf("❌ No trains available!\n");
                } else {
                    printf("Available Trains:\n");
                    for(int i = 0; i < train_count; i++) {
                        printf("Train %d: %s - %d seats available\n", 
                               trains[i].number, trains[i].name, trains[i].available_seats);
                    }
                }
                break;
                
            case 4:
                printf("Returning to main menu...\n");
                break;
                
            default:
                printf("❌ Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
}

void bookTicket() {
    if(passenger_count >= 100) {
        printf("❌ No more tickets available! Maximum passenger limit reached.\n");
        return;
    }
    
    int train_no;
    printf("Enter Train Number: ");
    scanf("%d", &train_no);
    
    // Find the train
    int train_index = -1;
    for(int i = 0; i < train_count; i++) {
        if(trains[i].number == train_no) {
            train_index = i;
            break;
        }
    }
    
    if(train_index == -1) {
        printf("❌ Train not found! Please check train number.\n");
        return;
    }
    
    if(trains[train_index].available_seats <= 0) {
        printf("❌ No seats available on this train!\n");
        return;
    }
    
    // Get passenger details
    struct Passenger *p = &passengers[passenger_count];
    p->pnr = pnr_counter++;
    p->train_number = train_no;
    
    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", p->name);
    printf("Enter Age: ");
    scanf("%d", &p->age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &p->gender);
    
    // Allocate seat
    p->seat_number = trains[train_index].total_seats - trains[train_index].available_seats + 1;
    strcpy(p->status, "Confirmed");
    p->fare = 500.0; // Fixed fare for now
    
    trains[train_index].available_seats--;
    passenger_count++;
    
    printf("\n🎫 *** TICKET BOOKED SUCCESSFULLY! ***\n");
    printf("📋 PNR Number: %d\n", p->pnr);
    printf("👤 Passenger: %s\n", p->name);
    printf("🚆 Train: %d - %s\n", p->train_number, trains[train_index].name);
    printf("💺 Seat Number: %d\n", p->seat_number);
    printf("💰 Fare: ₹%.2f\n", p->fare);
    printf("✅ Status: %s\n", p->status);
}

void cancelTicket() {
    printf("Ticket cancellation - To be implemented by Member 3\n");
}

void showReports() {
    printf("\n=== SYSTEM REPORTS ===\n");
    
    if(passenger_count == 0 && train_count == 0) {
        printf("❌ No data available for reports!\n");
        return;
    }
    
    // Calculate statistics
    int confirmed_tickets = 0;
    int cancelled_tickets = 0;
    float total_revenue = 0.0;
    float total_refunds = 0.0;
    
    for(int i = 0; i < passenger_count; i++) {
        if(strcmp(passengers[i].status, "Confirmed") == 0) {
            confirmed_tickets++;
            total_revenue += passengers[i].fare;
        } else if(strcmp(passengers[i].status, "Cancelled") == 0) {
            cancelled_tickets++;
            total_refunds += passengers[i].fare * 0.8; // 80% refund
        }
    }
    
    printf("📊 BOOKING STATISTICS:\n");
    printf("────────────────────────\n");
    printf("✅ Confirmed Tickets: %d\n", confirmed_tickets);
    printf("❌ Cancelled Tickets: %d\n", cancelled_tickets);
    printf("💰 Total Revenue: ₹%.2f\n", total_revenue);
    printf("💸 Total Refunds Given: ₹%.2f\n", total_refunds);
    printf("🎫 Net Revenue: ₹%.2f\n", total_revenue - total_refunds);
    
    printf("\n🚆 TRAIN WISE REPORT:\n");
    printf("────────────────────────\n");
    for(int i = 0; i < train_count; i++) {
        int passengers_on_train = 0;
        for(int j = 0; j < passenger_count; j++) {
            if(passengers[j].train_number == trains[i].number && 
               strcmp(passengers[j].status, "Confirmed") == 0) {
                passengers_on_train++;
            }
        }
        printf("Train %d: %s\n", trains[i].number, trains[i].name);
        printf("   Route: %s to %s\n", trains[i].source, trains[i].destination);
        printf("   Passengers: %d | Available Seats: %d/%d\n\n", 
               passengers_on_train, trains[i].available_seats, trains[i].total_seats);
    }
    
    printf("👥 PASSENGER DEMOGRAPHICS:\n");
    printf("────────────────────────\n");
    int male_count = 0, female_count = 0;
    for(int i = 0; i < passenger_count; i++) {
        if(passengers[i].gender == 'M' || passengers[i].gender == 'm') male_count++;
        else if(passengers[i].gender == 'F' || passengers[i].gender == 'f') female_count++;
    }
    printf("Male Passengers: %d\n", male_count);
    printf("Female Passengers: %d\n", female_count);
}

void saveData() {
    printf("Data saving - To be implemented by Member 4\n");
}

void loadData() {
    FILE *file = fopen("railway_data.txt", "r");
    if(file == NULL) {
        printf("ℹ️  No previous data found. Starting fresh system.\n");
        return;
    }
    
    // Load basic counts and counters
    fscanf(file, "%d %d %d", &train_count, &passenger_count, &pnr_counter);
    
    // Load all train data
    for(int i = 0; i < train_count; i++) {
        fscanf(file, "%d %s %s %s %d %d",
               &trains[i].number,
               trains[i].name,
               trains[i].source,
               trains[i].destination,
               &trains[i].total_seats,
               &trains[i].available_seats);
    }
    
    // Load all passenger data
    for(int i = 0; i < passenger_count; i++) {
        fscanf(file, "%d %s %d %c %d %d %s %f",
               &passengers[i].pnr,
               passengers[i].name,
               &passengers[i].age,
               &passengers[i].gender,
               &passengers[i].train_number,
               &passengers[i].seat_number,
               passengers[i].status,
               &passengers[i].fare);
    }
    
    fclose(file);
    printf("✅ Previous data loaded successfully!\n");
    printf("📊 Loaded: %d trains, %d passengers\n", train_count, passenger_count);
}
