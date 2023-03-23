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
            finish_a_task(tm);
            break;
        case 'c':
            delete_a_task(tm->unfinished);
            break;
        case 'd':
            update_a_task(tm->unfinished);
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
            delete_a_task(tm->finished);
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
    printf("Please enter description for the task(no more than 50 characters).Enter \'q\' to cancel this action.\n");
    char desc[MAXCHAR];
    while (fgets(desc, MAXCHAR, stdin) != NULL) {
        int len = strlen(desc);
        if (desc[len - 1] == '\n' && len != 1) {
            break;
        }
    }
    // 
    trim_backspace(desc);
    // check cancel 
    if (check_cancel(desc)) {
        return;
    }
    //create task
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

void finish_a_task(TaskManager* tm) {
    // get the index you want to finish 
    printf("Please enter the index number the task you want to finish\n");
    int index_num;
    scanf("%d", &index_num);
    if (index_num > tm->unfinished->count_num || index_num <= 0) {
        printf("Invalid Index\n");
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        return NULL;
    }
    Task* finish = take_task_from_list(tm->unfinished, index_num);
   
    if (finish != NULL) {
        push(tm->finished, finish);
        printf("Congratulations! You have just finished a task\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}

Task* take_task_from_list(List* list, int index) {
    Task* previous_task = list->head;
    // find the task before the task to be deleted
    while (index > 1) {
        previous_task = previous_task->next;
        index--;
    }
    Task* target_task = previous_task->next;
    Task* next_task = previous_task->next->next;
    previous_task->next = next_task;
    list->count_num--;
    target_task->next = NULL;
    retrace_top(list);
    return target_task;
}

void retrace_top(List* list) {
    Task* cur = list->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    list->top = cur;
}


void delete_a_task(List* list) {
     printf("Please enter the index number the task you wanted to delete\n");
     int index_num;
     scanf("%d", &index_num);
     
     //validation
     if (index_num > list->count_num || index_num <= 0) {
         printf("Invalid Index\n");
         return 1;
     }

     //delete
     Task* previous_task = list->head;
     while (index_num > 1) {
         previous_task = previous_task->next;
         index_num--;
     }
     Task* target_task = previous_task->next;
     Task* next_task = previous_task->next->next;
     previous_task->next = next_task;
     list->count_num--;
     free(target_task);
     retrace_top(list);
}

void trim_backspace(char* str) {
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int check_cancel(char* str) {
    if (strlen(str) == 1 && str[0] == 'q') {
        return 1;
    }
    return 0;
}

void update_a_task(List* list) {
    printf("Please enter the index number the task you wanted to update\n");
    int index_num;
    scanf("%d", &index_num);

    if (index_num > list->count_num || index_num <= 0) {
        printf("Invalid Index\n");
        return 1;
    }

    printf("Please enter description for the task ( no more than 50 characters ). Enter \'q\' to cancel this action.\n");
    // read user input
    char desc[MAXCHAR];
    while (fgets(desc, MAXCHAR, stdin) != NULL) {
        int len = strlen(desc);
        if (desc[len - 1] == '\n' && len != 1) {
            break;
        }
    }
    //fgets(desc, MAXCHAR, stdin)
    trim_backspace(desc);
    // check cancel 
    if (check_cancel(desc)) {
        return;
    }

    //create task
    Task* update_task = create_task(desc);
    Task* deleted = take_task_from_list(list, index_num);
    free(deleted);
    push(list, update_task);
}


