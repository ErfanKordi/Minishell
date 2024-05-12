/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:22:48 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 10:22:49 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// int		ft_echo(char *message[]);
int		ft_env(t_cmdtable *list, char *envp[]);
// int		ft_exit_changename(t_cmd_list *list);
// int		ft_export(t_cmd_list *list, char *envp[]);
// int		ft_pwd(t_cmd_list *list, char *envp[]);
// int		ft_unset(t_cmd_list *list, char *envp[]);
// int		ft_unsetenv(char *str, char *envp[]);
void	executor(t_cmdtable *list, char *envp[]);

// char	*get_path(t_cmd_list *list, char *envp[]);
// void	update_envp(char *envp[], char *variable, char *value);
// void	ft_cd(t_cmd_list *list, char *envp[]);

#endif
