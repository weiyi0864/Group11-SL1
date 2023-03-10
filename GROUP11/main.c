#include "user_interface.h"

char op;
int quit_flag;

int main()
{
    quit_flag = 0;
    //TaskManager* tm = init();
    print_greeting();
    while (1) {
        print_menu();
        take_user_input(&op);
        upper_menu_input(op, &quit_flag);
        if (quit_flag)
        {
            quit_program();
            break;
        }
    }
    return 0;

}