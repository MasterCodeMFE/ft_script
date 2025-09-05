#include "./../inc/ft_script.h"

// ---- IO ----
void process_pty_output(t_script_context *contex)
{
    char buf[1024];
    ssize_t n = read(contex->fd_master, buf, sizeof(buf));
    if(n > 0)
    { 
        write(1, buf, n);
        write(contex->fd_log, buf, n);
        if(contex->options->flush) //Si el flag -f está activado, fuerza flush inmediato
            fsync(contex->fd_log);
    }
}

void process_stdin_input(t_script_context *contex)
{
    char buf[1024];
    ssize_t n = read(0, buf, sizeof(buf));
    if(n > 0)
        write(contex->fd_master, buf, n);
}
