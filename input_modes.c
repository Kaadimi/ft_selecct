/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:39:33 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/12 16:47:56 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int			ft_outc(int c)
{
	return ((int)write(2, &c, 1));
}

int			ft_intlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			standard_space(t_files *head)
{
	int			i;
	t_files		*t;

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

void		set_input_mode(void)
{
	char				*term_name;
	struct termios		termios;

	if (!isatty(STDERR_FILENO) || !isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	tputs(tgetstr("ti", NULL), 1, ft_outc);
	tputs(tgetstr("vi", NULL), 1, ft_outc);
}

void		reset_input_mode(void)
{
	char				*term_name;
	struct termios		termios;

	if (!isatty(STDERR_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDERR_FILENO, &termios);
	termios.c_lflag |= ICANON;
	termios.c_lflag |= ECHO;
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios);
	tputs(tgetstr("te", NULL), 1, ft_outc);
	tputs(tgetstr("ve", NULL), 1, ft_outc);
}
