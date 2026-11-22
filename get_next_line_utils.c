/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salkhali <salkhali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:15:56 by salkhali          #+#    #+#             */
/*   Updated: 2026/11/20 14:29:30 by salkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_node	*create_node(char *content, ssize_t n_bytes)
{
	ssize_t	i;
	char	*str;
	t_node	*node;

	str = malloc(n_bytes + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n_bytes)
	{
		str[i] = content[i];
		i++;
	}
	str[i] = '\0';
	node = malloc(sizeof(t_node));
	if (!node)
	{
		free(str);
		return (NULL);
	}
	node->content = str;
	node->len = i;
	node->next = NULL;
	return (node);
}

void	append_node(t_list *list, t_node *new_node)
{
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
		list->total_len = new_node->len;
		return ;
	}
	list->total_len += new_node->len;
	list->tail->next = new_node;
	list->tail = new_node;
}

void	free_list(t_list *list)
{
	t_node	*head;
	t_node	*tmp;

	head = list->head;
	while (head != NULL)
	{
		tmp = head->next;
		free(head->content);
		free(head);
		head = tmp;
	}
	list->head = NULL;
	list->tail = NULL;
	list->total_len = 0;
}

char	*find_nl(char *str)
{
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		return (str);
	return (NULL);
}

int	read_loop(t_list *list, int fd, char *buff)
{
	ssize_t	n_bytes;
	t_node	*node;

	while (1)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes <= 0)
			break ;
		node = create_node(buff, n_bytes);
		if (!node)
			return (-1);
		append_node(list, node);
		if (find_nl(node->content))
			break ;
	}
	if (n_bytes < 0)
		return (-1);
	return (0);
}
