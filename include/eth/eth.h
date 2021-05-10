#ifndef MINTH_ETH_H
#define MINTH_ETH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <secp256k1.h>

typedef struct {
    unsigned char data[32];
} eth_secp256k1_seckey;

typedef struct {
    unsigned char data[65];
} eth_secp256k1_unc_pubkey;

typedef struct {
    unsigned char data[32];
} eth_keccak256_hash;

typedef eth_keccak256_hash eth_pubkey_khash;

unsigned char* eth_secp256k1_randseckey(eth_secp256k1_seckey* sk);

void eth_secp256k1_generateseckey(eth_secp256k1_seckey* sk, const secp256k1_context* ctx);

void eth_secp256k1_calculatepubkey(eth_secp256k1_unc_pubkey* pk, const secp256k1_context* ctx, const eth_secp256k1_seckey* sk);

void eth_keccak_calculatepkhash(eth_keccak256_hash* kh, const unsigned char* data);

void eth_pubkey_khash_calculate(eth_pubkey_khash* kh, const eth_secp256k1_unc_pubkey* pk);

const unsigned char* eth_pubkey_khash_getaddress(const eth_pubkey_khash* kh);

#ifdef __cplusplus
}
#endif

#endif
