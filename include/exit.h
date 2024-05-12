/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:35 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:04:49 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/*
	error.c
*/

/**
 * @brief Prints message of coresponding code and returns KO
 * @param code ID of error message -1 to -9 are pre init errors.
 * @param dt main data structure
 * @return KO
 */
t_ok	ft_error(int code, t_dt *dt);

/*
	exit_code.c
*/

/**
 * @brief Creates static variable for exit code
 * @param -
 * @return adress of current Exit Code for terminal.
 */
int		*ini_exit(void);
/**
 * @brief An exit structure
 * @param dt Main program data structure
 * @return
 */
void	ft_exit(t_dt *dt);
/**
 * @brief Changes programs exit code
 * @param code new exit code
 * @return
 */
void	exit_code(int code);

/*
	exit.c
*/

/**
 * @brief kills everything and closes pipes
 * @return
 */
void	exit_all_minishell(void);
/**
 * @brief An exit structure
 * @param args 
 * @param minishell Main program data structure
 * @return
 */
void	exit_shell(char **args, t_dt *minishell);

#endif
