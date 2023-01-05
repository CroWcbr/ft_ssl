/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/05 21:53:51 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

void print_test(char *err, uint8_t	*tt, int len_byte)
{
	int jj = 0;
	printf("\n%s\n", err);
	while (jj < len_byte)
	{
		int i = 7;
		if (jj % 4 == 0)
			printf("%d\t", jj);
		while (i >= 0)
		{
			printf("%d", (tt[jj] >> i) & 1);
			i--;
		}
		printf(" ");
		jj++;
		if (jj % 4 == 0)
			printf("\n");
	}
	printf("\n");
}

static uint8_t	*sha256_update_str(const char *str, const uint64_t len, uint64_t *new_len)
{
	uint8_t			*new_str;
	uint64_t		len_64_bit;

	*new_len = ((len + 1) / 64 + 1 + ((len + 1) % 64 > 56)) * 64;
	new_str = malloc(*new_len);
	if (!new_str)
		ft_err("Error malloc: sha256 new_str");
	ft_bzero(new_str, (size_t)(*new_len));
	ft_memcpy(new_str, str, len);
	ft_memset(new_str + len, 1 << 7, 1);
	len_64_bit = len * 8;
	for (int i = 0; i < 8; i++)
		ft_memcpy(new_str + *new_len - i - 1, (uint8_t *)&len_64_bit + i, 1);
	print_test("word", new_str, *new_len);
	return new_str;
}

void	sha256_algo(const uint8_t *new_str, \
		const uint64_t new_len, uint32_t *sha_buf, uint32_t *sha)
{
	int kk;

	kk = 0;
	while (kk < new_len / 64)
	{
		uint32_t	w[64];
		uint32_t i, j;

		for (i = 0, j = 0; i < 16; ++i, j += 4)
			w[i] = (((new_str + kk * 64)[j]) << 24) | ((new_str + kk * 64)[j + 1] << 16) | ((new_str + kk * 64)[j + 2] << 8) | ((new_str + kk * 64)[j + 3]);
		for ( ; i < 64; ++i)
			w[i] = SIG1(w[i - 2]) + w[i - 7] + SIG0(w[i - 15]) + w[i - 16];

print_test("w", (uint8_t *)&w, 4*16);
exit;
		sha[A] = sha_buf[H0];
		sha[B] = sha_buf[H1];
		sha[C] = sha_buf[H2];
		sha[D] = sha_buf[H3];
		sha[E] = sha_buf[H4];
		sha[F] = sha_buf[H5];
		sha[G] = sha_buf[H6];
		sha[H] = sha_buf[H7];

		uint32_t t1, t2;
		for (i = 0; i < 64; ++i) {
			t1 = sha[H] + EP1(sha[E]) + CH(sha[E],sha[F],sha[G]) + k[i] + w[i];
			t2 = EP0(sha[A]) + MAJ(sha[A],sha[B],sha[C]);

			sha[H] = sha[G];
			sha[G] = sha[F];
			sha[F] = sha[E];
			sha[E] = sha[D] + t1;
			sha[D] = sha[C];
			sha[C] = sha[B];
			sha[B] = sha[A];
			sha[A] = t1 + t2;
		}
		sha_buf[H0] += sha[A];
		sha_buf[H1] += sha[B];
		sha_buf[H2] += sha[C];
		sha_buf[H3] += sha[D];
		sha_buf[H4] += sha[E];
		sha_buf[H5] += sha[F];
		sha_buf[H6] += sha[G];
		sha_buf[H7] += sha[H];

		kk++;
	}
}

void	sha256(const char *str, const uint64_t len)
{
	uint8_t			*new_str;
	uint64_t		new_len;
	uint32_t		sha_buf[8];
	uint32_t		sha[8];
	
	new_str = sha256_update_str(str, len, &new_len);
	sha_buf[H0] = 0x6A09E667;
	sha_buf[H1] = 0xBB67AE85;
	sha_buf[H2] = 0x3C6EF372;
	sha_buf[H3] = 0xA54FF53A;
	sha_buf[H4] = 0x510E527F;
	sha_buf[H5] = 0x9B05688C;
	sha_buf[H6] = 0x1F83D9AB;
	sha_buf[H7] = 0x5BE0CD19;

	sha256_algo(new_str, new_len, sha_buf, sha);

	uint8_t	digist[32];
	for (int i = 0; i < 4; ++i) {
		digist[i]      = (sha_buf[0] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 4]  = (sha_buf[1] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 8]  = (sha_buf[2] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 12] = (sha_buf[3] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 16] = (sha_buf[4] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 20] = (sha_buf[5] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 24] = (sha_buf[6] >> (24 - i * 8)) & 0x000000ff;
		digist[i + 28] = (sha_buf[7] >> (24 - i * 8)) & 0x000000ff;
	}
	for (int iii = 0; iii < 32; iii++)
		printf("%02x", digist[iii]);
	printf("\n");
}
