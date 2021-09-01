int 	redir_builtins_pipe(t_link *actuel, int file, t_bool redir)
{
	t_redir *current;

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
	return (file);
}

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