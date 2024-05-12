/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:47:32 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:14:04 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_(t_dt *dt, int i)
{
	if (dt->input[i] == '\'')
		i += token_ini(TEXT_SQUOTE,
				lenght(&dt->input[i], '\'', dt), &dt->input[i], dt);
	else if (dt->input[i] == '\"')
		i += token_ini(TEXT_DQUOTE,
				lenght(&dt->input[i], '\"', dt), &dt->input[i], dt);
	else
		i += token_ini(TEXT,
				lenght(&dt->input[i], ' ', dt), &dt->input[i], dt);
	return (i);
}

void	ft_token(t_dt *dt)
{
	int			i;

	i = 0;
	while (dt->input[i] != '\0')
	{
		if (ft_isspace(dt->input[i]))
			i++;
		else if (dt->input[i] == '>' && dt->input[i + 1] == '>')
			i += token_ini(REDIRECTION_OUT_APPEND, 2, &dt->input[i], dt);
		else if (dt->input[i] == '>')
			i += token_ini(REDIRECTION_OUT, 1, &dt->input[i], dt);
		else if (dt->input[i] == '<' && dt->input[i + 1] == '<')
			i += token_ini(REDIRECTION_IN_HEREDOC, 2, &dt->input[i], dt);
		else if (dt->input[i] == '<')
			i += token_ini(REDIRECTION_IN, 1, &dt->input[i], dt);
		else if (dt->input[i] == '|')
			i += token_ini(PIPE, 1, &dt->input[i], dt);
		else
			i = ft_token_(dt, i);
	}
}

int	lenght_(char *str, t_dt *dt, int i)
{
	if (str[i] != '\0')
		i++;
	if (str[i] == '\'')
		i += lenght(&str[i], '\'', dt);
	else if (str[i] == '\"')
		i += lenght(&str[i], '\"', dt);
	else if (str[i] != '>' && str[i] != '<' && str[i] != ' ')
		i += lenght(&str[i], ' ', dt);
	return (i);
}

int	lenght(char *str, char stop, t_dt *dt)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == stop)
			break ;
		if (stop == ' ' && str[i] == '\'')
			stop = '\'';
		if (stop == ' ' && str[i] == '\"')
			stop = '\"';
		if (stop == ' ' && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			break ;
	}
	if (stop == '\'' || stop == '\"')
		i = lenght_(str, dt, i);
	return (i);
}

int	token_ini(t_token_type type, int lenght, char *data, t_dt *dt)
{
	t_token	*temp;
	t_token	*last;

	temp = ft_calloc(1, sizeof(t_token));
	if (!temp)
		ft_error(-10, dt);
	temp->data = data;
	temp->lenght = lenght;
	temp->type = type;
	temp->next = NULL;
	if (!dt->token)
		dt->token = temp;
	else
	{
		last = dt->token;
		while (last->next)
			last = last->next;
		last->next = temp;
	}
	return (lenght);
}
