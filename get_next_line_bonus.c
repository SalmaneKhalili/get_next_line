/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salkhali <salkhali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:00:11 by salkhali          #+#    #+#             */
/*   Updated: 2026/11/22 17:32:52 by salkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_to_list(t_list *list, int fd)
{
	char	*buff;
	size_t	size;

	size = BUFFER_SIZE;
	if (list->head && find_nl(list->head->content))
		return (0);
	buff = malloc(size + 1);
	if (!buff)
		return (-1);
	if (read_loop(list, fd, buff) == -1)
	{
		free(buff);
		free_list(list);
		return (-1);
	}
	free(buff);
	return (0);
}

static char	*extract_line(t_list *list)
{
	size_t	len;
	char	*str;
	t_node	*head;
	size_t	i;
	size_t	j;

	if (find_nl(list->tail->content))
		len = list->total_len - (list->tail->len - (find_nl(list->tail->content)
					- list->tail->content) - 1);
	else
		len = list->total_len;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	head = list->head;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < head->len && i < len)
			str[i++] = (head->content)[j++];
		head = head->next;
	}
	str[len] = '\0';
	return (str);
}

static int	update_list(t_list *list)
{
	char	*nl_ptr;
	t_node	*new;
	size_t	len;

	nl_ptr = find_nl(list->tail->content);
	if (nl_ptr)
	{
		len = list->tail->len - (nl_ptr - list->tail->content) - 1;
		if (len == 0)
		{
			free_list(list);
			return (0);
		}
		new = create_node(nl_ptr + 1, len);
		if (!new)
			return (-1);
		free_list(list);
		append_node(list, new);
	}
	else
		free_list(list);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	storage[MAX_OPEN];
	t_list			*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_OPEN)
		return (NULL);
	list = &storage[fd];
	if (read_to_list(list, fd) == -1)
		return (free_list(list), NULL);
	if (!list->head)
		return (NULL);
	line = extract_line(list);
	if (!line)
		return (free_list(list), NULL);
	if (update_list(list) == -1)
		return (free_list(list), free(line), NULL);
	return (line);
}
