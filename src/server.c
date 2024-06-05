/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:14 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/06/05 12:47:06 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_vec	g_string;

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static char	bit = 0;
	static int	sig_count = 0;

	(void)context;
	if (signum == SIGUSR1)
		sig_count++;
	else if (signum == SIGUSR2)
	{
		bit = bit | (1 << sig_count);
		sig_count++;
	}
	if (sig_count == 8)
	{
		vec_push(&g_string, bit);
		if (bit == '\0')
			vec_print(&g_string);
		bit = 0;
		sig_count = 0;
	}
	usleep(10);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (!vec_init(&g_string, 100))
		ft_puterror_fd("Vector initialisation failed!", STDERR_FILENO);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sa.sa_sigaction = handle_signal;
	server_pid = getpid();
	ft_printf("%i\n", server_pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
