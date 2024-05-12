/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:42:42 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/20 14:56:50 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_array(t_env *head, char **array)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		if (temp->value)
		{
			array[i] = (char *)malloc(ft_strlen(temp->key)
					+ ft_strlen(temp->value) + 2);
			ft_strlcpy(array[i], temp->key, ft_strlen(temp->key) + 1);
			ft_strlcat(array[i], "=", ft_strlen(array[i]) + 2);
			ft_strlcat(array[i], temp->value, ft_strlen(array[i])
				+ ft_strlen(temp->value) + 1);
			i++;
		}
		temp = temp->next;
	}
	array[i] = NULL;
}

int	count_env_variables_with_value(t_env *head)
{
	int		i;
	t_env	*temp;

	temp = head;
	i = 0;
	while (temp)
	{
		if (temp->value)
			i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_to_char_array(t_env *head)
{
	int		count;
	char	**result;

	count = count_env_variables_with_value(head);
	result = (char **)calloc((count + 1), sizeof(char *));
	assign_array(head, result);
	return (result);
}

int	update_env_value(t_env *head, const char *key, const char *new_value)
{
	t_env	*current;

	if (head == NULL || key == NULL || new_value == NULL)
		return (0);
	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(new_value);
			if (current->value == NULL)
				return (0);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	print_env_var_list(char **env)
{
	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
