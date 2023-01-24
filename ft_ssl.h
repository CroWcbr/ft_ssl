/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:49 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/24 23:28:24 by cdarrell         ###   ########.fr       */
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
	void			(*hash_func)(const char *str, const uint64_t len);
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

void		read_file(void (*hash_func)(const char *str, const uint64_t len), \
						t_hash *hash);

void		ft_err(char *str);

void		md5(const char *str, const uint64_t len);
void		sha256(const char *str, const uint64_t len);
void		sha512(const char *str, const uint64_t len);
void		whirlpool(const char *str, const uint64_t len);

#endif
