/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:18:26 by cdarrell          #+#    #+#             */
/*   Updated: 2023/02/27 18:38:44 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/whirlpool.h"

static void	whirlpool_find_w(uint64_t *w, const uint64_t *str)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < 8)
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
}

static void	wh_update_tmp_buf(uint64_t *tmp_buf, uint64_t *l, uint64_t *state)
{
	uint32_t	i;
	int			j;

	i = 0;
	while (i < 10)
	{
		l[0] = round_function(tmp_buf, 0, g_rc[i]);
		j = 0;
		while (++j < 8)
			l[j] = round_function(tmp_buf, j, 0);
		j = -1;
		while (++j < 8)
			tmp_buf[j] = l[j];
		j = -1;
		while (++j < 8)
			l[j] = round_function(state, j, tmp_buf[j]);
		j = -1;
		while (++j < 8)
			state[j] = l[j];
		i++;
	}
}

void	whirlpool_algorithm(const uint8_t *str, uint64_t *wh_buf)
{
	uint64_t	tmp_buf[8];
	uint64_t	state[8];
	uint64_t	l[8];
	uint64_t	w[8];
	int			j;

	whirlpool_find_w(w, (uint64_t *)str);
	j = -1;
	while (++j < 8)
		tmp_buf[j] = wh_buf[j];
	j = -1;
	while (++j < 8)
		state[j] = w[j] ^ tmp_buf[j];
	wh_update_tmp_buf(tmp_buf, l, state);
	j = -1;
	while (++j < 8)
		wh_buf[j] ^= state[j] ^ w[j];
}
