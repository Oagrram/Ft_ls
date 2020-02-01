
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

typedef	struct	flag
{
	int			f_l;
	int			f_a;
	int			f_r;
	int			f_t;
	int			f_R;
	int			f_g;
}				file_flags;

typedef	struct	filenode
{
	int			nlink;
	int			size;
	int			mtime;
	int			maj;
	int			min;
	char		type;
	char		linktype;
	char		*name;
	char		*time;
	char		*groupe;
	char		*user;
	char		*linkedfile;
	char		permision[11];
	struct filenode	*next;
	struct filenode	*previous;
	struct filenode	*next_file;
	struct filenode	*previous_file;

}				t_flist;

typedef struct	file_struct
{
	struct stat fileStat;
	struct dirent *sd;
	char		*path;
	char		**directories;
	DIR			*dir;
	t_flist		*head;
	t_flist		*node;
}					data;

typedef struct printspaces
{
	int link_length;
	int user_length;
	int groupe_length;
	int size_length;
	int maj_length;
	int min_length;
}				maxlength;

t_flist	*new_node(void);
int		stockage(struct stat fileStat, t_flist **node, char *name, char *path);
void	freelist(t_flist **head);
char	getfiletype(mode_t    mode);
int		check_flag(char *argv, file_flags *flags);
int		ft_get_dir(char *name, file_flags flags);
void	printlist(t_flist *ptr,file_flags flags,int ptr_move);
void	printnode(t_flist      *head, file_flags flags,maxlength *max);
int		ft_recursive(char *path, file_flags flags);
void	ft_check_folder(t_flist *p,char *path, file_flags flags);
void	freelist(t_flist **head);
t_flist	*sort_by_time(t_flist **head);
t_flist	*sort_by_ascii(t_flist **node, t_flist **lst);
void	swapelement(t_flist **node, t_flist **next);
void	reverse_lst(t_flist	*ptr,file_flags flags, int ptr_move);
int		get_lenght(t_flist *ptr,char type,int ptr_move);
int		ft_readdir(data system, char *name, file_flags flags);
void	ft_pathjoin(char **s1, char *s2);
int		get_link(char *name);
#endif