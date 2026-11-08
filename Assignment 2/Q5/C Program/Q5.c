#include <stdio.h>
#include <string.h>

/* Helper: returns the position of id in arr, or -1 if not found */
int findIndex(int arr[], int n, int id)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == id)
            return i;
    return -1;
}

/* Helper: asks until a positive number of days is entered */
int getDays()
{
    int days;
    do
    {
        printf("Enter number of days: ");
        scanf("%d", &days);
        if (days <= 0)
            printf("Days must be positive.\n");
    } while (days <= 0);
    return days;
}

void displayMenu()
{
    printf("\n1. Register Member\n2. Display Available Books\n3. Borrow a Book\n"
           "4. Return a Book\n5. Display Member Record\n6. Exit\nEnter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter name: ");
    scanf(" %49[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    do
    {
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type.\n");
    } while (*memberType != 1 && *memberType != 2);
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;
    printf("\n%-8s %-25s %s\n", "Book ID", "Title", "Available Copies");
    for (i = 0; i < totalBooks; i++)
        printf("%-8d %-25s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, i;

    if (*borrowedCount == 3)
    {
        printf("Limit reached: maximum 3 books at a time.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &id);
    i = findIndex(bookIDs, totalBooks, id);

    if (i == -1)
        printf("Invalid book ID.\n");
    else if (availableCopies[i] == 0)
        printf("No copies of \"%s\" available.\n", bookTitles[i]);
    else
    {
        getDays();
        borrowedBookIDs[(*borrowedCount)++] = id;
        availableCopies[i]--;
        printf("Borrowed \"%s\". Permitted period: %d days.\n", bookTitles[i], memberType == 1 ? 14 : 30);
    }
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, pos, allowed = (memberType == 1) ? 14 : 30;
    float fine, payable = 0;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);
    pos = findIndex(borrowedBookIDs, *borrowedCount, id);
    if (pos == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    days = getDays();
    availableCopies[findIndex(bookIDs, totalBooks, id)]++;

    if (days > allowed)
    {
        fine = (days - allowed) * (memberType == 1 ? 20 : 10);
        *totalFine += fine;
        printf("Late return. Fine charged: Rs. %.2f\nEnter membership code: ", fine);
        scanf("%19s", code);
        payable = (strcmp(code, "LIB2026") == 0) ? fine / 2 : fine;
        printf("Fine payable: Rs. %.2f\n", payable);
    }
    else
        printf("Returned on time. No fine.\n");

    for (; pos < *borrowedCount - 1; pos++)
        borrowedBookIDs[pos] = borrowedBookIDs[pos + 1];
    (*borrowedCount)--;
    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver)
{
    int i;
    printf("\nName: %s\nStudent ID: %d\nMembership type: %s\nBorrowed books: ",
           name, studentID, memberType == 1 ? "Student" : "Faculty");
    for (i = 0; i < borrowedCount; i++)
        printf("%d ", borrowedBookIDs[i]);
    if (borrowedCount == 0)
        printf("None");
    printf("\nTotal fine before waiver: Rs. %.2f\nFinal fine payable: Rs. %.2f\n", totalFine, fineAfterWaiver);
}

int main()
{
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {"Programming in C", "Data Structures", "Discrete Mathematics",
                              "Database Systems", "Operating Systems"};
    int availableCopies[5] = {3, 2, 1, 4, 0};
    char name[50];
    int studentID, memberType, registered = 0, choice;
    int borrowedBookIDs[3], borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        if (choice >= 3 && choice <= 5 && !registered)
        {
            printf("Please register first.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            if (registered)
                printf("A member is already registered.\n");
            else
            {
                registerMember(name, &studentID, &memberType);
                registered = 1;
            }
            break;
        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, 5);
            break;
        case 3:
            borrowBook(bookIDs, bookTitles, availableCopies, 5, borrowedBookIDs, &borrowedCount, memberType);
            break;
        case 4:
            fineAfterWaiver += returnBook(bookIDs, availableCopies, 5, borrowedBookIDs,
                                          &borrowedCount, memberType, &totalFine);
            break;
        case 5:
            displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount,
                                totalFine, fineAfterWaiver);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Enter 1-6.\n");
        }
    } while (choice != 6);

    return 0;