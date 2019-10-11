 # include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/ioctl.h>
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



typedef struct			s_files
{
	char				*name;
	int					selected;
	int					removed;
	int					underline;
	struct s_files	*next;
	struct s_files	*prev;
}                       t_files;

typedef struct			s_dimesions
{
	int					col;
	int					row;
}						t_dimensions;

void					select_right(t_files *t);
void    				select_left(t_files *t);
void    				select_choice(t_files *t);
void					remove_choice(t_files *t);
void					free_list(t_files *t);
void					print_selected(t_files *t);
struct termios 			*reset_terminal(struct termios *term);
int						ft_outc(int c);