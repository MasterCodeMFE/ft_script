#include "./../inc/ft_script.h"

void enable_raw_mode(struct termios *orig_termios)
{
    // Obtener la configuración actual
    if (ioctl(STDIN_FILENO, TCGETS, orig_termios) == -1)
        return;

    struct termios raw = *orig_termios;

    // MODO RAW COMPLETO - ESTO ES CRÍTICO
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);  // ISIG es clave
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    // Aplicar la nueva configuración
    ioctl(STDIN_FILENO, TCSETS, &raw);
}


void disable_raw_mode(struct termios *orig_termios)
{
    // Restaurar configuración original
    ioctl(STDIN_FILENO, TCSETS, orig_termios);
}

void run_principal_loop(t_script_context *contex)
{
    int alive = 1;
    fd_set fds;
    int max_fd = contex->fd_master > 0 ? contex->fd_master : 0;
    int status;

    contex->child_status = 0; // inicializamos aquí para -e

    while (alive)
    {
        FD_ZERO(&fds);
        FD_SET(contex->fd_master, &fds);
        FD_SET(0, &fds);

        if (select(max_fd + 1, &fds, NULL, NULL, NULL) == -1)
        {
            if (errno == EINTR)
                continue;  // Señal recibida, continuar
            break;         // Error real
        }
        if (select(max_fd + 1, &fds, NULL, NULL, NULL) == -1)
            break;

        if (FD_ISSET(contex->fd_master, &fds))
            process_pty_output(contex);

        if (FD_ISSET(0, &fds))
            process_stdin_input(contex);

        pid_t ret = waitpid(contex->child_pid, &status, WNOHANG);
        if (ret == contex->child_pid)
        {
            contex->child_status = status;
            alive = 0; // el hijo terminó, salimos del loop
        }
    }
}

void open_file(char *file, t_script_context *contex)
{
    if(contex->options->append)
        contex->fd_log = open(file, O_CREAT | O_RDWR | O_APPEND, FILE_PERMISSIONS);
    else
        contex->fd_log = open(file, O_CREAT | O_RDWR | O_TRUNC, FILE_PERMISSIONS);
    if(contex->fd_log == -1)
    {
        perror("No se pudo abrir el fichero");
        exit(1);
    }
}

int ft_script(char *file, char *shell, char **env, t_options *opt)
{
    t_script_context contex;
    struct termios orig_termios;

    contex.shell = shell;
    contex.envp = env;
    contex.options = opt;
    contex.child_status = 0; // inicializamos para -e
    orig_termios = (struct termios){0};
    // abrir fichero de log
    open_file(file, &contex);

    // mensaje inicial
    print_start_info(contex);

    if (spawn_child_process(&contex) != 0)
        return EXIT_FAILURE;

    enable_raw_mode(&orig_termios);
    if (contex.child_pid != 0)
        run_principal_loop(&contex);
    disable_raw_mode(&orig_termios);

    // Restaurar manejadores de señales
    restore_signal_handlers();

    // si -e está activado, esperar al hijo y obtener exit status
    if (contex.options->return_code)
        waitpid(contex.child_pid, &contex.child_status, 0);

    // mensaje final
    print_end_info(contex);

    if (file != NULL)
        close(contex.fd_log);

    // salir con el código de salida del hijo si -e
    if (contex.options->return_code)
    {
        if(!contex.options->quiet)
		    write(1,"Script done.\n", ft_strlen("Script done.\n"));
        exit(WEXITSTATUS(contex.child_status));
    }

    return 0;
}
