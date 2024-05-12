/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:27:38 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/22 14:40:55 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_path(char *tmp, char *tmp2, char *arg)
{
	if (arg[0] == '~')
		tmp = ft_strjoin(getenv("HOME"), arg + 1);
	else
	{
		if (access(arg, X_OK) == 0)
			chdir(arg);
		else
		{
			tmp = getcwd(NULL, 0);
			tmp2 = ft_strjoin(tmp, "/");
			free(tmp);
			tmp = ft_strjoin(tmp2, arg);
			free(tmp2);
		}
	}
	if (tmp && chdir(tmp) != 0)
	{
		perror("chdir");
		exit_code(1);
		return (0);
	}
	if (tmp)
		free(tmp);
	return (1);
}

void	execute_cd(char **args, t_env *envp_list)
{
	char	*tmp;
	char	*tmp2;
	char	*old_pwd;

	tmp = NULL;
	tmp2 = NULL;
	old_pwd = getcwd(NULL, 0);
	if (args[1] != NULL)
	{
		if (!make_path(tmp, tmp2, args[1]))
			return ;
	}
	else if (chdir(getenv("HOME")) != 0)
	{
		perror("chdir");
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit_code(1);
		return ;
	}
	tmp = getcwd(NULL, 0);
	update_env_value(envp_list, "PWD", tmp);
	update_env_value(envp_list, "OLDPWD", old_pwd);
	free(tmp);
	free(old_pwd);
}
