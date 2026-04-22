/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include "../include/mysh.h"

static int handle_empty_or_invalid_line(char *line)
{
    if (line[0] == '\n' || line[0] == '\0') {
        free(line);
        return 1;
    }
    return 0;
}

static void line_prompt(void)
{
    char *pwd = getcwd(NULL, 0);

    pwd = my_strafter(pwd, "/home");
    if (isatty(STDIN_FILENO)) {
        my_putstr(RESET);
        my_putstr(GREEN);
        my_putchar('~');
        my_putstr(pwd);
        my_putstr("> ");
        my_putstr(RESET);
        my_putstr(BLUE);
    }
}

static char *get_input_line(struct_mysh_t *mysh)
{
    char *line = NULL;
    size_t len = 0;

    line_prompt();
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        free_shell(mysh);
        return NULL;
    }
    return line;
}

static int process_and_execute(struct_mysh_t *mysh, char *line)
{
    char *processed_line = substitute_backticks(line, mysh);
    int code;

    if (!processed_line) {
        free(line);
        return 1;
    }
    code = parse_command(mysh, processed_line);
    free(line);
    free(processed_line);
    return code;
}

int mainloop(struct_mysh_t *mysh)
{
    char *line = get_input_line(mysh);

    if (!line)
        return 0;
    if (handle_empty_or_invalid_line(line))
        return 0;
    mysh->history = add_to_history(line, mysh->history);
    return process_and_execute(mysh, line);
}
