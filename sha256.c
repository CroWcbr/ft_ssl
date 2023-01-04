/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/05 02:37:21 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static unsigned char	*sha256_update_str(const char *str, const uint64_t len, uint64_t *new_len)
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
	// int j = 0;
	// while (j < 64)
	// {
	// 	int i = 7;
	// 	printf("%d\t%d\t", j, (int)new_str[j]);
	// 	while (i >= 0)
	// 	{
	// 		printf("%d", (new_str[j] & (1 << i)) >> i);
	// 		i--;
	// 	}
	// 	printf("\n");
	// 	j++;
	// }
	return new_str;
}

void print_test(char *err, uint8_t	*tt, int len_byte)
{
	int jj = 0;
	printf("%s\n", err);
	while (jj < len_byte)
	{
		int i = 7;
		if (jj % 4 == 0)
			printf("%d\t", jj);
		// printf("\n%p\n", &tt[jj]);
		while (i >= 0)
		{
			printf("%d", (tt[jj] >> i) & 1);
			i--;
		}
		// printf(" ");
		jj++;
		if (jj % 4 == 0)
			printf("\n");
	}
	printf("\n");
}

void	sha256_algo(const uint8_t *new_str, \
		const uint64_t new_len, uint32_t *sha_buf, uint32_t *sha)
{
	int kk = 0;

	uint32_t	m[64];
//	init_tmp_words(tmp_words, (uint32_t *)new_str);
	uint32_t i, j;
	
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (new_str[j] << 24) | (new_str[j + 1] << 16) | (new_str[j + 2] << 8) | (new_str[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];


	// while (kk < new_len / 64)
	// {
		uint32_t	w[64];

	// 	// printf("!!!!!!!!!!!!!!!!!!!!!!!\n");
	// 	ft_memcpy(w, new_str, 64);

		// int ii = 16;
		// for (; ii < 64; ii++)
		// {
	// 		uint32_t	s0;
	// 		uint32_t	s1;
	// 		s0 = SIG0(w[ii - 15]);
	// 		s1 = SIG1(w[ii - 2]);
	// 		// s0 = (w[ii - 15] >> 7 | w[ii - 15] << 25) ^ (w[ii - 15] >> 18 | w[ii - 15] << 14) ^ (w[ii - 15] >> 3);
	// 		// s1 = (w[ii - 2] >> 17 | w[ii - 2] << 15) ^ (w[ii - 2] >> 19 | w[ii - 2] << 13) ^ (w[ii - 2] >> 10);
	// 		w[ii] = w[ii - 16] + s0 + w[ii - 7] + s1;
			
	// 		printf("\n\t%u\n", w[1]);
	// 		print_test("w1", (uint8_t *)&w[1], sizeof(w[1]));

	// 		uint32_t xxxx2 = (uint32_t)(w[1]);
	// 		printf("\n\t%u\n", xxxx2);

	// 		uint32_t xxxx = 1864398703;
	// 		// printf("\n1\t%u\n", w[1]);
	// 		// printf("\n2\t%d\n", w[1]);
	// 		printf("\n3\t%u\n", xxxx);
	// 		print_test("xxxx", (uint8_t *)&xxxx, sizeof(xxxx));

	// 		// uint32_t xxxx2 = xxxx >> 3;
	// 		// printf("\n%u\n", xxxx2);
	// 		// for (int i = 31; i >= 0; i--)
	// 		// 	printf("%d", ((xxxx2 >> i) & 1));
	// 		// printf("\n");

	// 		// uint32_t xxxx3 = xxxx / 2 / 2 / 2;
	// 		// printf("\n%u\n", xxxx3);
	// 		// for (int i = 31; i >= 0; i--)
	// 		// 	printf("%d", ((xxxx3 >> i) & 1));
	// 		// printf("\n");


	// 		break;

	// 		// uint32_t tmp = 1864398703;
	// 		// uint32_t wr7 = w[ii - 15] << 7 | w[ii - 15] >> 25;
	// 		// // uint32_t wr725 = tmp << 25;
	// 		// print_test("w1", (uint8_t *)&tmp);
	// 		// print_test("wr7", (uint8_t *)&wr7);


	// 		// print_test("s0\t", (uint8_t *)&s0);
			
	// 		// print_test("s1\t", &s1);
	// 		// print_test("ww", w[ii]);
	// 		// printf("??????????????????????????\n");
	// 		// exit (0);
	// 	}

	// // int jj = 64;
	// // uint8_t	*tt = (uint8_t	*)w;
	// // while (jj < 64 * 4)
	// // {
	// // 	int i = 7;
	// // 	if (jj % 4 == 0)
	// // 		printf("%d\t", jj);
	// // 	while (i >= 0)
	// // 	{
	// // 		printf("%d", (tt[jj] & (1 << i)) >> i);
	// // 		i--;
	// // 	}
	// // 	// printf(" ");
	// // 	jj++;
	// // 	if (jj % 4 == 0)
	// // 		printf("\n");
	// // }


	// 	// int jj = 0;
	// 	// while (jj < 64)
	// 	// {	
	// 	// 	uint8_t	*tt = &w[jj];
	// 	// 	int i = 7;
	// 	// 	printf("%d\t%u\t\t", jj, w[jj]);
	// 	// 	uint8_t *ttt;
	// 	// 	ttt = tt;
	// 	// 	while (i >= 0)
	// 	// 	{
	// 	// 		printf("%d", (ttt[jj] & (1 << i)) >> i);
	// 	// 		i--;
	// 	// 	}
	// 	// 	tt++;
	// 	// 	ttt = tt;
	// 	// 	i = 7;
	// 	// 	printf(" ");
	// 	// 	while (i >= 0)
	// 	// 	{
	// 	// 		printf("%d", (ttt[jj] & (1 << i)) >> i);
	// 	// 		i--;
	// 	// 	}
	// 	// 	tt++;
	// 	// 	ttt = tt;
	// 	// 	i = 7;
	// 	// 	printf(" ");
	// 	// 	while (i >= 0)
	// 	// 	{
	// 	// 		printf("%d", (ttt[jj] & (1 << i)) >> i);
	// 	// 		i--;
	// 	// 	}
	// 	// 	tt++;
	// 	// 	ttt = tt;
	// 	// 	i = 7;
	// 	// 	printf(" ");
	// 	// 	while (i >= 0)
	// 	// 	{
	// 	// 		printf("%d", (ttt[jj] & (1 << i)) >> i);
	// 	// 		i--;
	// 	// 	}

	// 	// 	printf("\n");
	// 	// 	jj++;
	// 	// }

		uint32_t a, b, c, d, e, f, g, h;

		// sha[H0] = sha_buf[H0];
		// sha[H1] = sha_buf[H1];
		// sha[H2] = sha_buf[H2];
		// sha[H3] = sha_buf[H3];
		// sha[H4] = sha_buf[H4];
		// sha[H5] = sha_buf[H5];
		// sha[H6] = sha_buf[H6];
		// sha[H7] = sha_buf[H7];

		a = sha_buf[H0];
		b = sha_buf[H1];
		c = sha_buf[H2];
		d = sha_buf[H3];
		e = sha_buf[H4];
		f = sha_buf[H5];
		g = sha_buf[H6];
		h = sha_buf[H7];


		uint32_t t1, t2;
		for (i = 0; i < 64; ++i) {
			t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
			t2 = EP0(a) + MAJ(a,b,c);
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}
		sha_buf[H0] += a;
		sha_buf[H1] += b;
		sha_buf[H2] += c;
		sha_buf[H3] += d;
		sha_buf[H4] += e;
		sha_buf[H5] += f;
		sha_buf[H6] += g;
		sha_buf[H7] += h;

		// int j = -1;
		// while (++j < 64)
		// {
		// 	uint32_t E0, Ma, t2, E1, Ch, t1;
		// 	E0 = EP0(sha[A]);
		// 	Ma = MAJ(sha[A], sha[B], sha[C]);
		// 	t2 = E0 + Ma;
		// 	E1 = EP1(sha[E]);
		// 	Ch = CH(sha[E], sha[F], sha[G]);
		// 	t1 = sha[H] + E1 + Ch + k[j] + w[j];

		// 	sha[H] = sha[G];
		// 	sha[G] = sha[F];
		// 	sha[F] = sha[E];
		// 	sha[E] = sha[D] + t1;
		// 	sha[D] = sha[C];
		// 	sha[C] = sha[B];
		// 	sha[B] = sha[A];
		// 	sha[A] = t1 + t2;
		// }

		// sha_buf[H0] += sha[H0];
		// sha_buf[H1] += sha[H1];
		// sha_buf[H2] += sha[H2];
		// sha_buf[H3] += sha[H3];
		// sha_buf[H4] += sha[H4];
		// sha_buf[H5] += sha[H5];
		// sha_buf[H6] += sha[H6];
		// sha_buf[H7] += sha[H7];


	// 	kk++;
	// }
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

	// unsigned int	tmp = sha_buf[H0];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H1];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H2];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H3];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H4];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H5];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H6];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// tmp = sha_buf[H7];
	// printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	// printf("\n");

	unsigned char	digist[32];
	// ft_memcpy(digist + 0, &sha_buf[H0], 4);
	// ft_memcpy(digist + 4, &sha_buf[H1], 4);
	// ft_memcpy(digist + 8, &sha_buf[H2], 4);
	// ft_memcpy(digist + 12, &sha_buf[H3], 4);
	// ft_memcpy(digist + 16, &sha_buf[H4], 4);
	// ft_memcpy(digist + 20, &sha_buf[H5], 4);
	// ft_memcpy(digist + 24, &sha_buf[H6], 4);
	// ft_memcpy(digist + 28, &sha_buf[H7], 4);
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

	// uint64_t	ddd;
	// ddd = sha_buf[H0] | sha_buf[H1] | sha_buf[H2] | sha_buf[H3] | sha_buf[H4] | sha_buf[H5] | sha_buf[H6] | sha_buf[H7];
	// for (int iii = 0; iii < 32; iii++)
	// 	printf("%02x ", ddd);
	printf("\n");
}