#include "select.h"

int		ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

void	set_input_mode(void)
{
	char			*term_name;
	struct termios	termios;

	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

void    button_checker(char *buf)
{
    if (buf[0] == 27 && buf[2] == 68 && buf[1] == 91)
    {
       ft_putstr(tgetstr("le", NULL));
    }
    else if (RIGHT)
    {
        ft_putstr("first choice");
         ft_putstr(tgetstr("us", NULL));
         ft_putstr("second choice");
    }
    else if (UP)
    {
        ft_putstr(tgetstr("up", NULL));
    }
    else if (DOWN)
    {
        ft_putstr(tgetstr("do", NULL));
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
    new->selected = 0;
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

t_dimensions *getset(t_dimensions *dim)
{
    static t_dimensions *ret;

    if (dim)
        ret = dim;
    return ret;
}

void winsz_handler(int sig) {
    struct winsize w;
    t_dimensions   *f;

    f = getset(NULL);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    f->col = w.ws_col;
    f->row = w.ws_row;
    const char *s = "winsize changed!\n";
    write(STDOUT_FILENO, s, strlen(s));
}

int main(int ac, char **av, char **env)
{
    struct winsize w; 
    t_dimensions dim;
    t_files  *t;

    if (ac > 1)
    {
        t = create_list(ac - 1, av);
        while (t != NULL)
        {
            ft_putstr(tgetstr("us", NULL));
            // if (t->underline == 1)
            // {
            //     ft_putstr(tgetstr("us", NULL));
            //     ft_putstr(t->name);
            //    // ft_putstr(tgetstr("ue", NULL));
            // }
            // else
                ft_putstr(t->name);
            if (t->next)
                ft_putstr("  ");
            t = t->next;
        }
    }
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // dim.col = w.ws_col;
    // dim.row = w.ws_row;
    // getset(&dim);
    // while(1)
    // {
    //     signal(SIGWINCH, winsz_handler);
    //     printf ("lines %d\n", dim.row);
    //     printf ("columns %d\n", dim.col);
    // }
    // char    buf[BUFF_SIZ + 1];
    // int     ret;
    // t_files  *t;

    // if (ac > 1)
    // {
    //     t = create_list(ac - 1, av);
    //     while (t != NULL)
    //     {
    //          printf("this is the first node == %s  %d\n", t->name, t->selected);
    //          t = t->next;
    //     }
    // }

    //set_input_mode();
    // int  i = 1;
    // int  k;
    // while (1)
    // {
    //     ret = read(0, buf, BUFF_SIZ);
    //     //printf("this is ret %d\n", ret);
    //     buf[ret] = '\0';
    //     //printf("%d %d %d\n", buf[0], buf[1], buf[2]);
    //     button_checker(buf);
    //     k = 0;
    //     k = open(av[i], O_RDONLY);
    //     printf("this is k == %d", k);
    //     if (k > 0)
    //     {
    //         while ((read(k, buf, BUFF_SIZ)))
    //         {
    //             printf("%s\n", buf);
    //         }
    //     }
    //     else
    //         printf("%s ", av[i]);
    //    i++;
    // }
}