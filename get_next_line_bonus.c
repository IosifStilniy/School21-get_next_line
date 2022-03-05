/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:25:35 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:25:57 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

static char	*line_builder(char *str, char *buf, char **shift, int sw)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
		{
			*shift = buf + i;
			break ;
		}
	}
	if (sw)
		return (NULL);
	return (remal(str, buf, i));
}

static char	*trunc(char *str, char *buf, char **shift)
{
	char	*sshift;

	sshift = NULL;
	line_builder(NULL, buf, &sshift, 1);
	if (sshift && !*sshift)
		sshift = NULL;
	*shift = sshift;
	if (!sshift)
		return (NULL);
	buf = sshift;
	*(buf - 1) += 1;
	str = line_builder(str, buf, &sshift, 0);
	*shift = sshift;
	if (sshift == buf)
		*shift = NULL;
	return (str);
}

static t_up_list	*initialization(t_up_list **buf, int fd)
{
	t_up_list	*begin;
	t_up_list	*cpy;

	begin = lst_search(*buf, NULL, NULL, fd);
	if (begin)
		return (begin);
	begin = malloc(sizeof(*begin));
	if (!begin)
		return (NULL);
	begin->next = *buf;
	*buf = begin;
	begin->fd = fd;
	begin->buf = malloc(sizeof(*(begin->buf)) * ((size_t) BUFFER_SIZE + 1));
	cpy = *buf;
	if (!begin->buf)
		erase(NULL, &cpy, &begin);
	*buf = cpy;
	return (begin);
}

char	*get_next_line(int fd)
{
	ssize_t				ret;
	static t_up_list	*buf = NULL;
	t_up_list			*cursor;
	char				*str;
	char				*shift;

	if ((size_t) BUFFER_SIZE < 1)
		return (NULL);
	cursor = initialization(&buf, fd);
	str = NULL;
	str = trunc(str, cursor->buf, &shift);
	ret = BUFFER_SIZE;
	while (!shift && buf && cursor && cursor->buf)
	{
		ret = read(fd, cursor->buf, BUFFER_SIZE);
		if ((!ret || ret == -1) && !erase(NULL, &buf, &cursor))
			break ;
		cursor->buf[ret] = '\0';
		str = line_builder(str, cursor->buf, &shift, 0);
		if (!str)
			return (erase(str, &buf, &cursor));
	}
	return (str);
}
