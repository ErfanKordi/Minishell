/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junction_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:24:28 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/22 14:41:56 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_parent_builtin_cmds(t_cmdtable *table, t_dt *minishell)
{
	if (table->cmd[0])
	{
		if (!ft_strncmp(table->cmd[0], "cd", 2)
			&& ft_strlen(table->cmd[0]) == 2)
		{
			execute_cd(table->cmd, minishell->envp_lst);
		}
		else if (!ft_strncmp(table->cmd[0], "export", 6)
			&& ft_strlen(table->cmd[0]) == 6)
		{
			if (table->cmd[1])
				set_env(&minishell->envp_lst, table->cmd);
		}
		else if (!ft_strncmp(table->cmd[0], "unset", 5)
			&& ft_strlen(table->cmd[0]) == 5)
		{
			if (table->cmd[1])
				unset(&minishell->envp_lst, table->cmd);
		}
	}
}

int	exe_built_in_cmds(char **args, t_env *envp_lst)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		execute_echo(args + 1);
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
		execute_pwd();
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		print_env_var_list(env_to_char_array(envp_lst));
	else if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
	{
		if (!args[1])
			set_env(&envp_lst, args);
	}
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		return (0);
	else if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
		return (0);
	else if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		return (0);
	else
		return (1);
	return (0);
}
