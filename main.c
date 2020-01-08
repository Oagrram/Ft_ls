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



int ft_readdir(data system, char *name, file_flags flags)
{
    t_flist *tmp;

    system.head = NULL;
    while((system.sd = readdir(system.dir)) != NULL)
    {
        system.node =  new_node();
        system.path = ft_strjoin(name, "/");
        system.path = ft_strjoin(system.path, (system.sd)->d_name);
        //printf("(system.sd)->d_name = %s\n",(system.sd)->d_name);
        lstat(system.path, &(system.fileStat)); 
        stockage(system.fileStat, &system.node, (system.sd)->d_name);
        // printf("i am in sort by asccoiio \n");
        sort_by_ascii(&system.node, &system.head);
    }
    if (flags.flag_t == 1)
    {
        sort_by_time(&system.head);
        //printlist(&system.head,flags);

    }
    closedir(system.dir);
    tmp = system.head;
     if (!flags.flag_r)
         printlist(&system.head,flags);
     else
         reverse_lst(&system.head,flags);
    if (flags.flag_R)
        ft_check_folder(&tmp,name,flags);
    //freelist(&system.head);
    return (0);
}

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
    // (*argument)->next = new_node();
    // (*argument) = (*argument)->next;
    return 0;
}

int     main(int argc,char **argv)
{
    file_flags flags;
    int i = 0;
    data       system;
    t_flist *header;

    flags.flag_R = 0;
    header = NULL;
    printf("\n-\t-\t-\t-\t-\t-\t-\t- \n\n\n");
    printf("argc == %d\n",argc);
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
        // files = new_node();
        // files = ft_get_info(argv[++i] , flags);
        
        
        //header = system.node;
        while (argv[++i])
        {
            system.node =  new_node();
            get_argument(&system.node,argv[i],&header);
        }
        //printlist(&(header),flags);
    }
    while(header != NULL)
    {
        if (header->type == 'd')
        {
            ft_get_info(header->name,flags);
        }
        else
            printnode(&header,flags,5);
        header = header->next;
    }
    return (0);
}