# Ξ minth: ETH Box

A fun toolbox for Ethereum development convenience, with a prospective mini-wallet. Intended to provide easy access to interesting functionality through a CLI.

```
an Ξthwallet for all your Ξthwallet needs
Usage:
  minth [OPTION...]

  -h, --help      display this help and exit
  -g, --generate  generate a private key and display Ethereum data
  -a, --asm       open a tmux/vim session with :make assembly play in a
                  temporary dir
```

## Solidity Assembly Explorer

`minth -a`

Write contracts on the buffer on the left. Use `:make` on the rightmost buffer and navigate through the assembly output files! The rightmost buffer is open to the temporary directory, so `:e` tabbing or something similar (fzf) can guide you to them.

![minth -a](https://i.imgur.com/ow1XIvh.gif)

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

## License

This code has been licensed under the GNU General Public License v3.0.
