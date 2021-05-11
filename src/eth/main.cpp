#include <iostream>
#include <string>
#include <iterator>

#include "../../include/eth/eth.h"
#include "../../include/util/bytes.h"
using std::string;
using std::cout;
using std::back_inserter;

//OUT BUFF MUST BE AT LEAST TWICE SIZE BYTE BUFF
//ONLY TAKING 8 BITS BTW!!!!
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
    eth_pubkey_khash khash;
    eth_pubkey_khash_calculate(&khash, &pubkey);

    secp256k1_context_destroy(ctx);

    cout << "Private Key: ";
    eth_util_writebytestohex(stdout, prvkey.data, 32), putchar('\n');
    cout << "Public Key: ";
    eth_util_writebytestohex(stdout, pubkey.data, 32), putchar('\n');
    cout << "Keccak256 Hash: ";
    eth_util_writebytestohex(stdout, khash.data, 32), putchar('\n');
    cout << "Address: 0x";
    eth_util_writebytestohex(stdout, eth_pubkey_khash_getaddress(&khash), 32), putchar('\n');
    cout << "EIP-55 Encoded: 0x";
    eth_pubkey_khash_writeeip55address(stdout, &khash), putchar('\n');
}


