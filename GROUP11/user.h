#pragma once
#include "task.h"
#include "user_interface.h"
#include "md5.h"
#include <time.h>

int user_valiation();
void set_user_profile();
void set_username_and_password(char* username, char* password);
void generate_random_number(char* random_number);

void generate_hash_result(char* password, char* random_number, uint8_t* result);
void convert_to_hex(uint8_t* input, char* output);
void save_to_user_file(char* username, char* random_number, char* output);
void read_from_user_file(FILE* fp, char* username, char* random_number, char* output);
void get_password(char* password);
int password_validation(FILE* fp);
int validation(char* password, char* randnum, uint8_t* result, char* output);