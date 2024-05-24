/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:14 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/24 15:04:56 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_result = NULL;

static void	print_string(siginfo_t *info)
{
		kill(info->si_pid, SIGUSR1);
		ft_putstr_fd(g_result, STDOUT_FILENO);
		free(g_result);
		g_result = NULL;
}

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
	kill(info->si_pid, SIGUSR2);
	if (sig_count == 8)
	{
		g_result = ft_appchar(g_result, bit);
		if (bit == '\0')
			print_string(info);
		bit = 0;
		sig_count = 0;
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

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
