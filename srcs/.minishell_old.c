/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .minishell_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/17 18:15:16 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// #define MAXCOM 1000 // max number of letters to be supported	// NOT NECESSARY
#define MAXLIST 100 // max number of commands to be supported	// NOT NECESSARY
  
//	// Greeting shell during startup // Make a initial screen to launch the minishell // NOT NECESSARY
//	void init_shell()
//	{
//	    clear();	// FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // Clears the screen
//	    printf("\n\n\n\n******************"
//	        "************************");
//	    printf("\n\n\n\t****MY SHELL****");
//	    printf("\n\n\t-USE AT YOUR OWN RISK-");
//	    printf("\n\n\n\n*******************"
//	        "***********************");
//	    char* username = getenv("USER");
//	    printf("\n\n\nUSER is: @%s", username);
//	    printf("\n");
//	    sleep(1);	// FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // Puts the procces on pause
//	    clear();	// FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // Clears the screen
//	}
  
// Function to print Current Directory.
void printDir()
{
    char cwd[MAX_PATH];	//	1024 is the max path length for MacOS, 4096 for Linux
    getcwd(cwd, MAX_PATH);	
    printf("\nDir: %s", cwd);
}

// Function to take input
int takeInput(char* str)
{
    char* buf;
  
    buf = readline("\n>>> ");
    if (ft_strlen(buf) != 0) {	// #originally:# if (strlen(buf) != 0) {
        add_history(buf);
        ft_strlcpy(str, buf, MAX_LINE);	// #originally:# strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
  
// Function where the system command is executed
void execArgs(char** parsed)
{
    // Forking a child
    pid_t pid = fork(); 
  
    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}
  
// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
    // 0 is read end, 1 is write end
    int pipefd[2]; 
    pid_t p1, p2;
  
    if (pipe(pipefd) < 0) {
        printf("\nPipe could not be initialized");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not fork");
        return;
    }
  
    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
  
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command 1..");
            exit(0);
        }
    } else {
        // Parent executing
        p2 = fork();
  
        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }
  
        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
        } else {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
        }
    }
}
  
// Help command builtin
void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");
  
    return;
}
  
// Function to execute builtin commands
int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;
  
    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
  
    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
  
    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    default:
        break;
    }
  
    return 0;
}
  
// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
    int i = 0;
    while (i < 2)
	{
        strpiped[i] = strsep(&str, "|");	// FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // Finds the ocurrence of "|" and sets the pointer to the next possition and "|" to \0. Returns the original position of the pointer or NULL if EOF
        if (strpiped[i] == NULL)
            break;
		i++;
    }
  
    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}
  
// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i = 0;
  
    while (i < MAXLIST)
	{
        parsed[i] = strsep(&str, " ");  // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // FORBIDDEN // Finds the ocurrence of " " and sets the pointer to the next possition and " " to \0. Returns the original position of the pointer or NULL if EOF
  
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)		// se libra de pedazos vacíos
            i--;
		i++;
    }
}
  
int processString(char* str, char** parsed, char** parsedpipe)
{
  
    char* strpiped[2];
    int piped = 0;
  
    piped = parsePipe(str, strpiped);	// Finds if there are pipes and split the str in two parts
  
    if (piped) {	// if there is a pipe
		parseSpace(strpiped[0], parsed);		// splits the first part by its spaces
		parseSpace(strpiped[1], parsedpipe);	// splits the second part by its spaces

	} else { // if there is no pipe

		parseSpace(str, parsed);	// slits the original received string by its spaces	
	}

    if (ownCmdHandler(parsed))		// checks whether the command is a built-in command and executes it
		return 0;
	else							// if the command is a no-built-in command, tells the main function whether it's piped
		return 1 + piped;
}
  
//int	main(int argc, char *argv[], char *envp[])
//{
//	t_mini_data	data;
//
//	(void)argc;
//	(void)argv;
//	init_mini_data(&data);
//	set_env_list(&data, envp);
////	///////////// Print the env stored on the env list.
////	t_env	*printenv = data.env;
////	int		i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
////	set_env_value("SHLVL", "javi", data.env);
////	///////////// Print the env stored on the env list.
////	printenv = data.env;
////	i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
////	set_new_env("drink=tea", data.env);
////	///////////// Print the env stored on the env list.
////	printenv = data.env;
////	i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
////	unset_env("drink", &data.env);
////	///////////// Print the env stored on the env list.
////	printenv = data.env;
////	i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
////	unset_env("SHLVL", &data.env);
////	///////////// Print the env stored on the env list.
////	printenv = data.env;
////	i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
////	unset_env("TERM_SESSION_ID", &data.env);
////	///////////// Print the env stored on the env list.
////	printenv = data.env;
////	i = 0, j = 0;
////	while (printenv || envp[i])
////	{
////		if (envp[i])
////		{
////			printf("env j = %d###%s\n", j, envp[i]);
////			i++;
////		}
////		else
////			printf("env j = %d###---- i = %d\n", j, i);
////		if (printenv)
////		{
////			printf("msh j = %d###%s=%s\n", j, printenv->var[0], printenv->var[1]);
////			printenv = printenv->next;
////		}
////		else
////			printf("msh j = %d###----\n", j);
////		j++;
////	}
////	/////////////
//	printenv(data.env);
//	while (1)
//	{
//		signal_handler();
//		char *prompt = readline("JaviShell>>");
//		printf("%s\n", prompt);
//	}
//	free_env(&data);
//	return (0);
//}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini_data	data;

	(void)argc;
	(void)argv;
	init_mini_data(&data);
//	set_env_list(envp, &data);
	set_env_list(envp, &data.env);
	while(1)
	{
		data.line = readline("testcli_readline> ");
		parser(&data);
		free(data.line);
	}
}