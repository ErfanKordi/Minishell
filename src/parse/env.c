/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:12:16 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 10:32:30 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strgetbetween(const char *start, const char *end)
{
	char	*word;
	size_t	i;

	if ((*start == '\'' && *end == '\'') || (*start == '"' && *end == '"'))
	{
		start++;
		end--;
	}
	word = (char *)malloc((end - start + 2) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (*start && start <= end)
	{
		word[i] = *start;
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

t_env	*create_env_var_node_(char *str, t_env	*node, char	*eq_sign_pos)
{
	node->next = NULL;
	node->key = ft_strgetbetween(str, eq_sign_pos - 1);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(eq_sign_pos + 1);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	return (node);
}

t_env	*create_env_var_node(char *str)
{
	char	*eq_sign_pos;
	t_env	*node;

	eq_sign_pos = ft_strchr(str, '=');
	if (!eq_sign_pos)
	{
		node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!node)
			return (NULL);
		node->next = NULL;
		node->key = ft_strdup(str);
		if (!node->key)
			return (free(node), NULL);
		node->value = NULL;
		return (node);
	}
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	return (create_env_var_node_(str, node, eq_sign_pos));
}

void	free_env_var_list(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_env	*init_env_var(char *envp[])
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i++] != NULL)
	{
		new_node = create_env_var_node(envp[i - 1]);
		if (new_node == NULL)
			return (free_env_var_list(head), NULL);
		if (tail == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	return (head);
}
