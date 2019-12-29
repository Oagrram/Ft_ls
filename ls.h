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

#define l 1
#define a 2
#define t 3
#define r 4
#define R 5

typedef struct  flag
{
    int         flag_l;
    int         flag_a;
    int         flag_r;
    int         flag_t;
    int         flag_R;
}   file_flags;


typedef struct  filenode
{
    int         nlink; 
    int         size;
    int         mtime;
    char        type;
    char        *name;
    char        *time;
    char        *groupe;
    char        *user;
    char        permision[11];
    struct      filenode *next;
    struct      filenode *previous;
}                t_flist;

typedef struct file_struct
{
    struct       stat fileStat;
    struct       dirent *sd;
    char         *path;
    DIR          *dir;
    t_flist      *head;
    t_flist      *node;
}                data;
int     ft_get_info(char *name, file_flags *flags);
void    printlist(t_flist      **head);
void    printnode(t_flist      **head);
int ft_recursive(char *path);
int ft_check_folder(t_flist **lst,char *path);
void freelist(t_flist **head);
t_flist *sort_by_time(t_flist **node, t_flist **lst);
t_flist *sort_by_ascii(t_flist **node, t_flist **lst);
void    swapelement(t_flist **node, t_flist **next);
void reverse_lst(t_flist      **lst);

#endif
