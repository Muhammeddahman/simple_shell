#ifndef SHELL_H
#define SHELL_H

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
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
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
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
} info_t;

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
	int (*func)(info_t *);
} builtin_table;

/* Function declarations (with changed comments) */

/* my_fourteenth_file.c */
int customShell(info_t *, char **);
int findBuiltin(info_t *);
void findCommand(info_t *);
void forkCommand(info_t *);

/* seventh_file.c */
int isExecutableCommand(info_t *, char *);
char *duplicateCharacters(char *, int, int);
char *findCmdInPath(info_t *, char *, char *);

/* tenth_file.c */
int primaryFunction(int, char **);

/*  seventeenth_file.c */
void _printToStderr(char *);
int _putToStderr(char);
int _putToFD(char c, int fd);
int _printToFD(char *str, int fd);

/* first_file.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* fourth_file.c */
char *my_copy_string(char *, char *);
char *my_duplicate_string(const char *);
void my_print_string(char *);
int my_putchar(char);

/* fifth_file.c */
char *custom_copy_n_string(char *, char *, int);
char *custom_concatenate_n_strings(char *, char *, int);
char *custom_find_character(char *, char);

/* my_sixth_file.c */
char **splitString(char *, char *);
char **splitString2(char *, char);

/* second_file.c */
char *my_memset(char *, char, unsigned int);
void string_free(char **);
void *memory_resize(void *, unsigned int, unsigned int);

/* third_file.c */
int my_free(void **);

/* eightth_file.c */
int isInteractiveMode(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int convertStringToInt(char *);

/* ninth_file.c */
int safeStringToInteger(char *);
void displayError(info_t *, char *);
int displayDecimal(int, int);
char *convertToBase(long int, int, int);
void eliminateComments(char *);

/* twentytwoth_file.c */
int _customExit(info_t *);
int _customCd(info_t *);
int _customHelp(info_t *);

/* twentyoneth_file.c */
int _shHistory(info_t *);
int _shAlias(info_t *);

/* fifteenth_file.c module */
ssize_t get_user_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigint_handler(int);

/* my_thirteenth_file.c module */
void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

/*  nineteenth_file.c module */
char *_printEnv(info_t *, const char *);
int _retrieveEnvVar(info_t *);
int _setEnvironmentVar(info_t *);
int _unsetEnvironmentVar(info_t *);
int fillEnvList(info_t *);

/* eighteenth_file.c module */
char **fetchEnvironment(info_t *);
int removeEnvironmentVar(info_t *, char *);
int setEnvironmentVar(info_t *, char *, char *);

/* sixteenth_file.c */
char *getHistoryFile(info_t *info);
int writeHistoryFile(info_t *info);
int loadHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistoryList(info_t *info);

/* eleventh_file.c module */
list_t *prependNode(list_t **, const char *, int);
list_t *appendNode(list_t **, const char *, int);
size_t printListData(const list_t *);
int removeNodeAtIndex(list_t **, unsigned int);
void freeLinkedList(list_t **);

/* twelveth_file.c module */
size_t add_node(const list_t *);
char **add_node_end(list_t *);
size_t print_list_str(const list_t *);
list_t *delete_node_at_index(list_t *, char *, char);
ssize_t free_list(list_t *, list_t *);

/* twentieth_file.c */
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

#endif

