#pragma once
#include "task.h"

void print_greeting();
void take_user_input(char* op);
void print_menu();
void upper_menu_input(char op, int* quit_flag, TaskManager* tm);
void quit_program();

TaskManager* init();
List* init_list();

void display_all_lists(TaskManager* tm);
void display_list(List* list);

void print_ongoing_menu();
void print_finished_menu();

void manage_task_list(int state, TaskManager* tm);

void execute_function(int state, char op, TaskManager* tm, int* back_to_upper);

void add_a_new_task(List* list);
Task* create_task(char* desc);

void push(List* list, Task* new_task);