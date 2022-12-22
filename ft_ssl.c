/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/22 22:08:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_error(char *str)
{
	// write(2, str, ft_strlen(str));
	// write(2, "\n", 1);
	printf("%s\n", str);
	exit (1);
}

void print_ssl(t_ssl *ssl)
{
	printf("----------------------------\n");
	printf("type = \t%s\n", ssl->hash);
	printf("q = \t%d\n", ssl->q);
	printf("r = \t%d\n", ssl->r);
	t_list *tmp = ssl->hash_list;
	while(tmp)
	{
		t_hash	*th = (t_hash*)tmp->content;
		printf("%d %s %s\n", th->type, th->name, th->hash);
		tmp = tmp->next;
	}
	printf("----------------------------\n");
}

void free_ssl(t_ssl *ssl)
{
	free(ssl->hash);
	ft_lstclear(&ssl->hash_list, free);
	free(ssl);
}

// void	*ft_mmemcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned char	*tmp_dst;
// 	unsigned char	*tmp_src;
// 	size_t			i;

// 	if (src == dst || n == 0)
// 		return (dst);
// 	tmp_dst = (unsigned char *)dst;
// 	tmp_src = (unsigned char *)src;
// 	i = -1;
// 	while (++i < n)
// 	{
// 		printf("i = %ld\tsrc = %d\n" , i, (int)tmp_src[i]);
// 		*(tmp_dst + i) = *(tmp_src + i);
// 	}
// 	return (dst);
// }

int main(int argc, char **argv)
{
	t_ssl		*ssl;
	t_list		*tmp;
	t_hash		*hash;

	ssl = parse(argc, argv);
	print_ssl(ssl);

	tmp = ssl->hash_list;
	while (tmp)
	{
		hash = (t_hash*)tmp->content;
		if (hash->type == false)
			ssl->hash_func(hash->name, (uint64_t)ft_strlen(hash->name));
		else
		{
			char		input_buff[1000];
			char		*bytes;
			char		*result_bytes;
			
			size_t		n;
			int			fd;
			uint64_t	bytes_size;

			bytes = ft_strdup("");
			fd = open(hash->name, O_RDONLY);
			bytes_size = 0;

			while (1)
			{
				n = read(fd, input_buff, 1000);
				if (n == 0)
					break;
				
				char *tmp;
				tmp = bytes;
				
				bytes = (char*)malloc(bytes_size + n);

				ft_memcpy(bytes, tmp, bytes_size);
				ft_memcpy(bytes + bytes_size, input_buff, n);

				bytes_size += n;
			}
			ssl->hash_func(bytes, bytes_size);
			close(fd);
		}
		tmp = tmp->next;
	}

	free_ssl(ssl);

	// int x = 258;
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

	// printf("size2 = %ld\nwhile (j < 4)
	// {
	// 	printf("str = %d\n" , (int)str[j]);
	// 	int i = 7;
	// 	while (i >= 0)
	// 	{
	// 		printf("%d", (str[j] & (1 << i)) >> i);
	// 		i--;
	// 	}
	// 	printf("\n");
	// 	j++;
	// }" , sizeof(str));
	// printf("strJJJ = %d\n" , (int)str[j]);
	// 

	// printf("\n");
	return 0;
}
