#include "./../inc/ft_script.h"

int whitch_month_is_it(char *s)
{
    int month = 0;
    if (s[4]=='J' && s[5]=='a' && s[6]=='n')
        month = 1;
    else if (s[4]=='F')
        month = 2;
    else if (s[4]=='M' && s[5]=='a' && s[6]=='r')
        month = 3;
    else if (s[4]=='A' && s[5]=='p')
        month = 4;
    else if (s[4]=='M' && s[5]=='a' && s[6]=='y')
        month = 5;
    else if (s[4]=='J' && s[5]=='u' && s[6]=='n')
        month = 6;
    else if (s[4]=='J' && s[5]=='u' && s[6]=='l')
        month = 7;
    else if (s[4]=='A' && s[5]=='u')
        month = 8;
    else if (s[4]=='S')
        month = 9;
    else if (s[4]=='O')
        month = 10;
    else if (s[4]=='N')
        month = 11;
    else if (s[4]=='D')
        month = 12;
    return month;
}

// ---- Fecha y hora ----
void print_date(int fd)
{
    time_t  t = time(NULL);
    char    *s = ctime(&t);
    char    buf[32];
    char    month = 0;
    int     i= 0;
    int     j = 0;

    // año (20-23)
    for(i=20; i<24; i++)
        buf[j++] = s[i];
    buf[j++] = '-';
    // mes (4-6) convertido manualmente
    month = whitch_month_is_it(s);
    buf[j++] = '0' + month/10;
    buf[j++] = '0' + month%10;
    buf[j++] = '-';
    // día (8-9)
    if(s[8] == ' ')
        buf[j++] = '0';
    else
        buf[j++] = s[8];
    buf[j++] = s[9];
    buf[j++] = ' ';
    // hora (11-18)
    for(i=11; i<19; i++) buf[j++] = s[i];
    buf[j++] = ' ';
    // zona horaria fija +02:00
    buf[j++] = '+';
    buf[j++] = '0';
    buf[j++] = '2';
    buf[j++] = ':';
    buf[j++] = '0';
    buf[j++] = '0';
    buf[j++] = ' ';
    write(fd, buf, j);
}

// ---- Mostrar datos de la terminal ----
void print_terminal_info(int fd)
{
    struct winsize ws;
    char buf[128];
    ssize_t len;

    ft_putstr_fd("[", fd);

    // TERM
    char *term = getenv("TERM");
    if(term)
    {
        ft_putstr_fd("TERM=\"", fd);
        ft_putstr_fd(term, fd);
        ft_putstr_fd("\" ", fd);
    }

    // TTY
    len = readlink("/proc/self/fd/0", buf, sizeof(buf)-1);
    if(len != -1)
    {
        buf[len] = '\0';
        ft_putstr_fd("TTY=\"", fd);
        ft_putstr_fd(buf, fd);
        ft_putstr_fd("\" ", fd);
    }

    // Columnas y filas
    if(ioctl(0, TIOCGWINSZ, &ws) == 0)
    {
        ft_putstr_fd("COLUMNS=\"", fd);
        ft_putnbr_fd(ws.ws_col, fd);
        ft_putstr_fd("\" ", fd);

        ft_putstr_fd("LINES=\"", fd);
        ft_putnbr_fd(ws.ws_row, fd);
        ft_putstr_fd("\"", fd);
    }

    ft_putstr_fd("]\n", fd);
}

void print_start_info(t_script_context contex)
{
    if(!contex.options->quiet)
	    ft_putstr_fd("Script started on ", contex.fd_log);
    print_date(contex.fd_log);
	print_terminal_info(contex.fd_log);
}

void print_end_info(t_script_context contex)
{
    if(!contex.options->quiet)
            ft_putstr_fd("Script done on ", contex.fd_log);
    print_date(contex.fd_log);
    ft_putstr_fd("\n", contex.fd_log);
}
