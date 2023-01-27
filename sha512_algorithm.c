/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:23:27 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/28 02:34:03 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"
#include "ft_ssl.h"

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
	// print_test("w", (uint8_t *)w, 80 * 8);
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


// static uint8_t	*sha512_update_str(const char *str, const uint64_t len, uint64_t *new_len)
// {
// 	uint8_t			*new_str;
// 	__uint128_t		len_64_bit;

// 	*new_len = ((len + 1) / 128 + 1 + ((len + 1) % 128 > 112)) * 128;
// 	new_str = malloc(*new_len);
// 	if (!new_str)
// 		ft_err("Error malloc: sha256 new_str");
// 	ft_bzero(new_str, (size_t)(*new_len));
// 	ft_memcpy(new_str, str, len);
// 	ft_memset(new_str + len, 1 << 7, 1);
// 	len_64_bit = len * 8;
// 	for (int i = 0; i < 16; i++)
// 		ft_memcpy(new_str + *new_len - i - 1, (uint8_t *)&len_64_bit + i, 1);
// 	print_testt("word", new_str, *new_len);
// 	return new_str;
// }

// void	sha512_algo(const uint8_t *new_str, \
// 		const uint64_t new_len, uint64_t *sha_buf, uint64_t *sha)
// {
// 	int kk;

// 	kk = 0;
// 	// while (kk < new_len / 128)
// 	// {
// 		uint64_t	w[80];
// 		uint64_t i, j;

// 	int t;
// 	for (t = 0; t < 16; t++)
// 	{
// 		w[t] = ((unsigned long long int) new_str[t * 8 + 0] << 56) |
// 			((unsigned long long int) new_str[t * 8 + 1] << 48) |
// 			((unsigned long long int) new_str[t * 8 + 2] << 40) |
// 			((unsigned long long int) new_str[t * 8 + 3] << 32) |
// 			((unsigned long long int) new_str[t * 8 + 4] << 24) |
// 			((unsigned long long int) new_str[t * 8 + 5] << 16) |
// 			((unsigned long long int) new_str[t * 8 + 6] << 8) |
// 			((unsigned long long int) new_str[t * 8 + 7]);
// 	}

// 		for (t = 16; t < 80; t++) 
// 		{
// 			w[t] = w[t-16] + (w[t-7] + SIG0(w[t-15]) + w[t-2]) + SIG1(w[t-2]);
// 		}

// 		// for (i = 0, j = 0; i < 16; ++i, j += 8)
// 		// {
// 		// 	uint32_t x1 = (((new_str + kk * 64)[j]) << 24) | ((new_str + kk * 64)[j + 1] << 16) | ((new_str + kk * 64)[j + 2] << 8) | ((new_str + kk * 64)[j + 3]);
// 		// 	uint32_t x2 = (((new_str + kk * 64 + 64)[j]) << 24) | ((new_str + kk * 64 + 64)[j + 1] << 16) | ((new_str + kk * 64 + 64)[j + 2] << 8) | ((new_str + kk * 64 + 64)[j + 3]);

// 		// 	w[i] = (uint64_t)x2 >> 32 | (uint64_t)x1 << 32;

// 		// 	// w[i] = (((new_str + kk * 128)[j]) << 24) | ((new_str + kk * 128)[j + 1] << 16) | ((new_str + kk * 128)[j + 2] << 8) | ((new_str + kk * 128)[j + 3] | \
// 		// 	// 		((new_str + kk * 128)[j + 4]) << 56) | ((new_str + kk * 128)[j + 5] << 48) | ((new_str + kk * 128)[j + 6] << 40) | ((new_str + kk * 128)[j + 7] << 32);

// 		// 	// w[i] = (((new_str + kk * 128)[j]) << 56) | ((new_str + kk * 128)[j + 1] << 48) | ((new_str + kk * 128)[j + 2] << 40) | ((new_str + kk * 128)[j + 3] << 32 | \
// 		// 	// 		((new_str + kk * 128)[j + 4]) << 24) | ((new_str + kk * 128)[j + 5] << 16) | ((new_str + kk * 128)[j + 6] << 8) | ((new_str + kk * 128)[j + 7]);

