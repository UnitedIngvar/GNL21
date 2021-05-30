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

static char	*ft_get_line(char *cache)
{
	ssize_t	i;
	char	*line;

	if (!cache)
		return (NULL);
	while((*cache)[i] && cache[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (cache[i] && cache[i] != '\n')
	{
		line[i] = cache[i];
		i++;
	}
	return (line);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache;
	char	*buf;
	ssize_t		fr;

	if (fd < -1 || !*line || BUFFER_SIZE <= 0)
		return (-1);
	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	fr = 1;
	while (fr && !ft_strchr(cache, '\n'))
	{
		fr = read(fd, buf, BUFFER_SIZE);
		if (fr == -1)
			return (ft_free_on_signal(&buf, &cache, -1));
		cache = ft_strjoin(cache, buf);
	}
	free(buf);
	*line = ft_get_line(cache);
	cache = ft_strtrunc(cache);
	if (fd == 0)
		return (0);
	return (1);
}