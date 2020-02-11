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

void		get_us_gr_lk(struct stat state, t_flist *node)
{
	struct passwd	*user;
	struct group	*group;

	user = getpwuid(state.st_uid);
	group = getgrgid(state.st_gid);
	node->permision[9] = ('\0');
	node->nlink = (state.st_nlink);
	node->user = (user->pw_name);
	node->groupe = (group->gr_name);
	node->size = (state.st_size);
}

void		getpermition(struct stat state, t_flist **node)
{
	(*node)->permision[0] = ((state.st_mode & S_IRUSR) ? 'r' : '-');
	(*node)->permision[1] = ((state.st_mode & S_IWUSR) ? 'w' : '-');
	if ((state.st_mode & S_ISUID) && (state.st_mode & S_IXUSR))
		(*node)->permision[2] = 's';
	else if (state.st_mode & S_ISUID)
		(*node)->permision[2] = 'S';
	else
		(*node)->permision[2] = ((state.st_mode & S_IXUSR) ? 'x' : '-');
	(*node)->permision[3] = ((state.st_mode & S_IRGRP) ? 'r' : '-');
	(*node)->permision[4] = ((state.st_mode & S_IWGRP) ? 'w' : '-');
	if ((state.st_mode & S_ISGID) && (state.st_mode & S_IXGRP))
		(*node)->permision[5] = 's';
	else if (state.st_mode & S_ISGID)
		(*node)->permision[5] = 'S';
	else
		(*node)->permision[5] = ((state.st_mode & S_IXGRP) ? 'x' : '-');
	(*node)->permision[6] = ((state.st_mode & S_IROTH) ? 'r' : '-');
	(*node)->permision[7] = ((state.st_mode & S_IWOTH) ? 'w' : '-');
	if ((state.st_mode & S_ISVTX) && (state.st_mode & S_IXOTH))
		(*node)->permision[8] = 't';
	else if (state.st_mode & S_ISVTX)
		(*node)->permision[8] = 'T';
	else
		(*node)->permision[8] = ((state.st_mode & S_IXOTH) ? 'x' : '-');
	get_us_gr_lk(state, *node);
}

char		getfiletype(mode_t mode)
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

int			get_time(struct stat state, t_flist *node)
{
	int		i;
	time_t	now;
	char	*sub1;
	char	*sub2;

	i = 0;
	time(&now);
	if (state.st_mtime >= (now - 15552000))
		(*node).time = ft_strsub(ctime(&state.st_mtime), 4, 12);
	else
	{
		sub1 = ft_strsub(ctime(&state.st_mtime), 4, 7);
		sub2 = ft_strsub(ctime(&state.st_mtime), 19, 24);
		(*node).time = ft_strjoin(sub1, sub2);
		ft_strdel(&sub1);
		ft_strdel(&sub2);
		while ((*node).time[i++])
			if ((*node).time[i] == '\n')
				(*node).time[i] = '\0';
	}
	return (0);
}

int			stockage(struct stat state, t_flist **node, char *name, char *path)
{
	ssize_t len;

	(*node)->name = ft_strdup(name);
	(*node)->mtime = state.st_mtime;
	get_time(state, *node);
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
