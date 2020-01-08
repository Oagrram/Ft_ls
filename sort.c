#include "ls.h"

int *swap_content(t_flist **newnode, t_flist **ptr)
{
    t_flist *tmp = new_node();
     file_flags flags;
     flags.flag_l = 1;
     

     int i = 0;
     
    
    tmp->type = (*newnode)->type;
    (*newnode)->type = (*ptr)->type;
    (*ptr)->type = tmp->type;
    while(i++ < 11)
    {
        tmp->permision[i] = (*newnode)->permision[i];
        (*newnode)->permision[i] = (*ptr)->permision[i];
        (*ptr)->permision[i] = tmp->permision[i];
    }
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
    return 0;

}

// t_flist *sort_by_time(t_flist **node, t_flist **head)
// {
    
//     t_flist *ptr;
//     file_flags flags;

//     ptr = *head;
//     flags.flag_l = 1;
//     printf("iam in sort by time with node == %s\n",(*node)->name);
//     if (!*head)
//     {
//         *head = *node;
//         return (*head);
//     }
//     while(ptr->next != NULL)
//         ptr = ptr->next;
//     ptr->next = *node;
//     (*node)->previous = ptr; 
//     (*node)->next = NULL;
//     //printf("ptr time == %d\n node time == %d\n",ptr->mtime,(*node)->mtime);
//     while(ptr)
//     {
//         if (ptr->mtime < (*node)->mtime)
//         {
//             *head = swap_content(node,&ptr);
//             printlist(&(*head),flags);
//             printf("---------------------------------------------------------------------------------\n");
            
//         }
//         else if (ptr->mtime == (*node)->mtime && ft_strcmp((*node)->name, ptr->name) > 0)
//         {
//              *head =  swap_content(node,&ptr);
//              printlist(&(*head),flags);
//             printf("---------------------------------------------------------------------------------\n");
//         }
        
//         *node = ptr;
//         ptr = ptr->previous; 
//     }
//     printlist(&(*head),flags);
//     printf("---------------------------------------------------------------------------------\n");
//     return (*head);
// }





// t_flist *sort_by_time(t_flist **node, t_flist **lst)
// {
//     t_flist *ptr;
//     t_flist *tmp;

//     if (!*lst)
//     {
//         *lst = *node;
//         return (*lst);
//     }
//     ptr = *lst;
//     tmp = NULL;
//     while ((*node)->mtime <= ptr->mtime)
//     {
//         //printf("here\n");
//         if ((*node)->mtime == ptr->mtime && (ft_strcmp((*node)->name, ptr->name)))
//             break ;
//         tmp = ptr;
//         if (!ptr->next)
//             break ;
//         ptr = ptr->next;
//     }
//     if (!(ptr->next) && (*node)->mtime < ptr->mtime )
//     {
//         printf("here 1\n");
//         ptr->next = *node;
//         (*node)->previous = ptr;
//     }
//     else
//     {
//         printf("here 2\n");
//         (*node)->next = ptr;
//         ptr->previous = *node;
//         (*node)->previous = tmp;
//         if (tmp)
//             tmp->next = *node;
//         else
//             *lst = *node;
//     }
//   // printlist(&(*lst));
//     printf("================================\n");
//     return (*lst);
// }

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