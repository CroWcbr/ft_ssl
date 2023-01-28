/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:30:46 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:03:42 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static void	print_hash_and_pqrs(t_ssl *ssl)
{
	ft_putstr("type = \t");
	ft_putstr(ssl->hash);
	ft_putstr("\n");
	ft_putstr("p = \t");
	ft_putnbr_fd(ssl->p, 1);
	ft_putstr("\n");
	ft_putstr("q = \t");
	ft_putnbr_fd(ssl->q, 1);
	ft_putstr("\n");
	ft_putstr("r = \t");
	ft_putnbr_fd(ssl->r, 1);
	ft_putstr("\n");
	ft_putstr("s = \t");
	ft_putnbr_fd(ssl->s, 1);
	ft_putstr("\n");
}

static void	print_hash_list(t_ssl *ssl)
{
	t_list	*tmp;
	t_hash	*th;

	tmp = ssl->hash_list;
	while (tmp)
	{
		th = (t_hash *)tmp->content;
		ft_putnbr_fd(th->type, 1);
		ft_putstr("\t|");
		ft_putstr(th->name);
		ft_putstr("|\n");
		tmp = tmp->next;
	}
}

void	parse_print(t_ssl *ssl)
{
	ft_putstr("----------------------------\n");
	print_hash_and_pqrs(ssl);
	print_hash_list(ssl);
	ft_putstr("----------------------------\n");
}
