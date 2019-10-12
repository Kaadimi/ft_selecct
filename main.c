/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:06:27 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/12 16:46:11 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		button_checker_2(t_files *t, char *buf, int ret)
{
	if (DELETE || DEL)
	{
		remove_choice(t);
		file_printer(t);
	}
	else if (buf[0] == '\n' && ret == 1)
	{
		reset_input_mode();
		print_selected(t);
		free_list(t);
		exit(0);
	}
	else if (buf[0] == '*' && ret == 1)
	{
		select_remove_all(t, 1);
		file_printer(t);
	}
	else if (buf[0] == '-' && ret == 1)
	{
		select_remove_all(t, 0);
		file_printer(t);
	}
	else if (buf[0] == 27 && ret == 1)
		finish_him(-1);
}

void		button_checker(t_files *t, char *buf, int ret)
{
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
	else if (buf[0] == 'r' && ret == 1)
	{
		reset_choices(t);
		file_printer(t);
	}
	else
		button_checker_2(t, buf, ret);
}

void		node_to_list(t_files **list, t_files *node)
{
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
	*list = node;
}

t_files		*create_node(char *file, int underline)
{
	t_files *new;

	new = (t_files *)malloc(sizeof(t_files));
	new->name = ft_strdup(file);
	new->selected = 0;
	new->removed = 0;
	new->underline = underline;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files		*create_list(int ac, char **av)
{
	t_files *head;
	t_files *node;

	if (ac == 1)
		head = create_node(av[ac], 1);
	else
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

t_files		*getset(t_files *dim)
{
	static t_files *ret;

	if (dim)
		ret = dim;
	return (ret);
}

int			space_checker(t_files *head, int colums, int row)
{
	int		i;
	int		len;
	int		col;
	t_files	*t;

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
	if (((colums * row) < (i * (len + 2))) ||
			(col == 1 && i > row) || (col == 1 && (len + 1) > colums))
		return (0);
	return (1);
}

void		winsz_handler(int sig)
{
	struct winsize		w;
	t_files				*f;

	f = getset(NULL);
	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	if (!space_checker(f, w.ws_col, w.ws_row))
	{
		tputs(tgetstr("cl", NULL), 1, ft_outc);
		ft_putstr_fd("Not enough space", 2);
	}
	else
		file_printer(f);
}

void		loop_starter(t_files *t)
{
	char			buf[BUFF_SIZ + 1];
	int				ret;
	struct winsize	w;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	while (1)
	{
		signal_handler();
		ret = read(2, buf, BUFF_SIZ);
		buf[ret] = '\0';
		button_checker(t, buf, ret);
	}
}

int			main(int ac, char **av, char **env)
{
	t_files		*t;

	if (ac > 1)
	{
		set_input_mode();
		t = create_list(ac - 1, av);
		getset(t);
		winsz_handler(-1);
		loop_starter(t);
	}
	else
		ft_putstr_fd("No Files Selected\n", 2);
}
