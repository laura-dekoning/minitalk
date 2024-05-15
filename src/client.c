/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:36 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/15 20:46:04 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 2)
		return (0);
	server_pid = ft_atoi(argv[1]);
	printf("CLIENT: server_pid: %i\n", server_pid);
	return (0);
}
