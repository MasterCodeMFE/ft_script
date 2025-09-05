#include "./../inc/ft_script.h"

t_script_context *g_context = NULL;

// Manejador para SIGWINCH (cambio de tamaño de ventana)
void handle_winch(int sig)
{
	(void)sig;
    struct winsize ws;
    
    if (g_context && ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == 0)
    {
        ioctl(g_context->fd_master, TIOCSWINSZ, &ws);
    }
}

// Función para configurar manejadores de señales
void setup_signal_handlers(void)
{
    // Configurar manejador para SIGWINCH (cambio de tamaño de ventana)
    signal(SIGWINCH, handle_winch);
    
    // Para las otras señales, NO las ignoramos completamente
    // El modo raw del terminal las pasará al hijo automáticamente
    
    // IMPORTANTE: No usar SIG_IGN para estas señales
    // signal(SIGINT, SIG_IGN);   // NO hacer esto
    // signal(SIGQUIT, SIG_IGN);  // NO hacer esto  
    // signal(SIGTSTP, SIG_IGN);  // NO hacer esto
}

// Función para restaurar manejadores de señales
void restore_signal_handlers(void)
{
    signal(SIGWINCH, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
}