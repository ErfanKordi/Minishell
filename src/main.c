/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:23:11 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/23 09:38:10 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes all default values for main data structure.
 * @param argc ARGument Count. Number of input arguments.
 * @param argv ARGument Vector. String holding input arguments.
 * @param envp ENVironment Pointer. String with environment information.
 * @return pointer to main data structure.
*/
t_dt	*ini_dt(int argc, char *argv[], char *envp[])
{
	static t_dt		dt;

	if (argc != 1)
		ft_error(-1, &dt);
	(void)argv;
	dt = (t_dt){
		.exit = ini_exit(),
		.envp = envp,
		.envp_lst = init_env_var(envp),
		.input = NULL,
		.token = NULL,
		.fd_in = dup(STDIN_FILENO),
		.fd_out = dup(STDOUT_FILENO),
		.nrofpipes = 0
	};
	return (&dt);
}

/**
 * @brief Checks if input has something, skips all spaces and empty signs
 * @param dt main data structure
 * @return OK - input has something KO - input is empty
*/
t_ok	check_input(t_dt *dt)
{
	char		*temp;
	int			i;

	i = 0;
	temp = dt->input;
	while (ft_isspace(temp[i]) == 1)
		i++;
	if (temp[i] == '\0')
		return (KO);
	else
		return (OK);
}

/**
 * @brief Minishell loop
 * @param dt main data structure
 * @return
*/
void	ini_minishell(t_dt *dt)
{
	while (42)
	{
		setup_signals();
		dt->input = readline("Mini$hell ];> ");
		if (!dt->input)
			break ;
		if (check_input(dt) == OK)
		{
			add_history(dt->input);
			ft_token(dt);
			if (ft_parse(dt) == OK)
				prepare_and_execute(dt);
			free_token(dt);
			free_cmdtable(dt);
		}
		free(dt->input);
	}
}

// void ini_minishell(t_dt *dt)
// {
// 	while (42)
// 	{
// 		setup_signals();
// 		if (isatty(fileno(stdin)))
// 			dt->input = readline("");
// 		else
// 		{
// 			char *line;
// 			line = get_next_line(fileno(stdin));
// 			if (!line)
// 				break ;
// 			dt->input = ft_strtrim(line, "\n");
// 			free(line);
// 		}
// 		if (!dt->input)
// 			break ;
// 		if (check_input(dt) == OK)
// 		{
// 			add_history(dt->input);
// 			ft_token(dt);
// 			if (ft_parse(dt) == OK)
// 				prepare_and_execute(dt);
// 			free_token(dt);
// 			free_cmdtable(dt);
// 		}
// 		free(dt->input);
// 	}
// }

/**
 * @brief Hello World!
 * @param argc ARGument Count. Number of input arguments.
 * @param argv ARGument Vector. String holding input arguments.
 * @param envp ENVironment Pointer. String with environment information.
 * @return Exit code for terminal.
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_dt		*dt;

	dt = ini_dt(argc, argv, envp);
	ini_minishell(dt);
	free_env_var_list(dt->envp_lst);
	ft_exit(dt);
	return (*dt->exit);
}
