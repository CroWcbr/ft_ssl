/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:12:37 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/27 00:40:01 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>

#define ROTRIGHT(a,b)	(((a) >> (b)) | ((a) << (32-(b))))
#define CH(x,y,z)		(((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)			(ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x)			(ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x)			(ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x)			(ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

# define A	0
# define B	1
# define C	2
# define D	3
# define E	4
# define F	5
# define G	6
# define H	7

static const uint32_t	g_k[64] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, \
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
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2 \
};

typedef struct s_sha256
{
	uint8_t			*str;
	uint64_t		len;
	uint64_t		pos;
	uint64_t		len_64_bit;
	uint32_t		sha_buf[8];
	uint32_t		sha_tmp[8];
	uint8_t			*result;
}t_sha256;

#endif
