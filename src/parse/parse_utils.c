/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:25:35 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 11:28:17 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many(t_token_type token, t_token *start)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = start;
	while (temp && (token == PIPE || temp->type != PIPE))
	{
		if (token > 4 && temp->type < 4)
			temp = temp->next;
		else if (temp->type == token)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	free_cmdtable_(t_dt *dt, int i)
{
	int	j;

	j = 0;
	while (dt->cmdtable[i]->rdr[j].data)
	{
		free(dt->cmdtable[i]->rdr[j].data);
		j++;
	}
	free(dt->cmdtable[i]->rdr);
	j = 0;
	while (dt->cmdtable[i]->cmd[j])
	{
		free(dt->cmdtable[i]->cmd[j]);
		j++;
	}
	free(dt->cmdtable[i]->cmd);
	free(dt->cmdtable[i]);
}

void	free_cmdtable(t_dt *dt)
{
	int	i;

	if (!dt->cmdtable)
		return ;
	i = 0;
	while (dt->cmdtable[i])
	{
		free_cmdtable_(dt, i);
		i++;
	}
	free(dt->cmdtable);
	dt->cmdtable = NULL;
}
