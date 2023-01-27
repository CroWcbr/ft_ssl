/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:49 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/27 17:26:54 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>

# include <stdint.h>
# include "./libft/include/libft.h"

typedef enum s_bool
{
	false,
	true
}			t_bool;

typedef struct s_ssl
{
	char			*hash;
	uint32_t		crypt_len;
	uint8_t			*(*hash_func)(const char *str, const uint64_t len);
	t_bool			p;
	t_bool			q;
	t_bool			r;
	t_bool			s;
	t_list			*hash_list;
}					t_ssl;

// type : 0 - string, 1 - file
typedef struct s_hash
{
	t_bool			type;
	char			*name;
}				t_hash;

t_ssl		*parse(char **argv);
int			parse_argv(char **argv, t_ssl *ssl);
void		parse_flag_p(t_ssl *ssl);
t_hash		*create_hash_node(char *name);
void		parse_print(t_ssl *ssl);

uint8_t		*read_file(uint8_t *(*hash_func)(const char *str, const uint64_t len), \
						t_hash *hash);

void		print_test(char *err, uint8_t *tt, int len_byte);
void		ft_err(char *str);

uint8_t		*md5_main(const char *str, const uint64_t len);
void		md5_algorithm(const uint8_t *str, \
							uint32_t *md_buf, uint32_t *md_tmp);

uint8_t		*sha256_main(const char *str, const uint64_t len);
void		sha256_algorithm(const uint8_t *str, \
							uint32_t *md_buf, uint32_t *md_tmp);

uint8_t		*sha512_main(const char *str, const uint64_t len);
void		sha512_algorithm(const uint8_t *str, \
						uint64_t *sha_buf, uint64_t *sha_tmp);

// void		whirlpool(const char *str, const uint64_t len);

#endif
