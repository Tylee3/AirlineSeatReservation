#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int id;
    bool is_assigned;
    char last_name[20];
    char first_name[20];
} Seat;

void init_seats(Seat seats[], int size);
void run_first_menu(Seat outbound[], Seat inbound[], int size);
void show_first_menu();
char get_first_menu_choice();
void run_second_menu(Seat seats[], int size);
void show_second_menu();
char get_second_menu_choice();
void show_empty_count(Seat seats[], int size);
void show_empty_list(Seat seats[], int size);
void sort_indices_by_name(Seat seats[], int indices[], int count);
void show_alphabetical_list(Seat seats[], int size);
void assign_seat(Seat seats[], int size);
void delete_seat(Seat seats[], int size);
void save_seats(Seat seats[], int size, const char *filename);
void load_seats(Seat seats[], int size, const char *filename);

int main()
{
    Seat outbound[24];
    Seat inbound[24];

    init_seats(outbound, 24);
    init_seats(inbound, 24);

    load_seats(outbound, 24, "outbound.txt");
    load_seats(inbound, 24, "inbound.txt");

    run_first_menu(outbound, inbound, 24);
    return 0;
}

// Initializes all seats to empty and unassigned
void init_seats(Seat seats[], int size)
{
    for (int i = 0; i < size; i++)
    {
        seats[i].id = i + 1;
        seats[i].is_assigned = false;
        seats[i].last_name[0] = '\0';
        seats[i].first_name[0] = '\0';
    }
}

// Handles the first level menu loop
void run_first_menu(Seat outbound[], Seat inbound[], int size)
{
    char choice;

    while (1)
    {
        show_first_menu();
        choice = get_first_menu_choice();
        if (choice == 'a')
        {
            run_second_menu(outbound, size);
        }
        else if (choice == 'b')
        {
            run_second_menu(inbound, size);
        }
        else if (choice == 'c')
        {
            save_seats(outbound, size, "outbound.txt");
            save_seats(inbound, size, "inbound.txt");
            break;
        }
        else
        {
            fprintf(stderr, "Error. Please try again.\n");
        }
    }
}

// Prints the first level menu options
void show_first_menu()
{
    printf("a) Outbound Flight\n");
    printf("b) Inbound Flight\n");
    printf("c) Quit\n");
}

// Handles the first level user input
char get_first_menu_choice()
{
    char choice;
    scanf(" %c", &choice);
    return choice;
}

// Handles the second level menu option
void run_second_menu(Seat seats[], int size)
{
    char choice;

    while (1)
    {
        show_second_menu();
        choice = get_second_menu_choice();
        if (choice == 'f')
        {
            break;
        }

        switch (choice)
        {
        case 'a':
            show_empty_count(seats, size);
            break;
        case 'b':
            show_empty_list(seats, size);
            break;
        case 'c':
            show_alphabetical_list(seats, size);
            break;
        case 'd':
            assign_seat(seats, size);
            break;
        case 'e':
            delete_seat(seats, size);
            break;
        default:
            fprintf(stderr, "Invalid choice. Try again.\n");
        }
    }
}

// Prints the second level menu options
void show_second_menu()
{
    printf("a) Show number of empty seats\n");
    printf("b) Show list of empty seats\n");
    printf("c) Show alphabetical list of seats\n");
    printf("d) Assign a customer to a seat assignment\n");
    printf("e) Delete a seat assignment\n");
    printf("f) Return to Main menu\n");
}

// Handles the second level user input
char get_second_menu_choice()
{
    char choice;
    while (1)
    {
        scanf(" %c", &choice);
        if (choice >= 'a' && choice <= 'f')
        {
            return choice;
        }
        fprintf(stderr, "Invalid choice. Try again.\n");
    }
}

// Returns the empty seat count
void show_empty_count(Seat seats[], int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (seats[i].is_assigned == false)
        {
            count++;
        }
    }

    printf("Number of empty seats: %d\n", count);
}

// Returns the empty seat list
void show_empty_list(Seat seats[], int size)
{
    printf("List of empty seats:\n");

    for (int i = 0; i < size; i++)
    {
        if (seats[i].is_assigned == false)
        {
            printf("Seat %d is empty\n", seats[i].id);
        }
    }
}

