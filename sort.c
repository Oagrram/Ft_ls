#include "ls.h"
void    swap_rest(t_flist **newnode, t_flist **ptr)
{
    t_flist *tmp;

    tmp = new_node();
    tmp->nlink = (*newnode)->nlink;
    (*newnode)->nlink = (*ptr)->nlink;
    (*ptr)->nlink = tmp->nlink;
    tmp->user = (*newnode)->user;
    (*newnode)->user = (*ptr)->user;
    (*ptr)->user = tmp->user;
    tmp->groupe = (*newnode)->groupe;
    (*newnode)->groupe = (*ptr)->groupe;
    (*ptr)->groupe = tmp->groupe;
    tmp->size = (*newnode)->size;
    (*newnode)->size = (*ptr)->size;  
    (*ptr)->size = tmp->size;
    tmp->time = (*newnode)->time;
    (*newnode)->time = (*ptr)->time;
    (*ptr)->time = tmp->time;
    tmp->name = (*newnode)->name;
    (*newnode)->name = (*ptr)->name;
    (*ptr)->name = tmp->name;
    tmp->mtime = (*newnode)->mtime;
    (*newnode)->mtime = (*ptr)->mtime;
    (*ptr)->mtime = tmp->mtime;
    free(tmp);
}

int    *swap_content(t_flist **newnode, t_flist **ptr)
{
    t_flist *tmp;
    file_flags flags;
    int i;

    flags.flag_l = 1;
    i = 0;
    tmp = new_node();
    tmp->type = (*newnode)->type;
    (*newnode)->type = (*ptr)->type;
    (*ptr)->type = tmp->type;
    while(i++ < 11)
    {
        tmp->permision[i] = (*newnode)->permision[i];
        (*newnode)->permision[i] = (*ptr)->permision[i];
        (*ptr)->permision[i] = tmp->permision[i];
    }
    free(tmp);
    swap_rest(newnode, ptr);
    return (0);
}

t_flist *sort_by_time(t_flist **head)
{
    
    t_flist *ptr;
    t_flist *header;

    header = *head;
    while(header)
    {
        ptr = header;
        while(ptr)
        {
            if ((header->mtime == ptr->mtime && (ft_strcmp(header->name, ptr->name) > 0)) || header->mtime < ptr->mtime)
                swap_content(&header,&ptr);
            ptr = ptr->next;
        }
        header = header->next;
    }
    return (*head);
}



t_flist *sort_by_ascii(t_flist **node, t_flist **lst)
{
    t_flist *ptr;
    t_flist *tmp;

    if (!*lst)
    {
        *lst = *node;
        return (*lst);
    }
    ptr = *lst;
    tmp = NULL;
    while (ft_strcmp((*node)->name, ptr->name) > 0)
    {
        tmp = ptr;
        (*node)->previous = tmp;
        if (!ptr->next)
            break ;
        ptr = ptr->next;
    }
    if (!(ptr->next) && ft_strcmp((*node)->name, ptr->name) > 0)
    {
        ptr->next = *node;
        (*node)->previous = ptr;
    }
    else
    {
        (*node)->next = ptr;
        ptr->previous = *node;
        if (tmp)
            tmp->next = *node;
        else
            *lst = *node;
    }
    return (*lst);
    }