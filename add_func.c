#include "inc/ft_ls.h"

void 	str_toupper(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i--)
		str[i] = (char)ft_toupper(str[i]);
}