/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/28 02:42:16 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

static void	sha_init(t_sha512 *sha, const char *str, const uint64_t *len)
{
	sha->str = (uint8_t *)str;
	sha->len = *len;
	sha->pos = 0;
	sha->len_64_bit = sha->len * 8;
	sha->sha_buf[A] = 0x6a09e667f3bcc908;
	sha->sha_buf[B] = 0xbb67ae8584caa73b;
	sha->sha_buf[C] = 0x3c6ef372fe94f82b;
	sha->sha_buf[D] = 0xa54ff53a5f1d36f1;
	sha->sha_buf[E] = 0x510e527fade682d1;
	sha->sha_buf[F] = 0x9b05688c2b3e6c1f;
	sha->sha_buf[G] = 0x1f83d9abfb41bd6b;
	sha->sha_buf[H] = 0x5be0cd19137e2179;
	sha->result = malloc(64);
	if (!sha->result)
		ft_err("Error malloc: sha256.c - sha_init - sha->result");
}

static void	sha_update(t_sha512 *sha)
{
	while (sha->len - sha->pos > 128)
	{
		sha512_algorithm(sha->str + sha->pos, sha->sha_buf, sha->sha_tmp);
		sha->pos += 128;
	}
}

static void	sha_final(t_sha512 *sha)
{
	uint8_t				*new_str;
	uint64_t			new_len;
	uint64_t			pos;

	new_len = ((sha->len - sha->pos + 1) / 128 + 1 + \
				((sha->len - sha->pos + 1) % 128 > 112)) * 128;
	new_str = malloc(new_len);
	if (!new_str)
		ft_err("Error malloc: sha512_main.c - sha_final - new_str");
	ft_bzero(new_str, (size_t)(new_len));
	ft_memcpy(new_str, sha->str + sha->pos, sha->len - sha->pos);
	ft_memset(new_str + sha->len - sha->pos, 1 << 7, 1);
	for (int i = 0; i < 8; i++)
		ft_memcpy(new_str + new_len - i - 1, (uint8_t *)(&sha->len_64_bit) + i, 1);

	// print_test("new_str", new_str, 20);
	// printf("len = %ld\n", new_len);
	pos = 0;
	while (new_len > pos)
	{
		// printf("pos = %ld\n", pos);
		sha512_algorithm(new_str + pos, sha->sha_buf, sha->sha_tmp);
		pos += 128;
	}
	free(new_str);
}

uint8_t	*sha512_main(const char *str, const uint64_t len)
{
	t_sha512	sha;

	sha_init(&sha, str, &len);
	sha_update(&sha);
	sha_final(&sha);

	for (int i = 0; i < 8; ++i)
	{
		sha.result[i]      = ((sha.sha_buf[0]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 8]  = ((sha.sha_buf[1]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 16] = ((sha.sha_buf[2]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 24] = ((sha.sha_buf[3]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 32] = ((sha.sha_buf[4]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 40] = ((sha.sha_buf[5]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 48] = ((sha.sha_buf[6]) >> (56 - i * 8)) & 0x000000ff;
		sha.result[i + 56] = ((sha.sha_buf[7]) >> (56 - i * 8)) & 0x000000ff;
	}
	// for(int i = 0; i < 8; i++)
	// 	printf("%016lx", sha.sha_buf[i]);
	// printf("\n");

	return sha.result;
}
