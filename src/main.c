#include "minitalk.h"

char	*ft_appchar(char *str, char c)
{
	char	*result;
	int		len;

	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			ft_puterror_fd("Memory allocation failed!", STDERR_FILENO);
		len = 0;
	}
	else
		len = ft_strlen(str);
	result = malloc(len + 2 * sizeof(char));
	if (!result)
		ft_puterror_fd("Memory allocation failed!", STDERR_FILENO);
	ft_memcpy(result, str, len);
	result[len] = c;
	return (free(str), result);
}

int	main()
{
	char	*str = NULL;
	char	c;
	char	*result;

	// str = "HOI";
	c = 'a';
	result = ft_appchar(str, c);
	printf("%s\n", result);
	free(result);
	return (0);
}