/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:26:00 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:26:01 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include<stdlib.h>
# include<unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30000	
# endif

# define INIT_BUF_SIZE 512

typedef struct sup_list
{
	int				fd;
	char			*buf;
	struct sup_list	*next;
}	t_up_list;

char		*get_next_line(int fd);
char		*remal(char *str, char *buf, size_t len);
void		*erase(char *p1, t_up_list **p2, t_up_list **p3);
void		memshift(char *buf, size_t anchor);
t_up_list	*lst_search(t_up_list *begin, t_up_list **prev, t_up_list *target,
				int fd);

#endif