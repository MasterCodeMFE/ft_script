#include "./../inc/ft_script.h"

static const char *long_options[] = {
    "append", "command", "echo", "return", "flush", "force",
    "log-io", "log-in", "log-out", "log-timing",
    "logging-format", "output-limit", "quiet",
    "timing", "version", "help", NULL
};


/*Devulve 1 se es un argumento con opción y devulve 0 se es un argumento sin opción*/
static int option_requires_argument(char opt)
{
    return (opt == 'c' || opt == 'E' || opt == 'B' || opt == 'I' ||
            opt == 'O' || opt == 'T' || opt == 'm' || opt == 'o');
}

/*Devulve 1 se es un argumento con opción y devulve 0 se es un argumento sin opción*/
static int option_requires_argument_long(const char *opt)
{
    return (!ft_strcmp(opt, "command") ||
            !ft_strcmp(opt, "echo") ||
            !ft_strcmp(opt, "log-io") ||
            !ft_strcmp(opt, "log-in") ||
            !ft_strcmp(opt, "log-out") ||
            !ft_strcmp(opt, "log-timing") ||
            !ft_strcmp(opt, "logging-format") ||
            !ft_strcmp(opt, "output-limit") ||
            !ft_strcmp(opt, "timing"));
}

static void init_options(t_options *opt)
{
    ft_memset(opt, 0, sizeof(t_options));
}

static void set_option(t_options *opt, char c, char *val)
{
    switch (c) {
        case 'a': opt->append = 1; break;
        case 'c': opt->command = val; break;
        case 'E': opt->echo = val; break;
        case 'e': opt->return_code = 1; break;
        case 'f': opt->flush = 1; break;
        case 'B': opt->log_io = val; break;
        case 'I': opt->log_in = val; break;
        case 'O': opt->log_out = val; break;
        case 'T': opt->log_timing = val; break;
        case 'm': opt->logging_format = val; break;
        case 'o': opt->output_limit = atoi(val); break;
        case 'q': opt->quiet = 1; break;
        case 't': opt->timing_file = val; break;
        case 'V': print_version();
        case 'h': print_help();
        default:
            fprintf(stderr, "Opción -%c desconocida\n", c);
            exit(1);
    }
}

static void set_option_long(t_options *opt, const char *name, char *val)
{
    if (!ft_strcmp(name, "append"))
		opt->append = 1;
    else if (!ft_strcmp(name, "command"))
		opt->command = val;
    else if (!ft_strcmp(name, "echo"))	
		opt->echo = val;
    else if (!ft_strcmp(name, "return"))
		opt->return_code = 1;
    else if (!ft_strcmp(name, "flush"))
		opt->flush = 1;
    else if (!ft_strcmp(name, "force"))
		opt->force = 1;
    else if (!ft_strcmp(name, "log-io"))
		opt->log_io = val;
    else if (!ft_strcmp(name, "log-in"))
		opt->log_in = val;
    else if (!ft_strcmp(name, "log-out"))
		opt->log_out = val;
    else if (!ft_strcmp(name, "log-timing"))
		opt->log_timing = val;
    else if (!ft_strcmp(name, "logging-format"))
		opt->logging_format = val;
    else if (!ft_strcmp(name, "output-limit"))
		opt->output_limit = atoi(val);
    else if (!ft_strcmp(name, "quiet"))
		opt->quiet = 1;
    else if (!ft_strcmp(name, "timing"))
		opt->timing_file = val;
    else if (!ft_strcmp(name, "version"))
		print_version();
    else if (!ft_strcmp(name, "help"))
        print_help();
    else
	{
        fprintf(stderr, "Opción --%s desconocida\n", name);
        exit(1);
    }
}

static const char *match_long_option(const char *name)
{
    int match_count = 0;
    const char *match = NULL;

    for (int i = 0; long_options[i]; i++) {
        if (!ft_strncmp(long_options[i], name, ft_strlen(name))) {
            match_count++;
            match = long_options[i];
        }
    }
    if (match_count == 1)
        return match;
    else if (match_count > 1) {
        fprintf(stderr, "Opción --%s es ambigua\n", name);
        exit(1);
    }
    return NULL;
}

static void handle_short_options(char *arg, t_options *opt, int *i, int argc, char **argv)
{
    for (int j = 1; arg[j]; j++) {
        char c = arg[j];
        if (option_requires_argument(c)) {
            char *val = NULL;
            if (arg[j + 1] != '\0') {
                val = &arg[j + 1];
                j = ft_strlen(arg) - 1;
            } else if (*i + 1 < argc) {
                val = argv[++(*i)];
            } else {
                fprintf(stderr, "Opción -%c requiere argumento\n", c);
                exit(1);
            }
            set_option(opt, c, val);
            break;
        } else {
            set_option(opt, c, NULL);
        }
    }
}

static void handle_long_option(char *arg, t_options *opt, int *i, int argc, char **argv)
{
    char *eq = ft_strchr(arg, '=');
    char *name, *val = NULL;

    if (eq) {
        *eq = '\0';
        name = arg + 2;
        val = eq + 1;
    } else {
        name = arg + 2;
    }

    const char *full_name = match_long_option(name);
    if (!full_name) {
        fprintf(stderr, "Opción --%s desconocida\n", name);
        exit(1);
    }

    if (option_requires_argument_long(full_name)) {
        if (!val && *i + 1 < argc)
            val = argv[++(*i)];
        if (!val) {
            fprintf(stderr, "Opción --%s requiere argumento\n", full_name);
            exit(1);
        }
    }

    set_option_long(opt, full_name, val);
}

/*Funcion para parsear las opcines del comando*/
void parse_argument(int argc, char **argv, t_options *opt, char **file)
{
    init_options(opt);
    *file = NULL;

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (arg[0] == '-' && arg[1] == '-') {
            handle_long_option(arg, opt, &i, argc, argv);
        }
        else if (arg[0] == '-' && arg[1] != '\0') {
            handle_short_options(arg, opt, &i, argc, argv);
        }
        else {
            if (!*file)
                *file = arg;
        }
    }

    if (!*file)
        *file = "typescript";
}

/*Funcion para encontrar el shell en el envairoment*/
void parse_env(char **env, char **shell)
{
	for(int i = 0; env[i]; i ++)
	{
		if (ft_strncmp(env[i], "SHELL=", 6) == 0)
		{
			*shell = env[i] + 6;
		}
	}
	if (!*shell)
	{
		*shell = "/bin/sh";
	}
}