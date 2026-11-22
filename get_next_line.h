/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salkhali <salkhali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:51:48 by salkhali          #+#    #+#             */
/*   Updated: 2026/11/22 17:26:18 by salkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			*content;
	size_t			len;
	struct s_node	*next;
}					t_node;

typedef struct s_list
{
	t_node			*head;
	t_node			*tail;
	size_t			total_len;
}					t_list;

int					read_loop(t_list *list, int fd, char *buff);
char				*get_next_line(int fd);
t_node				*create_node(char *content, ssize_t n_bytes);
void				append_node(t_list *list, t_node *new_node);
void				free_list(t_list *list);
char				*find_nl(char *str);

#endif
