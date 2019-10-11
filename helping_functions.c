#include "select.h"

void    free_list(t_files *t)
{
    t_files *next;

    while (t)
    {
        next = t->next;
        free(t->name);
        free(t);
        t = next;
    }
    t = NULL;
}

void    print_selected(t_files *t)
{
    t_files *head;

    head = t;
    tputs(tgetstr("cl", NULL), 1, ft_outc);
    tputs(tgetstr("do", NULL), 1, ft_outc);
    while (head)
    {
        if (head->selected == 1 && t->removed == 0)
        {
            ft_putstr(head->name);
            ft_putstr(" ");
        }
        head = head->next;
    }
}

struct termios *reset_terminal(struct termios *term)
{
    static struct termios *save;

    if (term)
        save = term;
    return save;
}