/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:02 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:03:06 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/md5.h"

static void	md5_find_f_g(int i, uint32_t *md_tmp, uint32_t *f, uint32_t *g)
{
	if (i <= 15)
	{
		*f = (md_tmp[B] & md_tmp[C]) | ((~md_tmp[B]) & md_tmp[D]);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (md_tmp[D] & md_tmp[B]) | ((~md_tmp[D]) & md_tmp[C]);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = md_tmp[B] ^ md_tmp[C] ^ md_tmp[D];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = md_tmp[C] ^ (md_tmp[B] | (~md_tmp[D]));
		*g = (7 * i) % 16;
	}
}

static void	md5_find_m(uint32_t *m, const uint8_t *str)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		m[i] = *(str + i * 4) << 0 | \
				*(str + i * 4 + 1) << 8 | \
				*(str + i * 4 + 2) << 16 | \
				*(str + i * 4 + 3) << 24;
		i++;
	}	
}

void	md5_algorithm(const uint8_t *str, uint32_t *md_buf, uint32_t *md_tmp)
{
	uint32_t	f;
	uint32_t	g;
	int			i;
	uint32_t	m[16];

	md_tmp[A] = md_buf[A];
	md_tmp[B] = md_buf[B];
	md_tmp[C] = md_buf[C];
	md_tmp[D] = md_buf[D];
	i = 0;
	while (i < 64)
	{
		md5_find_f_g(i, md_tmp, &f, &g);
		md5_find_m(m, str);
		f = f + md_tmp[A] + g_k[i] + m[g];
		md_tmp[A] = md_tmp[D];
		md_tmp[D] = md_tmp[C];
		md_tmp[C] = md_tmp[B];
		md_tmp[B] += f << g_s[i] | f >> (32 - g_s[i]);
		i++;
	}
	md_buf[A] += md_tmp[A];
	md_buf[B] += md_tmp[B];
	md_buf[C] += md_tmp[C];
	md_buf[D] += md_tmp[D];
}
