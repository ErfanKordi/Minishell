/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:21:52 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/23 09:31:31 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prepares and executes commands in the minishell
 * @param minishell Pointer to the minishell data structure
 * @return 1 on success
 */
int	prepare_and_execute(t_dt *minishell)
{
	int		i;
	int		table_num;
	bool	last_cmd;

	i = -1;
	table_num = 0;
	exit_code(0);
	while (minishell->cmdtable[table_num])
		table_num++;
	if (minishell->cmdtable[0]->cmd_nb != 0 && table_num == 1
		&& !ft_strncmp(minishell->cmdtable[0]->cmd[0], "exit", 4))
	{
		exit_shell(minishell->cmdtable[0]->cmd, minishell);
		return (1);
	}
	while (++i < table_num)
	{
		if (i + 1 == table_num)
			last_cmd = true;
		execute(minishell->cmdtable[i], minishell, last_cmd);
	}
	ft_waitpid(minishell, table_num);
	return (1);
}

void	parent(t_cmdtable *table, int *fd, bool last_cmd)
{
	close(fd[1]);
	if (last_cmd)
	{
		dup2(table->fd_in, STDIN_FILENO);
		close(fd[0]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

/**
 * @brief Executes a command table in the minishell
 * @param table Pointer to the command table
 * @param minishell Pointer to the minishell data structure
 * @param last_cmd Flag indicating if this is the last command in a pipeline
 */
void	execute(t_cmdtable *table, t_dt *minishell, bool last_cmd)
{
	int	pid1;
	int	fd[2];

	pipe(fd);
	exe_parent_builtin_cmds(table, minishell);
	block_signal();
	set_heredoc(table, fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		setup_child_signals();
		if (*minishell->exit)
			ft_exit(minishell);
		else
			child(table, last_cmd, minishell, fd);
	}
	else
		parent(table, fd, last_cmd);
}

void	set_output_direction(int *fd, t_cmdtable *table, bool last_cmd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (table->fd_rdr_out)
	{
		dup2(table->fd_rdr_out, STDOUT_FILENO);
		close(table->fd_rdr_out);
	}
	else if (last_cmd && !table->fd_rdr_out)
	{
		dup2(table->fd_out, STDOUT_FILENO);
		close(table->fd_out);
	}
}

void	child(t_cmdtable *table, bool last_cmd, t_dt *minishell, int *fd)
{
	char	*path;

	close(fd[0]);
	if (check_redirections(table, fd) && table->cmd)
		exit(1);
	if (!table->cmd[0])
		ft_exit(minishell);
	else
	{
		set_output_direction(fd, table, last_cmd);
		if (exe_built_in_cmds(table->cmd, minishell->envp_lst) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		else
		{
			path = find_path(table, env_to_char_array(minishell->envp_lst),
					last_cmd);
			execve(path, table->cmd, env_to_char_array(minishell->envp_lst));
		}
	}
}
