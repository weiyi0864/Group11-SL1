#define _CRT_SECURE_NO_WARNINGS
#include "user_interface.h"

void print_greeting(){
    printf("Welcome to Task Manager Program\n");
}

void take_user_input(char* op)
{
    scanf(" %c", op);
}

void print_menu() {
    printf("Please select task list to manage. To choose a function, enter its letter label:\n");

    printf("a) Display all current tasks\n");

    printf("b) On going task list \n");

    printf("c) Finished task list \n");

    printf("d) Quit\n");
}

void upper_menu_input(char op, int* quit_flag) {
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    switch (op)
    {
    case 'a':
        //display_all_lists(tm);
        break;
    case 'b':
        //manage_task_list(0, tm);
        break;
    case 'c':
        //manage_task_list(1, tm);
        break;
    case 'd':
        *quit_flag = 1;
        break;
    default:
        printf("Wrong Command.\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}

void quit_program() {
    //save_to_file(tm);
    //destroy_task_manager(tm);
}