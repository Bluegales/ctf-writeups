#!/usr/bin/env python3

import os
from Crypto.Util.Padding import pad

import cpt


KEY_SIZE = 16
BLOCK_SIZE = 16

def xor(x, y):
    return bytes([a ^ b for a, b in zip(x, y)])

# Wrappers to work with bytes instead of strings.
def key_schedule(key):
    return cpt.key_schedule(key.decode('latin-1'))
def encrypt(block, round_keys):
    return cpt.encrypt(block.decode('latin-1'), round_keys).encode('latin-1')

def cbc_enc(msg, key):
    msg = pad(msg, BLOCK_SIZE)
    iv = os.urandom(BLOCK_SIZE)
    round_keys = key_schedule(key)

    ciphertext = iv
    for i in range(0, len(msg), BLOCK_SIZE):
        iv = encrypt(xor(iv, msg[i:i+BLOCK_SIZE]), round_keys)
        ciphertext += iv
    return ciphertext

with open('flag', 'r') as f:
    flag = f.read().strip()
assert(len(flag) == 33)

key = os.urandom(KEY_SIZE)
ciphertext = cbc_enc(flag.encode(), key)
print(ciphertext.hex())
