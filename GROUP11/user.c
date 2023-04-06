#define _CRT_SECURE_NO_WARNINGS
#include "user.h"



#define MAXNAME 11
#define MAXPASSWORD 21

int user_valiation()
{
    FILE* fp = fopen("user.txt", "r");

    if (fp == NULL || file_content_empty(fp))
    {
        // init from empty
        // set username and password, save username, random number, hash result to user.txt
        set_user_profile();
        return 1;
    }
    else {
        // init from file
        if (password_validation(fp))
        {
            return 1;
        }
        fclose(fp);
    }

}

void set_user_profile() {
    char username[MAXNAME];
    char password[MAXPASSWORD];
    char randnum[9];
    uint8_t result[16];
    char output[33];
    //set username and password
    set_username_and_password(username, password);
    //printf("%s\n", password);

    //generate random number
    generate_random_number(randnum);
    //printf("%s\n", randnum);

    //generate hash result
    generate_hash_result(password, randnum, result);
    convert_to_hex(result, output);
    //printf("%s\n", output);

    //save username, password, hash reuslt to file
    save_to_user_file(username, randnum, output);
}

void set_username_and_password(char* username, char* password) {
    char* prompt_username = "Please enter your username(no more than 10 characters).";
    char* prompt_password = "Please enter your password(no more than 20 characters).";

    get_multiple_line(username, prompt_username);
    get_multiple_line(password, prompt_password);
}

void generate_random_number(char* random_number) {
    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int num_chars = 8;

    srand(time(NULL)); // Seed the random number generator with current time

    for (int i = 0; i < num_chars; i++) {
        random_number[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    random_number[num_chars] = '\0'; // Add null terminator to the end
}

void generate_hash_result(char* password, char* random_number, uint8_t* result) {
    // concatenate two string 
    strcat(password, random_number);
    //printf("%s\n", password);
    md5String(password, result);
    /*for (int i = 0; i < 16; i++) {
        printf("%u ", result[i]);
    }*/
}

void convert_to_hex(uint8_t* input, char* output)
{
    for (int i = 0; i < 16; i++) {
        sprintf(output + 2 * i, "%02x", input[i]);
    }
}

void save_to_user_file(char* username, char* random_number, char* output) {
    FILE* fp = fopen("user.txt", "w+");
    fprintf(fp, "%s\n", username);
    fprintf(fp, "%s\n", random_number);
    fprintf(fp, "%s\n", output);
    fclose(fp);
}

int password_validation(FILE* fp)
{
    char username[MAXNAME];
    char password[MAXPASSWORD];
    char randnum[9];
    uint8_t result[16];
    char output[33];
    read_from_user_file(fp, username, randnum, output);
    printf("Welcome %s\n", username);
    while (1) {
        get_password(password);
        if (validation(password, randnum, result, output))
        {
            return 1;
        }
        else
        {
            printf("Wrong password.\n");
        }

    }

}

void read_from_user_file(FILE* fp, char* username, char* random_number, char* output) {
    //read from file
    char* line = NULL;
    size_t len = 0;
    size_t read;

    read = getline(&line, &len, fp);
    trim_backspace(line);
    strcpy(username, line);

    read = getline(&line, &len, fp);
    trim_backspace(line);
    strcpy(random_number, line);

    read = getline(&line, &len, fp);
    trim_backspace(line);
    strcpy(output, line);
}

void get_password(char* password) {

    char* prompt_password = "Please enter your password";
    get_multiple_line(password, prompt_password);
}

int validation(char* password, char* randnum, uint8_t* result, char* output) {

    char my_output[33];
    generate_hash_result(password, randnum, result);
    convert_to_hex(result, my_output);
    if (strcmp(output, my_output) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}