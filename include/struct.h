/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:07:06 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:06:40 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

/**
 * @brief Type of a token 0-3 Redirection, 4 pipe, 5-7 text
 * @param REDIRECTION_IN <
 * @param REDIRECTION_IN_HEREDOC <<
 * @param REDIRECTION_OUT >
 * @param REDIRECTION_OUT_APPEND >>
 * @param PIPE |
 * @param TEXT ...
 * @param TEXT_SQUOTE '...'
 * @param TEST_DQUOTE  "..."
 */
typedef enum e_token_type
{
	REDIRECTION_IN,
	REDIRECTION_IN_HEREDOC,
	REDIRECTION_OUT,
	REDIRECTION_OUT_APPEND,
	PIPE,
	TEXT,
	TEXT_SQUOTE,
	TEXT_DQUOTE
}					t_token_type;

/**
 * @brief Simple boolean definition for checks and returns
 * @param OK Positive outcome, value = 0
 * @param KO Negative outcome, value = 1
 */
typedef enum e_ok
{
	OK,
	KO
}			t_ok;

/**
 * @brief Token list structure
 * @param type Type of a token
 * @param data content of input assosiated with token
 * @param lenght lenght of data
 * @param next pointer to next node, NULL = end of list
 */
typedef struct s_token
{
	t_token_type	type;
	char			*data;
	int				lenght;
	struct s_token	*next;
}					t_token;

/**
 * @brief Redirection information
 * @param type Type of redirection
 * @param data Redirection destination or deliminator for heredoc
 */
typedef struct s_rdr
{
	t_token_type	type;
	char			*data;
}					t_rdr;

/**
 * @brief Command Table for Executor
 * @param cmd Array of command with options
 * @param cmd_nb Number of command elements (cmd + options)
 * @param rdr Array of redirections
 * @param rdr_nb Number of redirections (in and out)
 * @param fd_in input file, default - standard input
 * @param fd_out output file, default - standard output
 * @param fd_rdr_in input redirection file descriptor
 * @param fd_rdr_out output redirection file descriptor
 */
typedef struct t_cmdtable
{
	char			**cmd;
	int				cmd_nb;
	t_rdr			*rdr;
	int				rdr_nb;
	int				fd_in;
	int				fd_out;
	int				fd_rdr_in;
	int				fd_rdr_out;
}					t_cmdtable;

/**
 * @brief Environment list structure
 * @param key env variable name
 * @param value env variable value
 * @param next next node in the list. NULL = end of list
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/**
 * @brief Main data structure that holds all information needed for the program.
 * @param exit exit code of main process
 * @param envp ENVironment Pointer. String with environment information.
 * @param input pointer to minishells input
 * @param token linked list of tokens header
 * @param nrofpipes number of pipes
 */
typedef struct s_dt
{
	int				*exit;
	char			**envp;
	t_env			*envp_lst;
	char			*input;
	t_token			*token;
	t_cmdtable		**cmdtable;
	int				nrofpipes;
	int				fd_in;
	int				fd_out;
}					t_dt;

#endif