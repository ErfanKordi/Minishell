/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:47:35 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:30:21 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char *check, int i, t_dt *dt)
{
	t_env	*temp;
	char	*ret;

	temp = dt->envp_lst;
	ret = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, check, i) == 0 && temp->key[i] == '\0')
		{
			if (temp->value)
				ret = ft_strdup(temp->value);
			else
				ret = NULL;
			break ;
		}
		temp = temp->next;
	}
	return (ret);
}

char	*expand(char q, char *start, t_dt *dt)
{
	int		i;
	char	*temp;
	char	*exp;

	i = 0;
	if (start[i] == '?' && q != '\'')
		return (ft_itoa(*ini_exit()));
	if (start[i] == '?' && q == '\'')
		return (ft_strdup("$?"));
	while (start[i] == '_' || ft_isalnum(start[i]) == 1)
		i++;
	if (i == 0 && (q != ' ' || start[i] == ' ' || start[i] == '\0'))
		return (ft_strdup("$"));
	if (i == 0)
		return (ft_calloc(1, sizeof(char)));
	temp = ft_calloc(i + 1, sizeof(char));
	if (q == '\'')
	{
		ft_strlcpy(temp, &start[-1], i + 2);
		return (temp);
	}
	ft_strlcpy(temp, start, i + 1);
	exp = check_env(temp, i, dt);
	free(temp);
	return (exp);
}

char	*update_string(char *str, char *update)
{
	char	*temp;

	if (update)
		temp = ft_strjoin(str, update);
	else
		temp = ft_strjoin(str, "");
	if (str)
		free(str);
	if (update)
		free(update);
	return (temp);
}

int	ft_expander_(char *str, int i)
{
	if (str[i + 1] == '?')
		i++;
	else
	{
		while (str[i + 1] == '_' || ft_isalnum(str[i + 1]) == 1)
			i++;
	}
	return (i);
}

char	*ft_expander(char *s, int size, t_dt *dt)
{
	char	q;
	char	*temp;
	int		i;

	q = ' ';
	i = 0;
	temp = ft_calloc(1, sizeof(char));
	while (i < size)
	{
		if (q == ' ' && (s[i] == '\'' || s[i] == '\"'))
			q = s[i];
		else if ((q == '\'' && s[i] == '\'') || (q == '\"' && s[i] == '\"'))
			q = ' ';
		else if (s[i] == '$')
		{
			temp = update_string(temp, expand(q, &s[i + 1], dt));
			i = ft_expander_(s, i);
		}
		else
			temp = update_string(temp, ft_onecharstring(s[i]));
		i++;
	}
	if (q != ' ')
		return (NULL);
	return (temp);
}
