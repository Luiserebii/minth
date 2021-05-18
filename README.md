# Ξ minth: ETH Box

a meme eth-wallet impl, among other things

vitalik pls

## Godbolt Solidity Hack

`minth -a`

Write what you need to on the buffer on the left. Use `:make` on the rightmost buffer and navigate through the assembly output files! The rightmost buffer is open to the temporary directory, so `:e` tabbing or something similar (fzf) can guide you to them.

## Development Notes

Update libaether:
```
git submodule update --remote
```

Setup environment to run minth:
```
source ./scripts/setup.sh
```

## Installation

```
sudo apt install libgmp-dev
sudo apt install libsecp256k1-dev
```

`tmux` and `vim` and `solc` are required to be installed to use the `-a` option.
