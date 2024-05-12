/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:26 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:08:12 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ini_exit(void)
{
	static int	exit = 0;

	return (&exit);
}

void	exit_code(int code)
{
	int	*exit;

	exit = ini_exit();
	*exit = code;
}

void	ft_exit(t_dt *dt)
{
	exit(*dt->exit);
}
