/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpopa-po <jpopa-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:03:28 by agallipo          #+#    #+#             */
/*   Updated: 2021/09/01 21:44:51 by jpopa-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
char	*ft_check(char *buff, char *chk, char *line)
{
	char	*aux;
	char	*aux2;

	chk[0] = '\0';
	chk++;
	aux = ft_strjoin(line, buff);
	free(line);
	line = NULL;
	if (chk)
	{
		buff = ft_memmove(buff, chk, ft_strlen(chk));
		buff[ft_strlen(chk)] = '\0';
	}
	aux2 = ft_strjoin(aux, "\n");
	free(aux);
	return (aux2);
}

char	*ft_check2(char *buff, char *line, int *fd, int *rd)
{
	char	*aux;

	aux = ft_strjoin(line, buff);
	free(line);
	buff[0] = '\0';
	*rd = read(*fd, buff, BUFFER_SIZE);
	buff[*rd] = '\0';
	return (aux);
}

char	*ft_return(char *buff, char *chk, char *line, char *aux)
{
	aux = ft_check(buff, chk, line);
	return (aux);
}

char	*ft_return2(char *line, char *buff, int b, int *fd)
{
	if ((BUFFER_SIZE < 1 || read(*fd, NULL, 0) == -1) && b == 1)
	{
		free(buff);
		return (NULL);
	}
	if (b == 0)
	{
		free(line);
		free(buff);
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	t_var		variable;

	if ((BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1))
		return (ft_return2(variable.line, buff, 1, &fd));
	if (buff == NULL)
		buff = ft_calloc((sizeof(char) * (BUFFER_SIZE + 1)), 1);
	variable.line = ft_calloc(1, 1);
	if (!buff || !variable.line)
		return (NULL);
	variable.aux = NULL;
	variable.rd = BUFFER_SIZE;
	while (variable.rd > 0)
	{
		variable.chk = ft_strchr(buff, '\n');
		if (variable.chk != NULL)
			return (ft_return(buff, variable.chk, variable.line, variable.aux));
		else
		{
			variable.line = ft_check2(buff, variable.line, &fd, &variable.rd);
			if (variable.rd <= 0)
				return (ft_return2(variable.line, buff, 0, &fd));
		}
	}
	return (variable.aux);
}
*/
void	ft_rd(int fd, char *buff, char **line)
{
	t_var		variable;

	if (!*line || !ft_strchr(*line, '\n'))
	{
		buff[0] = '\0';
		variable.i = read(fd, buff, BUFFER_SIZE);
		buff[variable.i] = '\0';
		while (variable.i > 0)
		{
			buff[variable.i] = 0;
			if (!*line)
				*line = ft_substr(buff, 0, variable.i);
			else
			{
				variable.aux = *line;
				*line = ft_strjoin(*line, buff);
				free(variable.aux);
			}
			if (ft_strchr(buff, '\n'))
				break ;
			variable.i = read(fd, buff, BUFFER_SIZE);
		}
	}
	free(buff);
}

char	*ft_putln(char **line)
{
	t_var		variable;

	if (!*line)
		return (0);
	if (!ft_strchr(*line, '\n'))
	{
		variable.res = ft_substr(*line, 0, ft_strlen(*line));
		free(*line);
		*line = 0;
		return (variable.res);
	}
	variable.i = ft_strlen(*line);
	variable.j = ft_strlen(ft_strchr(*line, '\n'));
	variable.res = ft_substr(*line, 0, variable.i - variable.j + 1);
	variable.aux = *line;
	*line = ft_substr(ft_strchr(*line, '\n'), 1, variable.j);
	free(variable.aux);
	return (variable.res);
}

char	*get_next_line(int fd)
{
	t_var		variable;
	static char	*line[FD_SETSIZE];

	variable.buff = malloc(BUFFER_SIZE + 1);
	if (BUFFER_SIZE < 1 || fd == -1 || !variable.buff
		|| read(fd, variable.buff, 0) == -1)
	{
		free(variable.buff);
		return (NULL);
	}
	if ((read(fd, NULL, 0) == -1))
	{
		free(variable.buff);
		return (NULL);
	}
	ft_rd(fd, variable.buff, &line[fd]);
	return (ft_putln(&line[fd]));
}
/*
int main(int argc, char **argv)
{
	int fd;
	int	fd2;
	int ret = 0;
	char *line;
	int	variable.;

	line = 0;
	if (argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		i = 1;
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		else if (ret == 0)
			printf("EOF\n");
		fd2 = open(argv[2], O_RDONLY);
		close(fd);
		fd = fd2;
		while ((line = get_next_line(fd)) > 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		if (ret == 0)
			printf("EOF\n");
	}
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of file\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((line = get_next_line(fd)) != 0)
		{
			line = get_next_line(fd);
			printf("Line #%s\n", line);
			free(line);
		}
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		close(fd);
	}
	system("leaks a.out");
	return (0);
}

*/
