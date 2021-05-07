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

Just do each function for each key found in file.
