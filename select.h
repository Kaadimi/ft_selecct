/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:46:01 by ikadimi           #+#    #+#             */
/*   Updated: 2019/10/13 18:04:19 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include "libft/libft.h"
# include <pwd.h>
# define BUFF_SIZ 4
# define RIGHT (buf[2] == 67 && buf[1] == 91 && buf[0] == 27)
# define LEFT (buf[2] == 68 && buf[1] == 91 && buf[0] == 27)
# define UP (buf[2] == 65 && buf[1] == 91 && buf[0] == 27)
# define DOWN (buf[2] == 66 && buf[1] == 91 && buf[0] == 27)
# define DELETE (buf[0] == 127 && ret == 1)
# define DEL (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
# define HOME (buf[2] == 72 && buf[1] == 91 && buf[0] == 27)
# define END (buf[2] == 70 && buf[1] == 91 && buf[0] == 27)
# define MINUS (buf[0] == '-' && ret == 1)
# define ALL (buf[0] == '*' && ret == 1)
# define ENTER (buf[0] == '\n' && ret == 1)

typedef struct			s_files
{
	char				*name;
	int					selected;
	int					removed;
	int					underline;
	struct s_files		*next;
	struct s_files		*prev;
}						t_files;

typedef struct			s_dimesions
{
	int					col;
	int					len;
	int					i;
}						t_dimensions;

void					select_right(t_files *t, int i);
void					select_left(t_files *t, int i);
void					select_choice(t_files *t);
void					remove_choice(t_files *t);
void					free_list(t_files *t);
void					print_selected(t_files *t);
void					reset_terminal();
int						ft_outc(int c);
void					winsz_handler(int sig);
void					reset_input_mode();
void					set_input_mode();
t_files					*getset(t_files *dim);
void					signal_handler();
void					file_printer(t_files *head);
void					select_remove_all(t_files *head, int i);
void					reset_choices(t_files *head);
void					finish_him(int sig);
int						ft_intlen(const char *str);
int						standard_space(t_files *head);
t_files					*create_list(int ac, char **av);
int						space_checker(t_files *head, int colums, int row);
void					to_start(t_files *t);
void					to_end(t_files *t);
size_t					list_lenght(t_files *t);

#endif
