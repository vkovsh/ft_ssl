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

#ifndef FT_SSL_H
# define FT_SSL_H
# include "ft_printf.h"
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# define K_LEN 64
# define S_LEN 64
# define K_LEN_EXTENDED
# define LROT(x,c) (((x)<<(c))|((x)>>((sizeof(x)<<3)-(c))))
# define RROT(x,c) (((x)>>(c))|((x)<<((sizeof(x)<<3)-(c))))
# define CHUNK_SIZES "\100\100\100\200\200\200\200"
# define HASH_SIZES "\020\040\040\100\100\100\100"
# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8
# define FLAG_I 16
# define FLAG_O 32
# define FLAG_E 64
# define FLAG_D 128
# define FLAG_A 256
# define FLAG_K 512
# define FLAG_V 1024
# define FLAG_STDIN 2048
# define FLAGS_SSL "pqrsioedakv"
# define FLAG_SSL_TOTAL 11
# define PART_ONE "MD5","SHA256","SHA224","SHA512"
# define MD_TXT {PART_ONE,"SHA384","SHA512/256","SHA512/224"}
# define INV_OPT "%s '%c'\n", "ft_ssl: invalid option --"
# define NO_FILE "'%s': No such file or directory\n"
# define USG "ft_ssl command[command opts][command args]\n"
# define ALPHA_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ALPHA_LOW "abcdefghijklmnopqrstuvwxyz"
# define NUMBERS "0123456789"
# define BASE64_TRANSFORM ALPHA_UPPER ALPHA_LOW NUMBERS "+/"
# define CIPHER_TXT {"BASE64"}
# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	H0,
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
	H7,
	SHA_VAR_TOTAL
}					t_shavar;

typedef enum		e_hashtype
{
	HASH_UNDEFINED = -1,
	HASH_MD_FIVE,
	HASH_SHA256,
	HASH_SHA224,
	HASH_SHA512,
	HASH_SHA384,
	HASH_SHA512_256,
	HASH_SHA512_224,
	HASH_TOTAL
}					t_hashtype;

typedef enum		e_ciphertype
{
	CIPHER_UNDEFINED = -1,
	CIPHER_BASE64,
	CIPHER_TOTAL
}					t_ciphertype;

typedef enum		e_cmdtype
{
	HASH_CMD,
	CIPHER_CMD,
	TOTAL_CMD
}					t_cmdtype;

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
extern t_print_md g_print_funcs[HASH_TOTAL];
extern const char *g_format[HASH_TOTAL];

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
					size_t msg_len, size_t *new_msg_len);
void				*create_padded_msg_sha2(void *msg,
					size_t msg_len, size_t *new_msg_len);
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
int					get_cmd(const char *str,
					t_cmdtype cmdtype,
					int total);
uint8_t				append_flag(uint8_t flag,
					const char *str);
void				ft_info(const char *cmd);
void				hash_arg(uint16_t flags,
					char *txt, t_hashtype htype);
uint8_t				*get_file(const char *path,
					size_t *size);

/*
** BASE64 encode and decode functions
*/
char				*encode_to_base64(const uint8_t *bin,
					size_t lenght);
uint8_t				*decode_from_base64(const char *code);
void				print_base64_code(const int fd,
					const char *code);
#endif
