/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:28:33 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/25 15:02:27 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_ssl(t_ssl *ssl)
{
	t_list	*tmp;
	t_hash	*th;

	ft_putstr("----------------------------\n");
	ft_putstr("type = \t");
	ft_putstr(ssl->hash);
	ft_putstr("\n");
	ft_putstr("q = \t");
	ft_putnbr_fd(ssl->q, 1);
	ft_putstr("\n");
	ft_putstr("r = \t");
	ft_putnbr_fd(ssl->r, 1);
	ft_putstr("\n");
	tmp = ssl->hash_list;
	while (tmp)
	{
		th = (t_hash *)tmp->content;
		ft_putnbr_fd(th->type, 1);
		ft_putstr("\t");
		ft_putstr(th->name);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	ft_putstr("----------------------------\n");
}

void	ft_err(char *str)
{
	ft_putstr(str);
	exit (1);
}

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
// 	return 0;
// }

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
