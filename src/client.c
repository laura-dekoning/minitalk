/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:36 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/22 21:29:35 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received = 0;

static void	handle_acknowledgement(int sig)
{
	(void)sig;
	g_received = 1;
	if (sig == SIGUSR1)
		ft_putstr_fd("Received bit 0\n", STDOUT_FILENO);
	if (sig == SIGUSR2)
		ft_putstr_fd("Received bit 1\n", STDOUT_FILENO);
}

static void	send_string(char *str, int server_pid)
{
	int	i;
	int	b;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		b = 0;
		while (b < 8)
		{
			if (str[i] & (1 << b))
				error = kill(server_pid, SIGUSR2);
			else
				error = kill(server_pid, SIGUSR1);
			if (error != 0)
				ft_puterror_fd("Failed to send signal");
			while (!g_received)
				pause();
			g_received = 0;
			b++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3 || !ft_isnumber(argv[1]))
		ft_puterror_fd("Format: ./client  <pid>  <message>", STDERR_FILENO);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_puterror_fd("Invalid PID", STDERR_FILENO);
	str = argv[2];
	sa.sa_handler = handle_acknowledgement;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_string(str, server_pid);
	return (0);
}
