/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:23:27 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:42:46 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sha512.h"

static void	sha512_find_w(uint64_t *w, const uint8_t *str)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		w[i] = (str[j + 7] | \
				str[j + 6] << 8 | \
				str[j + 5] << 16 | \
				str[j + 4] << 24) | \
				((uint64_t)(str[j + 3] | \
							str[j + 2] << 8 | \
							str[j + 1] << 16 | \
							str[j] << 24) \
					<< 32);
		i++;
		j += 8;
	}
	while (i < 80)
	{
		w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];
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
		i++;
	}
}

void	sha512_algorithm(const uint8_t *str, \
						uint64_t *sha_buf, uint64_t *sha_tmp)
{
	uint64_t	w[80];
	uint32_t	i;

	sha512_find_w(w, str);
	i = -1;
	while (++i < 8)
		sha_tmp[i] = sha_buf[i];
	sha512_update_sha_tmp(sha_tmp, w);
	i = -1;
	while (++i < 8)
		sha_buf[i] += sha_tmp[i];
}
