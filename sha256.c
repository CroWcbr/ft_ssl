/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:37:14 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/25 15:01:29 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned int k[64] = {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, \
							0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, \
							0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, \
							0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, \
							0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, \
							0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, \
							0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, \
							0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, \
							0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, \
							0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, \
							0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, \
							0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, \
							0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, \
							0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, \
							0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, \
							0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

static unsigned char	*sha256_update_str(const char *str, const uint64_t len, uint64_t new_len)
{
	unsigned char		*new_str;
	uint64_t			tmp;

	// printf("%ld\t%ld\n", len, new_len);

	new_str = malloc(new_len);
	if (!new_len)
		ft_err("Error malloc: sha256 new_str");
	ft_memcpy(new_str, str, len);
	*(new_str + len) = 1 << 7;

// printf("%ld\t%ld\n", len, new_len);
	tmp = len + 1;
	while (tmp % 64 < 56)		//add 0 to 448 bit (56 byte)
		*(new_str + tmp++) = 0;
	// ft_memset(new_str + len + 1, 0, 56 - (len + 1) % 64);

// printf("%ld\t%ld\n", len, new_len);
	
	uint64_t tttttt = len * 8;
	// ft_memcpy(new_str + new_len - 8, &tttttt, 8);	//len

	for (int i = 0; i < 8; i++)
	{
		printf("%p\n", &tttttt + i);
		uint64_t tttttt2 = tttttt << (i * 8);
		ft_memcpy(new_str + new_len - i - 1, &tttttt2, 1);
		//*(new_str + new_len - 8 + i) = (unsigned char)(&tttttt + 7 - i);
	}

	
// printf("%ld\t%ld\n", len, new_len);
	// tmp = (len + 1) % 64;
	// while (tmp < 56)		//add 0 to 448 bit (56 byte)
	// 	*(new_str + tmp++) = 0;
	// uint64_t tttttt = len * 8;
	// ft_memcpy(new_str + tmp, &tttttt, 8);	//len
	// printf("new_str = %s\n", new_str);
	int j = 0;
	while (j < 64)
	{
		int i = 7;
		printf("%d\t%d\t", j, (int)new_str[j]);
		while (i >= 0)
		{
			printf("%d", (new_str[j] & (1 << i)) >> i);
			i--;
		}
		printf("\n");
		j++;
	}
	return new_str;
}

void	sha256(const char *str, const uint64_t len)
{
	unsigned int h0 = 0x6A09E667;
	unsigned int h1 = 0xBB67AE85;
	unsigned int h2 = 0x3C6EF372;
	unsigned int h3 = 0xA54FF53A;
	unsigned int h4 = 0x510E527F;
	unsigned int h5 = 0x9B05688C;
	unsigned int h6 = 0x1F83D9AB;
	unsigned int h7 = 0x5BE0CD19;

	uint64_t		new_len;
	unsigned char	*new_str;

	new_len = ((len + 1) / 64 + 1 + ((len + 1) % 64 > 56)) * 64;
	new_str = sha256_update_str(str, len, new_len);

	int kk = 0;
	while (kk < new_len / 64)
	{
		unsigned char w[64][4];
		int ii = 0;
		for (; ii < 16; ii++)
		{
			w[ii][0] = *(new_str + kk*64 + ii * 4);
			w[ii][1] = *(new_str + kk*64 + ii * 4 + 1);
			w[ii][2] = *(new_str + kk*64 + ii * 4 + 2);
			w[ii][3] = *(new_str + kk*64 + ii * 4 + 3);
		}

		// unsigned int s0, s1;
		// for (; ii < 64; ii++)
		// {
		// 	s0 = (w[ii-15] rotr 7) xor (w[ii-15] rotr 18) xor (w[ii-15] shr 3)
		// 	s1 = (w[ii-2] rotr 17) xor (w[ii-2] rotr 19) xor (w[ii-2] shr 10)
		// 	w[ii] = w[ii-16] + s0 + w[ii-7] + s1
		// }
		// для i от 16 до 63
        // s0 := (w[i-15] rotr 7) xor (w[i-15] rotr 18) xor (w[i-15] shr 3)
        // s1 := (w[i-2] rotr 17) xor (w[i-2] rotr 19) xor (w[i-2] shr 10)
        // w[i] := w[i-16] + s0 + w[i-7] + s1

		unsigned int a = h0;
		unsigned int b = h1;
		unsigned int c = h2;
		unsigned int d = h3;
		unsigned int e = h4;
		unsigned int f = h5;
		unsigned int g = h6;
		unsigned int h = h7;



		h0 = h0 + a;
		h1 = h1 + b;
		h2 = h2 + c;
		h3 = h3 + d;
		h4 = h4 + e;
		h5 = h5 + f;
		h6 = h6 + g;
		h7 = h7 + h;

	}
}
