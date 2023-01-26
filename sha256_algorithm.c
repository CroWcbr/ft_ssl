/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:23:42 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/26 22:53:58 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static void	sha256_find_w(uint32_t *w, const uint8_t *str)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		w[i] = ((str[j]) << 24) | ((str[j + 1]) << 16) | \
				((str[j + 2]) << 8) | (str[j + 3]);
		i++;
		j += 4;
	}
	while (i < 64)
	{
		w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];
		i++;
	}
}

static void	sha256_update_sha_tmp(uint32_t *sha_tmp, uint32_t *w)
{
	uint32_t	t1;
	uint32_t	t2;
	uint32_t	i;

	i = -1;
	while (++i < 64)
	{
		t1 = sha_tmp[H] + EP1(sha_tmp[E]) + \
			CH(sha_tmp[E], sha_tmp[F], sha_tmp[G]) + g_k[i] + w[i];
		t2 = EP0(sha_tmp[A]) + MAJ(sha_tmp[A], sha_tmp[B], sha_tmp[C]);
		sha_tmp[H] = sha_tmp[G];
		sha_tmp[G] = sha_tmp[F];
		sha_tmp[F] = sha_tmp[E];
		sha_tmp[E] = sha_tmp[D] + t1;
		sha_tmp[D] = sha_tmp[C];
		sha_tmp[C] = sha_tmp[B];
		sha_tmp[B] = sha_tmp[A];
		sha_tmp[A] = t1 + t2;
	}
}

void	sha256_algorithm(const uint8_t *str, \
						uint32_t *sha_buf, uint32_t *sha_tmp)
{
	uint32_t	w[64];
	uint32_t	i;

	sha256_find_w(w, str);
	i = -1;
	while (++i < 8)
		sha_tmp[i] = sha_buf[i];
	sha256_update_sha_tmp(sha_tmp, w);
	i = -1;
	while (++i < 8)
		sha_buf[i] += sha_tmp[i];
}
