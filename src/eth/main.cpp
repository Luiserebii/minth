#include <iostream>
#include "../../include/eth/eth.h"

using std::cout;

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


