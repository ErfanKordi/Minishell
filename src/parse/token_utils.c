/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:03:44 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 15:55:53 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_dt *dt)
{
	t_token		*temp;
	t_token		*f_temp;

	temp = dt->token;
	while (temp)
	{
		f_temp = temp;
		temp = temp->next;
		if (f_temp)
			free(f_temp);
	}
	dt->token = NULL;
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;

	result = malloc(n + 1);
	if (result)
	{
		strncpy(result, s, n);
		result[n] = '\0';
	}
	return (result);
}

char	*ft_onecharstring(char c)
{
	char		*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	return (str);
}
