/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:42:35 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:42:40 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSSL_H
# define FTSSL_H
# include "ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# define K_LEN 64
# define S_LEN 64
# define K_LEN_EXTENDED
# define LROT(x, c, sz) ((x << c) | (x >> (sz - c)))
# define RROT(x, c, sz) ((x >> c) | (x << (sz - c)))
# define CHUNK_SIZES "\100\100\100\200\200\200\200"
# define HASH_SIZES "\020\040\040\100\100\100\100"
# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8
# define FLAG_STDIN 32
# define FLAG_I 16
# define FLAGS_SSL "pqrsi"
# define FLAG_SSL_TOTAL 5
# define MD_TXT {"MD5","SHA256","SHA224","SHA512","SHA384","SHA512/256", "SHA512/224"}

extern uint32_t g_svars[S_LEN];
extern uint32_t	g_kvars_md[K_LEN];
extern uint32_t	g_kvars_sha[K_LEN];
extern uint64_t g_kvars_sha512[K_LEN_EXTENDED];

typedef enum		e_mdvar
{
	A_MD,
	B_MD,
	C_MD,
	D_MD,
	MD_VAR_TOTAL
}					t_mdvar;

typedef enum		e_shavar
{
	H_ZERO,
	H_ONE,
	H_TWO,
	H_THREE,
	H_FOUR,
	H_FIVE,
	H_SIX,
	H_SEVEN,
	SHA_VAR_TOTAL
}					t_shavar;

typedef enum		e_hashtype
{
	UNDEFINED = -1,
	HASH_MD_FIVE,
	HASH_SHA256,
	HASH_SHA224,
	HASH_SHA512,
	HASH_SHA384,
	HASH_SHA512_256,
	HASH_SHA512_224,
	HASH_TOTAL
}					t_hashtype;

typedef struct		s_container
{
	void			*vars;
	void			*padded_msg;
	size_t			padded_msg_len;
	t_hashtype		hashtype;
}					t_container;

typedef void	(*t_proceedchunk)(t_container *c,
				uint8_t *chunk);
typedef void	*(*t_create_padded_msg)(void *msg,
				size_t msg_len,
				size_t *new_msg_len);

extern t_proceedchunk g_chunkfuncs[HASH_TOTAL];
extern t_create_padded_msg g_cr_padd_funcs[HASH_TOTAL];

typedef void	(*t_print_md)(t_container *hash);
void				*get_stream(const int fd,
					void *buf,
					size_t buf_size);

/*
** Initialize hash values
*/
void				initialize_vars(t_container *c);

/*
** Creating padded messages 
** for differrent hash types
*/
void				*create_padded_msg_md5(void *msg,
					size_t msg_len,	size_t *new_msg_len);
void				*create_padded_msg_sha2(void *msg,
					size_t msg_len,	size_t *new_msg_len);
void				*create_padded_msg_sha512(void *msg,
					size_t msg_len, size_t *new_msg_len);

/*
** Chunk proceeding algorithms
** for different types
*/
void				proceed_chunk_md5(t_container *md,
					uint8_t *chunk);
void				proceed_chunk_sha2(t_container *sha,
					uint8_t *chunk);
void				proceed_chunk_sha512(t_container *sha,
					uint8_t *chunk);

t_container			ft_hash(uint8_t *msg,
					size_t len, t_hashtype htype);

char				*get_msg_from_file(const char *filename);
void				reverse(uint8_t *ptr, size_t size);
void				reverse_md(t_container *md);
void				ft_print_hash(t_container *hash);
void				ft_print_md5(t_container *hash);
void				ft_print_sha256(t_container *hash);
void				ft_print_sha224(t_container *hash);
void				ft_print_sha512(t_container *hash);
void				ft_print_sha384(t_container *hash);
void				ft_print_sha512_256(t_container *hash);
void				ft_print_sha512_224(t_container *hash);
#endif
