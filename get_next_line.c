void ft_free_null(char **p)
{
	if (p)
	{
		if (*p)
		{
			free(*p);
			*p = NULL;
		}
	}
}

int	ft_free_on_error(char **p1, char **p2, int sig)
{
	ft_free_null(p1);
	ft_free_null(p2);
	return (sig);
}

static ssize_t	ft_get_line(char **saved, char **line)
{
	char	*saved_p;
	char	*temp;

	saved_p = ft_strchr(*saved, '\n');
	if (saved_p)
	{
		saved_p = '\0';
		saved_p++;
		*line = ft_strdup(saved);
		if (!line)
			return (ft_free_on_signal(saved, NULL, -1));
		temp = ft_strdup(saved_p);
		if (!temp)
			return (ft_free_on_signal(saved, line, -1));
		free (*saved);
		*saved = temp;
		return (1);
	}
	return (0);
}
ssize_t get_saved(char **saved, char **line)
{
	ssize_t flag;

}
int	get_next_line(int fd, char **line)
{
	static char *saved;
	char		*buf;
	ssize_t		flag;

	flag = 1;
	while (flag)
	{
		flag = ft_get_line(&saved, line);
		if (flag)
			return(flag);
		else
			line = ft_strjoin(line, buf);
		buf = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!buf)
			return (ft_free_on_signal(&saved, line, -1)) ;
		flag = read(fd, buf, BUFFER_SIZE);
		if (flag == -1)
		{
			ft_free_on_signal(line, NULL, 0);
			return (ft_free_on_signal(&buf, &saved, -1));
		}
		saved = ft_strjoin(saved, buf);
		free(buf);
	}
	return (0);
}