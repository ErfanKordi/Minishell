/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:29:23 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/22 14:47:18 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the value of an existing environment variable
 * @param node Pointer to the node representing the environment variable
 * @param value New value to set
 * @return 1 on success, 0 on failure
 */
void	update_env(t_env *node, char *value)
{
	if (node->value)
		free(node->value);
	if (*value != '\0')
		node->value = ft_strdup(value);
	else
		node->value = NULL;
}

/**
 * @brief Adds a new environment variable node to the linked list
 * @param head Pointer to the head of the environment variable linked list
 * @param new_node Node to add to the linked list
 */
void	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	current = *head;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

int	characters_before_eq(char *str)
{
	int		i;
	char	q;

	q = ' ';
	i = 0;
	while (*str != '=')
	{
		if (*str == '\0')
			break ;
		if (q == ' ' && *str == '\'')
			q = '\'';
		else if (q == ' ' && *str == '\"')
			q = '\"';
		else if (q == '\'' && *str == '\'')
			q = ' ';
		else if (q == '\"' && *str == '\"')
			q = ' ';
		else
			i++;
		str++;
	}
	return (i);
}

void	prepare_and_add(t_env **head, char *key_val_str)
{
	t_env	*current;
	t_env	*new_node;
	char	*eq_sign_pos;

	new_node = NULL;
	eq_sign_pos = ft_strchr(key_val_str, '=');
	current = *head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key_val_str, ft_strlen(current->key))
			&& ft_strlen(current->key) == characters_before_eq(key_val_str))
		{
			if (eq_sign_pos)
				update_env(current, eq_sign_pos + 1);
			return ;
		}
		current = current->next;
	}
	new_node = create_env_var_node(key_val_str);
	add_env_node(head, new_node);
}

/**
 * @brief Sets or updates an environment variable
 * @param head Pointer to the head of the environment variable linked list

	* @param key_val_str String containing the key-value
			pair of the environment variable
 * @return 1 on success, 0 on failure
 */
void	set_env(t_env **head, char **key_val_str)
{
	int	i;

	i = 1;
	if (!key_val_str[1])
	{
		print_env_ascending(*head);
		return ;
	}
	while (key_val_str[i])
	{
		if (!is_valid_env_name(key_val_str[i]))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			exit_code(1);
		}
		else
		{
			prepare_and_add(head, key_val_str[i]);
			exit_code(0);
		}
		i++;
	}
}
