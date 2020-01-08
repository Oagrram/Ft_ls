
#include "ls.h"

void    getmaxint(t_flist **head,int *maxnlink)
{
    t_flist *ptr;
    int tmp;
    int count = 0;
    ptr = *head;
    *maxnlink = 0; 
    //while(ptr)
    //{
        tmp = ptr->nlink;
        while (tmp != 0)
        {
            tmp/= 10;
            ++count;
        }
        *maxnlink = count;
        
       // ptr = ptr->next;
    //}
}

void    printlist(t_flist **head,file_flags flags)
{
    t_flist *tmp;
    t_flist *tmp2;
    int maxlink = 0;
    tmp = *head;
    tmp2 = tmp;
    
    //getmaxint(head, &maxlink);
    //printf("maxnlink == %d\n",maxlink);
    while ((tmp) != NULL)
    {
        if ((!flags.flag_a && (tmp)->name[0] != '.') || (flags.flag_a))
            printnode(&(tmp), flags,maxlink);
        //printf("\n");
        (tmp) = (tmp)->next;
        //if (tmp)
        //ft_memdel((void**)&tmp->previous);
    }
    ft_putchar('\n');
    freelist(&(tmp));
}

void reverse_lst(t_flist      **lst,file_flags flags)
{
    t_flist *ptr;

    ptr = *lst;
    while ((ptr)->next != NULL)
    {
        (ptr)=(ptr)->next;
    }
    while((ptr) != NULL)
    {
        if ((!flags.flag_a && (ptr)->name[0] != '.') || (flags.flag_a))
           // printnode(&ptr,flags);
        //rintf(" <%s> \n",(ptr)->name);
        (ptr)=(ptr)->previous;
    }
    
    ft_putchar('\n');
}

void    printnode(t_flist      **head, file_flags flags, int maxlink)
{
    if (!flags.flag_l)
    {
        ft_putstr((*head)->name);
        ft_putchar(' ');
        return;
    }
    else
    {
        getmaxint(head, &maxlink);
        maxlink = 4 -  maxlink;
       // printf("maxlin ==== %d\n",maxlink);
        ft_putchar((*head)->type);
        ft_putstr((*head)->permision);
        
        
        while (maxlink )
        {
            ft_putchar(' ');
            maxlink--;
        }
        //ft_putstr("  ");
        ft_putnbr((*head)->nlink);
        ft_putchar(' ');
        ft_putstr((*head)->user);
        ft_putchar(9);
        ft_putstr((*head)->groupe);
        ft_putchar(9);
        ft_putnbr((*head)->size);
        ft_putchar(9);
        ft_putstr((*head)->time);
        ft_putchar(9);
        ft_putstr((*head)->name);
        ft_putchar('\n');
    }
}

void freelist(t_flist **head)
{
   t_flist *tmp;

   while (*head != NULL)
    {
       tmp = *head;
       *head = (*head)->next;
       ft_memdel((void**)&(tmp));
    }
}