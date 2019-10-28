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
# include <unistd.h>
# define LROT(x,c)(((x)<<(c))|((x)>>((sizeof(x)<<3)-(c))))
# define RROT(x,c)(((x)>>(c))|((x)<<((sizeof(x)<<3)-(c))))
# define ISSET_BIT(x,n)(((x)>>n)&1)
# define UNSET_BIT(x,n)((ISSET_BIT(x,n))?(x^((typeof(x))1<<n)):x)
# define SET_BIT(x,n)(x|((typeof(x))1<<n))
# define INVERT_BIT(x,n)(x^((typeof(x))1<<n))
# define FLAG_P 0x1
# define FLAG_Q 0x2
# define FLAG_R 0x4
# define FLAG_S 0x8
# define FLAG_I 0x10
# define FLAG_O 0x20
# define FLAG_E 0x40
# define FLAG_D 0x80
# define FLAG_A 0x100
# define FLAG_K 0x200
# define FLAG_V 0x400
# define FLAG_STDIN 0x800
# define FLAG_SSL_TOTAL 11

extern uint32_t g_svars[64];
extern uint32_t	g_kvars_md[64];
extern uint32_t	g_kvars_sha[64];
extern uint64_t g_kvars_sha512[80];

typedef enum		e_mdvar
{
	A_MD = 0,
	B_MD = 1,
	C_MD = 2,
	D_MD = 3,
	MD_VAR_TOTAL = 4
}					t_mdvar;

typedef enum		e_shavar
{
	H0 = 0,
	H1 = 1,
	H2 = 2,
	H3 = 3,
	H4 = 4,
	H5 = 5,
	H6 = 6,
	H7 = 7,
	SHA_VAR_TOTAL = 8
}					t_shavar;

typedef enum		e_hashtype
{
	HASH_UNDEFINED = -1,
	HASH_MD_FIVE = 0,
	HASH_SHA256 = 1,
	HASH_SHA224 = 2,
	HASH_SHA512 = 3,
	HASH_SHA384 = 4,
	HASH_SHA512_256 = 5,
	HASH_SHA512_224 = 6,
	HASH_TOTAL = 7
}					t_hashtype;

uint64_t	_set_bit(uint64_t x, uint8_t n);
uint8_t		_invert_bit(uint8_t byte, uint8_t n);
typedef struct termios t_termios;

typedef enum		e_ciphertype
{
	CIPHER_UNDEFINED = -1,
	CIPHER_BASE64 = 0,
	CIPHER_DES_ECB = 1,
	CIPHER_DES = 2,
	CIPHER_DES_CBC = 3,
	CIPHER_TOTAL = 4
}					t_ciphertype;

typedef enum		e_cmdtype
{
	HASH_CMD = 0,
	CIPHER_CMD = 1,
	TOTAL_CMD = 2
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

void				crypt_arg(const int read_fd,
					const int write_fd,
					const uint16_t flags,
					const t_ciphertype cipher_type);

/*
** BASE64 encode and decode functions
*/
char				*encode_to_base64(const uint8_t *bin,
					size_t lenght);
uint8_t				*decode_from_base64(const char *code);
void				print_base64_code(const int fd,
					const char *code);
char				*get_pwd(void);
uint64_t			initial_shuffle(uint64_t block);
uint64_t			swap_bits(uint64_t block,
					int a, int b);
uint32_t			f(uint32_t block, uint64_t key);
#endif
