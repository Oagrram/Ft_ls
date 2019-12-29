
#include "ls.h"


void    printlist(t_flist **head)
{
    t_flist *tmp;
    t_flist *tmp2;

    tmp = *head;
    tmp2 = tmp;
    while ((tmp) != NULL)
    {
        printnode(&(tmp));
        printf("\n");
        (tmp) = (tmp)->next;
        //if (tmp)
        //ft_memdel((void**)&tmp->previous);
        
    }
    freelist(&(tmp));
}

void reverse_lst(t_flist      **lst)
{
    t_flist *ptr;

    ptr = *lst;
    while ((ptr)->next != NULL)
    {
        (ptr)=(ptr)->next;
    }
    while((ptr) != NULL)
    {
        printnode(&ptr);
        //rintf(" <%s> \n",(ptr)->name);
        (ptr)=(ptr)->previous;
    }

}

void    printnode(t_flist      **head)
{
        ft_putchar((*head)->type);
        ft_putstr((*head)->permision);
        ft_putstr("  ");
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