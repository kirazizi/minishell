/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:43 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 13:04:27 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/////////////////////////// includes ///////////////////////////
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>

/////////////////////////// colors /////////////////////////////
# define MINI "$> minishell "
# define RED "\001\033[1;31m\002"
# define DEFAULT "\001\033[0;37m\002"

# define IN_SINGLE_QUOTES 1 
# define IN_DOUBLE_QUOTES 2
# define GENERAL_STATE    4

/////////////////////////// structs ////////////////////////////
typedef enum use
{
	PIPE = 1,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	SPACE_,
	DQ,
	SQ,
	VAR,
	COMOND,
}t_type;

typedef struct s_token
{
	t_type				type;
	char				*data;
	char				*value;
	char				is_input;
	struct s_token		*prev;
	struct s_token		*next;

}t_token;

typedef struct s_exc
{
	char			**arg;
	int				type;
	int				fdin;
	int				fdout;
	int				tmpdout;
	int				tmpdin;
	struct s_exc	*next;

}t_exc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}t_env;

typedef struct s_exp
{
	char			*name;
	char			*value;
	struct s_exp	*next;

}t_exp;

typedef struct s_leaks
{
	void			*delete;
	struct s_leaks	*next;

}t_leaks;

typedef struct s_var
{
	int		inp;
	int		outp;
	int		fd[2];

	int		is_vis;
	int		flg_exit;
	int		size;

	int		exit_status;
	int		status;

	int		heredoc;
	t_leaks	*delete;

}t_var;

/////////////////////////// global var ///////////////////////////
extern t_var	g_status;

//////////////////////////// exec ////////////////////////////////
long long	ft_atol(const char *str, t_var *var);
char		*ft_strfill(char *s1, char *s2, int n);
char		**ft_split(char *str);
char		**split_path(char *str);
t_exc		*ft_lstnew(char **argm, int in, int out);
int			size_exc(t_exc *lst);
int			ft_lstsize(t_env *lst);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
void		ft_env(t_env **myenv, char **env, t_var *var);
char		*ft_strncpy(char *s1, char *s2, size_t len);
void		ft_lstadd_back(t_env **lst, t_env *new);
void		ft_lstadd_back2(t_exc **lst, t_exc *new);
char		*ft_cmd(t_env *env, char **arg);
char		**ft_list_to_char(t_env *myenv);
char		**split_pipe(char *str);
char		**split_space(char *str);
void		ft_exec(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp);
void		ft_execve(t_env *myenv, t_exc *cmd);
void		ft_exec_mult(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp);
void		ft_print_env(t_env *myenv, t_var var);
char		*get_myenv(t_env *myenv, char *name);
void		ft_cd(t_exc *cmd, t_env *myenv, t_exp *myexp);
void		ft_pwd(t_env *myenv);
char		*ft_get_pwd(t_env *myenv);
void		ft_echo(t_exc *cmd);
void		cmd_export(t_exc *cmd, t_exp **expt, t_env **myenv, t_var var);
void		sort_list_exp(t_exp *export);
char		*get_keylen(char *env, char *spr);
void		ft_lstadd_back_exprt(t_exp **lst, t_exp *new);
t_exp		*creat_list_expt(char *name, char *value);
t_env		*creat_list(char *key, char *value);
void		ft_list_export(t_env *myenv, t_exp **myexp);
void		ft_unset(t_exc *cmd, t_env **myenv, t_exp **myexp);
int			is_alpha(int c);
int			is_digit(int i);
int			ft_atoi(const char *str);
void		ft_exit(t_exc *cmd, t_var *var);
void		ft_signal(void);
void		ft_catch_signal(void);
void		ft_lstclear2(t_token *lst);
int			is_builtin(t_exc *node);
void		execute_builtin(t_exc *cmd, t_env **myenv, t_var *var,
				t_exp **myexp);
char		*ft_itoa(int n);
void		update_shell_level(t_env **myenv);
void		ft_wait_exit(t_exc *cmd, t_var *var);
void		update_exit_status(t_env **myenv);
void		ft_printf(int fd, char *str, char *err);
char		*ft_strchr(const char *str, int c);
void		update_myenv(t_env *myenv, char *var, char *value);
void		update_myexp(t_exp *myexp, char *var, char *value);
char		*get_myenv(t_env *myenv, char *name);
void		ft_cd_part1(t_exc *cmd, t_env *myenv, t_exp *myexp, char *current);
void		ft_cd_part2(t_exc *cmd, t_env *myenv, t_exp *myexp, char *current);
void		ft_cd_part3(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current);
void		ft_cd_part4(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current);
void		ft_cd_part5(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current);
void		ft_unsetenv(t_env **myenv, char *name);
void		ft_unsetexp(t_exp **myexp, char *name);
void		fill_myenv_auto(t_env **myenv, char **env, t_var *var);
void		fill_myenv_manual(t_env **myenv, t_var *var, char *key,
				char *value);
