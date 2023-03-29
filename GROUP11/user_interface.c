#define _CRT_SECURE_NO_WARNINGS
#include "user_interface.h"


void print_greeting() {
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

    printf("d) Quits\n");
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

void quit_program(TaskManager* tm) {
    save_to_file(tm);
    destroy_task_manager(tm);
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
            //search a task
            search_a_task(tm->unfinished);
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
            search_a_task(tm->finished);
            break;
        case 'c':
            *back_to_upper = 1;
            break;
        default:
            printf("Wrong Command.\n");
        }
    }
}

TaskManager* init() {
    TaskManager* tm = init_task_manager();

    FILE* fp = fopen("data.txt", "r");

    if (fp == NULL || file_content_empty(fp))
    {
        // init from empty
    }
    else {
        // init from file
        read_from_file(tm);
        fclose(fp);
    }
    return tm;
}


//init from empty
TaskManager* init_task_manager() {
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
    dummy_node->next = NULL;
    return l;
}

int file_content_empty(FILE* fp)
{

    fseek(fp, 0, SEEK_END); // go to end of file
    if (ftell(fp) == 0)
    {
        return 1;
    }
    fseek(fp, 0, SEEK_SET);
    return 0;
}

void read_from_file(TaskManager* tm) {
    FILE* fp = fopen("data.txt", "r");
    char* line = NULL;
    size_t len = 0;
    size_t read;
    List* list = tm->unfinished;
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);
        trim_backspace(line);
        if (line[0] == '0') {
            //printf("get unfinished\n");
            continue;
        }
        if (line[0] == '1') {
            //printf("get finished\n");
            list = tm->finished;
            continue;
        }
        Task* t = (Task*)malloc(sizeof(Task));
        t->next = NULL;
        // printf("%s\n", line);
        strcpy(t->title, line);
        read = getline(&line, &len, fp);
        strcpy(t->desc, line);
        push(list, t);
    }
    fclose(fp);
}

size_t getline(char** lineptr, size_t* n, FILE* stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    size_t bufsize = *n;
    int c = fgetc(stream);

    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(bufsize);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    size_t i = 0;
    while (c != EOF) {
        if (i >= bufsize - 1) {
            bufsize *= 2;
            char* new_ptr = realloc(*lineptr, bufsize);
            if (new_ptr == NULL) {
                return -1;
            }
            *lineptr = new_ptr;
            *n = bufsize;
        }

        (*lineptr)[i] = c;
        i++;

        if (c == '\n') {
            break;
        }

        c = fgetc(stream);
    }

    (*lineptr)[i] = '\0';
    return i;
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
        printf("%d. %s\n", counter, current_task->title);
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

void get_multiple_line(char* target, char* prompt)
{
    printf("%s\n", prompt);

    while (fgets(target, MAXCHAR, stdin) != NULL) {
        int len = strlen(target);
        if (target[len - 1] == '\n' && len != 1) {
            break;
        }
    }
    // 
    trim_backspace(target);
}

int get_task_detail(char* title, char* desc)
{
    char* prompt_title = "Please enter the title for the task(no more than 50 characters).Enter \'q\' to cancel this action.";
    get_multiple_line(title, prompt_title);
    // check cancel 
    if (check_cancel(title)) {
        return 1;
    }

    char* prompt_desc = "Please enter the description for the task(no more than 100 characters).Enter \'q\' to cancel this action.";
    get_multiple_line(desc, prompt_desc);
    // check cancel 
    if (check_cancel(desc)) {
        return 1;
    }

    return 0;
}

void add_a_new_task(List* list)
{
    char title[MAXCHAR];
    char desc[MAXCHAR];
    if (get_task_detail(title, desc)) {
        return;
    }

    //create task
    Task* new_task = create_task(title, desc);
    push(list, new_task);
    printf("Successfully added the new task.\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}


Task* create_task(char* title, char* desc) {

    Task* task = (Task*)malloc(sizeof(Task));
    strcpy(task->title, title);
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

    char title[MAXCHAR];
    char desc[MAXCHAR];
    if (get_task_detail(title, desc)) {
        return;
    }
    //create task
    Task* update_task = create_task(title, desc);
    Task* deleted = take_task_from_list(list, index_num);
    free(deleted);
    push(list, update_task);
}

void search_a_task(List* list) {
    char* prompt_search = "Please enter keyword to search a task. Enter \'q\' to cancel this action.";
    // read user input
    char desc[MAXCHAR];
    get_multiple_line(desc, prompt_search);
    if (check_cancel(desc)) {
        return;
    }
    Task* target = search_the_task(list, desc);
    if (target == NULL) {
        printf("Sorry, the task you searched is not in the list\n");
    }
    else {
        print_task(target);
    }
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}

Task* search_the_task(List* list, char* keyword) {
    if (empty(list)) {
        printf("Can not search empty list\n");
        return NULL;
    }
    Task* cur = list->head;
    while (cur != NULL) {
        char* ret = strstr(cur->desc, keyword);
        if (ret != NULL) {
            // search hit
            return cur;
        }
        cur = cur->next;
    }
    // search failed 
    return NULL;

}

int empty(List* list) {
    if (list->top == list->head) {
        return 1;
    }
    return 0;
}

void print_task(Task* task) {
    printf("###########################\n");
    printf("%s\n", task->title);
    printf("%s\n", task->desc);
    printf("###########################\n");
}

void destroy_task_manager(TaskManager* tm) {
    destroy_list(tm->finished);
    destroy_list(tm->unfinished);
    free(tm);
}

void destroy_list(List* list) {
    Task* cur = list->head;
    // iterate thru the whole list and free task item memory one by one
    while (cur != NULL) {
        Task* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

void save_to_file(TaskManager* tm) {
    FILE* fp = fopen("data.txt", "w+");
    fprintf(fp, "0\n");
    Task* un = tm->unfinished->head->next;

    while (un != NULL) {
        fprintf(fp, "%s\n", un->title);
        fprintf(fp, "%s\n", un->desc);
        un = un->next;
    }
    fprintf(fp, "1\n");
    Task* fin = tm->finished->head->next;

    while (fin != NULL) {
        fprintf(fp, "%s\n", fin->title);
        fprintf(fp, "%s\n", fin->desc);
        fin = fin->next;
    }
    fclose(fp);
}