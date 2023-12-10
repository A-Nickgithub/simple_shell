#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int numb;
	char *strg;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} inform_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inform_t *);
} builtin_table;

/* shell_loop.c */
int hsh(inform_t *, char **);
int find_builtin(inform_t *);
void find_cmd(inform_t *);
int is_exec(inform_t *inform, char *path);
void fork_cmd(inform_t *);
int handle_set_unset_env(inform_t *inform __attribute__((unused)), int setenv_flag);
/* path.c */
int is_cmd(inform_t *, char *);
char *dup_chara(char *, int, int);
char *find_path(inform_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char chara, int filedes);
int _putsfd(char *strg, int filedes);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* strg2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_reallocate.c */
char *_memset(char *, char, unsigned int);
void free_string(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem.c */
int my_free(void **);

/* atoi.c */
int interact(inform_t *);
int is_delm(char, char *);
int _alpha(int);
int my_atoi(char *);

/* errors2.c */
int _erratoi(char *);
void print_error(inform_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int myexi(inform_t *);
int _cd(inform_t *);
int _help(inform_t *);

/* builtin2.c */
int _history(inform_t *);
int set_alias(inform_t *inform, char *strg);
int set2_alias(inform_t *inform, char *strg);
int prt_alias(list_t *node);
int mainalias(inform_t *);

/*get_line.c */
ssize_t get_input(inform_t *);
int _getline(inform_t *, char **, size_t *);
void sigintHandler(int);
ssize_t input_buff(inform_t *, char **, size_t *);
ssize_t read_buff(inform_t *, char *, size_t *);

/* get_info.c */
void clear_inform(inform_t *);
void set_inform(inform_t *, char **);
void free_inform(inform_t *, int);

/* enviroment.c */
char *_getenv(inform_t *, const char *);
int _env(inform_t *);
int my_setenv(inform_t *);
int my_unsetenv(inform_t *);
int pop_env_list(inform_t *);

/* getenvirnoment.c */
char **get_environment(inform_t *);
int _unsetenv(inform_t *, char *);
int _setenv(inform_t *, char *, char *);

/* history.c */
char *history_file(inform_t *inform);
int create_history(inform_t *inform);
int read_history(inform_t *inform);
int build_history_list(inform_t *inform, char *buff, int linecount);
int renumber_history(inform_t *inform);

/* list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*list2.c */
size_t list_length(const list_t *);
char **list_to_strg(list_t *);
size_t print_list(const list_t *);
list_t *node_starts(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(inform_t *, char *, size_t *);
void check_chain(inform_t *, char *, size_t *, size_t, size_t);
int replace_alias(inform_t *);
int replace_var(inform_t *);
int replace_string(char **, char *);

#endif
