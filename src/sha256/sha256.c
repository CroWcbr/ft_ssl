/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/29 01:44:13 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sha256.h"

static void	sha_init(t_sha256 *sha, const char *str, const uint64_t *len)
{
	sha->str = (uint8_t *)str;
	sha->len = *len;
	sha->pos = 0;
	sha->len_64_bit = sha->len * 8;
	sha->sha_buf[A] = 0x6A09E667;
	sha->sha_buf[B] = 0xBB67AE85;
	sha->sha_buf[C] = 0x3C6EF372;
	sha->sha_buf[D] = 0xA54FF53A;
	sha->sha_buf[E] = 0x510E527F;
	sha->sha_buf[F] = 0x9B05688C;
	sha->sha_buf[G] = 0x1F83D9AB;
	sha->sha_buf[H] = 0x5BE0CD19;
	sha->result = malloc(32);
	if (!sha->result)
		ft_err("Error malloc: sha256.c - sha_init - sha->result");
}

static void	sha_update(t_sha256 *sha)
{
	while (sha->len - sha->pos > 64)
	{
		sha256_algorithm(sha->str + sha->pos, sha->sha_buf, sha->sha_tmp);
		sha->pos += 64;
	}
}

static void	sha_final(t_sha256 *sha)
{
	uint8_t		*new_str;
	uint64_t	new_len;
	uint64_t	pos;
	int			i;

	new_len = ((sha->len - sha->pos + 1) / 64 + 1 + \
				((sha->len - sha->pos + 1) % 64 > 56)) * 64;
	new_str = malloc(new_len);
	if (!new_str)
		ft_err("Error malloc: sha256_main.c - sha_final - new_str");
	ft_bzero(new_str, (size_t)(new_len));
	ft_memcpy(new_str, sha->str + sha->pos, sha->len - sha->pos);
	ft_memset(new_str + sha->len - sha->pos, 1 << 7, 1);
	i = -1;
	while (++i < 8)
		ft_memcpy(new_str + new_len - i - 1, \
					(uint8_t *)(&sha->len_64_bit) + i, 1);
	pos = 0;
	while (new_len > pos)
	{
		sha256_algorithm(new_str + pos, sha->sha_buf, sha->sha_tmp);
		pos += 64;
	}
	free(new_str);
}

uint8_t	*sha256_main(const char *str, const uint64_t len)
{
	t_sha256	sha;
	int			i;

	sha_init(&sha, str, &len);
	sha_update(&sha);
	sha_final(&sha);
	i = -1;
	while (++i < 8)
	{
		sha.result[i] = (sha.sha_buf[0] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 4] = (sha.sha_buf[1] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 8] = (sha.sha_buf[2] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 12] = (sha.sha_buf[3] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 16] = (sha.sha_buf[4] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 20] = (sha.sha_buf[5] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 24] = (sha.sha_buf[6] >> (24 - i * 8)) & 0x000000ff;
		sha.result[i + 28] = (sha.sha_buf[7] >> (24 - i * 8)) & 0x000000ff;
	}
	return (sha.result);
}
