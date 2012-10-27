#ifndef __PICOCOIN_H__
#define __PICOCOIN_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <glib.h>
#include <openssl/bn.h>
#include "coredefs.h"

struct wallet;

struct p2p_addr {
	unsigned char	ip[16];
	unsigned short	port;
	uint64_t	nServices;
};

struct buffer {
	void		*p;
	size_t		len;
};

/* base58.c */
extern GString *base58_encode(const void *data_, size_t data_len);
extern GString *base58_address_encode(unsigned char addrtype, const void *data,
			       size_t data_len);

/* bignum.c */
extern void bn_setvch(BIGNUM *vo, const void *data_, size_t data_len);
extern void reverse_copy(unsigned char *dst, const unsigned char *src, size_t len);

/* dns.c */
extern GList *get_dns_seed_addrs(void);

/* main.c */
extern GHashTable *settings;
extern const char ipv4_mapped_pfx[12];
extern struct wallet *cur_wallet;
extern const struct chain_info *chain;

/* net.c */
extern void network_sync(void);

/* aes.c */
extern GString *read_aes_file(const char *filename, void *key, size_t key_len,
			      size_t max_file_len);
extern bool write_aes_file(const char *filename, void *key, size_t key_len,
		    const void *plaintext, size_t pt_len);

static inline bool is_ipv4_mapped(const unsigned char *ipaddr)
{
	return memcmp(ipaddr, ipv4_mapped_pfx, 12) == 0;
}

static inline char *setting(const char *key)
{
	return g_hash_table_lookup(settings, key);
}

#endif /* __PICOCOIN_H__ */
