/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:17:57 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/22 15:26:13 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell_parent(int *pipe_fd, int child_pid)
{
	ssize_t	bytes_read;
	int		pid;
	char	buffer[256];

	close(pipe_fd[1]);
	close(STDOUT_FILENO);
	bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		pid = ft_atoi(buffer);
		if (pid != child_pid)
		{
			if (kill(pid, SIGTERM) == -1)
				perror("kill");
		}
		bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
	}
	if (bytes_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, NULL, 0);
}

void	exit_all_minishell(void)
{
	int		pipe_fd[2];
	int		child_pid;
	char	*pgrep_args[4];

	pgrep_args[0] = "pgrep";
	pgrep_args[1] = "-x";
	pgrep_args[2] = "minishell";
	pgrep_args[3] = NULL;
	pipe(pipe_fd);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve("/usr/bin/pgrep", pgrep_args, NULL);
		exit(0);
	}
	else
		exit_minishell_parent(pipe_fd, child_pid);
}

bool	ft_str_isdigit(const char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

void	exit_minishell(int arg_count, t_dt *minishell,
			int	*exit_code_var, char **args)
{
	if (arg_count == 1)
	{
		close(minishell->fd_out);
		close(minishell->fd_in);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_all_minishell();
		exit(*exit_code_var);
	}
	else if (arg_count == 2)
	{
		if (ft_str_isdigit(args[1]) || (args[1][0] == '-'
			&& ft_str_isdigit(args[1] + 1)))
		{
			*exit_code_var = ft_atoi(args[1]);
			ft_putstr_fd("exit\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			*exit_code_var = 255;
		}
	}
}

void	exit_shell(char **args, t_dt *minishell)
{
	int	exit_code_var;
	int	arg_count;

	exit_code_var = 0;
	arg_count = 0;
	while (args[arg_count] != NULL)
		arg_count++;
	if (arg_count <= 2)
		exit_minishell(arg_count, minishell, &exit_code_var, args);
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit_code(1);
		return ;
	}
	close(minishell->fd_out);
	close(minishell->fd_in);
	exit_all_minishell();
	exit(exit_code_var);
}

// void	exit_shell(char **args, t_dt *minishell)
// {
// 	int	exit_code_var;
// 	int	arg_count;

// 	exit_code_var = 0;
// 	arg_count = 0;
// 	while (args[arg_count] != NULL)
// 		arg_count++;
// 	if (arg_count == 1)
// 	{
// 		close(minishell->fd_out);
// 		close(minishell->fd_in);
// 		ft_putstr_fd("exit\n", STDERR_FILENO);
// 		exit_all_minishell();
// 		exit(exit_code_var);
// 	}
// 	if (arg_count == 2)
// 	{
// 		if (ft_isdigit(args[1][0]) || (args[1][0] == '-'
// 				&& ft_isdigit(args[1][1])))
// 		{
// 			dup2(minishell->fd_out, STDOUT_FILENO); // close fd_out and in
// 			close(minishell->fd_out);
// 			close(minishell->fd_in);
// 			exit_code_var = atoi(args[1]);
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			exit_all_minishell();
// 			exit(exit_code_var);
// 		}
// 		else
// 		{
// 			dup2(minishell->fd_out, STDOUT_FILENO);
// 			close(minishell->fd_out);
// 			close(minishell->fd_in);
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
// 			ft_putstr_fd(args[1], STDOUT_FILENO);
// 			ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
// 			exit_all_minishell();
// 			exit(255);
// 		}
// 	}
// 	if (arg_count > 2)
// 	{
// 		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
// 		exit_code(1);
// 		return ;
// 	}
// }
