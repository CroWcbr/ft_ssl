/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:59:47 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/25 15:16:09 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*ft_strjoin_add_n(char const *s1, char const *s2, int n)
{
	char	*tmp;
	size_t	len;

	if (!s1 || !s2)
		return ((void *)0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (n > 0)
		len++;
	tmp = (char *)malloc(len * sizeof(char));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, s1, len);
	ft_strlcat(tmp, s2, len);
	if (n > 0)
		ft_strlcat(tmp, "\n", len);
	return (tmp);
}

static char	*read_stdin(char *tmp_stdin, char *tmp_del)
{
	int		r;
	char	*line;

	if (!tmp_stdin)
		ft_err("Error malloc: pars_flag_p.c - read_stdin - tmp_stdin");
	while (1)
	{
		r = gnl(0, &line);
		if (r < 0)
			ft_err("Error gnl: pars_flag_p.c - read_stdin - line in gnl");
		if (line)
		{
			tmp_del = tmp_stdin;
			tmp_stdin = ft_strjoin_add_n(tmp_stdin, line, r);
			if (!tmp_stdin)
				ft_err("Error malloc: pars_flag_p.c - read_stdin - tmp");
			free(tmp_del);
			free(line);
		}
		if (r == 0)
			break ;
	}
	return (tmp_stdin);
}

void	parse_flag_p(t_ssl *ssl)
{
	t_list	*new_list;
	t_hash	*input;

	input = malloc(sizeof(t_hash));
	if (!input)
		ft_err("Error malloc: parsing_flag_p.c - parse_flag_p - input");
	input->type = false;
	input->name = read_stdin(ft_strdup(""), NULL);
	if (!input->name)
		ft_err("Error malloc: pars_flag_p.c -  parse_flag_p - input->name");
	input->len = ft_strlen(input->name);
	new_list = ft_lstnew(input);
	if (!new_list)
		ft_err("Error malloc: parsing_flag_p.c - parse_flag_p - new_list");
	ft_lstadd_front(&ssl->hash_list, new_list);
}
