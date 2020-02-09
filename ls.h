
#ifndef LS_H
# define LS_H

# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "pwd.h"
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>

# define MAX_PATH    4096

typedef	struct		s_flags
{
	int				f_l;
	int				f_a;
	int				f_r;
	int				f_t;
	int				f_rm;
	int				f_g;
}					t_flags;

typedef	struct		s_flist
{
	int				nlink;
	int				size;
	int				mtime;
	int				maj;
	int				min;
	char			type;
	char			linktype;
	char			*name;
	char			*time;
	char			*groupe;
	char			*user;
	char			*linkedfile;
	char			permision[11];
	struct s_flist	*next;
	struct s_flist	*previous;
	struct s_flist	*next_file;
	struct s_flist	*previous_file;

}					t_flist;

typedef struct		s_data
{
	struct stat		state;
	struct dirent	*sd;
	char			*path;
	char			**directories;
	DIR				*dir;
	t_flist			*head;
	t_flist			*node;
}					t_data;

typedef	struct		s_maxlength
{
	int				link_length;
	int				user_length;
	int				groupe_length;
	int				size_length;
	int				maj_length;
	int				min_length;
}					t_maxlength;

typedef	struct		s_ftls
{
	t_flist			*head;
	t_flist			*node;
	int				nf;
	int				nd;
	int				c;
	int				nero;
	int				argc;
}					t_ftls;

t_flist	*new_node(void);
t_flist	*sort_by_time(t_flist **head);
t_flist	*sort_by_ascii(t_flist **node, t_flist **lst);
char	getfiletype(mode_t	mode);
int		stockage(struct stat state, t_flist **node, char *name, char *path);
int		check_flag(char *argv, t_flags *flags);
int		get_dir(char *name, t_flags flags);
int		sort_eroor(char **t, int i);
int		check_argv(t_flist *p, char c, t_flags flags);
void	freelist(t_flist **head);
void	printlist(t_flist *ptr, t_flags flags, int ptr_move);
void	printnode(t_flist	*head, t_flags flags, t_maxlength *max);
void	printlist(t_flist *ptr, t_flags flag, int ptr_move);
void	print_spaces(t_flist *p, char type, int max, int spacead);
void	ft_check_folder(t_flist *p, char *path, t_flags flags);
void	freelist(t_flist **head);
void	swapelement(t_flist **node, t_flist **next);
void	reverse_lst(t_flist	*ptr, t_flags flags, int ptr_move);
void	ft_pathjoin(char **s1, char *s2);
void	get_files(t_flist **ptr, t_flags flags);
int		get_lenght(t_flist *ptr, char type, int ptr_move);
int		ft_readdir(t_data system, char *name, t_flags flags);
int		ft_recursive(char *path, t_flags flags);
int		get_link(char *name);

#endif