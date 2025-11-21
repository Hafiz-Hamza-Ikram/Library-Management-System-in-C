#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define MAX_BOOKS 100
int main_menu();
int book_categories()
{
    int choice;
    char buffer[20];
    char category[1][15];
    char line[256];
    int found = 0;

    while(1)
    {
        printf("\n===VIEW CATEGORIES MENU===\n");
        printf("1. Maths.\n");
        printf("2. Comp.Sc.\n");
        printf("3. Law.\n");
        printf("4. English.\n");
        printf("5. Urdu.\n");
        printf("6. Misc.\n");
        printf("7. Go Back to Previous Menu.\n");

        printf("Enter 1-7 to select from above Menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Integer Validation
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        FILE *books = fopen("BOOKS.txt", "r");
        if (books == NULL) {
            printf("No books found...\n");
            return 0;
        }

        switch(choice)
        {
        case 1:
            strcpy(category[0], "Maths");
            break;
        case 2:
            strcpy(category[0], "Comp.Sc.");
            break;
        case 3:
            strcpy(category[0], "Law");
            break;
        case 4:
            strcpy(category[0], "English");
            break;
        case 5:
            strcpy(category[0], "Urdu");
            break;
        case 6:
            strcpy(category[0], "Misc.");
            break;
        case 7:
            fclose(books);
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            continue;
        }

        printf("\nCategory: %s\n", category[0]);
        printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");

        while (fgets(line, sizeof(line), books) != NULL)
        {
            //strstr to find category occurence
            if (strstr(line, category[0]) != NULL)
            {
                printf("%s", line);
                found = 1;
            }
        }
        //If category not found
        if (!found)
        {
            printf("No books found in this category.\n");
        }
        fclose(books);
    }
    return 0;
}
int isAlphanumeric(char *str)
{
    while (*str)
    {
        // Allow spaces and Alphanumeric
        if (!isalnum(*str) && *str != ' ')
        {
            return 0; // Not alphanumeric
        }
        str++;
    }
    // Valid
    return 1;
}
int removeNewline(char str[])
{
    //strcspn returns index value when reaches \n in the str; then that index changes to \0
    str[strcspn(str, "\n")] = '\0';
    return 0;
}
int count_existing_books()
{
    //Line array of 256; as usually lines of a text file comprise 256 characters each
    char line[256];
    int existing_count = 0;

    FILE *books;
    books = fopen("BOOKS.txt", "r");
    if(books == NULL)
    {
        printf("No Existing Books. Starting Fresh...\n");
        return 0;
    }
    //Loop to increment Existing Count as long as line is NULL
    while(fgets(line, sizeof(line), books) != NULL)
    {
        existing_count++;
    }

    fclose(books);

    //Return value of existing count
    return existing_count;
}
struct book
{
    int Book_ID;
    char Book_Name[50];
    char Author_Name[40];
    char Book_Edition[15];
    char Category[10];
};
int add_books()
{
    struct book b[MAX_BOOKS];
    int count = count_existing_books();
    int i = count;
    int choice;
    char buffer[20];
    char line[256];
    int id;

    //Count Print
    printf("\nAlready Existing Books: %d\n", count);

    while(1)
    {
        printf("\n====ADD BOOKS MENU====\n");
        printf("1. Add a Book.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Integer Validation
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        switch(choice)
        {
        case 1:
            printf("Enter Book ID: ");
            fgets(buffer, sizeof(buffer), stdin);

            int found = 0;
            // ID Validation (Integer Type)
            if(sscanf(buffer, "%d", &b[i].Book_ID) != 1)
            {
                printf("Please enter a Valid Number...\n");
                found = 1;
            }
            if(found)
            {
                continue;
            }
            // ID Validation (Positive)
            if(b[i].Book_ID <= 0)
            {
                printf("Enter a Positive ID...\n");
                found = 1;
            }
            if(found)
            {
                continue;
            }
            // ID Validation (Maximum 8 Digits)
            if (b[i].Book_ID > 99999999)
            {
                printf("The ID must not exceed 8 digits...\n");
                found = 1;
            }
            if (found)
            {
                continue;
            }
            // ID Validation (Not already stored)
            FILE *books = fopen("BOOKS.txt", "a+");
            if(books == NULL)
            {
                printf("Error in Opening File...\n");
                return 1;
            }
            while(fgets(line, sizeof(line), books) != NULL)
            {
                sscanf(line, "%d", &id);
                if(id == b[i].Book_ID)
                {
                    printf("ID already Present in the Data...\n");
                    found = 1;
                    break;
                }
            }
            fclose(books);

            if(found)
            {
                continue;
            }

            // Adding Books
            books = fopen("BOOKS.txt", "a");
            if(books == NULL)
            {
                printf("Error in Opening File...\n");
                return 1;
            }
            // Validate Book Name
            printf("Enter Book Name (Max 49 characters): ");
            fgets(buffer, sizeof(buffer), stdin);

            if(sscanf(buffer, "%s", b[i].Book_Name) != 1)
            {
                printf("Please enter a Valid Name...\n");
                found = 1;
            }
            else if(strlen(b[i].Book_Name) > 49)
            {
                printf("Book Name is too long. Maximum 49 characters allowed.\n");
                found = 1;
            }
            else if(!isAlphanumeric(b[i].Book_Name))
            {
                printf("Invalid Book Name. Only alphanumeric characters are allowed.\n");
                found = 1;
            }
            else
            {
                printf("Valid\n");
            }
            if(found)
            {
                continue;
            }

            // Validate Author Name
            printf("Enter Author Name (Max 39 characters): ");
            fgets(buffer, sizeof(buffer), stdin);

            if(sscanf(buffer, "%s", b[i].Author_Name) != 1)
            {
                printf("Please enter a Valid Name...\n");
                found = 1;
            }
            else if(strlen(b[i].Author_Name) > 39)
            {
                printf("Author Name is too long. Maximum 39 characters allowed.\n");
                found = 1;
            }
            else if(!isAlphanumeric(b[i].Author_Name))
            {
                printf("Invalid Author Name. Only alphanumeric characters are allowed.\n");
                found = 1;
            }
            else
            {
                printf("Valid\n");
            }
            if(found)
            {
                continue;
            }

            // Validate Book Edition
            printf("Enter Book Edition (Max 14 characters): ");
            fgets(buffer, sizeof(buffer), stdin);

            if(sscanf(buffer, "%s", b[i].Book_Edition) != 1)
            {
                printf("Please enter a Valid Name...\n");
                found = 1;
            }
            else if(strlen(b[i].Book_Edition) > 14)
            {
                printf("Book Edition is too long. Maximum 14 characters allowed.\n");
                found = 1;
            }
            else if(!isAlphanumeric(b[i].Book_Edition))
            {
                printf("Invalid Book Edition. Only alphanumeric characters are allowed.\n");
                found = 1;
            }
            else
            {
                printf("Valid\n");
            }
            if(found)
            {
                continue;
            }

            // Validate Category
            Category:
            printf("Enter Book Category (Maths, Comp.Sc., Law, English, Urdu, Misc.): ");
            fgets(b[i].Category, sizeof(b[i].Category), stdin);
            removeNewline(b[i].Category);

            if(strcmp(b[i].Category, "Maths") != 0 &&
                strcmp(b[i].Category, "Comp.Sc.") != 0 &&
                strcmp(b[i].Category, "Law") != 0 &&
                strcmp(b[i].Category, "English") != 0 &&
                strcmp(b[i].Category, "Urdu") != 0 &&
                strcmp(b[i].Category, "Misc.") != 0)
            {
                printf("Invalid Category. Please enter a valid category from the list.\n");
                goto Category;
            }
            else
            {
                printf("Valid\n");
            }

            // Success Message
            printf("Book Added Successfully!\n");
            count++;

            fprintf(books, "%-8d %-52s %-42s %-16s %-15s\n",
                    b[i].Book_ID,
                    b[i].Book_Name,
                    b[i].Author_Name,
                    b[i].Book_Edition,
                    b[i].Category);

            fclose(books);
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int display_books()
{
    int choice;
    char buffer[20];
    char line[256];

    while(1)
    {
        printf("\n=====DISPLAY BOOKS MENU=====\n");
        printf("1. Display List of All Books.\n");
        printf("2. Display Book List by Category.\n");
        printf("3. Go Back to Previous Menu.\n");

        printf("Enter 1-3 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Integer Validation
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        FILE *books = fopen("BOOKS.txt", "r");
        if (books == NULL)
        {
            printf("No books found to display.\n");
            return 0;
        }

        switch(choice)
        {
        case 1:
            printf("\nBooks List:\n");
            while (fgets(line, sizeof(line), books) != NULL)
            {
                printf("%s", line);
            }
            fclose(books);
            break;
        case 2:
            printf("\nCategory Wise Books List:\n");
            char categories[6][15] = {"Maths", "Comp.Sc.", "Law", "English", "Urdu", "Misc."};
            int found;

            //Loop  to Print 6 Categories
            for (int i = 0; i < 6; i++)
            {
                found = 0;

                printf("\nCategory: %s\n", categories[i]);
                printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");

                //Rewind everytime
                rewind(books);

                while (fgets(line, sizeof(line), books) != NULL)
                {
                    if (strstr(line, categories[i]) != NULL)
                    {
                        printf("%s", line);
                        found = 1;
                    }
                }
                if (!found)
                {
                    printf("No books found in this category.\n");
                }
            }
            fclose(books);
            break;
        case 3:
            fclose(books);
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int search_book()
{
    int choice;
    char buffer[20];
    char search[50];
    char line[256];
    int found;

    while(1)
    {
        printf("\n=====SEARCH MENU=====\n");
        printf("1. Search by entering anything.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Integer Validation
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        FILE *books = fopen("BOOKS.txt", "r");
        if (books == NULL) {
            printf("No books found to search.\n");
            return 0;
        }

        switch(choice)
        {
        case 1:
            printf("Search by entering anything: \n");
            fgets(search, sizeof(search), stdin);
            removeNewline(search);

            printf("Searching for %s ...\n", search);

            found = 0;

            printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");

            while (fgets(line, sizeof(line), books) != NULL)
            {
                if (strstr(line, search) != NULL)
                {
                    printf("%s", line);
                    found = 1;
                }
            }
            if (!found)
            {
                printf("No Data Found.\n");
            }
            break;
        case 2:
            fclose(books);
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
        fclose(books);
    }
    return 0;
}
int update_book()
{
    struct book b[MAX_BOOKS];
    int choice;
    int i;
    int found = 0;
    int id;
    char new_b_name[50], new_a_name[40], new_Ed[15], new_category[10];
    char buffer[20];
    char line[256];

    while(1)
    {
        printf("\n====UPDATE MENU====\n");
        printf("1. Update Book Name.\n");
        printf("2. Update Author Name.\n");
        printf("3. Update Book Edition.\n");
        printf("4. Update Book Category.\n");
        printf("5. Go Back to Previous Menu.\n");

        printf("Enter 1-5 to choose from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Integer Validation
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }
        if(choice >= 1 && choice <= 4)
        {
            printf("Enter Book ID to update Book Details: ");
            scanf("%d", &id);
            getchar();

            i = 1;

            FILE *books = fopen("BOOKS.txt", "r+");
            if(books == NULL)
            {
                printf("No Books found to Update...\n");
                return 1;
            }

            while(fgets(line, sizeof(line), books) != NULL)
            {
                int j = sscanf(line, "%d %49[^\t] %39[^\t] %13[^\t] %[^\n]",
                                &b[i].Book_ID,
                                b[i].Book_Name,
                                b[i].Author_Name,
                                b[i].Book_Edition,
                                b[i].Category);
                if(b[i].Book_ID == id)
                {
                    found = 1;

                    printf("CURRENT DETAILS: \n");
                    printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");
                    printf("%s\n", line);

                    switch(choice)
                    {
                    case 1:
                        printf("Enter New Book Name: ");
                        fgets(new_b_name, sizeof(new_b_name), stdin);
                        removeNewline(new_b_name);
                        strcpy(b[i].Book_Name, new_b_name);
                        break;

                    case 2:
                        printf("Enter New Author Name: ");
                        fgets(new_a_name, sizeof(new_a_name), stdin);
                        removeNewline(new_a_name);
                        strcpy(b[i].Author_Name, new_a_name);
                        break;

                    case 3:
                        printf("Enter New Book Edition: ");
                        fgets(new_Ed, sizeof(new_Ed), stdin);
                        removeNewline(new_Ed);
                        strcpy(b[i].Book_Edition, new_Ed);
                        break;

                    case 4:
                        New_Category:
                        printf("Enter New Book Category: (Maths, Comp.Sc., Law, English, Urdu, Misc.) ");
                        fgets(new_category, sizeof(new_category), stdin);
                        removeNewline(new_category);
                        if (strcmp(new_category, "Maths") != 0 &&
                            strcmp(new_category, "Comp.Sc.") != 0 &&
                            strcmp(new_category, "Law") != 0 &&
                            strcmp(new_category, "English") != 0 &&
                            strcmp(new_category, "Urdu") != 0 &&
                            strcmp(new_category, "Misc.") != 0)
                        {
                            printf("Invalid Category. Please enter a valid category from the list.\n");
                            goto New_Category;
                        }
                        strcpy(b[i].Category, new_category);
                        break;

                    default:
                        printf("You entered Invalid Input...");
                        break;
                    }

                    fseek(books, -139, SEEK_CUR);

                    fprintf(books, "%-8d %-52s %-42s %-16s %-15s",
                                b[i].Book_ID,
                                b[i].Book_Name,
                                b[i].Author_Name,
                                b[i].Book_Edition,
                                b[i].Category);
                    printf("Book Updated Successfully...\n");
                    break;
                }
            }
            fclose(books);
            if(!found)
            {
                printf("Book ID did not found in the data...\n");
            }
        }
        else if(choice == 5)
        {
            printf("Returning to Previous Menu...\n");
            main_menu();
        }
        else
        {
            printf("You entered Invalid Input...\n");
        }
    }
    return 0;
}
int delete_book()
{
    int id, choice;
    int temp_id;
    int found = 0;
    char line[256];
    char buffer[20];

    while(1)
    {
        printf("\n=====Delete Menu=====\n");
        printf("1. Delete Book.\n");
        printf("2. Go Back to Previous Menu.\n");
        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Validating Integer Input
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        switch(choice)
        {
        case 1:
            printf("Enter Book ID to Delete the Book: ");
            scanf("%d", &temp_id);
            getchar();

            FILE *books = fopen("BOOKS.txt", "r");
            if(books == NULL)
            {
                printf("No Books found to Delete...\n");
                return 1;
            }
            //Opening Temporary File
            FILE *update = fopen("Deleted.txt", "w");
            if(update == NULL)
            {
                printf("Error in Creating Temporary File...\n");
                fclose(books);
                return 1;
            }
            //Reading Lines
            while(fgets(line, sizeof(line), books) != NULL)
            {
                //Reading only ID from the line
                sscanf(line, "%d", &id);
                if(id == temp_id)
                {
                    printf("Deleted Book Details:\n");
                    printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");
                    printf("%s", line);
                    found = 1;
                }
                else
                {
                    fprintf(update, "%s", line);
                }
            }
            fclose(books);
            fclose(update);

            //If a Book is deleted
            if(found)
            {
                //Remove BOOKS.txt and check for errors
                if (remove("BOOKS.txt") != 0)
                {
                    printf("Error deleting BOOKS.txt");
                    return 1;
                }
                // Rename Deleted.txt to BOOKS.txt and check for errors
                if (rename("Deleted.txt", "BOOKS.txt") != 0)
                {
                    printf("Error renaming Deleted.txt to BOOKS.txt");
                    return 1;
                }
                printf("Book Deleted Successfully...\n");
            }
            else
            {
                //Remove the temporary file
                if (remove("Deleted.txt") != 0)
                {
                    printf("Error deleting BOOKS.txt");
                    return 1;
                }
                printf("Book ID did not found in the data to Delete...\n");
            }
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("Invalid Input...\n");
            break;
        }
    }
    return 0;
}
struct issue_book
{
    int book_id;
    char stu_name[50];
    char roll_no[17];
    char issue_date[11];
};
void get_current_date(char buffer[])
{
    //Take Time in Seconds since the UNIX epoch
    time_t now = time(NULL);
    //Break Time into Individual Components
    struct tm *local = localtime(&now);
    // Format current date as YYYY-MM-DD
    strftime(buffer, 11, "%Y-%m-%d", local);
}
int count_issued_books()
{
    //Line array of 256; as usually lines of a text file comprise 256 characters each
    char line[256];
    int existing_count = 0;

    FILE * fp = fopen("Issued Books List.txt", "r");
    if(fp == NULL)
    {
        printf("No Issued Books. Starting Fresh...\n");
        return 0;
    }
    //Loop to increment Existing Count as long as line is NULL
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        existing_count++;
    }

    fclose(fp);
    //Return value of existing count
    return existing_count;
}
int issue_book()
{
    int choice;
    char buffer[20];
    char line[256];
    int id;
    int found = 0;
    struct issue_book issue;
    int total = count_issued_books();

    while(1)
    {
        printf("\n====ISSUE BOOK MENU====\n");
        printf("1. Issue a Book.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Validating Integer Input
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        switch(choice)
        {
        case 1:
            printf("Enter Book ID: ");
            scanf("%d", &issue.book_id);
            getchar();

            printf("Enter Student Name: ");
            fgets(buffer, sizeof(buffer), stdin);

            if(sscanf(buffer, "%s", issue.stu_name) != 1)
            {
                printf("Please enter a Valid Name...\n");
                found = 1;
            }
            else if(strlen(issue.stu_name) > 49)
            {
                printf("Student Name is too long. Maximum 49 characters allowed.\n");
                found = 1;
            }
            else if(!isAlphanumeric(issue.stu_name))
            {
                printf("Invalid Student Name. Only alphanumeric characters are allowed.\n");
                found = 1;
            }
            else
            {
                printf("Valid\n");
            }
            if(found)
            {
                continue;
            }

            printf("Enter Roll No: ");
            fgets(buffer, sizeof(buffer), stdin);

            if(sscanf(buffer, "%s", issue.roll_no) != 1)
            {
                printf("Please enter a Valid Name...\n");
                found = 1;
            }
            else if(strlen(issue.roll_no) > 16)
            {
                printf("Roll No is too long. Maximum 16 characters allowed.\n");
                found = 1;
            }
            else
            {
                printf("Valid\n");
            }
            if(found)
            {
                continue;
            }

            FILE *books = fopen("BOOKS.txt", "r");
            if (books == NULL)
            {
                printf("No books found to Issue.\n");
                return 0;
            }

            while(fgets(line, sizeof(line), books) != NULL)
            {
                sscanf(line, "%d", &id);
                if(issue.book_id == id)
                {
                    found = 1;

                    FILE *fp = fopen("Issued Books List.txt", "a");
                    if(fp == NULL)
                    {
                        printf("Error in Opening File...\n");
                        return 1;
                    }

                    //Function Call to get Current Date
                    get_current_date(issue.issue_date);

                    //Printing Header
                    if(total == 0)
                    {
                        fprintf(fp, "%-9s %-50s %-17s %-12s\n", "Book ID", "Student Name", "Roll No", "Issue Date");
                    }

                    fprintf(fp, "%-9d %-50s %-17s %-12s\n", issue.book_id, issue.stu_name, issue.roll_no, issue.issue_date);
                    printf("Book issued successfully to %s on %s.\n", issue.stu_name, issue.issue_date);
                    total++;

                    fclose(fp);
                }
            }
            fclose(books);
            if(!found)
            {
                printf("Book ID did not found in the data to Issue...\n");
            }
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int issued_book_list()
{
    int choice;
    char line[256];
    char buffer[20];

    while(1)
    {
        printf("\n====DISPLAY ISSUED BOOKS LIST====\n");
        printf("1. Display List of All Issued Books.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Validating Integer Input
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        FILE * fp = fopen("Issued Books List.txt", "r");
        if(fp == NULL)
        {
            printf("There are no Books Issued.\n");
            return 1;
        }
        switch(choice)
        {
        case 1:
            while(fgets(line, sizeof(line), fp) != NULL)
            {
                printf("%s", line);
            }
            fclose(fp);
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            fclose(fp);
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int date_difference(char date1[], char date2[])
{
    struct tm tm1 = {0}, tm2 = {0};
    time_t t1, t2;

    // Parse the dates into struct tm
    sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);

    // Adjust years and months (tm_year is years since 1900, tm_mon is 0-based)
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;

    // Convert to time_t
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    // Calculate difference in seconds and convert to days
    double sec_diff = difftime(t2, t1);
    return (int)(sec_diff / (60 * 60 * 24));
}
int defaulters_list()
{
    int choice;
    char buffer[20];
    char line[256];
    char t_date[11];
    char name[50], no[15], date[11];
    int id;

    while(1)
    {
        printf("\n====DEFAULTED STUDENTS MENU====\n");
        printf("1. Display List of Defaulted Students.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Validating Integer Input
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        switch(choice)
        {
        case 1:
            printf("Searching for Defaulted Students...\n\n");
            FILE * fp = fopen("Issued Books List.txt", "r");
            if(fp == NULL)
            {
                printf("No Issued Books Found...\n");
                return 1;
            }
            while(fgets(line, sizeof(line), fp) != NULL)
            {
                int i = sscanf(line, "%d %46[^\t] %13[^\t] %[^\n]",
                               &id, name, no, date);
                if(i == 4)
                {
                    get_current_date(t_date);
                    int days_diff = date_difference(date, t_date);

                    if(days_diff > 14)
                    {
                        printf("Status: Defaulter (Overdue by %d day(s)\n", days_diff - 14);
                        printf("%-9s %-50s %-17s %-12s\n", "Book ID", "Student Name", "Roll No", "Issue Date");
                        printf("%s\n", line);
                    }
                }
            }
            fclose(fp);
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int delete_issue_book()
{
    int id, choice;
    int temp_id;
    int found = 0;
    char line[256];
    char buffer[20];

    while(1)
    {
        printf("\n=====DELETE ISSUED BOOK=====\n");
        printf("1. Delete Issue Book.\n");
        printf("2. Go Back to Previous Menu.\n");

        printf("Enter 1-2 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        //Validating Integer Input
        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            continue;
        }

        switch(choice)
        {
        case 1:
            printf("Enter Book ID to Delete the Issue Book: ");
            scanf("%d", &temp_id);
            getchar();

            FILE *books = fopen("Issued Books List.txt", "r");
            if(books == NULL)
            {
                printf("No Books found to Delete...\n");
                return 1;
            }
            //Opening Temporary File
            FILE *update = fopen("Delete Issue Books.txt", "w");
            if(update == NULL)
            {
                printf("Error in Creating Temporary File...\n");
                fclose(books);
                return 1;
            }
            //Reading Lines
            while(fgets(line, sizeof(line), books) != NULL)
            {
                //Reading only ID from the line
                sscanf(line, "%d", &id);
                if(id == temp_id)
                {
                    printf("Deleted Book Details:\n");
                    printf("%-8s %-52s %-42s %-16s %-15s\n", "Book ID", "Book Name", "Author Name", "Book Edition", "Book Category");
                    printf("%s", line);
                    found = 1;
                }
                else
                {
                    fprintf(update, "%s", line);
                }
            }
            fclose(books);
            fclose(update);

            //If a Book is deleted
            if(found)
            {
                //Remove and check for errors
                if (remove("Issued Books List.txt") != 0)
                {
                    printf("Error deleting Issued Books List.txt");
                    return 1;
                }
                // Rename and check for errors
                if (rename("Delete Issue Books.txt", "Issued Books List.txt") != 0)
                {
                    printf("Error renaming Delete Issue Books.txt to Issued Books List.txt");
                    return 1;
                }
                printf("Issue Book Deleted Successfully...\n");
            }
            else
            {
                //Remove the temporary file
                if (remove("Delete Issue Books.txt") != 0)
                {
                    printf("Error deleting Delete Issue Books.txt");
                    return 1;
                }
                printf("Book ID did not found in the data to Delete...\n");
            }
            break;
        case 2:
            printf("Returning to Previous Menu...\n");
            main_menu();
            break;
        default:
            printf("Invalid Input...\n");
            break;
        }
    }
    return 0;
}
int main()
{
    main_menu();
    return 0;
}
int main_menu()
{
    int choice;
    char buffer[20];

    while(1)
    {
        printf("\n=====LIBRARY MANAGEMENT SYSTEM=====\n");
        printf("1.  Book Categories\n");
        printf("2.  Add Books\n");
        printf("3.  Display Book List\n");
        printf("4.  Search Book\n");
        printf("5.  Update Book\n");
        printf("6.  Delete Book\n");
        printf("7.  Issue Book\n");
        printf("8.  Issued Books List\n");
        printf("9.  Delete an Issued Book (Returned)\n");
        printf("10. Defaulted Students List\n");
        printf("11. Exit\n");
        printf("Enter 1-11 to select from above menu: ");
        fgets(buffer, sizeof(buffer), stdin);

        if(sscanf(buffer, "%d", &choice) != 1)
        {
            printf("Please enter a Valid Number...\n");
            main_menu();
        }

        switch(choice)
        {
        case 1:
            book_categories();
            break;
        case 2:
            add_books();
            break;
        case 3:
            display_books();
            break;
        case 4:
            search_book();
            break;
        case 5:
            update_book();
            break;
        case 6:
            delete_book();
            break;
        case 7:
            issue_book();
            break;
        case 8:
            issued_book_list();
            break;
        case 9:
            delete_issue_book();
            break;
        case 10:
            defaulters_list();
            break;
        case 11:
            printf("Exiting the program...\n");
            exit(0);
            break;
        default:
            printf("You entered Invalid Input...\n");
            break;
        }
    }
    return 0;
}
