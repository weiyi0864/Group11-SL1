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

void upper_menu_input(char op, int* quit_flag, TaskManager* tm) {
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    switch (op)
    {
    case 'a':
        display_all_lists(tm);
        break;
    case 'b':
        manage_task_list(0, tm);
        break;
    case 'c':
        manage_task_list(1, tm);
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

void print_ongoing_menu() {
    printf("Please select action to current task list\n");

    printf("a) Add a new task\n");

    printf("b) Finish a task \n");

    printf("c) Delete a task \n");

    printf("d) Update a task \n");

    printf("e) Search a task \n");

    printf("f) Back to main menu\n");
}

void print_finished_menu() {
    printf("Please select action to current task list\n");

    printf("a) Delete a task\n");

    printf("b) Search a task \n");

    printf("c) Back to main menu\n");
}


void execute_function(int state, char op, TaskManager* tm, int* back_to_upper) {
    if (state == 0) {
        switch (op)
        {
        case 'a':
            // add a new task
            add_a_new_task(tm->unfinished);
            break;
        case 'b':
            // finish a task 
            //finish_a_task(tm);
            break;
        case 'c':
            //delete_a_task(tm->unfinished);
            break;
        case 'd':
            //update_a_task(tm->unfinished);
            break;
        case 'e':
            // search a task
            //search_a_task(tm->unfinished);
            break;
        case 'f':
            *back_to_upper = 1;
            break;
        default:
            printf("Wrong Command.\n");
        }
    }
    else if (state == 1) {
        switch (op)
        {
        case 'a':
            //delete_a_task(tm->finished);
            break;
        case 'b':
            //search_a_task(tm->finished);
            break;
        case 'c':
            *back_to_upper = 1;
            break;
        default:
            printf("Wrong Command.\n");
        }
    }
}

//init from empty
TaskManager* init() {
    TaskManager* manager = (TaskManager*)malloc(sizeof(TaskManager));
    manager->finished = init_list();
    manager->unfinished = init_list();
    return manager;
}

List* init_list() {
    List* l = (List*)malloc(sizeof(List));
    l->count_num = 0;
    Task* dummy_node = (Task*)malloc(sizeof(Task));
    l->head = dummy_node;
    l->top = dummy_node;
    return l;
}

void display_all_lists(TaskManager* tm) {
    printf("Ongoing Task List\n");
    display_list(tm->unfinished);
    printf("Finished Task List\n");
    display_list(tm->finished);
}

void display_list(List* list) {
    if (list->top == list->head) {
        printf("No tasks in the list so far\n");
        return;
    }
    Task* current_task = list->head->next;
    int counter = 1;
    while (current_task != NULL) {
        printf("%d. %s\n",counter, current_task->desc);
        current_task = current_task->next;
        counter++;
    }
}

void manage_task_list(int state, TaskManager* tm) {
    int back_to_upper = 0;
    while (1) {
        if (state == 0) {
            printf("Ongoing Task List:\n");
            display_list(tm->unfinished);
            printf("\n");
            print_ongoing_menu();
        }
        if (state == 1) {
            printf("Finished Task List:\n");
            display_list(tm->finished);
            printf("\n");
            print_finished_menu();
        }
        char op;
        take_user_input(&op);
        execute_function(state, op, tm, &back_to_upper);
        if (back_to_upper) {
            break;
        }
    }
}

void add_a_new_task(List* list)
{
    printf("Please\n");
    char desc[MAXCHAR] = "my new task description\n";
    Task* new_task = create_task(desc);
    push(list, new_task);
    printf("Successfully added the new task.\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}


Task* create_task(char* desc) {

    Task* task = (Task*)malloc(sizeof(Task));
    strcpy(task->desc, desc);
    task->next = NULL;
    return task;
}

void push(List* list, Task* new_task) {
    //locate current last task on the list
    Task* current_last = list->top;
    current_last->next = new_task;
    // ==list->top->next = new_task;
    list->top = new_task;
    list->count_num++;

}