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
#define WR_BUFFER_SZ 1024
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
#define HIST_LIMIT	4096

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


int a_cmd(t_info *, char *);
char *duplicate_char(char *, int, int);
char *get_path(t_info *, char *, char *);


int loophsh(char **);


void puts_err(char *);
int putchar_err(char);
int filedes_put(char c, int fd);
int filedes_puts(char *str, int fd);


int _strlen(const char *);
int _strcmp(char *, char *);
char *begins_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, const char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


char **str_token(char *, char *);
char **str_token2(char *, char);


char *_memset(char *, char, unsigned int);
void f_release(char **);
void *_realloc(void *, unsigned int, unsigned int);


int free_add(void **);


int interact(t_info *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);


int atoi_error(char *);
void err_print(t_info *, char *);
int print_dec(int, int);
char *num_conv(long int, int, int);
void comment_rem(char *);


int my_exit(t_info *);
int change_cd(t_info *);
int help_cd(t_info *);


int my_hist(t_info *);
int rem_alias(t_info *, char *);
int put_alias(t_info *, char *);
int write_alias(t_list *);
int my_alias(t_info *);


ssize_t find_input(t_info *);
int get_line(t_info *, char **, size_t *);
void handleCtrlC(int);
ssize_t insert_buf(t_info *, char **, size_t *);
ssize_t rd_buffer(t_info *, char *, size_t *);


void delete_info(t_info *);
void put_info(t_info *, char **);
void free_inf(t_info *, int);


char *get_env(t_info *, const char *);
int my_env(t_info *);
int my_set_env(t_info *);
int my_unset_env(t_info *);
int fill_env_list(t_info *);


char **find_environ(t_info *);
int remenv(t_info *, char *);
int set_env(t_info *, char *, char *);


char *get_history(t_info *);
int wr_hist(t_info *);
int rd_hist(t_info *);
int hist_build(t_info *, char *, int);
int hist_renum(t_info *);


t_list *insert_node(t_list **, const char *, int);
t_list *insert_node_end(t_list **,const char *, int);
size_t put_str_list(const t_list *);
int rem_node_at_index(t_list **, unsigned int);
void clear_list(t_list **);


size_t len_list(const t_list *);
char **list_strings_conv(t_list *);
size_t put_list(const t_list *);
t_list *begin_node(t_list *, char *, char);
ssize_t set_node_index(t_list *, t_list *);


int is_linked(t_info *, char *, size_t *);
void chk_link(t_info *, char *, size_t *, size_t, size_t);
int change_alias(t_info *);
int change_vars(t_info *);
int change_string(char **, char *);

#endif
