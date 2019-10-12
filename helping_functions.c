/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:29:48 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/12 16:35:28 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void		free_list(t_files *t)
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

void		reset_terminal(struct termios term)
{
	char			*term_name;
	struct termios	termios;

	if (!isatty(STDERR_FILENO) || !isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag |= ICANON;
	termios.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	tputs(tgetstr("te", NULL), 1, ft_outc);
	tputs(tgetstr("ve", NULL), 1, ft_outc);
}

void		finish_him(int sig)
{
	t_files *t;

	reset_input_mode();
	t = getset(NULL);
	free_list(t);
	exit(0);
}

void		suspend(int sig)
{
	reset_input_mode();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\32");
}

void		restart(int sig)
{
	t_files *t;

	t = getset(NULL);
	set_input_mode();
	file_printer(t);
	signal(SIGTSTP, suspend);
}

void		signal_handler(void)
{
	signal(SIGWINCH, winsz_handler);
	signal(SIGTSTP, suspend);
	signal(SIGCONT, restart);
	signal(SIGHUP, finish_him);
	signal(SIGINT, finish_him);
	signal(SIGQUIT, finish_him);
	signal(SIGILL, finish_him);
	signal(SIGTRAP, finish_him);
	signal(SIGABRT, finish_him);
	signal(SIGEMT, finish_him);
	signal(SIGFPE, finish_him);
	signal(SIGKILL, finish_him);
	signal(SIGBUS, finish_him);
	signal(SIGSEGV, finish_him);
	signal(SIGSYS, finish_him);
	signal(SIGPIPE, finish_him);
	signal(SIGALRM, finish_him);
	signal(SIGTERM, finish_him);
	signal(SIGURG, finish_him);
	signal(SIGXCPU, finish_him);
	signal(SIGXFSZ, finish_him);
	signal(SIGVTALRM, finish_him);
	signal(SIGPROF, finish_him);
	signal(SIGUSR1, finish_him);
	signal(SIGUSR2, finish_him);
}
