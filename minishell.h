/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:38:01 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/10 16:30:01 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C Program to design a shell in Linux
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
#include "pipex/pipex.h"
#include "libft/libft.h"

# include <fcntl.h>
# include <errno.h>
# include <signal.h>


int			g_exit_status;


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")	// ???

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



//#define PIPE '|'
#define	TOKIN '<'
#define TOKOUT '>'
#define	TOKHERE '<' + 1
#define TOKAPPN '>' + 1

#define CONTINUE 1
#define QUOTERR 2
#define SYNTERR 3
#define TOKERR 4
#define	AMBRED 5
#define NOTFILE 6
#define	PIPING 7
#define	DUPING 8
#define	FORKING 9

#define	IN 1
#define	OUT 0

#define NOSET -1
#define PIPED -2

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
//	int				entry_pipe[2];
//	int				exit_pipe[2];
	char			**cmd;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_mini_data
{
	char			*shell_name;
	char			*prompt;
	t_env			*env;
	char			**envp;
	char			*line;
	t_cmds			*cmds;
	int				cmd_num;
	int				err;
}				t_mini_data;

t_env	*add_env_link(char **env_var, int definition);
int		builtiner(char **cmd, t_mini_data *data);
int		check_open_quotes(char *line);
int		env(char **envp);
void	erase_quotes(char *line);
void		executer(t_mini_data *data, t_cmds **cmds);
//void	*exit_shell(t_mini_data *data);
int		exit_shell(t_mini_data *data);
int		expand_env_var(char **line, int *i, t_env **env);
void	expand_var(char **line, int *pos, t_env *env);
int		export(char **cmd, t_mini_data *data);
int		export_env(char *env_var, t_env **env);
int		external(t_cmds *cmd, t_mini_data *data);
char	*file_path(char *line, t_mini_data *data);
void	free_cmds(t_cmds **cmds);
void 	init_mini_data(t_mini_data *data);
void	line_to_cmds(t_mini_data *data, t_cmds	**cmd);
void	parse_files(char *line, t_cmds *cmd, t_mini_data *data);
void	parse_cmd(char **line, t_cmds *cmd, t_mini_data *data);
int		parser(t_mini_data *data);
int		pwd(void);
void	quotes_status(char c, char *quo);
void	reset_envp(t_mini_data *data);
t_env	**search_env(char *env_name, t_env **env);
void	set_env_list(char *envp[], t_mini_data *data);
t_env	*set_env_value(char **var, int def, t_env *env);
void	signal_handler(void);
void	trim_spaces(char *line);
char	tokenizer(char *line, t_cmds *cmd);
int		unset(char **cmd, t_mini_data *data);
