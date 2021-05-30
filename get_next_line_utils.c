char	*ft_strtrunc(char *str, char c)
{
	char	*res;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while ((*str)[i] && (*str)[i] != '\n')
	{
		i++;
		if (!str[i])
		{
			free(*str);
			return (NULL);
		}
	}
	res = ft_calloc(sizeof(char), ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	i++;
	while(str[i])
		res[j++] = str[i++];
	free(str);
	return (res);
}

int main(void)
{
	return (1);
}