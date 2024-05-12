/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:28:03 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:12:43 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/*
	env.c
*/

/**
 * @brief Gets the word inside of the quotes
 * @param start pointer to the word start
 * @param end
 * @return Pointer to 
 */
char	*ft_strgetbetween(const char *start, const char *end);
/**
 * @brief Creates a new node for an environment variable
 * @param str String containing the key-value pair of the environment variable
 * @return Pointer to the newly created node on success, NULL on failure
 */
t_env	*create_env_var_node(char *str);
/**
 * @brief Frees memory of environment list
 * @param head First element of env list
 * @return 
 */
void	free_env_var_list(t_env *head);
/**
 * @brief Creates environment variable list by coping system envp
 * @param envp Pointer to original envp from the system
 * @return 
 */
t_env	*init_env_var(char *envp[]);

/*
	token.c
*/

/**
 * @brief Tokenization - Turning input into tokens
 * @param dt main data structure
 * @return
 */
void	ft_token(t_dt *dt);
/**
 * @brief Calculate the lenght of string for token
 * @param str Pointer to first character in input for token
 * @param stop Stop character that closes token
 * @param dt main data structure
 * @return lenght of data
 */
int		lenght(char *str, char stop, t_dt *dt);
/**
 * @brief Create a new token and add it at the end of the token list
 * @param type Type of a token
 * @param lenght lenght of data
 * @param data content of input assosiated with token
 * @param dt main data structure
 * @return lenght of data
 */
int		token_ini(t_token_type type, int lenght, char *data, t_dt *dt);
/**
 * @brief Memory free of all tokens
 * @param dt main data structure
 * @return
 */
void	free_token(t_dt *dt);
/**
 * @brief Duplicates string to the size of n. Null terminates after n characters.
 * @param s string to duplicate
 * @param n size to duplicate 
 * @return pointer to new string
 */
char	*ft_strndup(const char *s, size_t n);
/**
 * @brief Creates a nullterminated string with just one character
 * @param c character to put in string
 * @return pointer to newly allocated string
 */
char	*ft_onecharstring(char c);

/*
	parse.c
*/

/**
 * @brief Checks the tokens and creates command table
 * @param dt main data structure
 * @return OK - command table ready for execution 
 * KO - tokens are not valid for execution
 */
t_ok	ft_parse(t_dt *dt);
/**
 * @brief fills the command table with commands and redirections
 * @param cmdtable pointer to a pipe section in command table
 * @param token pointer to token to that section
 * @param dt main data structure
 * @return 
 */
t_ok	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt);
/**
 * @brief Create an command table of height of number of pipes.
 * @param dt main data structure
 * @return OK - command table created KO - tokens are not valid for execution
 */
t_ok	create_cmdtable(t_dt *dt);
/**
 * @brief How many tokens are ther`e in token list.
 *  If PIPE - counts pipes in whole list.
 *  If TEXT - counts elements for cmd between pipes.
 * 	If REDIRECTION - counts number of redirections between pipes.
 * @param token token to be counted
 * @param start token from which to start the count
 * @return number of pipes or tokens between pipes
 */
int		how_many(t_token_type token, t_token *start);
/**
 * @brief Memory free of the command table
 * @param dt main data structure
 * @return 
 */
void	free_cmdtable(t_dt *dt);

/*
	expander.c
*/

/**
 * @brief Checks environment list for key and returns a string with value
 * @param check variable name/key to check
 * @param i lenght of name/key to check
 * @param dt main data structure
 * @return pointer to newly allocated string with value
 */
char	*check_env(char *check, int i, t_dt *dt);
/**
 * @brief Expands the environment variables into values from iput string
 * @param s string to expand
 * @param size lenght of the string to expand
 * @param dt main data structure
 * @return poitner to newly allocated string after expansion
 */
char	*ft_expander(char *s, int size, t_dt *dt);

#endif
