#include <stdio.h>

#define MAX_SENSORS 50
#define MAX_READINGS 100

/* Reads all temperature readings into the 2D array */
void inputReadings(float temp[][MAX_READINGS], int sensors, int readings)
{
    int i, j;
    for (i = 0; i < sensors; i++)
    {
        printf("Enter %d readings for Sensor %d: ", readings, i + 1);
        for (j = 0; j < readings; j++)
            scanf("%f", &temp[i][j]);
    }
}

/* Analyzes one sensor's readings (one row of the array), prints that
   sensor's report, and returns the average temperature. */
float analyzeSensor(float row[], int readings, int sensorNo)
{
    int j, critical = 0, warning = 0, streak = 0, longest = 0;
    float total = 0, highest = row[0], lowest = row[0];

    for (j = 0; j < readings; j++)
    {
        total += row[j];

        if (row[j] > highest) highest = row[j];
        if (row[j] < lowest)  lowest = row[j];

        if (row[j] >= 40)
            critical++;
        else if (row[j] >= 35)
            warning++;

        if (row[j] >= 35)
        {
            streak++;
            if (streak > longest)
                longest = streak;
        }
        else
            streak = 0;
    }

    float average = total / readings;

    printf("\n--- Sensor %d Report ---\n", sensorNo);
    printf("Total temperature       : %.2f\n", total);
    printf("Average temperature     : %.2f\n", average);
    printf("Highest temperature     : %.2f\n", highest);
    printf("Lowest temperature      : %.2f\n", lowest);
    printf("Critical readings (>=40): %d\n", critical);
    printf("Warning readings (35-39): %d\n", warning);
    printf("Longest streak (>=35)   : %d hour(s)\n", longest);

    return average;
}

/* Returns the sensor number (1-based) with the highest average */
int highestAverageSensor(float averages[], int sensors)
{
    int i, best = 0;
    for (i = 1; i < sensors; i++)
        if (averages[i] > averages[best])
            best = i;
    return best + 1;
}

int main(void)
{
    float temp[MAX_SENSORS][MAX_READINGS];
    float averages[MAX_SENSORS];
    int sensors, readings, i, best;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &readings);

    inputReadings(temp, sensors, readings);

    for (i = 0; i < sensors; i++)
        averages[i] = analyzeSensor(temp[i], readings, i + 1);

    best = highestAverageSensor(averages, sensors);

    printf("\n=== Final Report ===\n");
    printf("Sensor with highest average: Sensor %d\n", best);
    printf("Its average temperature    : %.2f\n", averages[best - 1]);

    return 0;
}