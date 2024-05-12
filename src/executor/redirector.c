/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:21:06 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/23 09:32:06 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a heredoc file
 * @param delimiter The delimiter of the heredoc (e.g., EOF)
 * @return File descriptor to the heredoc file on success,
	EXIT_FAILURE on failure
 */
int	create_heredoc(char *delimiter, t_cmdtable *table, int *fd_pipe)
{
	int		fd;
	char	*line;

	fd = ft_open("heredoc", REDIRECTION_IN_HEREDOC);
	dup2(table->fd_in, STDIN_FILENO);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = ft_open("heredoc", REDIRECTION_IN);
	if (fd == -1)
		return (EXIT_FAILURE);
	dup2(fd_pipe[0], STDIN_FILENO);
	return (EXIT_SUCCESS);
}

/**
 * @brief Sets the output file for a command table
 * @param table Pointer to the command table
 * @param file Name of the output file
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	set_outfile(t_cmdtable *table, char *file)
{
	table->fd_rdr_out = ft_open(file, REDIRECTION_OUT);
	if (table->fd_rdr_out < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Sets the input file for a command table
 * @param table Pointer to the command table
 * @param file Name of the input file
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	set_infile(t_cmdtable *table, char *file)
{
	int	exit_code;

	table->fd_rdr_in = ft_open(file, REDIRECTION_IN);
	if (table->fd_rdr_in < 0)
		return (EXIT_FAILURE);
	else
	{
		exit_code = EXIT_SUCCESS;
		if (dup2(table->fd_rdr_in, STDIN_FILENO) == -1)
			exit_code = EXIT_FAILURE;
		close(table->fd_rdr_in);
	}
	return (exit_code);
}

/**
 * @brief Appends the output to a file for a command table
 * @param file Name of the output file to append
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	append_file(t_cmdtable *table, char *file)
{
	table->fd_rdr_out = ft_open(file, REDIRECTION_OUT_APPEND);
	if (table->fd_rdr_out < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Checks and applies redirections for a command table
 * @param table Pointer to the command table
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	check_redirections(t_cmdtable *table, int *fd_pipe)
{
	int	i;
	int	exit_status;

	(void)fd_pipe;
	i = 0;
	if (table->rdr_nb)
	{
		while (i < table->rdr_nb)
		{
			if (table->rdr[i].type == REDIRECTION_IN)
				exit_status = set_infile(table, table->rdr[i].data);
			else if (table->rdr[i].type == REDIRECTION_OUT)
				exit_status = set_outfile(table, table->rdr[i].data);
			else if (table->rdr[i].type == REDIRECTION_OUT_APPEND)
				exit_status = append_file(table, table->rdr[i].data);
			if (exit_status)
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
