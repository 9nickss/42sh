/*
** EPITECH PROJECT, 2025
** mysh h
** File description:
** mysh h
*/

#include "my.h"
#include "mylist.h"
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <glob.h>
#include <time.h>

#ifndef _MYSH_H_
    #define _MYSH_H_

    #define RESET   "\033[0m"
    #define GREEN   "\033[0;32m"
    #define BLUE    "\033[0;34m"
    #define NB_BUILTIN 10

typedef struct alias_s {
    char *name;
    char *command;
    struct alias_s *next;
} alias_t;

typedef struct history_s {
    char *cmd;
    int nb;
    char *time;
    struct history_s *next;
} history_t;

typedef struct struct_mysh {
    char **tab;
    char *old_pwd;
    int exit_value;
    linked_list_t *list;
    linked_list_t *local_vars;
    history_t *history;
} struct_mysh_t;

typedef struct pipe_data {
    int prev_pipe[2];
    int curr_pipe[2];
    int is_first_cmd;
    int has_next;
} pipe_data_t;

//mainloop

int mainloop(struct_mysh_t *mysh);

// and_or.c
int execute_and_or(struct_mysh_t *mysh, char *line);

//backticks

typedef struct child_params {
    int pipefd[2];
    char **args;
    char **env_array;
} child_params_t;

char *execute_command(char *cmd, struct_mysh_t *sh);
int free_shell(struct_mysh_t *mysh);
void free_linked_list(linked_list_t *list);
int child_process(int pipefd[2], const char *cmd, char **env_array);
char *find_command_path(const char *cmd, char **env);
char *substitute_backticks(const char *input, struct_mysh_t *sh);

//globing

int process_wildcards_command(char **args, struct_mysh_t *mysh);

// history.c

history_t *add_to_history(const char *cmd, history_t *history);
int my_history(struct_mysh_t *mysh);

typedef struct inhibitor_state_s {
    int in_single_quotes;
    int in_double_quotes;
    int escaped;
    int backslash_count;
} inhibitor_state_t;

// exec_prog.c

int error_execve(struct_mysh_t *mysh, char **env);
int handle_signal(struct_mysh_t *mysh, int status);
int exec_command(struct_mysh_t *mysh);
int fork_without_pipe(struct_mysh_t *mysh);

// exit_shell.c

int display_free_exit(struct_mysh_t *mysh, int value);
int my_exit(struct_mysh_t *mysh);

// init_struct.c

struct_mysh_t *init_struct(char **env);

// main.c

int parse_ptr(char *str);
int check_builtin(struct_mysh_t *mysh, char *line);
int main_program(struct_mysh_t *mysh);
int main(int ac, char **av, char **env);

// my_cd.c

void new_pwd(struct_mysh_t *mysh, char *pwd);
int home_pwd(struct_mysh_t *mysh);
int old_pwd(struct_mysh_t *mysh);
int classic_cd(struct_mysh_t *mysh);
int my_cd(struct_mysh_t *mysh);

// my_env.c

int print_env(struct_mysh_t *mysh);
int my_env(struct_mysh_t *mysh);

// parse_env.c

char **parse_env(struct_mysh_t *mysh, char *id, int size);
char *find_path(struct_mysh_t *mysh);

// exec_command.c

int parse_command(struct_mysh_t *mysh, char *line);

// setenv.c

int error(struct_mysh_t *mysh);
void copy_into_ll(struct_mysh_t *mysh);
int my_setenv(struct_mysh_t *mysh);

// stock_env.c

void remove_node(linked_list_t **head, const char *value, int size);
int add_to_list_back(linked_list_t **list, void *data);
linked_list_t *env_to_ll(char **env);
char **ll_to_env(linked_list_t *list);

// unsetenv.c

int my_unsetenv(struct_mysh_t *mysh);

// do_pipe.c

int exec_pipe(struct_mysh_t *params, char *line);

// free_shell.c

int free_shell(struct_mysh_t *mysh);

// inihibitor_handling.c

char **inhibitor_parsing(char const *s, char const *sep);
void reset_state(inhibitor_state_t *state);
void update_state(inhibitor_state_t *state, char const c);

// inhibitor_helpers.c

char get_escaped_char(char c);
char **allocate_result(char const *s, char const *sep,
    inhibitor_state_t *state, int *word_count);
void process_char(char current_char, char *array_line, int *row_target,
    inhibitor_state_t *state);
char *process_word(char const *s, int start_idx, int word_len,
    inhibitor_state_t *state);
void handle_quote_char(char current_char, inhibitor_state_t *state);

// more_helpers.c

int nb_words(char const *str, char const *sep, inhibitor_state_t *state);
void handle_escaped_char(char current_char, char *array_line, int *row_target,
    inhibitor_state_t *state);
int is_recognized_escape(char c);
int separator(char const c, char const *sep, inhibitor_state_t *state);
char *clean_str(const char *str, const char *separators);

// alias.c and unalias.c

int my_alias(struct_mysh_t *mysh);
alias_t **get_alias(void);
void free_alias_list(alias_t *head);
int my_unalias(struct_mysh_t *mysh);
int resolve_and_update_alias(struct_mysh_t *mysh, alias_t **head, char *line);

// which.c

typedef struct which {
    char *path_env;
    char *executable_path;
    int found;
    int status;
} which_t;

int my_which(struct_mysh_t *mysh);

typedef struct expand_state {
    const char *str;
    char *result;
    int i;
    int j;
} expand_state_t;

// Local variable commands
int my_set(struct_mysh_t *mysh);
int my_unset(struct_mysh_t *mysh);

// Local variable display functions
int print_local_vars(struct_mysh_t *mysh);
int print_all_vars(struct_mysh_t *mysh);
void print_formatted_var(char *data, int max_name_len);
int find_max_name_length(linked_list_t *list);

// Local variable utilities
char *get_var_value(struct_mysh_t *mysh, const char *var_name);
char *find_in_list(linked_list_t *list, const char *var_name, int name_len);
char **parse_local_var(struct_mysh_t *mysh, char *id, int size);
void expand_command_vars(struct_mysh_t *mysh);

#endif /* _MYSH_H_ */
