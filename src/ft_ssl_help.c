/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:28:33 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:50:20 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

void	ft_err(char *str)
{
	ft_putstr(str);
	exit (1);
}

void	print_test(char *err, uint8_t *tt, int len_byte)
{
	int	j;
	int	i;

	j = 0;
	ft_putstr(err);
	ft_putstr("\n");
	while (j < len_byte)
	{
		i = 8;
		if (j % 4 == 0)
		{
			ft_putnbr_fd(j, 1);
			ft_putstr("\t");
		}
		while (--i >= 0)
			ft_putnbr_fd((tt[j] >> i) & 1, 1);
		ft_putstr(" ");
		j++;
		if (j % 4 == 0)
			ft_putstr("\n");
	}
	ft_putstr("\n");
}
