/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:14 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/15 19:44:07 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	printf("%i\n", server_pid);
	return (0);
}