// 		// }
// 			// w[i] = (((new_str + kk * 128)[j]) << 56) | ((new_str + kk * 128)[j + 1] << 48) | ((new_str + kk * 128)[j + 2] << 40) | ((new_str + kk * 128)[j + 3] << 32 | \
// 			// 		((new_str + kk * 128)[j + 4]) << 24) | ((new_str + kk * 128)[j + 5] << 16) | ((new_str + kk * 128)[j + 6] << 8) | ((new_str + kk * 128)[j + 7]);

// 		// for ( ; i < 80; ++i)
// 		// 	w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];

// 		// print_testt("w", (uint8_t *)&w, 1024);
// 		sha[A] = sha_buf[H0];
// 		sha[B] = sha_buf[H1];
// 		sha[C] = sha_buf[H2];
// 		sha[D] = sha_buf[H3];
// 		sha[E] = sha_buf[H4];
// 		sha[F] = sha_buf[H5];
// 		sha[G] = sha_buf[H6];
// 		sha[H] = sha_buf[H7];

// 		uint64_t t1, t2;
// 		for (i = 0; i < 80; ++i) 
// 		{
// 			t1 = sha[H] + EP1(sha[E]) + CH(sha[E],sha[F],sha[G]) + k[i] + w[i];
// 			t2 = EP0(sha[A]) + MAJ(sha[A],sha[B],sha[C]);

// 			sha[H] = sha[G];
// 			sha[G] = sha[F];
// 			sha[F] = sha[E];
// 			sha[E] = sha[D] + t1;
// 			sha[D] = sha[C];
// 			sha[C] = sha[B];
// 			sha[B] = sha[A];
// 			sha[A] = t1 + t2;
// 		}
// 		sha_buf[H0] += sha[A];
// 		sha_buf[H1] += sha[B];
// 		sha_buf[H2] += sha[C];
// 		sha_buf[H3] += sha[D];
// 		sha_buf[H4] += sha[E];
// 		sha_buf[H5] += sha[F];
// 		sha_buf[H6] += sha[G];
// 		sha_buf[H7] += sha[H];

// 		kk++;
// 	// }
// }

// void	sha512(const char *str, const uint64_t len)
// {
// 	uint8_t			*new_str;
// 	uint64_t		new_len;
// 	uint64_t		sha_buf[8];
// 	uint64_t		sha[8];

// 	new_str = sha512_update_str(str, len, &new_len);
// 	sha_buf[H0] = 0x6a09e667f3bcc908;
// 	sha_buf[H1] = 0xbb67ae8584caa73b;
// 	sha_buf[H2] = 0x3c6ef372fe94f82b;
// 	sha_buf[H3] = 0xa54ff53a5f1d36f1;
// 	sha_buf[H4] = 0x510e527fade682d1;
// 	sha_buf[H5] = 0x9b05688c2b3e6c1f;
// 	sha_buf[H6] = 0x1f83d9abfb41bd6b;
// 	sha_buf[H7] = 0x5be0cd19137e2179;

// 	sha512_algo(new_str, new_len, sha_buf, sha);

// 	uint8_t	digist[64];
// 	for (int i = 0; i < 8; ++i) {
// 		digist[i]      = (sha_buf[0] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 8]  = (sha_buf[1] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 16]  = (sha_buf[2] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 24] = (sha_buf[3] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 32] = (sha_buf[4] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 40] = (sha_buf[5] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 48] = (sha_buf[6] >> (56 - i * 8)) & 0x000000ff;
// 		digist[i + 56] = (sha_buf[7] >> (56 - i * 8)) & 0x000000ff;
// 	}
// 	for (int iii = 0; iii < 64; iii++)
// 		printf("%02x", digist[iii]);
// 	printf("\n");
// }
