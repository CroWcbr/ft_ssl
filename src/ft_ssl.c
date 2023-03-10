/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/11 02:53:05 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

t_bool is_debug = false;

static void	mandatory_part(char **argv)
{
	t_ssl		*ssl;
	t_list		*tmp;
	t_hash		*hash;
	uint8_t		*result;

	ssl = parse(argv);
	if (!ssl)
		return ;
	if (IS_DEBUG)
		parse_print(ssl);
	tmp = ssl->hash_list;
	while (tmp)
	{
		hash = (t_hash *)tmp->content;
		if (hash->type == false)
			result = ssl->hash_func(hash->name, ft_strlen(hash->name));
		else
			result = read_file(ssl->hash_func, hash, ssl->hash);
		print_hash(ssl, hash, result);
		free(hash->name);
		tmp = tmp->next;
		free(result);
	}
	ft_lstclear(&ssl->hash_list, free);
	free(ssl);
}

static void	work_like_openssl(void)
{
	int		r;
	char	*line;
	char	**argv;

	while (1)
	{
		ft_putstr("OPENSSL > ");
		r = gnl(0, &line);
		if (line[0] != '\0' && line)
		{
			argv = ft_split(line, ' ');
			free(line);
			mandatory_part(argv);
			ft_free_split(argv);
		}
		if (r == 0)
			break ;
		if (r < 0)
			ft_err("Error gnl: ft_ssl - work_like_openssl - line in gnl");
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		work_like_openssl();
	else
		mandatory_part(argv + 1);
	return (0);
}
