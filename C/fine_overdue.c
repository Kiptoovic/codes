#include <stdio.h>
#include <math.h>
int main () {
    int book_id, due_day, due_month, due_year;//, return_date, fine_rate, days_overdue;
    int return_day, return_month, return_year;
    int days_overdue, fine_rate, fine_amount;
    //int fine_amount;
    char due_date[11], return_date[11];

    //prompts user to input the book ID
    printf("What is the Book ID? ");
    scanf("%d", &book_id);

    //prompts user to enter the due day
    printf("Enter the due date: ");
    scanf("%s", &due_date);
    
    //prompts user to enter the return date
    printf("Enter the return date ");
    scanf("%d", &return_date);

    //combines due date string into one component
        scanf(due_date, "%d/%d/%d", &return_day, &return_month, &return_year);

    //calculates the overdue days
    //int days_overdue = ;
    //printf("%d\n", days_overdue);



    return 0;

}