#include <sys/random.h>
#include <secp256k1.h>
#include <iostream>
#include <cassert>

namespace eth {

namespace secp256k1 {

typedef struct {
    unsigned char data[32];
} seckey;

typedef struct {
    unsigned char data[65];
} unc_pubkey;

}
}

unsigned char* genseckey(eth::secp256k1::seckey* sk) {
    //Fill our raw buffer with CSPRNG bytes from /dev/urandom
    getrandom(sk, 32, 0);
    //Mask off all unneeded bytes
    for(size_t i = 0; i < 32; ++i) {
        sk->data[i] &= 0xFF;
    }
    return sk->data;
}

int main() {
    //Define our 32-bit private key
    eth::secp256k1::seckey prvkey;
    //Create secp256k1 context obj
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    //Generate a new one until valid
    while(!secp256k1_ec_seckey_verify(ctx, genseckey(&prvkey)))
        ;

    //Generate public key
    secp256k1_pubkey secp_pubkey;
    int pkcres = secp256k1_ec_pubkey_create(ctx, &secp_pubkey, prvkey.data);
    assert(pkcres);

    //Write secp256k1 public key to uncompressed 65-bit representation
    eth::secp256k1::unc_pubkey pubkey;
    size_t outputlen = sizeof(eth::secp256k1::unc_pubkey);
    secp256k1_ec_pubkey_serialize(ctx, pubkey.data, &outputlen, &secp_pubkey, SECP256K1_EC_UNCOMPRESSED);

    secp256k1_context_destroy(ctx);
    
    

}

