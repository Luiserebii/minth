#include <sys/random.h>
#include <secp256k1.h>

typedef struct {
    unsigned char data[32];
} seckey;

void genseckey(seckey* sk) {
    //Fill our raw buffer with CSPRNG bytes from /dev/urandom
    getrandom(sk, 32, 0);
    //Mask off all unneeded bytes
    for(size_t i = 0; i < 32; ++i) {
        sk->data[i] &= 0xFF;
    }
}

int main() {
    //Define 32-byte array
    seckey prvkey;
    //Create secp256k1 context obj
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    //Generate a new one until valid
    //
    //

    secp256k1_context_destroy(ctx);
    
    

}

