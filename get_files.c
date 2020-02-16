/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:19:13 by oagrram           #+#    #+#             */
/*   Updated: 2020/02/08 22:19:16 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		get_link(char *name)
{
	int		tmp;
	char	*tmplink;
	t_data	str;

	tmp = 0;
	str.path = name;
	tmplink = ft_strnew(MAX_PATH);
	while ((tmp = readlink(str.path, tmplink, MAX_PATH + 1) >= 0))
		str.path = tmplink;
	if (name[0] == '/')
		tmplink = ft_strjoin("/", tmplink);
	if (lstat(tmplink, &(str.state)) == -1)
	{
		ft_putstr("./ft_ls: ");
		perror(name);
		return (0);
	}
	free(tmplink);
	if (S_ISDIR(str.state.st_mode))
		return (2);
	else
		return (1);
	return (0);
}

void	link_files(t_flist *ptr, t_flist **head)
{
	t_flist *cur;

	while (ptr != NULL)
	{
		if (ptr->type != 'd')
		{
			if (!(*head))
			{
				(*head) = ptr;
				cur = ptr;
				cur->previous_file = NULL;
			}
			else
			{
				cur->next_file = ptr;
				cur->next_file->previous_file = cur;
				cur = cur->next_file;
			}
		}
		ptr = ptr->next;
	}
}

void	get_files(t_flist **ptr, t_flags flags)
{
	t_flist *head;
	t_flist *tmp;

	head = NULL;
	tmp = (*ptr);
	if (flags.f_t)
	{
		sort_by_time(&(*ptr));
		tmp = (*ptr);
	}
	link_files(*ptr, &head);
	if (!head)
	{
		*ptr = tmp;
		return ;
	}
	if (!flags.f_r)
		printlist(head, flags, 2);
	else
		reverse_lst(head, flags, 2);
	(*ptr) = tmp;
}
