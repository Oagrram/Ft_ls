/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:13:49 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/08 22:13:52 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	get_name(char *name)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] == '/')
			j = i;
		i++;
	}
	if (j == 0)
		perror(name);
	else
		perror(&name[j + 1]);
}

int		get_dir(char *name, t_flags flags)
{
	t_data	sys;

	if (lstat(name, &(sys.state)) == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
		return (0);
	}
	if (S_ISDIR(sys.state.st_mode) && ((sys.state.st_mode & S_IXUSR) ? 0 : 1) &&
	((sys.state.st_mode & S_IWUSR) ? 1 : 0) &&
	((sys.state.st_mode & S_IRUSR) ? 1 : 0))
		return (0);
	if (!(sys.dir = opendir(name)))
	{
		ft_putstr("./ft_ls: ");
		get_name(name);
		return (0);
	}
	ft_readdir(sys, name, flags);
	return (0);
}
