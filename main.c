#include "select.h"

int		ft_outc(int c)
{
	return ((int)write(2, &c, 1));
}

int     ft_intlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void	set_input_mode(void)
{
	char			*term_name;
	struct termios	termios;

	if (!isatty(STDERR_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDERR_FILENO, &termios);
    reset_terminal(&termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios);
    tputs(tgetstr("ti", NULL), 1, ft_outc);
	tputs(tgetstr("vi", NULL), 1, ft_outc);
}

int     standard_space(t_files *head)
{
   int i;
   t_files *t;
   
   t = head;
   i = 0;
   while (t)
   {
       if (t->removed == 0)
       {
           if (ft_intlen(t->name) > i)
            i = ft_intlen(t->name);
       }
       t = t->next;
   }
   return (i);
}

void    space_adder(char *str, int len)
{
    int i;

    i = ft_intlen(str);
    while (i <= len)
    {
        write(2, " ", 1);
        i++;
    }
}

void    file_printer(t_files *head)
{
    t_files         *t;
    int             len;
    struct winsize  w;
    int             col;
    int             i = 0;
    int fd = open("/dev/ttys002", O_RDWR);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    len = standard_space(head);
    t = head;
    col = 1;
    dprintf(fd, "this is col == %d this is len == %d\n", w.ws_col, len);
    if (w.ws_col / (len + 1) > 1)
        col = (w.ws_col / (len + 1));
    tputs(tgetstr("cl", NULL), 1, ft_outc);
    while (t != NULL)
    {
        if (t->removed == 0)
        {
            //dprintf(fd, "this is i == %d this is col == %d", i, col);
            if ((i % col) == 0 && i > 0)
                 tputs(tgetstr("do", NULL), 1, ft_outc);
            if (t->selected == 1 && t->underline == 1)
            {
                tputs(tgetstr("mr", NULL), 1, ft_outc);
                tputs(tgetstr("us", NULL), 1, ft_outc);
            }
            else if (t->underline == 1)
                tputs(tgetstr("us", NULL), 1, ft_outc);
            else if (t->selected == 1)
                tputs(tgetstr("mr", NULL), 1, ft_outc);
            ft_putstr_fd(t->name, 2);
            tputs(tgetstr("me", NULL), 1, ft_outc);
            tputs(tgetstr("ue", NULL), 1, ft_outc);
            if (t->next)
                space_adder(t->name, len);
            i++;
        }
        t = t->next;
    }
}

void    button_checker(t_files *t,  char *buf, int ret)
{
    int i;
    t_files *head;

    i = -2;

    if (LEFT)
    {
        select_left(t);
        file_printer(t); 
    }
    else if (RIGHT)
    {
        select_right(t);
        file_printer(t);
    }
    else if (buf[0] == ' ' && ret == 1)
    {
       select_choice(t);
       file_printer(t);
    }
    else if (buf[0] == 127 && ret == 1)
    {
       remove_choice(t);
       file_printer(t); 
    }
    else if (buf[0] == '\n' && ret == 1)
    {
        print_selected(t);
        free_list(t);
        tcsetattr(STDERR_FILENO, TCSAFLUSH, reset_terminal(NULL));
        tputs(tgetstr("te", NULL), 1, ft_outc);
	    tputs(tgetstr("ve", NULL), 1, ft_outc);
        exit(0);
    }
}

void			node_to_list(t_files **list, t_files *node)
{
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
	*list = node;
}

t_files     *create_node(char *file, int underline)
{
    t_files *new;

    new = (t_files *)malloc(sizeof(t_files));
    new->name = ft_strdup(file);
    new->selected = 0;
    new->removed = 0;
    new->underline = underline;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

t_files		*create_list(int ac, char **av)
{
    t_files *head;
    t_files *node;

    head = create_node(av[ac], 0);
    while (ac > 1)
    {
        ac--;
        if (ac == 1)
            node = create_node(av[ac], 1);
        else
            node = create_node(av[ac], 0);
        node_to_list(&head, node);
    }
	return (head);
}

t_files *getset(t_files *dim)
{
    static t_files *ret;

    if (dim)
        ret = dim;
    return ret;
}

int    space_checker(t_files *head, int colums, int row)
{
    int     i;
    int     len;
    int     col;
    t_files *t;
    //int fd = open("/dev/ttys002", O_RDWR);

    i = 0;
    col = 1;
    t = head;
    len = standard_space(head);
    if (colums / (len + 1) > 1)
        col = (colums / (len + 1));
    while (t)
    {
        if (t->removed == 0)
            i++;
        t = t->next;
    }
    // dprintf(fd, "enaugh space this is space == %d this is i == %d\n", (colums * row), i);
    if (((colums * row) < (i * (len + 2))) || (col == 1 && i > row))
        return (0);
    return (1);
}

void winsz_handler(int sig) {
    struct winsize  w;
    t_files         *f;

    f = getset(NULL);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (!space_checker(f, w.ws_col, w.ws_row))
    {
       tputs(tgetstr("cl", NULL), 1, ft_outc);
       ft_putstr_fd("Not enough space", 2);
    }
    else
        file_printer(f);
}

void    Loop_starter(t_files *t)
{
    char            buf[BUFF_SIZ + 1];
    int             ret;
    struct winsize  w; 

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    while (1)
    {
       signal(SIGWINCH, winsz_handler); 
       ret = read(2, buf, BUFF_SIZ);
       buf[ret] = '\0';
       button_checker(t, buf, ret); 
    }
}

int main(int ac, char **av, char **env)
{
    t_files         *t;

    set_input_mode();
    if (ac > 1)
    {
        t = create_list(ac - 1, av);
        getset(t);
        file_printer(t);
        Loop_starter(t);
    }
    else
        ft_putstr_fd("No Files Selected\n", 2);
}