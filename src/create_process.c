#include "./../inc/ft_script.h"

// ---- Crear proceso hijo ----
int spawn_child_process(t_script_context *contex)
{
    char *args[4];
    struct winsize ws;

    // Obtener tamaño de terminal del padre
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
        perror("ioctl TIOCGWINSZ");

    // Crear PTY maestro/esclavo
    if (openpty(&contex->fd_master, &contex->fd_slave, NULL, NULL, &ws) == -1)
        return -1;

    contex->child_pid = fork();
    if (contex->child_pid == -1)
        return -1;

    if (contex->child_pid == 0) // HIJO
    {
        setsid(); // Nueva sesión
        if (ioctl(contex->fd_slave, TIOCSCTTY, 0) == -1)
            perror("ioctl TIOCSCTTY hijo");

        // Duplicar PTY a stdin, stdout, stderr
        dup2(contex->fd_slave, STDIN_FILENO);
        dup2(contex->fd_slave, STDOUT_FILENO);
        dup2(contex->fd_slave, STDERR_FILENO);

        // Cerrar fds innecesarios
        close(contex->fd_slave);
        close(contex->fd_master);

        // Ejecutar shell o comando
        if (contex->options->command)
        {
            args[0] = contex->shell;
            args[1] = "-c";
            args[2] = contex->options->command;
            args[3] = NULL;
        }
        else
        {
            setenv("PS1", "\\u@ft_script$ ", 1);
            args[0] = contex->shell;
            args[1] = "-li";
            args[2] = NULL;
        }

        execve(contex->shell, args, contex->envp);
        perror("execve");
        exit(1);
    }
    else // PADRE
    {
        // Cerrar extremo esclavo en el padre
        close(contex->fd_slave);
    }

    return 0;
}
