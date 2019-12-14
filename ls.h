/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:24:39 by oagrram           #+#    #+#             */
/*   Updated: 2019/12/02 11:25:57 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct  filenode
{
    int         nlink; 
    int         size;
    char        type;
    char        *name;
    char        *time;
    char        *groupe;
    char        *user;
    char        permision[11];
    struct      filenode *next;
}                t_flist;

typedef struct file_struct
{
    struct       stat fileStat;
    struct       dirent *sd;
    char         *path;
    DIR          *dir;
    t_flist      *head;
    t_flist      *lst;
}                sys;

void    *printlist(t_flist      **head);
void    printfile(t_flist **head, char *name);
void freelist(t_flist *head);

#endif
