/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/27 02:55:29 by cdarrell         ###   ########.fr       */
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

void	*ft_mmemcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	size_t			i;

	if (src == dst || n == 0)
		return (dst);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	i = -1;
	while (++i < n)
	{
		printf("i = %ld\tsrc = %d\n" , i, (int)tmp_src[i]);
		*(tmp_dst + i) = *(tmp_src + i);
	}
	return (dst);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		work_like_openssl();
	else
		mandatory_part(argv + 1);

	// int x = 1;
	// unsigned char *tmp_x = (unsigned char *)(&x);
	// printf("-----------\n");
	// int k = 0;

	// printf("addr_x = %p\n", &x);
	// printf("addr_tmp_x = %p\n", tmp_x);
	// while (k < 4)
	// {
	// 	printf("k = %d\t%d\t%p\n", k, (int)(*(tmp_x + k)), tmp_x + k);
	// 	k++;
	// }
	// printf("-----------\n");
	// printf("size1 = %ld\n" , sizeof(x));
	// int j = 0;
	// unsigned char str[4];
	// ft_bzero(str, 4);
	// ft_mmemcpy(str, &x, 4);


	// while (j < 4)
	// {
	// 	printf("str = %d\n" , (int)str[j]);
	// 	int i = 7;
	// 	while (i >= 0)
	// 	{
	// 		printf("%d", (str[3 - j] & (1 << i)) >> i);
	// 		i--;
	// 	}
	// 	printf("\n");
	// 	j++;
	// }
	// printf("strJJJ = %d\n" , (int)str[j]);
	



	return (0);
}
