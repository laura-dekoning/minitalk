#include "libft.h"

int	main()
{
	char	*str;
	char	c;
	char	*result;

	str = "HOI";
	c = "a";
	result = ft_appchar(str, c);
	printf("%s\n", result);
	return (0);
}