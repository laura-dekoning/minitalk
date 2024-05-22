#include "minitalk.h"

char	*ft_appchar(char *str, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(str);
	result = ft_calloc(len + 2, sizeof(char));
	if (!result)
		ft_puterror_fd("Memory allocation failed!", STDERR_FILENO);
	ft_memcpy(result, str, len);
	result[len] = c;
	return (result);
}

int	main()
{
	char	*str;
	char	c;
	char	*result;

	str = "HOI";
	c = 'a';
	result = ft_appchar(str, c);
	printf("%s\n", result);
	return (0);
}