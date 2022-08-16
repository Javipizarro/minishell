/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:38:01 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/16 19:03:24 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <termios.h>
#include <readline/history.h>
#include "libft/libft.h"

# include <signal.h>
# include <fcntl.h>
# include <errno.h>


unsigned char	g_exit_status;

#define SHNAME "JaviShell"

#define MAX_PATH 1024	//	1024 is the max path length for MacOS, 4096 for Linux
#define MAX_NAME 255	//
#define MAX_LINE 4096	/*	In canonical mode:
						**	The maximum line length is 4096 chars (including the
						**	terminating newline character); lines longer than 4096 chars
						**	are truncated.  After 4095 characters, input processing (e.g.,
						**	ISIG and ECHO* processing) continues, but any input data after
						**	4095 characters up to (but not including) any terminating
						**	newline is discarded.  This ensures that the terminal can
						**	always receive more input until at least one line can be read.
						*/

#define	TOKIN '<'
#define TOKOUT '>'
#define	TOKHERE '<' + 1
#define TOKAPPN '>' + 1

//#define KEEPGESTAT -1
//#define CONTINUE 1
#define CMDINTERR 2
#define QUOTERR 3
#define TOKERR 4
#define	AMBRED 5
#define NOTFILE 6
#define	PIPING 7
#define	DUPING 8
#define	FORKING 9
#define IDENERR 10
#define	HOMELESS 11
#define TOOMARG 12
#define ISDIRFILE 13
#define ISDIRCMD 126
#define CMDERR 127
#define CMD_INTER 130
#define NOINTARG 255
#define CONTINUE 256
////
//#define CMDPROB 256

#define	IN 1
#define	OUT 0

#define	GENERAL 0
#define EXEC 1
#define HEREDOC 2

#define NOSET -1

#define	EXIT_STAT -1


typedef struct s_env
{
	char			**var;
	struct s_env	*next;
}				t_env;

typedef struct s_cmds
{
	char			tok_in;
	char			tok_out;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	char			avoid;
	char			**cmd;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_mini_data
{
	t_env			*env;
	char			**envp;
	char			*line;
	t_cmds			*cmds;
	int				cmd_num;
	int				err_print;
	int				err_exit;
	struct termios	termattr;
}				t_mini_data;

////
void	backup_termattr(struct termios *termattr);
void	restore_termattr(struct termios *termattr);
void	turn_off_echoctl(void);
////

t_env	*add_env_link(char **env_var, int definition);
int		builtiner(char **cmd, t_mini_data *data, pid_t pid);
int		cd(t_mini_data *data, char **cmd, pid_t pid);
int		chek_dir(char *path);
int		check_open_quotes(char *line);
int		echo(char **cmd, pid_t pid);
int		env(char **envp, pid_t pid);
void	erase_quotes(char *line);
void	executer(t_mini_data *data, t_cmds **cmds);
int		exit_shell(t_mini_data *data, char **cmd, pid_t pid);
int		expand_env_var(char **line, int *i, t_env **env);
char	*expand_var(char **line, int *pos, const char *var_name, t_env *env);
int		export(char **cmd, t_mini_data *data, pid_t pid);
int		export_env(char *env_var, t_env **env);
int		external(t_cmds *cmd, t_mini_data *data);
//void	external(t_cmds *cmd, t_mini_data *data);
char	*extract_env_var_name(char *line, int pos);
char	*get_file_path(char *line, t_mini_data *data);
void	free_cmds(t_cmds **cmds);
void	free_stuff(t_mini_data *data);
int		heredoc(t_mini_data *data, char *path[]);
void 	init_mini_data(t_mini_data *data);
void	kill_son(t_mini_data *data, pid_t pid);
void	line_to_cmds(t_mini_data *data, t_cmds	**cmd);
int		manage_errors(char *cmd_name, int error, char *culprit);
int		parse_files(char *line, t_cmds *cmd, t_mini_data *data);
void	parse_cmd(char **line, t_cmds *cmd, t_mini_data *data);
int		parser(t_mini_data *data);
int		pwd(char **cmd, pid_t pid);
void	quotes_status(char c, char *quo);
void	reset_envp(t_mini_data *data);
t_env	**search_env(const char *env_name, t_env **env);
void	set_env_list(char *envp[], t_mini_data *data);
t_env	*set_env_value(char *var_name, char *var_val[], t_env *env);
void	set_exit_status(int const status);
void	signal_handler(t_mini_data *data, int type, int pid);
void	trim_spaces(char *line);
char	tokenizer(char *line, t_cmds *cmd);
int		unset(char **cmd, t_mini_data *data, pid_t pid);

void	print_cmd(t_cmds *cmd, char *msg);