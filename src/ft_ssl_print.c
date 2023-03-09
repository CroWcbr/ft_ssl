/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:49:28 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/10 01:54:54 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

void	print_hash(t_ssl *ssl, t_hash *hash, uint8_t *result)
{
	size_t	i;
	int flag = 0;



	if (!result)
		return ;

	char *tmp = ft_strdup(ssl->hash);
	i = 0;
	while (i < ft_strlen(tmp))
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}

	if (ssl->q && ssl->p)
	{
		ssl->p = 0;
		printf("%s", hash->name);
	}
	if (ssl->q)
		;
	else if (hash->type == 0 && ssl->p == 1)
	{
		int len = ft_strlen(hash->name) - 1;
		printf("(\"%.*s\")= ", len, hash->name);
		ssl->p = 0;
		flag = 1;
	}
	else if (hash->type == 0 && ft_lstsize(ssl->hash_list) == 1 && ssl->s == 0)
		printf("%s(stdin)= ", tmp);
	else if (hash->type == 1 && ssl->r == 0)
		printf("%s (%s) = ", tmp, hash->name);
	else if (hash->type == 0 && ssl->s == 1 && ssl->p == 0 && ssl->r == 0)
	{
		printf("%s (\"%s\") = ", tmp, hash->name);
		ssl->s = 0;
	}

	i = -1;
	while (++i < ssl->crypt_len)
		printf("%02x", result[i]);

	if (ssl->r == 1 && ssl->q == 0 && flag == 0)
	{
		if (ssl->s == 0)
			printf(" %s", hash->name);
		else
		{
			ssl->s = 0;
			printf(" \"%s\"", hash->name);
		}
		flag = 0;
	}

	printf("\n");
}
