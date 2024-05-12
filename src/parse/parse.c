/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:35 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:15:51 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ok	create_cmdtable(t_dt *dt)
{
	int		i;
	t_token	*temp;

	temp = dt->token;
	dt->nrofpipes = how_many(PIPE, temp);
	dt->cmdtable = (t_cmdtable **)ft_calloc(dt->nrofpipes + 2,
			sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		return (ft_error(-10, dt));
	i = 0;
	while (temp != NULL && i <= dt->nrofpipes)
	{
		dt->cmdtable[i] = ft_calloc(1, sizeof(t_cmdtable));
		if (!dt->cmdtable[i])
			return (ft_error(-10, dt));
		if (fill_cmdtable(dt->cmdtable[i], temp, dt) != OK)
			return (KO);
		while (temp && temp->type != PIPE)
			temp = temp->next;
		i++;
		if (temp)
			temp = temp->next;
	}
	return (OK);
}

t_ok	fill_cmdtable_(t_cmdtable *cmdtab, t_token *temp, t_dt *dt)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type > 4)
		{
			cmdtab->cmd[i[0]] = ft_expander(temp->data, temp->lenght, dt);
			if (cmdtab->cmd[i[0]] == NULL)
				return (ft_error(-11, dt));
			i[0]++;
		}
		else
		{
			cmdtab->rdr[i[1]].type = temp->type;
			temp = temp->next;
			cmdtab->rdr[i[1]].data = ft_expander(temp->data, temp->lenght, dt);
			if (cmdtab->rdr[i[1]].data == NULL)
				return (ft_error(-11, dt));
			i[1]++;
		}
		temp = temp->next;
	}
	return (OK);
}

t_ok	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	cmdtable->cmd_nb = how_many(TEXT, token)
		+ how_many(TEXT_SQUOTE, token)
		+ how_many(TEXT_DQUOTE, token);
	cmdtable->rdr_nb = how_many(REDIRECTION_IN, token)
		+ how_many(REDIRECTION_OUT, token)
		+ how_many(REDIRECTION_IN_HEREDOC, token)
		+ how_many(REDIRECTION_OUT_APPEND, token);
	cmdtable->fd_in = dt->fd_in;
	cmdtable->fd_out = dt->fd_out;
	cmdtable->cmd = (char **)ft_calloc(cmdtable->cmd_nb + 1, sizeof(char *));
	cmdtable->rdr = (t_rdr *)ft_calloc(cmdtable->rdr_nb + 1, sizeof(t_rdr));
	if (!cmdtable->cmd || !cmdtable->rdr)
		return (ft_error(-10, dt));
	if (fill_cmdtable_(cmdtable, token, dt) != OK)
		return (KO);
	return (OK);
}

t_ok	ft_parse(t_dt *dt)
{
	t_token	*temp;

	temp = dt->token;
	if (temp && temp->type == PIPE)
		return (ft_error(-12, dt));
	while (temp)
	{
		if (temp->type < 5 && !temp->next)
			return (ft_error(-13, dt));
		if (temp->type < 4 && temp->next->type < 5)
			return (ft_error(-14, dt));
		temp = temp->next;
	}
	if (create_cmdtable(dt) != OK)
		return (KO);
	return (OK);
}
