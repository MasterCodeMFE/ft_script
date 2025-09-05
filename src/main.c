#include "./../inc/ft_script.h"

void	print_options(t_options *opt, char *shell)
{
	printf("SHELL: %s\n", 	shell);
	printf("append: %d\n", opt->append);
	printf("command: %s\n", opt->command ? opt->command : "(null)");
	printf("echo: %s\n", opt->echo ? opt->echo : "(null)");
	printf("return_code: %d\n", opt->return_code);
	printf("flush: %d\n", opt->flush);
	printf("force: %d\n", opt->force);
	printf("log_io: %s\n", opt->log_io ? opt->log_io : "(null)");
	printf("log_in: %s\n", opt->log_in ? opt->log_in : "(null)");
	printf("log_out: %s\n", opt->log_out ? opt->log_out : "(null)");
	printf("log_timing: %s\n", opt->log_timing ? opt->log_timing : "(null)");
	printf("logging_format: %s\n", opt->logging_format ? opt->logging_format : "(null)");
	printf("output_limit: %d\n", opt->output_limit);
	printf("quiet: %d\n", opt->quiet);
	printf("timing_file: %s\n", opt->timing_file ? opt->timing_file : "(null)");
	printf("version: %d\n", opt->version);
	printf("help: %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", opt->help);
}

int  main(int argc, char **argv, char **env)
{
	char *file;
	t_options opt;
	char *shell;
	(void) argc;

	file = NULL;
	shell = NULL;
	parse_argument(argc, argv, &opt, &file);
	parse_env(env, &shell);
	//print_options(&opt, shell);
	if(!opt.quiet)
	{
		write(1, "Script started, output log file is '", ft_strlen("Script started, output log file is '"));
		write(1, file, ft_strlen(file));
		write(1,"'.\n", ft_strlen("'.\n"));
	}
	ft_script(file, shell, env, &opt);
	if(!opt.quiet)
		write(1,"Script done.\n", ft_strlen("Script done.\n"));
}
