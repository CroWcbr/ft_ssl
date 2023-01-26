/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:28:33 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/27 00:41:23 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_err(char *str)
{
	ft_putstr(str);
	exit (1);
}

void print_test(char *err, uint8_t *tt, int len_byte)
{
	int jj = 0;
	printf("\n%s\n", err);
	while (jj < len_byte)
	{
		int i = 7;
		if (jj % 4 == 0)
			printf("%d\t", jj);
		while (i >= 0)
		{
			printf("%d", (tt[jj] >> i) & 1);
			i--;
		}
		printf(" ");
		jj++;
		if (jj % 4 == 0)
			printf("\n");
	}
	printf("\n");
}
