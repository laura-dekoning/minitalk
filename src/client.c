/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:36 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/17 11:28:11 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*str;

	if (argc != 3 || !ft_isnumber(argv[1]))
		return (0);
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	printf("CLIENT: server_pid: %i\n", server_pid);
	return (0);
}
