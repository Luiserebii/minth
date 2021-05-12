#!/bin/sh
CC=solc
TEMP_FILENAME=.minth.temp.sol
TEMP_FOLDER=solc.asm.out

TMP_DIR=$(mktemp -d -t ci-XXXXXXXXXX);
trap "rm -rf $TMP_DIR" EXIT
cd $TMP_DIR
mkdir $TEMP_FOLDER

touch $TEMP_FILENAME
tmux new-session -d "vim ${TEMP_FILENAME}" \; \
	split-window -h \; \
	send-keys "vim" C-m \; \
	send-keys ":setglobal makeprg=rm\ -rf\ $TEMP_FOLDER/*\ &&\ clear\ &&\ ${CC}\ --asm\ ${TEMP_FILENAME}\ --overwrite\ -o\ ${TEMP_FOLDER}" C-m \; \
	display "Use :make to compile the Solidity on the left and navigate to the asm with the right vim!" \; \
       	attach 

rm -rf $TMP_DIR
