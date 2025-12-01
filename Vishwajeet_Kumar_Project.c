#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 5
#define WAITLIST_LIMIT 5

typedef struct {
    int pnr;
    char name[50];
    int age;
    int seat_row;
    int seat_col;
    int waitlisted;  
} Passenger;

typedef struct {
    int train_no;
    char source[20];
    char destination[20];
    int seat_matrix[MAX_SEATS][MAX_SEATS]; 
} Train;



Passenger *passenger_list = NULL;
int passenger_count = 0;
int pnr_counter = 1000;
int waitlist_count = 0;

Train train = {12345, "CityA", "CityB", {0}};

float ticket_price = 500.0;
float revenue = 0;



void loadData();
void saveData();
void bookTicket();
void cancelTicket();
void showReport();
void printSeatMatrix();
int checkAvailability();
void addPassenger(Passenger p);
void waitlistPassenger(Passenger p);


int main() {
    loadData();

    int choice;

    while (1) {
        printf("\n===== RAILWAY BOOKING SYSTEM =====\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Show Seat Matrix\n");
        printf("4. Generate Report\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: bookTicket(); break;
        case 2: cancelTicket(); break;
        case 3: printSeatMatrix(); break;
        case 4: showReport(); break;
        case 5:
            saveData();
            printf("Exiting system...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
}



void loadData() {
    FILE *fp = fopen("bookings.dat", "rb");
    if (fp == NULL) return;

    fread(&passenger_count, sizeof(int), 1, fp);
    fread(&pnr_counter, sizeof(int), 1, fp);
    fread(&revenue, sizeof(float), 1, fp);
    fread(&train.seat_matrix, sizeof(train.seat_matrix), 1, fp);

    passenger_list = malloc(passenger_count * sizeof(Passenger));
    fread(passenger_list, sizeof(Passenger), passenger_count, fp);

    fclose(fp);
}


void saveData() {
    FILE *fp = fopen("bookings.dat", "wb");

    fwrite(&passenger_count, sizeof(int), 1, fp);
    fwrite(&pnr_counter, sizeof(int), 1, fp);
    fwrite(&revenue, sizeof(float), 1, fp);
    fwrite(&train.seat_matrix, sizeof(train.seat_matrix), 1, fp);
    fwrite(passenger_list, sizeof(Passenger), passenger_count, fp);

    fclose(fp);
}


void bookTicket() {
    Passenger p;
    p.pnr = ++pnr_counter;
    p.waitlisted = 0;

    printf("Enter passenger name: ");
    scanf("%s", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);

    int found = 0;
    int row, col;

    
    for (row = 0; row < MAX_SEATS && !found; row++) {
        for (col = 0; col < MAX_SEATS && !found; col++) {
            if (train.seat_matrix[row][col] == 0) {
                train.seat_matrix[row][col] = 1;
                p.seat_row = row;
                p.seat_col = col;
                found = 1;
            }
        }
    }

    
    if (!found) {
        if (waitlist_count < WAITLIST_LIMIT) {
            p.waitlisted = 1;
            p.seat_row = -1;
            p.seat_col = -1;
            waitlistPassenger(p);
            printf("All seats are booked. You are added to WAITLIST.\n");
        } else {
            printf("Sorry! Train fully booked and waitlist full.\n");
        }
        return;
    }

   
    addPassenger(p);
    revenue += ticket_price;

    printf("Ticket booked successfully!\n");
    printf("PNR: %d | Seat: R%dC%d\n", p.pnr, p.seat_row + 1, p.seat_col + 1);
}


void cancelTicket() {
    int pnr;
    printf("Enter PNR to cancel: ");
    scanf("%d", &pnr);

    int i, found = -1;

  
    for (i = 0; i < passenger_count; i++) {
        if (passenger_list[i].pnr == pnr) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Invalid PNR!\n");
        return;
    }

    Passenger p = passenger_list[found];

   
    if (!p.waitlisted) {
        train.seat_matrix[p.seat_row][p.seat_col] = 0;
    }

    
    for (i = found; i < passenger_count - 1; i++) {
        passenger_list[i] = passenger_list[i + 1];
    }

    passenger_count--;
    passenger_list = realloc(passenger_list, passenger_count * sizeof(Passenger));

    printf("Ticket cancelled successfully!\n");
}



void addPassenger(Passenger p) {
    passenger_count++;
    passenger_list = realloc(passenger_list, passenger_count * sizeof(Passenger));
    passenger_list[passenger_count - 1] = p;
}


void waitlistPassenger(Passenger p) {
    waitlist_count++;
    addPassenger(p);
}



void printSeatMatrix() {
    printf("\nSeat Matrix (0 = Empty, 1 = Booked):\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        for (int j = 0; j < MAX_SEATS; j++) {
            printf("%d ", train.seat_matrix[i][j]);
        }
        printf("\n");
    }
}


void showReport() {
    printf("\n=========== REPORT ===========\n");
    printf("Total Bookings: %d\n", passenger_count);
    printf("Waitlisted: %d\n", waitlist_count);
    printf("Revenue: %.2f\n", revenue);
    printf("================================\n");
}
