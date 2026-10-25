#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    // 1. Input Seating Plan Dimensions
    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Invalid number of rows.\n");
        return 1;
    }

    printf("Enter number of seats per row: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Invalid number of seats per row.\n");
        return 1;
    }

    int grid[rows][cols];

    // Input seating arrangement row by row with safety checks
    printf("\nEnter seating status row by row (0 for available, 1 for booked):\n");
    for (int r = 0; r < rows; r++) {
        printf("Row %d (%d values separated by spaces): ", r, cols);
        for (int c = 0; c < cols; c++) {
            while (scanf("%d", &grid[r][c]) != 1 || (grid[r][c] != 0 && grid[r][c] != 1)) {
                // Clear invalid input buffer to prevent freezing
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Invalid value. Enter 0 or 1 for seat %d: ", c);
            }
        }
    }

    // 2. Display Initial Seating Arrangement
    printf("\n--- Initial Seating Arrangement ---\n");
    printf("      ");
    for (int c = 0; c < cols; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < rows; r++) {
        printf("Row %d: ", r);
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }

    // 3. Seat Availability Report
    int total_available = 0;
    printf("\n--- Seat Availability Report ---\n");
    for (int r = 0; r < rows; r++) {
        int row_available = 0;
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) {
                row_available++;
            }
        }
        printf("Row %d: %d available seats\n", r, row_available);
        total_available += row_available;
    }
    printf("Total available seats in the hall: %d\n", total_available);

    // 4. Input Group Booking Request
    int k;
    printf("\nEnter number of customers in group (k): ");
    while (scanf("%d", &k) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid input. Enter group size (k): ");
    }

    // Validation
    if (k <= 0 || k > cols) {
        printf("Invalid group size. Must be between 1 and %d.\n", cols);
        return 0;
    }

    // 5. Search for k consecutive seats starting from the middle row
    int found_row = -1;
    int found_start_col = -1;
    int mid = rows / 2;

    for (int dist = 0; dist < rows; dist++) {
        int candidate_rows[2];
        int num_candidates = 0;

        if (dist == 0) {
            candidate_rows[num_candidates++] = mid;
        } else {
            int lower_row = mid - dist;
            int upper_row = mid + dist;

            if (lower_row >= 0) {
                candidate_rows[num_candidates++] = lower_row;
            }
            if (upper_row < rows) {
                candidate_rows[num_candidates++] = upper_row;
            }
        }

        for (int i = 0; i < num_candidates; i++) {
            int r = candidate_rows[i];
            int consecutive_free = 0;

            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 0) {
                    consecutive_free++;
                    if (consecutive_free == k) {
                        found_row = r;
                        found_start_col = c - k + 1;
                        break;
                    }
                } else {
                    consecutive_free = 0;
                }
            }

            if (found_row != -1) {
                break;
            }
        }

        if (found_row != -1) {
            break;
        }
    }

    // 6 & 7. Confirm Booking or Handle Failure
    if (found_row != -1) {
        for (int c = found_start_col; c < found_start_col + k; c++) {
            grid[found_row][c] = 1;
        }

        printf("\n--- Booking Confirmed ---\n");
        printf("Allocated Row: %d\n", found_row);
        printf("Allocated Seats: ");
        for (int c = found_start_col; c < found_start_col + k; c++) {
            printf("%d ", c);
        }
        printf("\n");

        printf("\n--- Updated Seating Arrangement ---\n");
        printf("      ");
        for (int c = 0; c < cols; c++) {
            printf("%d ", c);
        }
        printf("\n");

        int updated_total_available = 0;
        for (int r = 0; r < rows; r++) {
            printf("Row %d: ", r);
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 0) {
                    printf("_ ");
                    updated_total_available++;
                } else {
                    printf("X ");
                }
            }
            printf("\n");
        }

        printf("\nRemaining available seats in the hall: %d\n", updated_total_available);
    } else {
        printf("\nBooking Unsuccessful: No row contains %d consecutive available seats.\n", k);
        printf("Seating plan remains unchanged.\n");
    }

    return 0;
}