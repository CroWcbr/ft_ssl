/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2023/02/27 17:54:19 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/whirlpool.h"

#include <stdio.h>

static void	whirlpool_init(t_whirlpool *wh, \
							const char *str, \
							const uint64_t *len)
{
	int	i;

	wh->str = (uint8_t *)str;
	wh->len = *len;
	wh->pos = 0;
	wh->len_64_bit = wh->len * 8;
	i = -1;
	while (++i < 8)
		wh->wh_buf[i] = 0;
	wh->result = malloc(64);
	if (!wh->result)
		ft_err("Error malloc: whirlpool.c - whirlpool_init - wh->result");
}

static void	whirlpool_update(t_whirlpool *wh)
{
	while (wh->len - wh->pos > 64)
	{
		whirlpool_algorithm(wh->str + wh->pos, wh->wh_buf);
		wh->pos += 64;
	}
}

static void	whirlpool_final(t_whirlpool *wh)
{
	uint8_t		*new_str;
	uint64_t	new_len;
	uint64_t	pos;
	int			i;

	new_len = ((wh->len - wh->pos + 1) / 64 + 1 + \
				((wh->len - wh->pos + 1) % 64 > 32)) * 64;
	new_str = malloc(new_len);
	if (!new_str)
		ft_err("Error malloc: wh_main.c - wh_final - new_str");
	ft_bzero(new_str, (size_t)(new_len));
	ft_memcpy(new_str, wh->str + wh->pos, wh->len - wh->pos);
	ft_memset(new_str + wh->len - wh->pos, 1 << 7, 1);
	i = -1;
	while (++i < 8)
		ft_memcpy(new_str + new_len - i - 1, \
				(uint8_t *)(&wh->len_64_bit) + i, 1);
	pos = 0;
	while (new_len > pos)
	{
		whirlpool_algorithm(new_str + pos, wh->wh_buf);
		pos += 64;
	}
	free(new_str);
}

uint8_t	*whirlpool(const char *str, const uint64_t len)
{
	t_whirlpool	wh;
	int			i;

	whirlpool_init(&wh, str, &len);
	whirlpool_update(&wh);
	whirlpool_final(&wh);
	i = -1;
	while (++i < 8)
	{
		wh.result[i] = (wh.wh_buf[0] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 8] = (wh.wh_buf[1] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 16] = (wh.wh_buf[2] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 24] = (wh.wh_buf[3] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 32] = (wh.wh_buf[4] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 40] = (wh.wh_buf[5] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 48] = (wh.wh_buf[6] >> (56 - i * 8)) & 0x000000ff;
		wh.result[i + 56] = (wh.wh_buf[7] >> (56 - i * 8)) & 0x000000ff;
	}
	return (wh.result);
}
