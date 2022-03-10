#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	*s1 = "home=here";
	char	*s2 = "home";
	int	ret;

	ret = ft_strncmp(s1, s2, ft_strlen(s2)+1);
	printf("ret:%d\n", ret);
	return (0);
}