int			check_is_directory(char *arg);
int			check_is_executabe(char *arg);
int			check_is_slash(char *arg);
char		*remove_qouats(char *word);
void		singl_built(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp);
void		singl_comand(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp);
void		mult_command(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp);
void		syntax_error(char *input);
int			syntax_quote(char *input);
void		replace_export_list(char *name, char *value, t_exp **myexp_head);
void		update_export_list(char *name, char *value, t_exp **myexp_head);
void		replace_env_list(char *name, char *value, t_env **myenv_head);
void		update_env_list(char *name, char *value, t_env **myenv_head);
void		ft_print_export(t_exp *exp, t_var var);
int			is_var(char *arg);
int			size_arg(char **arg);
int			check_export(char *str);
int			parsing_export(char *arg);
char		*allocat_new_name(char *name);
char		*join_quates(char *value, char *new_value);
void		add_back(t_exp **myexp, char *name, char *value);
void		sort_list_exp(t_exp *export);
void		error_pars(char *str, int *i);
char		**split_path(char *str);
char		**ft_alloc_path(char **out, char *str);
void		herdoc_signal_handler(int sig);
void		ft_prompt(t_env **myenv, t_exp **myexp, t_var *var);
void		execut_main(t_exc *cmd, t_env **myenv, t_var var, t_exp **myexp);
int			my_here_doc(t_token **token, t_env *env);
char		*expand_heredoc(char *line, t_env *env);
void		remove_redrc_qts(char *word);

////////////////////// free //////////////////////////////
t_leaks		*ft_delete_add(void *delete);
void		ft_delete_back(t_leaks **lst, t_leaks *new);
void		ft_lstdelete(t_leaks **lst);
void		free_end(t_exc *cmd, t_token *token, char *input);

////////////////////// parsing //////////////////////////
void		print_token(t_token *token);
void		ft_token_add(t_token **tokens, char *res);
int			ft_initialize(char *tmp);
int			ft_strcmp(char *s1, char *s2);
int			check_syntax(char *input);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strl(const char *str);
void		ft_check_split(t_token **token, char **input);
int			check_syntax_list(t_token *token);
char		*ft_strncpy(char *s1, char *s2, size_t len);
void		ft_lstadd_back(t_env **lst, t_env *new);
char		*ft_strdup(const char *s);
size_t		ft_strlen_long(const char *s);
char		*replace_env(t_env *env, char *input);
char		*ft_strjoinn(const char *s1, const char *s2);
void		ft_check_var(t_token **token, t_env *env);
int			ft_check(t_token **token, char *tmp, t_env *env, t_exc **cmd);
char		*replace_env(t_env *env, char *input);
char		**ft_sp(char const *s, char c);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
int			checkisvarchar(char str);
int			ft_len(char *str);
void		join_words(t_token **token, t_exc **cmd);
int			redirection_input(t_token **token, t_exc **cmd);
int			redirection_output(t_token **tmp, t_exc **cmd);
int			redirection_append(t_token **token, t_exc **cmd);
void		redirection_heredoc(t_token **token, t_exc **cmd);
char		**ft_split_use(char const *s, char c);
void		ft_lstclear(t_exc **lst);
void		printT(t_exc *cmd);
void		printToD(char **str);
void		redirection_heredoc(t_token **token, t_exc **cmd);
void		ft_lstclear(t_exc **lst);
void		ft_lstclear2(t_token *lst);
void		make_prev(t_token *token);
void		thecheck_splite(t_token **token, char *input);
void		remov_space(char *str);
char		*ft_check_e(t_token **token, t_env *env);
void		removewhitespacenodes(t_token *head);
char		*removedoublesinglequotes(char *p);
void		removed_q_suit(t_exc **token);
char		*ft_strtrim(char const *s1, char const *set);
char		*get_env_from_data(char *input);
int			check_syntax_end(char *input);
char		*ft_strndup(const char *s, size_t n);
void		check_qoutes(char c, int *in_quotes, int *in_quotes_s);
void		ft_her_appa(int *i, char **input, t_token **token);
void		suit_ex_quotes(int *i, t_token **token, char **output);
void		ft_in_out(int *i, char **input, t_token **token);
void		suit_end_ex(char **output, int *i, t_token **token);
void		suit_check_e(int *i, t_token **token, t_env **env, char **output);
char		*get_env_from_data(char *input);
char		*get_env_var(char *word, t_env *env);
char		*ft_check_e(t_token **token, t_env *env);
int			redirection(t_token **token, t_exc **cmd, t_env *env);
int			red_2_out(t_token **tmp, t_exc **use, char **word, t_token **token);
int			red_2_in(t_token **tmp, t_exc **use, char **word, t_token **token);
int			red_2_appand(t_token **tmp, t_exc **use, char **word,
				t_token **token);
void		ft_init_words(int *i, int *inside_word, int *nw, int *in_quotes);
void		suit_words(int *inside_word, int *nw);
void		inti_ex(int *i, int *j, int *in_quotes);
int			check_syntax_list(t_token *token);

#endif