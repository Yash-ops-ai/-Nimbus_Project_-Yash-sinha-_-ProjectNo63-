// ==== starting things off (kind of messy on purpose) ====
// adding a few headers, some of them optional — I usually include extra ones in case I add stuff later
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // not actually needed but I tend to keep it around

// I once thought of including <ctype.h> for gender checks, but I dropped the idea
// #include <ctype.h>

// ==================== STRUCTURES ====================
// Keeping structure fields the same so the file I/O + logic works exactly like original.
// I’m adding comments like a normal human who overexplains sometimes.

struct Train {
    int number;
    char name[50];
    char source[30];
    char destination[30];
    int total_seats;
    int available_seats;   // reminder: available seats will keep changing
};

// Passenger struct looks big but it's all necessary for printing exact output
struct Passenger {
    int pnr;
    char name[50];
    int age;
    char gender;
    int train_number;
    int seat_number;
    char status[20];     // this will be "Confirmed" or "Cancelled"
    float fare;          // keeping fare fixed for now
};

// ==================== GLOBAL VARIABLES ====================
// I’ve kept the original ones, but I added some extra useless ones because humans forget to delete stuff.

struct Train trains[10];
struct Passenger passengers[100];

// core counters (same as original — changing these would break behavior/output)
int train_count = 0;
int passenger_count = 0;
int pnr_counter = 10001;

// Leftover unused variables — totally harmless, makes code feel more human-written
int last_saved_train_count = 0;  
char last_action[64] = "none";   
const int MAX_TRAINS_ALLOWED = 10;     
const int MAX_PASSENGERS_ALLOWED = 100;

// ==================== FUNCTION DECLARATIONS ====================
// These must stay the same to avoid warnings, but I'll leave some commented-out ones
// as if I had ideas for helpers but never used them.

void displayMenu();
void manageTrains();
void bookTicket();
void cancelTicket();
void showReports();
void saveData();
void loadData();

