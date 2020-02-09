/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:32:51 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/09 17:32:52 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ls.h"

t_flist		*new_node(void)
{
	t_flist *node;

	node = (t_flist*)ft_memalloc(sizeof(t_flist));
	return (node);
}

void	getpermition(struct stat state, t_flist **node)
{
	struct passwd	*user;
	struct group	*group;

	user = getpwuid(state.st_uid);
	group = getgrgid(state.st_gid);
	(*node)->permision[0] = ((state.st_mode & S_IRUSR) ? 'r' : '-');
	(*node)->permision[1] = ((state.st_mode & S_IWUSR) ? 'w' : '-');
	(*node)->permision[2] = ((state.st_mode & S_IXUSR) ? 'x' : '-');
	(*node)->permision[3] = ((state.st_mode & S_IRGRP) ? 'r' : '-');
	(*node)->permision[4] = ((state.st_mode & S_IWGRP) ? 'w' : '-');
	(*node)->permision[5] = ((state.st_mode & S_IXGRP) ? 'x' : '-');
	(*node)->permision[6] = ((state.st_mode & S_IROTH) ? 'r' : '-');
	(*node)->permision[7] = ((state.st_mode & S_IWOTH) ? 'w' : '-');
	(*node)->permision[8] = ((state.st_mode & S_IXOTH) ? 'x' : '-');
	(*node)->permision[9] = (' ');
	(*node)->permision[9] = ('\0');
	(*node)->nlink = (state.st_nlink);
	(*node)->user = (user->pw_name);
	(*node)->groupe = (group->gr_name);
	(*node)->size = (state.st_size);
}

char	getfiletype(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISWHT(mode))
		return ('w');
	return ('?');
}

int		stockage(struct stat state, t_flist **node, char *name,char *path)
{
	ssize_t len;
	time_t	now;

	(*node)->name = ft_strdup(name);
	(*node)->mtime = state.st_mtime;
	time(&now);
	if (state.st_mtime >= (now - 15552000))
		(*node)->time = ft_strsub(ctime(&state.st_mtime), 4, 12);
	else
	{
		int i = 0;
		(*node)->time = ft_strjoin(ft_strsub(ctime(&state.st_mtime), 4, 7),
		ft_strsub(ctime(&state.st_mtime), 19, 24));
		while ((*node)->time[i++])
		{
			if ((*node)->time[i] == '\n')
				(*node)->time[i] = '\0';
		}
	}
	(*node)->type = getfiletype(state.st_mode);
	getpermition(state, &(*node));
	if ((*node)->type == 'l')
	{
		(*node)->linkedfile = malloc(MAX_PATH + 1);
		len = readlink(path, (*node)->linkedfile, MAX_PATH + 1);
		(*node)->linkedfile[len] = '\0';
	}
	if ((*node)->type == 'b' || (*node)->type == 'c')
	{
		(*node)->maj = major(state.st_rdev);
		(*node)->min = minor(state.st_rdev);
	}
	return (0);
}

int		ft_readdir(t_data sys, char *name, t_flags flags)
{
	char	*tmp;
	int		total = 0;;

	sys.head = NULL;
	while ((sys.sd = readdir(sys.dir)) != NULL)
	{
		sys.node = new_node();
		sys.path = ft_strjoin(name, "/");
		tmp = sys.path;
		sys.path = ft_strjoin(sys.path, (sys.sd)->d_name);
		ft_strdel(&tmp);
		if (lstat(sys.path, &(sys.state)) != -1)
		{
			stockage(sys.state, &sys.node, (sys.sd)->d_name, sys.path);
			sort_by_ascii(&sys.node, &sys.head);
			ft_strdel(&sys.path);
		}
		else
		{
			ft_putstr("./ft_ls: ");
			perror(name);
			return (0);
		}
		total = total + sys.state.st_blocks;
	}
	if (flags.f_t)
		sort_by_time(&sys.head);
	closedir(sys.dir);
	if (flags.f_l || flags.f_g)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putendl("");
	}
	if (!flags.f_r)
		printlist(sys.head, flags, 1);
	else
		reverse_lst(sys.head, flags, 1);
	if (flags.f_rm)
		ft_check_folder(sys.head, name, flags);
	freelist(&sys.head);
	return (0);
}

// int ft_readdir(t_data sys, char *name, t_flags flags)
// {
//     // t_flist *tmp;
//     char *directories;
//      char *ptr;

//     // //printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//     directories = NULL;
//     sys.head = NULL;
//     sys.path = NULL;
//     while((sys.sd = readdir(sys.dir)) != NULL)
//     {
//         if (!sys.sd)
//         {
//             printf("eroor");
//             perror("ft_ls :");
//             return (0);
//         }
//         sys.node =  new_node();
//         //printf("\t=>%s\n", name);
//         //ft_strdel(&sys.path);
//         sys.path = ft_strjoin(name, "/");
//         ptr = sys.path;
//         sys.path = ft_strjoin(sys.path, (sys.sd)->d_name);
//         ft_strdel(&ptr);
//         if (lstat(sys.path, &(sys.state)) != -1)
//         {
//             if (flags.f_R && S_ISDIR(sys.state.st_mode)
//             && ft_strcmp(ft_strrchr(sys.path, '/') + 1, "..")
//             && ft_strcmp(ft_strrchr(sys.path, '/') + 1, "."))
//             {
//                 ptr = directories;
//                 directories = ft_strjoin(directories, sys.path);
//                 free(ptr);
//                 ptr = directories;
//                 directories = ft_strjoin(directories, ":");
//                 free(ptr);
//             }
//             stockage(sys.state, &sys.node, (sys.sd)->d_name,sys.path);
//             sort_by_ascii(&sys.node, &sys.head);
//         }
//     }
//      sys.directories = ft_strsplit(directories, ':');
//      free(directories);
//     if (flags.f_t)
//         sort_by_time(&sys.head);
//     closedir(sys.dir);
//     if (!flags.f_r)
//         printlist(sys.head, flags, 1);
//     else
//         reverse_lst(sys.head, flags, 1);
//     if (flags.f_R && sys.directories)
//     {
//         //  ft_check_folder(&sys.head,name,flags);
//         int i = 0;
//         while (sys.directories[i])
//         {
//             ft_recursive(sys.directories[i],flags);
//             ft_strdel(&sys.directories[i]);
//             i++;
//         }
//         free(sys.directories);
//      }
//     //printf("\n+_+_+_+_+_+__+_+_+_+_+_+_+_+_+_+_+_+_+_+_++\n");
//     /*if (flags.f_t == 1)
//         sort_by_time(&sys.head);
//     printf("here 1\n");
//     closedir(sys.dir);
//     tmp = sys.head;
//     printf("here 1\n");
//     if (!flags.f_r)
//         printlist(sys.head,flags,1);
//     else
//         reverse_lst(sys.head,flags,1);
//     printf("here 1\n");
//     if (flags.f_R)
//         ft_check_folder(&sys.head,name,flags);
//     printf("here 1\n");*/
//     //freelist(&sys.head);
//     return (0);
// }
