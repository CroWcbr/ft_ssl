/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_read_hash_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:24:13 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/27 01:35:02 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*str_append(char *str_file, char *input_buff, size_t r, uint64_t *len)
{
	char		*tmp;

	tmp = (char *)malloc(*len + r);
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - str_append - str_file");
	ft_memcpy(tmp, str_file, *len);
	free(str_file);
	ft_memcpy(tmp + *len, input_buff, r);
	*len += r;
	return (tmp);
}

static char	*read_to_str(int fd, uint64_t *len)
{
	char		*str_file;
	char		input_buff[1000];
	size_t		r;

	str_file = ft_strdup("");
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - hash_file - str_file");
	while (1)
	{
		r = read(fd, input_buff, 1000);
		if (r == 0)
			break ;
		if (r < 0)
		{
			free (str_file);
			ft_err("Error read: ft_ssl.c - hash_file - r");
		}
		// str_file = str_append(str_file, input_buff, r, len);

		char		*tmp = str_file;

		str_file = (char *)malloc(*len + r);
		if (!str_file)
			ft_err("Error malloc: ft_ssl.c - str_append - str_file");
		ft_memcpy(str_file, tmp, *len);
		free(tmp);
		ft_memcpy(str_file + *len, input_buff, r);
		*len += r;

	}
	return (str_file);
}

uint8_t	*read_file(uint8_t *(*hash_func)(const char *str, const uint64_t len), \
						t_hash *hash)
{
	char		*str_file;
	uint64_t	len;
	int			fd;

	fd = open(hash->name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("No file\n");
		return (NULL);
	}
	len = 0;
	// str_file = read_to_str(fd, &len);


	char		input_buff[1000];
	size_t		r;

	str_file = ft_strdup("");
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - hash_file - str_file");
	while (1)
	{
		r = read(fd, input_buff, 1000);
		if (r == 0)
			break ;
		if (r < 0)
		{
			free (str_file);
			ft_err("Error read: ft_ssl.c - hash_file - r");
		}
		str_file = str_append(str_file, input_buff, r, &len);

		// char		*tmp = str_file;

		// printf("!!! = %ld\n", len);
		// printf("!!! = %ld\n", r);
		// str_file = (char *)malloc(((size_t)len + r)*sizeof(char));
		// if (!str_file)
		// 	ft_err("Error malloc: ft_ssl.c - str_append - str_file");
		// ft_memcpy(str_file, tmp, len);
		// free(tmp);
		// ft_memcpy(str_file + len, input_buff, r);
		// len += r;

		// char		*tmp = str_file;

		// str_file = (char *)malloc(r*sizeof(char));
		// str_file = ft_memcpy(str_file, input_buff, r);
		// len = r;
	}

	uint8_t *ttt = hash_func(str_file, len);
	// printf("4444\n");
	// // printf("????????????? = |%s|\n", str_file);
	// ft_putstr("------------------------\n");
	// if (!str_file)
	// 	ft_putstr("11111111111111111111111\n");
	// else
	// 	ft_putstr("22222222222222222222222\n");
	// // ft_putnbr_fd((int)(ft_strlen(c)), 1);
	// ft_putstr("\n------------------------\n");
	// printf("4444\n");
	free(str_file);
	// printf("5555\n");
	close(fd);
// printf("3333\n");
	return (ttt);
}
