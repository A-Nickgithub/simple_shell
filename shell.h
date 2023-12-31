#ifndef SHELL_H_
#define SHELL_H_
/* const Macros */

extern char **environ;
extern char *program_invocation_name;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/* Structs */
/**
 * struct built_in - Struct to handle the built-ins commands
 * @command: input command to handle
 * @f: function pointer to execute the command
 *
 * Description: has a command an function pointer to react to it
 */
typedef struct built_in
{
	char *command;
	int (*f)(char **argv);
} built_in_t;

int myexit(char **argv);
int _printenv(char **argv);
int _setenv(char **argv);
int _cd(char **argv);
int _unsetenv(char **argv);

/* functions prototypes */
void sign_handler(int i);
char *read_input();
void _freeall(char **argv, char **path);
char *_strcat(char *string1, char *string2);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *source);
char *_strdup(char *str);
unsigned int _strcspn(char *s, char *pref);
char *_strchr(char *s, char b);

int check_existence(char *file);
char **token_buff(char *buff, char *delimiter);
void _puts(char *s);
int _putchar(const char c);
void _printd(int n);

char *_getenv(char *key);
char *_strtok(char *string, char *delm);

int _atoi(char *s);

int shell_execute(char **argv, built_in_t built_in_arr[]);
int shell_launch(char **argv);

void _error_handler(int *status, int err, char **argv);
void _print_base_error(int err, char **argv);

void _non_int(built_in_t arr[]);
#endif
