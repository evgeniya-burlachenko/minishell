/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:18:36 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 13:29:24 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "./z_array.h"
# include "./errors.h"

# define PROMPT			"〰minishell: "
# define PROMPTHERDOC	"〰>: "
# define PIPESTATUS		"PIPESTATUSSpeltKelly"
# define PROMPTEXIT		"\033[1A〰minishell: exit\n"

int		runner(char *read_buff, t_z_array *params, t_z_array *envir);

int		builtins_cd(t_z_array *argv, t_z_array *envp);
int		builtins_echo(t_z_array *argv, t_z_array *envp);
int		builtins_env(t_z_array *argv, t_z_array *envp);
int		builtins_exit(t_z_array *argv, t_z_array *envp);
int		builtins_export(t_z_array *argv, t_z_array *envp);
int		builtins_pwd(t_z_array *argv, t_z_array *envp);
int		builtins_unset(t_z_array *argv, t_z_array *envp);
int		try_to_execve(t_z_array *params, t_z_array *env);

void	utls_print_error(char *str);
void	utls_print_errno(char *ref, char *obj, char *subj);
int		utls_print_e_return(char *ref, char *obj, char *subj, int code);
int		utls_print_bash_errors(char *str, int status);
int		utls_ft_strcmp(const char *s1, const char *s2);
void	utls_ft_free_split_array(char **arr);
void	utls_ft_memset(char **str, char c);
void	utls_ft_set(char **str, char *new_value);
void	*utls_ft_alloc(size_t size);
void	utls_ft_4free(void *p1, void *p2, void *p3, void *p4);
int		utls_ft_is_space(char c);
int		utls_ft_ifkey(char c);
char	*ft_strrchr_2(const char *s, int c);
char	*utls_keys_get(char *str);
int		utls_keys_validate(char *key);
char	*utls_keys_value_get(char *key, t_z_array *envp);
char	*utls_keys_create_string(char *key, char *value);
int		utls_keys_pipestatus(int status, t_z_array *envp);
void	utls_redirect_set_fd(int fd_str_inp, int fd_str_out, int set_reset);
int		utls_redirect_open_files(t_z_array *redic, int *i, int *o);
void	utls_redirect_close_files(int *i, int *o);
int		utls_redirect_is_ctrl_sqnce(char *str);
void	utls_redirect_dup2(int a, int b);
void	utls_redirect_dup2_and_close(int a, int b);
int		utls_redirect_dup(int a);
void	utls_redirect_dup_std_backup(int *f0, int *f1);
int		utls_redirect_files_o(int *i, int *o, char *f);
int		utls_redirect_files_oapp(int *i, int *o, char *f);
int		utls_redirect_files_i(int *i, int *o, char *f);

void	utls_export_is_plus(char **str, int *flag);
int		utls_export_setvar(char *key, char *value, t_z_array *envp);
int		utls_export_set_only_key(char *key, t_z_array *envp);
int		utls_export_remove_old(t_z_array *envp, char *str);
void	utls_test_print_array(t_z_array *arr);
void	utls_export_set_underscore(t_z_array *params, t_z_array *env);

int		utls_preparser_tests_single_quote(char *str);
int		utls_preparser_tests_pipes(char *str);
int		utls_preparser_tests_start_pipe(char *str);
int		utls_preparser_tests_redic(char *str);
int		utls_preparser_tests_dots(char *str);
char	*utls_parser_str3join(char *start, char *inside, char *finish);

char	*set_env_inside_string(char *s, t_z_array *env, int *j, int *nl);

int		utls_others_is_directory(const char *path);
int		utls_others_error_handling(int status, char *str);
int		utls_others_is_whith_path(char *command);

int		ft_preparser(char *str);
char	*parser(char *str, t_z_array *params, t_z_array *env);
char	*ft_dollar(char *str, int *i, t_z_array *env, int is_qu);
char	*ft_tilda(char *str, int *i, t_z_array *env);
char	*ft_gap2(char *str, int *i, t_z_array *env);
char	*ft_gap(char *str, int *i);
char	*ft_redic1(char *str, int *i, t_z_array *params);
char	*ft_redic2(char *str, int *i, t_z_array *params);
void	ft_heredoc(int *i, char *stop_word);

void	signals_init(void);
void	signals_pause(void);
void	signals_reset(void);
void	signals_heredoc(void);

void	fork_errors_fork(void);
void	fork_errors_waitpid(void);
void	fork_errors_pipe(void);

void	rl_replace_line(const char *text, int clear_undo);
void	ft_clean(char *ptr);
char	*ft_join_or_dup(char *start, char *end);
int		is_control_char(char c);
char	*ft_substr_or_empty(char *str, int start_index, int count);

#endif
