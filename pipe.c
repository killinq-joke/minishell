/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/16 09:43:51by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal g_signal;

int heredoc_non_pipe_command(t_link *actuel, int tmpp)
{
	t_redir *current;

	current = actuel->redir;
	while (current)
	{
		if (!ft_strcmp(current->redir, "<<"))
		{
			char *line;
			char *tmp;

			tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
			line = readline("> ");
			while (line && ft_strcmp(line, current->arg))
			{
				write(tmpp, line, ft_strlen(line));
				write(tmpp, "\n", 1);
				tmp = line;
				line = readline("> ");
				free(tmp);
			}
			free(line);
			tmpp = open("/tmp/hd", O_RDONLY);
			unlink("/tmp/hd");
		}
		current = current->next;
	}
	return (tmpp);
}

void minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	t_redir *current;
	char	**path;
	char	**env;
	int		fd[2];
	int		i;
	int		co = 0;
	char	*command;
	char	*tmp;
	int		tmpp = STDIN_FILENO;
	int		out = dup(STDOUT_FILENO);
	int		taille;
	int		file = -2;
	t_bool	errorleft = false;
	t_bool	redir = false;


	taille = linklen(cmd);
	actuel = cmd;
	all->exit_status = 0;
	echo_control_seq(true);
	env = envtab(all->headenv);
	while (actuel)
	{
		if (actuel->next)
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				pipe(fd);
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, "<<"))
					{
						char *line;
						char *tmp;

						tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
						line = readline("> ");
						while (line && ft_strcmp(line, current->arg))
						{
							write(tmpp, line, ft_strlen(line));
							write(tmpp, "\n", 1);
							tmp = line;
							line = readline("> ");
							free(tmp);
						}
						free(line);
						tmpp = open("/tmp/hd", O_RDONLY);
						unlink("/tmp/hd");
					}
					current = current->next;
				}
				out = dup(STDOUT_FILENO);
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, ">"))
					{
						redir = true;
						file = open(current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
					}
					if (!ft_strcmp(current->redir, ">>"))
					{
						redir = true;
						file = open(current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
					}
					if (!ft_strcmp(current->redir, "<"))
					{
						file = open(current->arg, O_RDONLY);
						if (file == -1)
							break;
					}
					current = current->next;
				}
				if (file == -1)
				{
					errorleft = true;
					file = open("/dev/null", O_RDONLY);
					dup2(file, STDOUT_FILENO);
					ft_puterr("minishell: ");
					ft_puterr(current->arg);
					ft_puterr(": No such file or directory\n");
				}
				g_signal.childpid = fork();
				if (!g_signal.childpid)
				{
					dup2(tmpp, STDIN_FILENO);
					if (!errorleft && !redir)
						dup2(fd[1], STDOUT_FILENO);
					else if (redir)
						dup2(file, STDOUT_FILENO);
					if (ft_strcmp(actuel->command[0], "pwd") == 0)
						pwd();
					if (ft_strcmp(actuel->command[0], "echo") == 0)
						echo(actuel);
					if (ft_strcmp(actuel->command[0], "env") == 0)
						printenv(all->headenv);
					if (ft_strcmp(actuel->command[0], "cd") == 0)
						cd(actuel, all->headenv, all);
					if (ft_strcmp(actuel->command[0], "export") == 0)
						export(actuel->command, all->headenv);
					if (ft_strcmp(actuel->command[0], "unset") == 0)
						unset(actuel->command, all);
					if (ft_strcmp(actuel->command[0], "exit") == 0)
						;
					exit(0);
				}
				if (file != -1)
					close(file);
				dup2(out, STDOUT_FILENO);
				close(fd[1]);
				tmpp = fd[0];
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				pipe(fd);
				tmpp = heredoc_non_pipe_command(actuel, tmpp);
				out = dup(STDOUT_FILENO);
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, ">"))
					{
						redir = true;
						file = open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						dup2(file, STDOUT_FILENO);
						close(file);
					}
					if (!ft_strcmp(current->redir, ">>"))
					{
						redir = true;
						file = open(current->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
						dup2(file, STDOUT_FILENO);
						close(file);
					}
					if (!ft_strcmp(current->redir, "<"))
					{
						file = open(current->arg, O_RDONLY);
						if (file == -1)
						{
							errorleft = true;
							ft_puterr("minishell: ");
							ft_puterr(current->arg);
							ft_puterr(": No such file or directory\n");
							close(file);
							file = open("/dev/null", O_RDONLY);
							tmpp = dup(file);
							close(file);
							break ;
						}
						tmpp = dup(file);
						close(file);
					}
					current = current->next;
				}
				int fdd;
				fdd = open(actuel->command[0], O_RDONLY);
				if (fdd != -1)
				{
					g_signal.childpid = fork();
					if (!g_signal.childpid)
					{
						dup2(tmpp, STDIN_FILENO);
						if (!errorleft && !redir)
							dup2(fd[1], STDOUT_FILENO);
						if (!errorleft)
						{
							if (execve(actuel->command[0], actuel->command, env) == -1)
								exit(errno);
						}
						exit(0);
					}
					dup2(out, STDOUT_FILENO);
					waitpid(g_signal.childpid, &all->exit_status, 0);
					if (WEXITSTATUS(all->exit_status))
						all->exit_status = 1;
				}
				close(fd[1]);
				if (!errorleft)
					tmpp = fd[0];
				waitpid(g_signal.childpid, &all->exit_status, 0);
				if (WIFEXITED(g_signal.childpid))
					all->exit_status = 127;
			}
			else
			{
				int fdd;

				pipe(fd);
				i = -1;
				tmp = ft_getenv("PATH", all->headenv);
				path = ft_split(tmp, ':');
				free(tmp);
				if (!path)
				{
					ft_puterr("minishell:");
					ft_puterr(actuel->command[0]);
					ft_puterr(" : No such file or directory\n");
				}
				else
				{
					tmpp = heredoc_non_pipe_command(actuel, tmpp);
					out = dup(STDOUT_FILENO);
					current = actuel->redir;
					while (current)
					{
						if (!ft_strcmp(current->redir, ">"))
						{
							redir = true;
							file = open(current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
							dup2(file, STDOUT_FILENO);
							close(file);
						}
						if (!ft_strcmp(current->redir, ">>"))
						{
							redir = true;
							file = open(current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
							dup2(file, STDOUT_FILENO);
							close(file);
						}
						if (!ft_strcmp(current->redir, "<"))
						{
							file = open(current->arg, O_RDONLY);
							if (file == -1)
							{
								errorleft = true;
								ft_puterr("minishell: ");
								ft_puterr(current->arg);
								ft_puterr(": No such file or directory\n");
								close(file);
								file = open("/dev/null", O_RDONLY);
								tmpp = dup(file);
								close(file);
								break ;
							}
							tmpp = dup(file);
							close(file);
						}
						current = current->next;
					}
					while (path[++i])
					{
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);
						free(tmp);
						fdd = open(command, O_RDONLY);
						if (fdd != -1 && ft_strlen(actuel->command[0]))
						{
							co = 1;
							g_signal.childpid = fork();
							if (!g_signal.childpid)
							{
								dup2(tmpp, STDIN_FILENO);
								if (!errorleft && !redir)
									dup2(fd[1], STDOUT_FILENO);
								if (!errorleft)
								{
									if (execve(command, actuel->command, env) == -1)
									{
										free(command);
										exit(errno);
									}
								}
								free(command);
								exit(0);
							}
							dup2(out, STDOUT_FILENO);
							waitpid(g_signal.childpid, &all->exit_status, 0);
							if (WEXITSTATUS(all->exit_status))
								all->exit_status = 1;
							free(command);
							break ;
						}
						free(command);
					}
					close(fd[1]);
					if (!errorleft)
						tmpp = fd[0];
					if (co == 0)
					{
						all->exit_status = 127;
						ft_puterr("minishell: ");
						ft_puterr(actuel->command[0]);
						ft_puterr(": command not found\n");
					}
				}
				freetokens(path);
			}
		}
		else
		{
			if (!ft_strcmp(actuel->command[0], "echo") || !ft_strcmp(actuel->command[0], "cd") || !ft_strcmp(actuel->command[0], "pwd") || !ft_strcmp(actuel->command[0], "exit") || !ft_strcmp(actuel->command[0], "export") || !ft_strcmp(actuel->command[0], "unset") || !ft_strcmp(actuel->command[0], "env"))
			{
				tmpp = heredoc_non_pipe_command(actuel, tmpp);
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, ">"))
					{
						redir = true;
						file = open(current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
						dup2(file, STDOUT_FILENO);
					}
					if (!ft_strcmp(current->redir, ">>"))
					{
						redir = true;
						file = open(current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
						dup2(file, STDOUT_FILENO);
					}
					if (!ft_strcmp(current->redir, "<"))
					{
						errorleft = true;
						file = open(current->arg, O_RDONLY);
						if (file == -1)
							break ;
					}
					current = current->next;
				}
				if (file == -1)
				{
					ft_puterr("minishell: ");
					ft_puterr(current->arg);
					ft_puterr(": No such file or directory\n");
				}
				else if ((ft_strcmp(actuel->command[0], "unset") == 0) && (taille == 1))
					unset(actuel->command, all);
				else if (ft_strcmp(actuel->command[0], "exit") == 0 && (taille == 1))
				{
					ft_putstr("exit\n");
					if (actuel->command[1])
					{
						if (ft_strisnum(actuel->command[1]) == 1)
							exit(ft_atoi(actuel->command[1]));
						else
						{
							ft_puterr("minishell: ");
							ft_puterr(actuel->command[1]);
							ft_puterr(": numeric argument required\n");
						}
					}
					exit(0);
				}
				else if (ft_strcmp(actuel->command[0], "cd") == 0)
					cd(actuel, all->headenv, all);
				else if (ft_strcmp(actuel->command[0], "export") == 0)
					export(actuel->command, all->headenv);
				else
				{
					g_signal.childpid = fork();
					if (!g_signal.childpid)
					{
						if (file != -1)
							close(file);
						dup2(tmpp, STDIN_FILENO);
						if (ft_strcmp(actuel->command[0], "echo") == 0)
							echo(actuel);
						if (ft_strcmp(actuel->command[0], "env") == 0)
							printenv(all->headenv);
						if (ft_strcmp(actuel->command[0], "pwd") == 0)
							pwd();
						if (file != -1)
							close(file);
						exit(1);
					}
					if (file != -1)
						close(file);
				}
				dup2(out, STDOUT_FILENO);
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				tmpp = heredoc_non_pipe_command(actuel, tmpp);
				if (opendir(actuel->command[0]))
				{
					all->exit_status = 126;
					ft_puterr("minishell: ");
					ft_puterr(actuel->command[0]);
					ft_puterr(" : is a Directory \n");
				}
				else
				{
					out = dup(STDOUT_FILENO);
					current = actuel->redir;
					while (current)
					{
						if (!ft_strcmp(current->redir, ">"))
						{
							file = open(current->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
							dup2(file, STDOUT_FILENO);
							close(file);
						}
						if (!ft_strcmp(current->redir, ">>"))
						{
							file = open(current->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
							dup2(file, STDOUT_FILENO);
							close(file);
						}
						if (!ft_strcmp(current->redir, "<"))
						{
							tmpp = dup(STDIN_FILENO);
							redir = true;
							file = open(current->arg, O_RDONLY);
							if (file == -1)
							{
								ft_puterr("minishell: ");
								ft_puterr(current->arg);
								ft_puterr(": No such file or directory\n");
								break ;
							}
							tmpp = dup(file);
							close(file);
						}
						current = current->next;
					}
					int fd;
					fd = open(actuel->command[0], O_RDONLY);
					if (file == -1)
					{
					}
					else if (fd == -1)
					{
						all->exit_status = 127;
						ft_puterr("minishell: ");
						ft_puterr(actuel->command[0]);
						ft_puterr(": No such file or directory\n");
					}
					else
					{
						g_signal.childpid = fork();
						if (!g_signal.childpid)
						{
							dup2(tmpp, STDIN_FILENO);
							if (execve(actuel->command[0], actuel->command, env) == -1)
								exit(errno);
						}
						if (file != -1)
							dup2(out, STDOUT_FILENO);
						waitpid(g_signal.childpid, &all->exit_status, 0);
						if (WEXITSTATUS(all->exit_status))
							all->exit_status = 1;
					}
				}
			}
			else
			{
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, "<<"))
					{
						char *line;
						char *tmp;

						tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
						line = readline("> ");
						while (line && ft_strcmp(line, current->arg))
						{
							write(tmpp, line, ft_strlen(line));
							write(tmpp, "\n", 1);
							tmp = line;
							line = readline("> ");
							free(tmp);
						}
						free(line);
						tmpp = open("/tmp/hd", O_RDONLY);
						unlink("/tmp/hd");
					}
					current = current->next;
				}
				if (opendir(actuel->command[0]))
				{
					all->exit_status = 126;
					ft_puterr("minishell: ");
					ft_puterr(actuel->command[0]);
					ft_puterr(" : is a Directory \n");
				}
				out = dup(STDOUT_FILENO);
				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, ">"))
					{
						file = open(current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
						dup2(file, STDOUT_FILENO);
						close(file);
					}
					if (!ft_strcmp(current->redir, ">>"))
					{
						file = open(current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
						dup2(file, STDOUT_FILENO);
						close(file);
					}
					if (!ft_strcmp(current->redir, "<"))
					{
						tmpp = dup(STDIN_FILENO);
						redir = true;
						file = open(current->arg, O_RDONLY);
						if (file == -1)
						{
							ft_puterr("minishell: ");
							ft_puterr(current->arg);
							ft_puterr(": No such file or directory\n");
							break ;
						}
						tmpp = dup(file);
						close(file);
					}
					current = current->next;
				}
				tmp = ft_getenv("PATH", all->headenv);
				path = ft_split(tmp, ':');
				free(tmp);
				if (file == -1)
				{
				}
				else if (!path)
				{
					ft_puterr("minishell: ");
					ft_puterr(actuel->command[0]);
					ft_puterr(" : No such file or directory\n");
				}
				else
				{
					int fd;
					i = -1;
					while (path[++i])
					{
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);
						free(tmp);
						fd = open(command, O_RDONLY);
						if (fd != -1 && ft_strlen(actuel->command[0]))
						{
							co = 1;
							g_signal.childpid = fork();
							if (!g_signal.childpid)
							{
								dup2(tmpp, STDIN_FILENO);
								if (file != -1)
									close(file);
								if (execve(command, actuel->command, env) == -1)
									exit(errno);
								free(command);
							}
							waitpid(g_signal.childpid, &all->exit_status, 0);
							if (WEXITSTATUS(all->exit_status))
								all->exit_status = 1;
							else if (WTERMSIG(all->exit_status))
								all->exit_status = 128 + WTERMSIG(all->exit_status);
							free(command);
							break ;
						}
						free(command);
					}
					if (file != -1)
						dup2(out, STDOUT_FILENO);
					if (co == 0)
					{
						all->exit_status = 127;
						ft_puterr("minishell: ");
						ft_puterr(actuel->command[0]);
						ft_puterr(": command not found\n");
					}
				}
				freetokens(path);
			}
		}
		actuel = actuel->next;
	}
	freetokens(env);
}
