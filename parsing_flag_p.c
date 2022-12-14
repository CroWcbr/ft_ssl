/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:59:47 by cdarrell          #+#    #+#             */
/*   Updated: 2022/07/25 18:58:02 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static char	*ft_strjoin_add_n(char const *s1, char const *s2, int r)
{
	char	*tmp;
	size_t	len;

	if (!s1 || !s2)
		return ((void *)0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (r > 0)
		len++;
	tmp = (char *)malloc(len * sizeof(char));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, s1, len);
	ft_strlcat(tmp, s2, len);
	if (r > 0)
		ft_strlcat(tmp, "\n", len);
	return (tmp);
}

static char	*read_stdin(char *tmp_stdin, char *tmp_del)
{
	int		r;
	char	*line;

	if (!tmp_stdin)
		ft_error("Error malloc: parsing_flag_p.c - read_stdin");
	while (1)
	{
		tmp_del = tmp_stdin;
		r = gnl(0, &line);
		if (r == -1)
			ft_error("Error gnl: r == -1");
		if (line)
		{
			tmp_stdin = ft_strjoin_add_n(tmp_del, line, r);
			if (!tmp_stdin)
				ft_error("Error malloc: parsing_flag_p.c - read_stdin");
			free(tmp_del);
			free(line);
			if (r == 0)
				printf("\n");
		}
		if (r == 0)
			break ;
	}
	return (tmp_stdin);
}

void	parse_flag_p(t_ssl *ssl)
{
	char	*tmp_stdin;
	t_list	*new_list;

	tmp_stdin = read_stdin(ft_strdup(""), NULL);
	new_list = ft_lstnew(tmp_stdin);
	if (!new_list)
		ft_error("Error malloc: parsing_flag_p.c - parse_flag_p");
	ft_lstadd_front(&ssl->hash_list, new_list);
}
