/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:45 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/26 21:17:40 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	check_usage(char *argv)
{
	if (ft_strcmp(argv, "md5") && \
			ft_strcmp(argv, "sha256") && \
			ft_strcmp(argv, "sha512") && \
			ft_strcmp(argv, "whirlpool"))
	{
		ft_putstr("ft_ssl: Error: [");
		ft_putstr(argv);
		ft_putstr("] is an invalid command.\n");
		ft_putstr("\n");
		ft_putstr("Commands:\n");
		ft_putstr("md5\n");
		ft_putstr("sha256\n");
		ft_putstr("sha512\n");
		ft_putstr("whirlpool\n");
		ft_putstr("\n");
		ft_putstr("Flags:\n");
		ft_putstr("-p -q -r -s\n");
		return (0);
	}
	else
		return (1);
}

static void	*init_ssl_hash_function(t_ssl *ssl)
{
	if (!ft_strcmp(ssl->hash, "md5"))
	{
		ssl->hash_func = &md5_main;
		ssl->crypt_len = 16;
	}
	else if (!ft_strcmp(ssl->hash, "sha256"))
	{
		ssl->hash_func = &sha256_main;
		ssl->crypt_len = 32;
	}
	// else if (!ft_strcmp(ssl->hash, "sha512"))
	// {
	// 	ssl->hash_func = &sha512;
	// 	ssl->crypt_len = 64;
	// }
	// else if (!ft_strcmp(ssl->hash, "whirlpool"))
	// {
	// 	ssl->hash_func = &whirlpool;
	// 	ssl->crypt_len = 64;
	// }
}

static t_ssl	*init_ssl(char *hash_alg)
{	
	t_ssl	*ssl;

	ssl = malloc(sizeof(t_ssl));
	if (!ssl)
		ft_err("Error malloc: parsing.c - init_ssl - ssl");
	ssl->hash = hash_alg;
	init_ssl_hash_function(ssl);
	ssl->p = false;
	ssl->q = false;
	ssl->r = false;
	ssl->s = false;
	ssl->hash_list = NULL;
	return (ssl);
}

t_hash	*create_hash_node(char *name)
{
	t_hash	*input;

	input = malloc(sizeof(t_hash));
	if (!input)
		ft_err("Error malloc: parsing.c - parse_hash_list - input");
	input->type = true;
	input->name = ft_strdup(name);
	if (!input->name)
		ft_err("Error malloc: parsing.c - parse_hash_list - input->name");
	return (input);
}

t_ssl	*parse(char **argv)
{
	t_ssl	*ssl;

	if (!check_usage(argv[0]))
		return (NULL);
	ssl = init_ssl(argv[0]);
	if (!parse_argv(argv + 1, ssl))
	{
		free(ssl);
		return (NULL);
	}
	if (ssl->p == true || !ssl->hash_list)
		parse_flag_p(ssl);
	return (ssl);
}
