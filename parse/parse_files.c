/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/02 17:55:04 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Finds redirection tokens, stores them into the cmd structure.
**	Opens the files pointed by the redirection tokens the way they have
**	to be oppened, and stores their fds into the cmd structure.
**	Returns 0 if everything is OK or the error value if it's not.
*/

int	parse_files(char *line, t_cmds *cmd)
{
	int i;
	char	quo;
	char    token;

	i = -1;
	quo = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == '<' || line[i] == '>')
			token = tokenizer(&line[i], cmd);
		if (!token)
			continue
		open_file(token, get_file_path(&line[i]), cmd);

		// Hay que escribir estas de arriba,
		// Coger ruta de archivo, abrirlo...
		
			
	}


}

