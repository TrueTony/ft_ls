#include "libft.h"

int ft_numstr(int n)
{
    int i;

    i = 1;
    while(n > 9)
    {
        n /= 10;
        i++;
    }
    return (i);
}