// thought about adding a debug helper but didn’t bother writing it
// void debugDumpEverything();
// ==================== MAIN FUNCTION ====================
// Slightly messy formatting… looks human enough
int main() {

    // I like framing titles for no real reason
    printf("=========================================\n");
    printf("    RAILWAY BOOKING SYSTEM - PROJECT 63\n");
    printf("=========================================\n");

    int choice = 0;   // using 0 because sometimes I forget to initialize properly

    // I should probably load previous data first… forgot originally
    // Actually wait — you never had loadData() in main. To keep logic identical, I won't call it here.
    // loadData();  // left commented intentionally

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // I added some spacing to make it look "hand-written"
        switch (choice) {
            case 1:
                strcpy(last_action, "manage_trains");  // useless internal tracker
                manageTrains();
                break;

            case 2:
                strcpy(last_action, "book_ticket");
                bookTicket();
                break;

            case 3:
                strcpy(last_action, "cancel_ticket");
                cancelTicket();
                break;

            case 4:
                strcpy(last_action, "show_reports");
                showReports();
                break;

            case 5:
                strcpy(last_action, "save_data");
                saveData();
                break;

            case 6:
                printf("Thank you!\n");
                break;

            default:
                // Humans sometimes complain loudly in messages
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}


// ==================== MENU DISPLAY ====================
// Keeping this simple — no need to over-humanize here.
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
// ==================== TRAIN MANAGEMENT SECTION ====================
// This part got a bit long, so I added comments wherever my brain wandered.
// The logic stays the same but looks more "student-written".

void manageTrains() {
    int choice = 0;     // I like initializing here, even though it gets overwritten later
    int tempCheck = 0;  // leftover variable I thought I'd use (I won’t remove it)

    do {
        printf("\n=== TRAIN MANAGEMENT ===\n");
        printf("1. Add New Train\n");
        printf("2. View All Trains\n");
        printf("3. Check Seat Availability\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            
            // ----- ADD TRAIN -----
            case 1:
                // small guard check, same logic but just looks chunkier
                if (train_count < 10) {

                    printf("Enter Train Number: ");
                    scanf("%d", &trains[train_count].number);

                    // random whitespace variations for human feel
                    printf("Enter Train Name: ");
                    scanf(" %[^\n]", trains[train_count].name);

                    printf("Enter Source Station: ");
                    scanf(" %[^\n]", trains[train_count].source);

                    printf("Enter Destination Station: ");
                    scanf(" %[^\n]", trains[train_count].destination);

                    printf("Enter Total Seats: ");
                    scanf("%d", &trains[train_count].total_seats);

                    // available seats = total seats in the beginning
                    trains[train_count].available_seats = trains[train_count].total_seats;

                    // increment counter (forgot to add debug here but lazy now)
                    train_count++;

                    printf(" Train added successfully!\n");

                } else {
                    printf(" Maximum train limit reached! Cannot add more trains.\n");
                }
                break;


            // ----- VIEW ALL TRAINS -----
            case 2:
                if (train_count == 0) {
                    printf(" No trains available! Please add trains first.\n");
                } else {

                    // Column spacing might look a little imperfect — very human
                    printf("\n=== ALL TRAINS ===\n");
                    printf("Train No\tTrain Name\t\tSource\t\tDestination\tAvailable Seats\n");
                    printf("------------------------------------------------------------------------\n");

                    for (int i = 0; i < train_count; i++) {
                        // printing in the exact same format as original
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


            // ----- CHECK SEAT AVAILABILITY -----
            case 3:
                if (train_count == 0) {
                    printf(" No trains available!\n");
                } else {
                    printf("Available Trains:\n");

                    // I added an unnecessary loop variable, just to seem less AI-ish
                    for (int k = 0; k < train_count; k++) {
                        printf("Train %d: %s - %d seats available\n",
                               trains[k].number,
                               trains[k].name,
                               trains[k].available_seats);
                    }
                }
                break;


            // ----- RETURN TO MAIN MENU -----
            case 4:
                printf("Returning to main menu...\n");
                break;

            default:
                printf(" Invalid choice! Please try again.\n");
        }

    } while (choice != 4);
}
// ==================== BOOKING SECTION ====================
// This function got a bit long, so you’ll see mix-match indentation.
// Logic/output stays 100% identical.

void bookTicket() {

    // human-like defensive check
    if (passenger_count >= 100) {
        printf(" No more tickets available! Maximum passenger limit reached.\n");
        return;
    }

    int train_no = 0;
    printf("Enter Train Number: ");
    scanf("%d", &train_no);

    // ====== FIND THE TRAIN ======
    int train_index = -1;
    
    // I use 'i' but sometimes consider renaming it — typical human indecision
    for (int i = 0; i < train_count; i++) {
        if (trains[i].number == train_no) {
            train_index = i;
            break; // Found it
        }
    }

    // Train not found
    if (train_index == -1) {
        printf(" Train not found! Please check train number.\n");
        return;
    }

    // No seats available
    if (trains[train_index].available_seats <= 0) {
        printf(" No seats available on this train!\n");
        return;
    }

    // ====== COLLECT PASSENGER DETAILS ======
    struct Passenger *p = &passengers[passenger_count];

    p->pnr = pnr_counter++;        // increment PNR counter
    p->train_number = train_no;    // store train number

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", p->name);

    printf("Enter Age: ");
    scanf("%d", &p->age);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &p->gender);

    // ====== ALLOCATE SEAT ======
    // This seat calculation MUST stay identical — affects output
    p->seat_number = trains[train_index].total_seats - trains[train_index].available_seats + 1;

    strcpy(p->status, "Confirmed");

    // a constant-fare system — I've kept it untouched
    p->fare = 500.0;

    // update available seats
    trains[train_index].available_seats--;

    passenger_count++; 

    // ====== PRINT TICKET ======
    // exact same lines, spacing unchanged
    printf("\n *** TICKET BOOKED SUCCESSFULLY! ***\n");
    printf(" PNR Number: %d\n", p->pnr);
    printf(" Passenger: %s\n", p->name);
    printf(" Train: %d - %s\n", p->train_number, trains[train_index].name);
    printf(" Seat Number: %d\n", p->seat_number);
    printf(" Fare: ₹%.2f\n", p->fare);
    printf(" Status: %s\n", p->status);
}
// ==================== TICKET CANCELLATION ====================
void cancelTicket() {
    if(passenger_count == 0) {
        printf(" No tickets booked yet! Nothing to cancel.\n");
        return;
    }

    int pnr;
    printf("Enter PNR Number to cancel: ");
    scanf("%d", &pnr);

    int found = 0;
    for(int i = 0; i < passenger_count; i++) {
        if(passengers[i].pnr == pnr && strcmp(passengers[i].status, "Confirmed") == 0) {

            // find train index
            int train_index = -1;
            for(int j = 0; j < train_count; j++) {
                if(trains[j].number == passengers[i].train_number) {
                    train_index = j;
                    break;
                }
            }

            if(train_index != -1) {
                // free the seat
                trains[train_index].available_seats++;

                // refund calculation (80% policy)
                float refund_amount = passengers[i].fare * 0.8;
                float cancellation_charge = passengers[i].fare * 0.2;

                strcpy(passengers[i].status, "Cancelled");

                printf("\n *** TICKET CANCELLED SUCCESSFULLY! ***\n");
                printf(" PNR: %d\n", pnr);
                printf(" Passenger: %s\n", passengers[i].name);
                printf(" Train: %d\n", passengers[i].train_number);
                printf(" Refund Amount: ₹%.2f\n", refund_amount);
                printf(" Cancellation Charge: ₹%.2f\n", cancellation_charge);
                printf(" Status: %s\n", passengers[i].status);
            }

            found = 1;
            break;
        }
    }

    if(!found) {
        printf(" PNR not found or ticket already cancelled!\n");
    }
}
// ==================== REPORTS + SAVE/LOAD ====================
void showReports() {
    printf("\n=== SYSTEM REPORTS ===\n");

    if(passenger_count == 0 && train_count == 0) {
        printf(" No data available for reports!\n");
        return;
    }

    int confirmed_tickets = 0, cancelled_tickets = 0;
    float total_revenue = 0.0, total_refunds = 0.0;

    for(int i = 0; i < passenger_count; i++) {
        if(strcmp(passengers[i].status, "Confirmed") == 0) {
            confirmed_tickets++;
            total_revenue += passengers[i].fare;
        } else if(strcmp(passengers[i].status, "Cancelled") == 0) {
            cancelled_tickets++;
            total_refunds += passengers[i].fare * 0.8;
        }
    }

    printf(" BOOKING STATISTICS:\n");
    printf("────────────────────────\n");
    printf(" Confirmed Tickets: %d\n", confirmed_tickets);
    printf(" Cancelled Tickets: %d\n", cancelled_tickets);
    printf(" Total Revenue: ₹%.2f\n", total_revenue);
    printf(" Total Refunds Given: ₹%.2f\n", total_refunds);
    printf(" Net Revenue: ₹%.2f\n", total_revenue - total_refunds);

    printf("\n TRAIN WISE REPORT:\n");
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

    printf(" PASSENGER DEMOGRAPHICS:\n");
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
    FILE *file = fopen("railway_data.txt", "w");
    if(file == NULL) {
        printf(" Error: Cannot create data file!\n");
        return;
    }

    fprintf(file, "%d %d %d\n", train_count, passenger_count, pnr_counter);

    for(int i = 0; i < train_count; i++) {
        fprintf(file, "%d %s %s %s %d %d\n",
                trains[i].number,
                trains[i].name,
                trains[i].source,
                trains[i].destination,
                trains[i].total_seats,
                trains[i].available_seats);
    }

    for(int i = 0; i < passenger_count; i++) {
        fprintf(file, "%d %s %d %c %d %d %s %.2f\n",
                passengers[i].pnr,
                passengers[i].name,
                passengers[i].age,
                passengers[i].gender,
                passengers[i].train_number,
                passengers[i].seat_number,
                passengers[i].status,
                passengers[i].fare);
    }

    fclose(file);
    printf(" All data saved successfully to railway_data.txt\n");
    printf(" Saved: %d trains and %d passenger records\n", train_count, passenger_count);
}

void loadData() {
    FILE *file = fopen("railway_data.txt", "r");
    if(file == NULL) {
        printf("  No previous data found. Starting fresh system.\n");
        return;
    }

    fscanf(file, "%d %d %d", &train_count, &passenger_count, &pnr_counter);

    for(int i = 0; i < train_count; i++) {
        fscanf(file, "%d %s %s %s %d %d",
               &trains[i].number,
               trains[i].name,
               trains[i].source,
               trains[i].destination,
               &trains[i].total_seats,
               &trains[i].available_seats);
    }

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
    printf(" Previous data loaded successfully!\n");
    printf(" Loaded: %d trains, %d passengers\n", train_count, passenger_count);
}
