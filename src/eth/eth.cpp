#include <sys/random.h>
#include <secp256k1.h>
#include <iostream>
#include <ethash/keccak.h>

#include <assert.h>
#include <string.h>

using std::cout;

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

unsigned char* eth_secp256k1_randseckey(eth_secp256k1_seckey* sk) {
    //Fill our raw buffer with CSPRNG bytes from /dev/urandom
    getrandom(sk->data, 32, 0);
    //Mask off all unneeded bytes
    for(size_t i = 0; i < 32; ++i) {
        sk->data[i] &= 0xFF;
    }
    return sk->data;
}

//OUT BUFF MUST BE AT LEAST TWICE SIZE BYTE BUFF
//ONLY TAKING 8 BITS BTW!!!!
char* bytestohex(char* out, const unsigned char* bytes, size_t bytes_sz) {
    static char hextable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                              'B', 'C', 'D', 'E', 'F'};
    for(size_t i = 0; i < bytes_sz; ++i) {
        *out++ = hextable[(bytes[i] >> 4) & 0xF];
        *out++ = hextable[bytes[i] & 0xF];
    }
    *out++ = '\0';
    return out;
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
    ethash_hash256 ehash = ethash_keccak256(data, 64);
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

int main() {
    //Define our 32-bit private key
    eth_secp256k1_seckey prvkey;
    //Create secp256k1 context obj
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    //Generate a valid secret key
    eth_secp256k1_generateseckey(&prvkey, ctx);

    //Calculate the uncompressed public key
    eth_secp256k1_unc_pubkey pubkey;
    eth_secp256k1_calculatepubkey(&pubkey, ctx, &prvkey);

    //Generate hash
    eth_keccak256_hash khash;
    eth_pubkey_khash_calculate(&khash, &pubkey);

    secp256k1_context_destroy(ctx);

    char prvstr[500];
    char pubstr[500];
    char hashstr[500];
    bytestohex(prvstr, prvkey.data, 32);
    bytestohex(pubstr, pubkey.data, 65);
    bytestohex(hashstr, khash.data, 32);
    cout << "Private Key: " << prvstr << '\n';
    cout << "Public Key: " << pubstr << '\n';
    cout << "Keccak256 Hash: " << hashstr << '\n';
    //Printing the last 20 bytes, which is the ETH address!
    cout << "Address: 0x" << (hashstr+24) << '\n';
}

