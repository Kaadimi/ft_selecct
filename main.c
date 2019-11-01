/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:06:27 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/18 09:04:23 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		button_checker_2(t_files *t, char *buf, int ret)
{
	if (DELETE || DEL)
	{
		select_left(t, -1);
		file_printer(t);
	}
	else if (ENTER)
	{
		reset_input_mode();
		print_selected(t);
		free_list(t);
		exit(0);
	}
	else if (ALL)
		select_remove_all(t, 1);
	else if (MINUS)
		select_remove_all(t, 0);
	else if (END)
		to_end(t);
	else if (buf[0] == 27 && ret == 1)
		finish_him(-1);
}

void		button_checker(t_files *t, char *buf, int ret)
{
	struct winsize		w;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	if (!space_checker(t, w.ws_col, w.ws_row))
		return ;
	if (LEFT)
		select_left(t, 0);
	else if (RIGHT)
		select_right(t, 0);
	else if (buf[0] == ' ' && ret == 1)
	{
		select_right(t, -1);
		file_printer(t);
	}
	else if (buf[0] == 'r' && ret == 1)
	{
		reset_choices(t);
		file_printer(t);
	}
	else if (HOME)
		to_start(t);
	else
		button_checker_2(t, buf, ret);
	if (ALL || MINUS || END || LEFT || RIGHT || HOME)
		file_printer(t);
}

void		winsz_handler(int sig)
{
	struct winsize		w;
	t_files				*f;

	(void)sig;
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

int			main(int ac, char **av)
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
