#include <iostream>

#include <cxxopts.hpp>
#include <termcolor/termcolor.hpp>

#include "../../include/cli/cli.h"
#include <aether/eth/eth.h>

using std::cout;
using std::endl;

namespace cli {

int run(int argc, char* argv[]) {
    cxxopts::Options mainopts(PROG_NAME, PROG_DESC);
    mainopts.add_options()
        ("h,help", "display this help and exit")
        ("g,generate", "generate a private key and display Ethereum data")
        ("a,asm", "open a tmux/vim session with :make assembly play in a temporary dir")
    ;

    auto result = mainopts.parse(argc, argv);

    if(result.count("generate")) {
        cli::generate();
        return 0;
    } else if(result.count("asm")) {
        system("./scripts/godbolt.sh");
        return 0;
    } else if(result.count("help")) {
        cout << mainopts.help() << endl;
        return 0;
    } else {
        //Nothing matched, so just display help and exit
        cout << mainopts.help() << endl;
        return 0;
    }
}

void generate() {
    eth_secp256k1_seckey prvkey;
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

    cout << "Private Key: " << termcolor::bright_grey;
    eth_util_writebytestohex(stdout, prvkey.data, 32);
    cout << '\n' << termcolor::reset << "Public Key (Uncompressed): " << termcolor::yellow;
    eth_util_writebytestohex(stdout, pubkey.data, 32);
    cout << '\n' << termcolor::reset;
    cout << "Keccak256 Hash: " << termcolor::blue;
    eth_util_writebytestohex(stdout, khash.data, 32);
    cout << '\n' << termcolor::reset;
    
    cout << "Address: " << termcolor::bright_blue << "0x";
    eth_util_writebytestohex(stdout, eth_pubkey_khash_getaddress(&khash), 20);
    cout << '\n' << termcolor::reset;

    cout << "EIP-55 Encoded: " << termcolor::green << "0x";
    eth_pubkey_khash_writeeip55address(stdout, &khash);
    cout << '\n' << termcolor::reset;
}

}
