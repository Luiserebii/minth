#include <sys/random.h>
#include <secp256k1.h>
#include <ethash/keccak.h>

#include <assert.h>
#include <string.h>

#include "../../include/eth/eth.h"

unsigned char* eth_secp256k1_randseckey(eth_secp256k1_seckey* sk) {
    //Fill our raw buffer with CSPRNG bytes from /dev/urandom
    getrandom(sk->data, 32, 0);
    //Mask off all unneeded bytes
    for(size_t i = 0; i < 32; ++i) {
        sk->data[i] &= 0xFF;
    }
    return sk->data;
}

void eth_secp256k1_generateseckey(eth_secp256k1_seckey* sk, const secp256k1_context* ctx) {
    //Generate a new one until valid
    while(!secp256k1_ec_seckey_verify(ctx, eth_secp256k1_randseckey(sk)))
        ;
}

void eth_secp256k1_calculatepubkey(eth_secp256k1_unc_pubkey* pk, const secp256k1_context* ctx, const eth_secp256k1_seckey* sk) {
    //Generate public key
    secp256k1_pubkey secp_pubkey;
    int pkcres = secp256k1_ec_pubkey_create(ctx, &secp_pubkey, sk->data);
    assert(pkcres);

    //Write secp256k1 public key to uncompressed 65-bit representation
    size_t outputlen = 65;
    secp256k1_ec_pubkey_serialize(ctx, pk->data, &outputlen, &secp_pubkey, SECP256K1_EC_UNCOMPRESSED);
}

void eth_keccak_calculatepkhash(eth_keccak256_hash* kh, const unsigned char* data) {
    union ethash_hash256 ehash = ethash_keccak256(data, 64);
    memcpy(kh->data, ehash.str, 32);
}

void eth_pubkey_khash_calculate(eth_pubkey_khash* kh, const eth_secp256k1_unc_pubkey* pk) {
    //Grab the pointer up from the public key, as we ignore the first uncompressed byte
    const unsigned char* pk_data = pk->data + 1;
    eth_keccak_calculatepkhash(kh, pk_data);
}

const unsigned char* eth_pubkey_khash_getaddress(const eth_pubkey_khash* kh) {
    return kh->data+12;
}
