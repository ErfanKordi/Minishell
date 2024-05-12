/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:38:50 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/22 14:46:45 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_cmd_list	t_cmd_list;

typedef enum e_redirect
{
	piping,
	infile,
	outfile,
	here_doc,
	append,
}							t_redirect;

typedef struct s_redir_list
{
	t_redirect				redirection;
	char					*file;
	struct s_redir_list		*next;
	struct s_redir_list		*prev;
}							t_redir_list;

typedef struct s_cmd_list
{
	char					**str;
	char					*cmd;
	char					*builtin;
	int						in;
	int						out;
	struct s_redir_list		*redirect_list;
	struct s_cmd_list		*next;
	struct s_cmd_list		*prev;
}							t_cmd_list;

// exe.c
int							prepare_and_execute(t_dt *minishell);
int							exe_built_in_cmds(char **args, t_env *envp_lst);
void						execute(t_cmdtable *table, t_dt *minishell,
								bool last_cmd);
int							ft_open(char *file, t_token_type rdr_type);
char						*ft_strgetbetween(const char *start,
								const char *end);
void						exe_parent_builtin_cmds(t_cmdtable *table,
								t_dt *minishell);
void						child(t_cmdtable *table, bool last_cmd,
								t_dt *minishell, int *fd);

// junction_box.c
void						exe_parent_builtin_cmds(t_cmdtable *table,
								t_dt *minishell);
int							exe_built_in_cmds(char **args, t_env *envp_lst);

// redirector.c
int							check_redirections(t_cmdtable *table, int *fd);

// builtin.c
void						execute_echo(char **args);
void						execute_cd(char **args, t_env *envp_list);
int							execute_pwd(void);
void						print_env_var_list(char **env);
void						set_env(t_env **head, char **key_val_str);
void						unset(t_env **head, char **var);

// exe_utils.c
void						ft_waitpid(t_dt *minishell, int nb_cmd);
char						*get_env(char **env, const char *name);
char						*cmd_path(char *cmd, char **env);
int							is_valid_env_name(const char *name);

// exe_utils1.c
void						free_arrayofstrings(char **array);
t_env						*create_env_var_node(char *str);
void						print_env_ascending(t_env *head);
int							count_env_variables(t_env *head);
// signals.c
void						block_signal(void);
void						setup_heredoc_signals(void);
void						setup_signals(void);
void						setup_child_signals(void);

// exe_utils2.c
char						**env_to_char_array(t_env *head);
char						*find_path(t_cmdtable *table, char **env,
								bool last_cmd);
int							update_env_value(t_env *head, const char *key,
								const char *new_value);
int							ft_strcmp(const char *s1, const char *s2);

// executor_utils.c
int							cmd_is_builtin(char *cmd);
void						free_double_char(char **stuff);
void						ft_close_fd(int fd);

void						free_cmd_list(t_cmd_list *cmd_list);

// builtin.c
int							execute_builtin(t_cmdtable *list, char *envp[]);
int							cmd_is_builtin(char *cmd);
int							ft_echo(char *message[]);
int							ft_env(t_cmdtable *list, char *envp[]);
int							ft_unsetenv(char *str, char *envp[]);

#endif