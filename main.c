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

int     ft_get_info(char *name, file_flags flags)
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
    else
    {
        system.node =  new_node();
        stockage(system.fileStat,&system.node, name);
        //printnode(&system.node,flags);
       freelist(&system.node);
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

void    get_files(t_flist *ptr)
{
    t_flist *head;
    t_flist *cur;

    while(ptr != NULL)
    {
        if (ptr->type != 'd')
        {
            if (!head)
            {
                head = ptr;
                cur = ptr;
            }
            else
            {
                


            }
            head = ptr;
            head->previous =  NULL;
            break;
        }
        ptr = ptr->next;
    }

}

int     main(int argc,char **argv)
{
    file_flags flags;
    int i = 0;
    data       system;
    t_flist *header;

    flags.flag_R = 0;
    header = NULL;
    if (argc == 1 || (argc == 2 && argv[1][0] == '-'))
    {
        check_flag(argv[argc-1], &flags);
         ft_get_info(".", flags);
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
    get_files(header);
    while(header != NULL)
    {
        if (header->type == 'd')
        {
            ft_get_info(header->name,flags);
        }
        //else
            //printnode(&header,flags,5);
        header = header->next;
    }
    return (0);
}