/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:30:39 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/18 11:42:33 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_validate(char *var)
{
	int	i;

	i = 1;
	if (var == NULL || (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '=' && var[i] != '_'
			&& var[i] != ' ')
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	unset_env(t_env **head, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, var, ft_strlen(var)))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	unset(t_env **head, char **var)
{
	int	i;

	i = 1;
	if (var[1][0] == '-')
	{
		ft_putstr_fd("bash: unset: -T: invalid option\n", 2);
		ft_putstr_fd("unset: usage: unset [-f] [-v] [name ...]\n", 2);
		exit_code(2);
	}
	while (var[i])
	{
		if (var_validate(var[i]))
			unset_env(head, var[i]);
		else
			exit_code(1);
		i++;
	}
}
