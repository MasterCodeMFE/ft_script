#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pty.h>
#include <utmp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include "./../libft/libft.h"

#define FILE_PERMISSIONS 0644 
#define MAX_HISTORY 100
#define VERSION "0.8"

struct termios_min {
    unsigned int c_lflag;
};

typedef struct s_options {
    int append;
    char *command;
    char *echo;
    int return_code;
    int flush;
    int force;
    char *log_io;
    char *log_in;
    char *log_out;
    char *log_timing;
    char *logging_format;
    int output_limit;
    int quiet;
    char *timing_file;
    int version;
    int help;
} t_options;

typedef struct s_script_context {
    int     fd_log;
    int     fd_master;
    int     fd_slave;
    pid_t   child_pid;
    t_options *options;
    char    **envp;
    char    *shell;
    int     child_status;


    // Variables para el modo crudo y el historial
    struct termios saved_attributes;
    char *history[MAX_HISTORY];
    int history_count;
    int history_index;
    char line_buffer[1024];
    int line_len;
} t_script_context;

extern t_script_context *g_context;

int ft_script(char *file, char *shell, char **env, t_options *opt);
void parse_argument(int argc, char **argv, t_options *opt, char **file);
void parse_env(char **env, char **shell);
void print_start_info(t_script_context contex);
void print_end_info(t_script_context contex);
void print_terminal_info(int fd);
int spawn_child_process(t_script_context *contex);
void process_pty_output(t_script_context *contex);
void process_stdin_input(t_script_context *contex);
void print_version(void);
void print_help(void);
void process_stdin_input(t_script_context *contex);
void setup_signal_handlers(void);
void restore_signal_handlers(void);


#endif