/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:06:11 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/22 14:40:36 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles the SIGINT signal
/// @param signo The signal number
static void	handle_parent_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_code(1);
	}
}

/// @brief Sets up the terminal config.
static void	setup_termios_config(void)
{
	struct termios	termios_config;

	tcgetattr(0, &termios_config);
	termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_config);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/// @brief Blocks teh SIGINT, SIQUIT signals
void	block_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;

	sa_int = (struct sigaction){};
	setup_termios_config();
	sa_int.sa_handler = handle_parent_signal;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
