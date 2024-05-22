/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lade-kon <lade-kon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 19:29:14 by lade-kon      #+#    #+#                 */
/*   Updated: 2024/05/22 21:23:12 by lade-kon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	bit = 0;
	static int	sig_count = 0;
	char		*result;

	result = NULL;
	if (signum == SIGUSR1)
		sig_count++;
	else if (signum == SIGUSR2)
	{
		bit = bit | (1 << sig_count);
		sig_count++;
	}
	if (sig_count == 8)
	{

		bit = 0;
		sig_count = 0;
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

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
