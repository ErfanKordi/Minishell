/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:23:32 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/20 14:57:03 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env *head)
{
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int	count_env_variables(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	sort_env_linked_list(t_env *head, int count)
{
	int		i;
	t_env	*current;
	t_env	*next;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		current = head;
		next = head->next;
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(current->key, next->key) > 0)
				swap_nodes(current, next);
			current = next;
			next = next->next;
			j++;
		}
		i++;
	}
}

void	print_env_ascending(t_env *head)
{
	int		i;
	int		count;
	t_env	*current;

	current = head;
	count = count_env_variables(current);
	sort_env_linked_list(current, count);
	i = 0;
	while (i < count)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
		i++;
	}
}
