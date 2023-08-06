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

/* macros */
#define RD_BUFFER_SZ 1024
#define WR_BUFF_SZ 1024
#define BUFFER_FLUSH -1
#define NORM_CMD	0
#define OR_CMD		1
#define AND_CMD		2
#define CHAIN_CMD	3
#define LOWCASE_CONV	1
#define UNSIGN_CONV	2
#define GETLN_USE 0
#define STRTOK_USE 0
#define FILE_HISTORY	".history_of_simple_shell"
#define MAX_LIMIT	4096

extern char **environ;


/**
 * struct str_list -  linked list
 * @number: field for number
 * @string: field for string
 * @next: pointer to another node
 */
typedef struct str_list
{
	int number;
	char *str;
	struct str_list *next;
} t_list;

/**
 *struct data - functional pseudo arguments passed,
 *		to allow uniform prototype for func ptr struct
 *@ag: getline generated string containing arguments
 *@av: arg generated strings of array
 *@path: current command's string path
 *@ac: count of argument
 *@count_line: count of error
 *@error_code: when exited, gives error code
 *@count_line_flag: flags up for inputed line
 *@name_f: filename of the program
 *@env_list: environ's local copy of linked list
 *@environ: environ copy from LL env
 *@hist: node of history
 *@alias: node of alias
 *@changed_env: environ change 
 *@stat: last executed command 
 *@cmd_ads: pointer's address to command_bufffer
 *@cmd_type: command types
 *@read_file_desc: line input read from file descriptor
 *@hist_cnt: count of history line
 */
typedef struct data
{
	char *ag;
	char **av;
	char *path;
	int ac;
	unsigned int count_line;
	int error_code;
	int count_line_flag;
	char *name_f;
	t_list *env_list;
	t_list *hist;
	t_list *alias;
	char **environ;
	int changed_env;
	int stat;

	char **cmd_ads;
	int cmd_type; 
	int read_file_desc;
	int hist_cnt;
} t_info;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct in_built - the inbuilt structure 
 *@flag_type: command flag builtings
 *@functn: function for the struct
 */
typedef struct in_built
{
	char *flag_type;
	int (*functn)(t_info *);
} in_built_chart;



int hash(t_info *, char **);
int get_inbuilt(t_info *);
void get_cmd(t_info *);
void fork_cmd(t_info *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void puts_err(char *);
int putchar_err(char);
int filedes_put(char c, int fd);
int filedes_puts(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int atoi_error(char *)
void err_print(t_info *, char *)
int print_dec(int, int);
char *num_conv(long int, int, int);
void comment_rem(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
