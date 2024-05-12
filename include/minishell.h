/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:28:06 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/22 17:44:56 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "struct.h"
# include "parse.h"
# include "builtin.h"
# include "executor.h"
# include "utils.h"
# include "exit.h"

t_env	*create_env_var_node(char *str);
void	set_heredoc(t_cmdtable *table, int *fd);
int		create_heredoc(char *delimiter, t_cmdtable *table, int *fd_pipe);
int		set_infile(t_cmdtable *table, char *file);

# define FALSE 0
# define TRUE 1

#endif
