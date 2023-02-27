/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool_utily.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:22:55 by cdarrell          #+#    #+#             */
/*   Updated: 2023/02/27 18:39:38 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/whirlpool.h"

static uint64_t	whirlpool_op_rotright(uint64_t x, char rotright)
{
	return ((x >> rotright) | (x << (64 - rotright)));
}

uint64_t	round_function(uint64_t *a, int n, uint64_t c)
{
	uint64_t	rf;

	rf = g_t[(a[n] >> 56) & 0xFF];
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 7) % 8] >> 48) & 0xFF], 8);
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 6) % 8] >> 40) & 0xFF], 16);
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 5) % 8] >> 32) & 0xFF], 24);
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 4) % 8] >> 24) & 0xFF], 32);
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 3) % 8] >> 16) & 0xFF], 40);
	rf ^= whirlpool_op_rotright(g_t[(a[(n + 2) % 8] >> 8) & 0xFF], 48);
	rf ^= whirlpool_op_rotright(g_t[a[(n + 1) % 8] & 0xFF], 56);
	rf ^= c;
	return (rf);
}
