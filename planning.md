# Ξ 

## Prospective Functionality
  * Generate ETH Private Key
    * Randomly create one and store on file + in memory
      * Allow for serious CSPRNG option, another loose option
    * Accept name parameter
    * Give step-by-step colored output!
  * Display ETH Private Key, Public Key, Address of each Private Key
  * Display EIP-55 Encoded Address of Private Key
  * Display ICAP (Direct, Basic)
  * Step-by-step output of each process above
  * ICAP Validation
  * Transaction Generation
    * RLP Encode -> Keccak-256 hash -> ECDSA Signature
    * Payload of RLP Encode + ECDSA Sig 
    * Note: Request network (mainnet, ropsten, rinkeby)
    * Print transaction hex to stdout
  * Godbolt - tmux of vim and solc asm output

Just do each function for each key found in file.

## Implementation

### ETH Private Key Generation

```
It is assumed that the sender has a valid private key pr, which is a randomly selected positive integer (represented as a byte array of length 32 in big-endian form) in the range [1, secp256k1n − 1].
[1]
```
```
secp256k1n = 115792089237316195423570985008687907852837564279074904382605163141518161494337 
[1]
```

Note that secp256k1n is the order n of G [2].

Thus, randomly generate 256 bits of random. Use POSIX `ssize_t getrandom(void *buf, size_t buflen, unsigned int flags)` for CSPRNG, which uses /dev/urandom [3]. To store these large numbers (2^256), use GNU's GMP [4]. Note that `CHAR_BIT` from `<limits.h>` or `<climits>` will be useful to calculate our buffer size [5].

Therefore:
```cpp
namespace mathutil {
constexpr int ceil(double d) {
    //Ensure d is can return a valid int - define ranges!
    assert();
    int i = (int) d;
    return ((d - i) > 0) ? i + 1 : i;
}
}

#define PRIVKEY_BUFF 256
constexpr int pkbsz = mathutil::ceil((double) PRIVKEY_BUFF / CHAR_BIT);
unsigned char privkeybuff[pkbsz];
getrandom(addressBuff, pkbsz, 0);

/**
 * Writes the bits in `c` to `bits`, up to `lim` bits.
 */
char* bitbufbincwrite(char* bits, unsigned char c, size_t lim) {
    for(size_t i = 0; i < lim; ++i) {
        *bits++ = '0' + ((c >> i) & 1);
    }
    return bits;
}

/**
 * Writes `n` bits in `buf` to `bits`, as contiguous binary chars (e.g. "101001001"). Note that this means `bits` is not expected to be a null-terminated string. `bufsz` identifies the size of `buf`. 
 */
void bitbufbinwrite(char* bits, const unsigned char* buf, size_t bufsz, size_t n) {
    assert(bufsz * CHAR_BIT >= n);
    for(size_t i = 0; i < bufsz; ++i, ++buf, n-=CHAR_BIT) {
        if(n > CHAR_BIT) {
            bits = bitbufbincwrite(bits, *buf, CHAR_BIT);
        } else {
            bitbufbincwrite(bits, *buf, n);
            return;
        }
    }
}

char bits[PRIVKEY_BUFF_BITS + 1];
printcharbuf(privkeybuff, pkbsz);
bitbufbinwrite(bits, privkeybuff, pkbsz, PRIVKEY_BUFF_BITS);
bits[PRIVKEY_BUFF_BITS + 1] = '\0'; //null-terminate for gmp

const mpz_class SECP251K1N("115792089237316195423570985008687907852837564279074904382605163141518161494337");
// while generate, compare mpz_class(bits), continue until less than SECP251K1N

//Finally, a valid private key!
```


## References
1. "Ethereum: A Secure Decentralised Generalised Transaction Ledger". https://ethereum.github.io/yellowpaper/paper.pdf
2. "SEC 2: Recommended Elliptic Curve Domain Parameters". http://www.secg.org/sec2-v2.pdf
3. https://man7.org/linux/man-pages/man2/getrandom.2.html 
4. https://gmplib.org/
5. https://en.cppreference.com/w/c/types/limits
