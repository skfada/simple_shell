#ifndef SAJESH_H
#define SAJESH_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_sajesh.history"
#define HIST_MAX	4096

extern char **environ;
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

/**
 * struct liststr - singly linked list
 * @num: number
 * @str: string
 * @next: lionker
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passsk_data -
 *@env_changed: environmnet for change
 *@status: status for exit
 *@cmd_buf: cmd reader
 *@cmd_buf_type: cmd reader
 *@readfd: file descriptor reader
 *@histcount: history nmbert
 *@arg: argh input
 *@linecount_flag: flag line copunt
 *@fname: dile nbame
 *@env: list of environment
 *@environ: lisnked environment
 *@history: history list
 *@alias: the linked alias
 *@argv: arrtg toke
 *@path: path lovaation
 *@argc: atrc
 *@line_count: line countr
 *@err_num: err
 */
typedef struct passsk_data
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} sk_data_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin -
 *@type: data type
 *@func: functon
 */
typedef struct builtin
{
	char *type;
	int (*func)(sk_data_t *);
} builtin_table;


void sagesh_find_cmd(sk_data_t *);
void sagesh_fork_cmd(sk_data_t *);
int hsh(sk_data_t *, char **);
int sagesh_findBuiltin(sk_data_t *);

char *sajesh_dupChars(char *, int, int);
char *sajesh_findPath(sk_data_t *, char *, char *);
int sajesh_isCmd(sk_data_t *, char *);

int loophsh(char **);

int sajesh_putfd(char c, int fd);
int sajeshsajesh_putsfd(char *str, int fd);
void sajesh_eputs(char *);
int sajesh_eputchar(char);

char *sajesh_startsWith(const char *, const char *);
char *sajesh_strcat(char *, char *);
int sajesh_strlen(char *);
int sajesh_strcmp(char *, char *);

char *sajesh_strcpy(char *, char *);
int sajesh_putchar(char);
char *sajesh__strdup(const char *);
void sajesh_puts(char *);

char *sajesh_strncat(char *, char *, int);
char *sajesh_strchr(char *, char);
char *sajesh_strncpy(char *, char *, int);

char **sajesh_strtow2(char *, char);
char **sajesh_strtow(char *, char *);

void sajesh_ffree(char **);
char *sajesh_memset(char *, char, unsigned int);
void *sajesh_realloc(void *, unsigned int, unsigned int);

int sajesh_bfree(void **);

int sajesh_isDelim(char, char *);
int sajesh_interactive(sk_data_t *);
int sajesh_atoi(char *);
int sajesh_isalpha(int);

void sajesh_removeComments(char *);
int sajesh_print_d(int, int);
char *sajesh_convertNumber(long int, int, int);
int sajesh_erratoi(char *);
void sajesh_printError(sk_data_t *, char *);

int sajesh_help(sk_data_t *);
int sajesh_exit(sk_data_t *);
int sajesh_cd(sk_data_t *);

int sajesh_alias(sk_data_t *);
int sajesh_hist(sk_data_t *);

void sagesh_sigintHandler(int);
ssize_t get_input(sk_data_t *);
int sajesh_getline(sk_data_t *, char **, size_t *);


void sagesh_setSkData(sk_data_t *, char **);
void sagesh_clearSkData(sk_data_t *);
void sagesh_free_skData(sk_data_t *, int);

int _sajeshSetEnv(sk_data_t *);
int _sajeshUnsetEnv(sk_data_t *);
char *sajesh_getenv(sk_data_t *, const char *);
int sajesh_env(sk_data_t *);
int sajesh_EnvList(sk_data_t *);

int sajesh_setEnv(sk_data_t *, char *, char *);
char **sajesh_getEnviron(sk_data_t *);
int sajesh_unsetEnv(sk_data_t *, char *);

char *sajesh_getHistFile(sk_data_t *sk_data);
int sajesh_renumberHist(sk_data_t *sk_data);
int sagesh_writeHist(sk_data_t *sk_data);
int sajesh_readHist(sk_data_t *sk_data);
int sajesh_buildHistList(sk_data_t *sk_data, char *buf, int linecount);

size_t sajesh_printListStr(const list_t *);
list_t *sajesh_addNode(list_t **, const char *, int);
void sajesh_freeList(list_t **);
list_t *sajesh_addNode_end(list_t **, const char *, int);
int sajesh_delNodeAtIindex(list_t **, unsigned int);


size_t sajesh_listLen(const list_t *);
list_t *sajesh_nodeStartsWith(list_t *, char *, char);
ssize_t sajesh_getNodeIndex(list_t *, list_t *);
char **sajesh_listToStrings(list_t *);
size_t sajesh_printList(const list_t *);

int sk_replaceAlias(sk_data_t *);
int sajesh_replaceVars(sk_data_t *);
int sk_replaceString(char **, char *);
int sajesh_isChain(sk_data_t *, char *, size_t *);
void sajesh_checkChain(sk_data_t *, char *, size_t *, size_t, size_t);

#endif
