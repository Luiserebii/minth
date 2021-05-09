#include <sys/random.h>
#include <secp256k1.h>
#include <sodium.h>
#include <iostream>
#include <cassert>

using std::cout;

namespace eth {

namespace secp256k1 {

typedef struct {
    unsigned char data[32];
} seckey;

typedef struct {
    unsigned char data[65];
} unc_pubkey;

typedef struct {
    unsigned char data[32];
} keccak256_hash;

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

//OUT BUFF MUST BE AT LEAST TWICE SIZE BYTE BUFF
//ONLY TAKING 8 BITS BTW!!!!
void writehexbytestostr(char* out, const unsigned char* bytes, size_t bytes_sz) {
    static char hextable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                              'B', 'C', 'D', 'E', 'F'};
    for(size_t i = 0; i < bytes_sz; ++i) {
        *out++ = hextable[(bytes[i] >> 4) & 0xF];
        *out++ = hextable[bytes[i] & 0xF];
    }
    *out = '\0';
}

int main() {
    //Define our 32-bit private key
    eth::secp256k1::seckey prvkey;
    //Create secp256k1 context obj
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
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

    //Generate hash
    eth::secp256k1::keccak256_hash khash;
    //Grab the pointer up from the public key, as we ignore the first uncompressed bit
    unsigned char* eth_pkey_in = pubkey.data + 1;
    size_t eth_khash_in_sz = sizeof(eth::secp256k1::unc_pubkey) - 1;
    crypto_hash_sha256(khash.data, eth_pkey_in, eth_khash_in_sz);

    

    secp256k1_context_destroy(ctx);
    
    char prvstr[500];
    char pubstr[500];
    writehexbytestostr(prvstr, prvkey.data, 32);
    writehexbytestostr(pubstr, khash.data, 32);
    cout << "Private Key: " << prvstr << '\n';
    //Printing the last 20 bytes, which is the ETH address!
    cout << "Address: 0x" << (pubstr+24) << '\n';
}

