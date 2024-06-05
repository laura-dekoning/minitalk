/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:36 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/06/05 16:38:28 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received = 0;

static void	handle_acknowledgement(int sig)
{
	static unsigned int	i = 0;

	(void)sig;
	g_received = 1;
	if (sig == SIGUSR1)
		ft_putstr_fd("Message succesfully received\n", STDOUT_FILENO);
	if (sig == SIGUSR2)
		ft_printf("Bit %i has been received!\n", i);
	i++;
}

static void	send_bit(char c, int b, int server_pid)
{
	int	error;

	error = 0;
	if (c & (1 << b))
		error = kill(server_pid, SIGUSR2);
	else
		error = kill(server_pid, SIGUSR1);
	if (error != 0)
		ft_puterror_fd("Failed to send signal", STDERR_FILENO);
	while (!g_received)
		pause();
	g_received = 0;
}

static void	send_char(char c, int server_pid)
{
	int	b;

	b = 0;
	while (b < 8)
	{
		send_bit(c, b, server_pid);
		b++;
	}
}

static void	send_string(char *str, int server_pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(str[i], server_pid);
		i++;
	}
	send_char(str[i], server_pid);
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
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_acknowledgement;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_string(str, server_pid);
	return (0);
}
