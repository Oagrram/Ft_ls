/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:50:58 by oagrram           #+#    #+#             */
/*   Updated: 2019/12/02 10:51:20 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int     ft_get_dir(char *name, file_flags flags)
{
    data       system;
    
    lstat(name, &(system.fileStat));
    if (S_ISDIR(system.fileStat.st_mode))
    {
        if (!(system.dir = opendir(name)))
        {
            printf("eroor");
            perror("ft_ls :");
            return (0);
        }
        ft_readdir(system, name, flags);
    }
    return (0);
}

int get_argument(t_flist **argument, char *argv,t_flist **head)
{
    data system;
    lstat(argv, &(system.fileStat));
    stockage(system.fileStat,&(*argument), argv);
    sort_by_ascii(&(*argument), &(*head));
    return 0;
}

void    get_files(t_flist *ptr,file_flags flags)
{
    t_flist *head;
    t_flist *cur;

    head = NULL;
    while(ptr != NULL)
    {
        if (ptr->type != 'd')
        {
            if (!head)
            {
                head = ptr;
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
    if (!head)
        return;
    flags.flag_a = 1;
    if (flags.flag_t)
        sort_by_time(&head);
    if (!flags.flag_r)
         printlist(head,flags,2);
     else
         reverse_lst(head,flags,2);
}

int     main(int argc,char **argv)
{
    int i;
    file_flags flags;
    data       system;
    t_flist *header;

    i = 0;
    flags.flag_R = 0;
    header = NULL;
    if (argc == 1 || (argc == 2 && argv[1][0] == '-'))
    {
        if (check_flag(argv[argc-1], &flags) == 1)
            return (0);
        ft_get_dir(".", flags);
    }
    else
    {
        if (argv[1][0] == '-')
        {
            check_flag(argv[1], &flags);
            i++;
        }
        while(argv[++i])
        {
            system.node =  new_node();
            get_argument(&system.node,argv[i],&header);
        }
    }
    get_files(header,flags);
    while(header != NULL)
    {
        if (header->type == 'd')
            ft_get_dir(header->name,flags);
        header = header->next;
    }
    return (0);
}