/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:49:28 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/12 01:39:47 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static void	pre_print_hash(t_ssl *ssl, t_hash *hash)
{
	if (ssl->q && ssl->p)
		printf("%s", hash->name);
	else if (ssl->q == 0 && hash->type == 0 && ssl->p == 1)
		printf("(\"%.*s\")= ", (int)(ft_strlen(hash->name) - 1), hash->name);
	else if (ssl->q == 0 && hash->type == 0 && \
			ft_lstsize(ssl->hash_list) == 1 && ssl->s == 0)
		printf("(stdin)= ");
	else if (ssl->q == 0 && hash->type == 1 && ssl->r == 0)
		printf("%s (%s) = ", ssl->hash, hash->name);
	else if (ssl->q == 0 && hash->type == 0 && \
			ssl->s == 1 && ssl->p == 0 && ssl->r == 0)
	{
		printf("%s (\"%s\") = ", ssl->hash, hash->name);
		ssl->s = 0;
	}
}

static void	after_print_hash(t_ssl *ssl, t_hash *hash)
{
	if (ssl->r == 1 && ssl->q == 0 && ssl->p == 0)
	{
		if (ssl->s == 0)
			printf(" %s", hash->name);
		else
		{
			printf(" \"%s\"", hash->name);
			ssl->s = 0;
		}
	}
	ssl->p = 0;
	printf("\n");
}

void	print_hash(t_ssl *ssl, t_hash *hash, uint8_t *result)
{
	size_t	i;

	if (!result)
		return ;
	pre_print_hash(ssl, hash);
	i = 0;
	while (i < ssl->crypt_len)
		printf("%02x", result[i++]);
	after_print_hash(ssl, hash);
}
