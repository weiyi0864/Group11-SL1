#pragma once
#include "task.h"

void print_greeting();
void take_user_input(char* op);
void print_menu();
void upper_menu_input(char op, int* quit_flag, TaskManager* tm);

void quit_program(TaskManager* tm);
void destroy_task_manager(TaskManager* tm);
void destroy_list(List* list);

TaskManager* init();
TaskManager* init_task_manager();
List* init_list();
int file_content_empty(FILE* fp);
void read_from_file(TaskManager* tm);
size_t getline(char** lineptr, size_t* n, FILE* stream);

void display_all_lists(TaskManager* tm);
void display_list(List* list);

void print_ongoing_menu();
void print_finished_menu();

void manage_task_list(int state, TaskManager* tm);

void execute_function(int state, char op, TaskManager* tm, int* back_to_upper);

void add_a_new_task(List* list);
Task* create_task(char* desc);
void trim_backspace(char* str);
int check_cancel(char* str);

void finish_a_task(TaskManager* tm);
Task* take_task_from_list(List* list, int index);
void retrace_top(List* list);

void push(List* list, Task* new_task);

void delete_a_task(List* list);

void update_a_task(List* list);

void search_a_task(List* list);
Task* search_the_task(List* list, char* keyword);
int empty(List* list);
void print_task(Task* task);

void save_to_file(TaskManager* tm);

void get_multiple_line(char* target, char* prompt);
int get_task_detail(char* title, char* desc);