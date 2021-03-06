/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:26:21 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:26:22 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

t_up_list	*lst_search(t_up_list *begin, t_up_list **prev, t_up_list *target,
	int fd)
{
	if (prev)
		*prev = NULL;
	while (begin)
	{
		if ((target && begin == target) || (!target && begin->fd == fd))
			break ;
		if (prev)
			*prev = begin;
		begin = begin->next;
	}
	return (begin);
}

void	*erase(char *p1, t_up_list **p2, t_up_list **p3)
{
	t_up_list	*begin;
	t_up_list	*prev;

	if (p1)
		free(p1);
	if (!p2 && !p3)
		return (NULL);
	begin = lst_search(*p2, &prev, *p3, 0);
	if (!begin)
		return (NULL);
	if (prev)
		prev->next = begin->next;
	if (begin->buf)
		free(begin->buf);
	begin->buf = NULL;
	if (begin == *p2)
		*p2 = (*p2)->next;
	begin->next = NULL;
	free(begin);
	*p3 = NULL;
	return (NULL);
}

static size_t	getlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*remal(char *str, char *buf, size_t len)
{
	size_t	size;
	size_t	addsize;
	size_t	i;
	char	*new_str;

	addsize = BUFFER_SIZE;
	if (BUFFER_SIZE < INIT_BUF_SIZE)
		addsize = INIT_BUF_SIZE;
	size = getlen(str);
	new_str = str;
	if (!size || (size % addsize) + len >= addsize - 1)
		new_str = malloc(sizeof(*new_str) * (size + 1 + addsize));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str && new_str != str && str[++i] && i < size)
		new_str[i] = str[i];
	if (str && new_str != str)
		erase(str, NULL, NULL);
	new_str[size + len] = '\0';
	while (len--)
		new_str[size + len] = buf[len];
	return (new_str);
}
