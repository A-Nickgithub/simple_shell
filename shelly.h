#ifndef SHELLY_H
#define SHELLY_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

/* environment variables */
extern char **environ;
extern __sighandler_t signal(int __sig, __sighandler_t __handler);

/* handle built ins */
int checker(char **cmd, char *buf);
void promptuser(void);
void handlesignal(int m);
char **tokenizer(char *line);
char *testpath(char **path, char *command);
char *append(char *path, char *command);
int handlebuiltin(char **command, char *line);
void exitcmd(char **command, char *line);

void printenv(void);

/* string handlers */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
char *_strchr(char *s, char c);

void exec(char *cp, char **cmd);
char *findpath(void);

/* helper function for efficient free */
void freebuffers(char **buf);

struct builtin
{
	char *env;
	char *exit;
} builtin;

struct info
{
	int final_exit;
	int ln_count;
} info;

struct flags
{
	bool interactive;
} flags;

#endif /* SHELL_H */