// Bubble sort helper function for show_alphabetical_list
void sort_indices_by_name(Seat seats[], int indices[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int a = indices[j];
            int b = indices[j + 1];

            int cmp = strcmp(seats[a].last_name, seats[b].last_name);
            if (cmp > 0)
            {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
            else if (cmp == 0)
            {
                cmp = strcmp(seats[a].first_name, seats[b].first_name);
                if (cmp > 0)
                {
                    int temp = indices[j];
                    indices[j] = indices[j + 1];
                    indices[j + 1] = temp;
                }
                else if (cmp == 0)
                {
                    if (seats[a].id > seats[b].id)
                    {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
        }
    }
}

// Returns the seats in an ordered list by id, last name, and first name
void show_alphabetical_list(Seat seats[], int size)
{
    int indices[24];
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (seats[i].is_assigned)
        {
            indices[count++] = i;
        }
    }

    if (count == 0)
    {
        printf("No seats assigned\n");
        return;
    }

    sort_indices_by_name(seats, indices, count);

    printf("Alphabetical list of seats:\n");
    for (int i = 0; i < count; i++)
    {
        int index = indices[i];
        printf("Seat %d: %s, %s\n", seats[index].id, seats[index].last_name, seats[index].first_name);
    }
}

// Assigns a new person to a seat
void assign_seat(Seat seats[], int size)
{
    int empty = 0;
    for (int i = 0; i < size; i++)
    {
        if (!seats[i].is_assigned)
        {
            printf("Seat %d is empty\n", seats[i].id);
            empty++;
        }
    }

    if (empty == 0)
    {
        printf("No seats available\n");
        return;
    }

    int seat_num;
    printf("Input a seat number (0 to cancel)\n");
    scanf("%d", &seat_num);

    if (seat_num == 0)
    {
        printf("Action cancelled\n");
        return;
    }

    if (seat_num < 1 || seat_num > size)
    {
        printf("Invalid seat number\n");
        return;
    }

    if (seats[seat_num - 1].is_assigned)
    {
        printf("Seat %d is already assigned\n", seat_num);
        return;
    }

    printf("Enter last name:\n");
    scanf("%19s", seats[seat_num - 1].last_name);

    printf("Enter first name:\n");
    scanf("%19s", seats[seat_num - 1].first_name);

    seats[seat_num - 1].is_assigned = true;
    printf("Seat %d assigned to %s, %s\n", seats[seat_num - 1].id, seats[seat_num - 1].last_name, seats[seat_num - 1].first_name);
}

// Deletes a person from a seat
void delete_seat(Seat seats[], int size)
{
    int seat_num;
    printf("Input a seat number (0 to cancel)\n");
    scanf("%d", &seat_num);

    if (seat_num == 0)
    {
        printf("Action cancelled\n");
        return;
    }
    if (seat_num < 1 || seat_num > size)
    {
        printf("Invalid seat number\n");
        return;
    }
    if (!seats[seat_num - 1].is_assigned)
    {
        printf("Seat %d is not assigned\n", seat_num);
        return;
    }

    seats[seat_num - 1].is_assigned = false;
    seats[seat_num - 1].last_name[0] = '\0';
    seats[seat_num - 1].first_name[0] = '\0';
    printf("Seat %d cleared\n", seats[seat_num - 1].id);
}

void save_seats(Seat seats[], int size, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file for saving");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%d %d %s %s\n", seats[i].id, seats[i].is_assigned, seats[i].last_name, seats[i].first_name);
    }

    fclose(fp);
}

void load_seats(Seat seats[], int size, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("No saved data found\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (fscanf(fp, "%d %d %19s %19s", &seats[i].id, (int *)&seats[i].is_assigned, seats[i].last_name, seats[i].first_name) == 4)
        {
        }
        else
        {
            seats[i].is_assigned = false;
            seats[i].last_name[0] = '\0';
            seats[i].first_name[0] = '\0';
        }
    }

    fclose(fp);
}