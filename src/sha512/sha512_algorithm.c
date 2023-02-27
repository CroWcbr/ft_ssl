/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:23:27 by cdarrell          #+#    #+#             */
/*   Updated: 2023/02/27 17:55:53 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sha512.h"

static void	sha512_find_w(uint64_t *w, const uint64_t *str)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		w[i] = ((((str[i]) & 0xff00000000000000ull) >> 56) | \
			(((str[i]) & 0x00ff000000000000ull) >> 40) | \
			(((str[i]) & 0x0000ff0000000000ull) >> 24) | \
			(((str[i]) & 0x000000ff00000000ull) >> 8) | \
			(((str[i]) & 0x00000000ff000000ull) << 8) | \
			(((str[i]) & 0x0000000000ff0000ull) << 24) | \
			(((str[i]) & 0x000000000000ff00ull) << 40) | \
			(((str[i]) & 0x00000000000000ffull) << 56));
		i++;
		j += 8;
	}
	while (i < 80)
	{
		w[i] = sha512_op_sig1(w[i - 2]) + w[i - 7] + \
				sha512_op_sig0(w[i - 15]) + w[i - 16];
		i++;
	}
}

static void	sha512_update_sha_tmp(uint64_t *sha_tmp, uint64_t *w)
{
	uint64_t	t1;
	uint64_t	t2;
	uint32_t	i;

	i = 0;
	while (i < 80)
	{
		t1 = sha_tmp[H] + sha512_op_ep1(sha_tmp[E]) + \
			sha512_ch(sha_tmp[E], sha_tmp[F], sha_tmp[G]) + g_k[i] + w[i];
		t2 = sha512_op_ep0(sha_tmp[A]) + \
			sha512_maj(sha_tmp[A], sha_tmp[B], sha_tmp[C]);
		sha_tmp[H] = sha_tmp[G];
		sha_tmp[G] = sha_tmp[F];
		sha_tmp[F] = sha_tmp[E];
		sha_tmp[E] = sha_tmp[D] + t1;
		sha_tmp[D] = sha_tmp[C];
		sha_tmp[C] = sha_tmp[B];
		sha_tmp[B] = sha_tmp[A];
		sha_tmp[A] = t1 + t2;
		i++;
	}
}

void	sha512_algorithm(const uint8_t *str, \
						uint64_t *sha_buf, uint64_t *sha_tmp)
{
	uint64_t	w[80];
	uint32_t	i;

	sha512_find_w(w, (uint64_t *)str);
	i = -1;
	while (++i < 8)
		sha_tmp[i] = sha_buf[i];
	sha512_update_sha_tmp(sha_tmp, w);
	i = -1;
	while (++i < 8)
		sha_buf[i] += sha_tmp[i];
}
