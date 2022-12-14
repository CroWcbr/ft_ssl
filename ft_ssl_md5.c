/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2022/07/25 22:50:32 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	ft_error(char *str)
{
	// write(2, str, ft_strlen(str));
	// write(2, "\n", 1);
	printf("%s", str);
	exit (1);
}

void print_ssl(t_ssl *ssl)
{

	printf("type = \t%s\n", ssl->hash);
	printf("p = \t%d\n", ssl->p);
	printf("q = \t%d\n", ssl->q);
	printf("r = \t%d\n", ssl->r);
	printf("s = \t%d\n", ssl->s);
	int i = 0;
	t_list *tmp = ssl->hash_list;
	while(tmp)
	{
		printf("%s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
}

void free_ssl(t_ssl *ssl)
{
	free(ssl->hash);
	ft_lstclear(&ssl->hash_list, free);
	free(ssl);
}

int main(int argc, char **argv)
{
	t_ssl		*ssl;
	t_list		*tmp;

	ssl = parse(argc, argv);
	print_ssl(ssl);

	tmp = ssl->hash_list;
	while (tmp)
	{
		// if (ssl->p == true)
			ssl->hash_func((char*)tmp->content);
		tmp = tmp->next;
	}

	free_ssl(ssl);
	return 0;
}
