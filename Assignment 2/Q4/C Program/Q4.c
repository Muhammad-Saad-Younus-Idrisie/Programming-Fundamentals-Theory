#include <stdio.h>

#define MAX_DAYS 7

/* Inputs and validates the number of festival days (1-7) */
int getValidDays()
{
    int days;

    do
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7)
            printf("Invalid input. Days must be between 1 and 7.\n");
    } while (days < 1 || days > 7);

    return days;
}

/* Processes one day's orders, displays the day's statistics
   and returns the day's total sales */
float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0, highest = 0, average;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    for (i = 1; i <= orders; i++)
    {
        do
        {
            printf("  Enter amount for order %d: Rs. ", i);
            scanf("%f", &amount);
            if (amount <= 0)
                printf("  Invalid amount. It must be greater than zero.\n");
        } while (amount <= 0);

        total += amount;
        if (amount > highest)
            highest = amount;
    }

    average = total / orders;

    printf("Day %d Summary\n", dayNumber);
    printf("  Total sales          : Rs. %.2f\n", total);
    printf("  Average order amount : Rs. %.2f\n", average);
    printf("  Highest order amount : Rs. %.2f\n", highest);

    return total;
}

/* Returns the day number (starting from 1) with the highest sales.
   If there is a tie, the earliest day is returned. */
int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, best = 0;

    for (i = 1; i < numberOfDays; i++)
        if (dailySales[i] > dailySales[best])   /* '>' keeps the earliest day on a tie */
            best = i;

    return best + 1;
}

/* Prints one asterisk for every complete Rs. 100 of each day's sales */
void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;

    printf("\nDaily Sales Bar Chart (* = Rs. 100)\n");
    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
            printf("*");
        printf("\n");
    }
}

int main(void)
{
    float dailySales[MAX_DAYS];
    float festivalTotal = 0;
    int days, i, bestDay;

    days = getValidDays();

    for (i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, days);

    printf("\n=== Festival Sales Summary ===\n");
    printf("Total festival sales        : Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales      : Day %d (Rs. %.2f)\n", bestDay, dailySales[bestDay - 1]);

    displayBarChart(dailySales, days);

    return 0;
}