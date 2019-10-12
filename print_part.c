/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:32:44 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/12 16:34:13 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		print_selected(t_files *t)
{
	t_files *head;
	int		virg;

	virg = 0;
	head = t;
	while (head)
	{
		if (head->selected == 1 && t->removed == 0 && virg == 0)
		{
			ft_putstr(head->name);
			virg++;
		}
		else if (head->selected == 1 && t->removed == 0)
		{
			ft_putstr(" ");
			ft_putstr(head->name);
		}
		head = head->next;
	}
}

void		space_adder(char *str, int len)
{
	int i;

	i = ft_intlen(str);
	while (i <= len)
	{
		write(2, " ", 1);
		i++;
	}
}

void		file_modes(t_files *t)
{
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
}

void		file_printer(t_files *head)
{
	t_files			*t;
	struct winsize	w;
	t_dimensions	d;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	d.len = standard_space(head);
	t = head;
	d.col = 1;
	d.i = 0;
	if (w.ws_col / (d.len + 1) > 1)
		d.col = (w.ws_col / (d.len + 1));
	tputs(tgetstr("cl", NULL), 1, ft_outc);
	while (t != NULL)
	{
		if (t->removed == 0)
		{
			file_modes(t);
			d.i++;
			if ((d.i % d.col) == 0)
				tputs(tgetstr("do", NULL), 1, ft_outc);
			else if (t->next)
				space_adder(t->name, d.len);
		}
		t = t->next;
	}
}
