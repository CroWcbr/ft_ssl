/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/26 22:44:21 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*str_append(char *str_file, char *input_buff, size_t r, uint64_t *len)
{
	char		*tmp;

	tmp = str_file;
	str_file = (char *)malloc(*len + r);
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - str_append - str_file");
	ft_memcpy(str_file, tmp, *len);
	free(tmp);
	ft_memcpy(str_file + *len, input_buff, r);
	*len += r;
	return (str_file);
}

static void	hash_file(void (*hash_func)(const char *str, const uint64_t len), \
						t_hash *hash)
{
	char		*str_file;
	char		input_buff[1000];
	size_t		r;
	int			fd;

	fd = open(hash->name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("No file\n");
		return ;
	}
	str_file = ft_strdup("");
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - hash_file - str_file");
	while (1)
	{
		r = read(fd, input_buff, 1000);
		if (r == 0)
			break ;
		if (r < 0)
			ft_err("Error read: ft_ssl.c - hash_file - r");
		str_file = str_append(str_file, input_buff, r, &hash->len);
	}
	hash_func(str_file, hash->len);
	free(str_file);
	close(fd);
}

static void	mandatory_part(char **argv)
{
	t_ssl		*ssl;
	t_list		*tmp;
	t_hash		*hash;

	ssl = parse(argv);
	if (!ssl)
		return ;
	print_ssl(ssl);
	tmp = ssl->hash_list;
	while (tmp)
	{
		hash = (t_hash *)tmp->content;
		if (hash->type == false)
			ssl->hash_func(hash->name, hash->len);
		else
			hash_file(ssl->hash_func, hash);
		free(hash->name);
		tmp = tmp->next;
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
		if (line)
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
