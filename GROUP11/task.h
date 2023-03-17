#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 50

typedef struct Task Task;

struct Task {
    char desc[MAXCHAR];//test description
    Task* next;
};

// linked list to hold tasks
typedef struct List {
    int count_num;
    Task* head;
    Task* top;
}List;

// task manager holds two linked list 
// finished and unfinished
typedef struct TaskManager {
    List* finished;
    List* unfinished;
}TaskManager;

