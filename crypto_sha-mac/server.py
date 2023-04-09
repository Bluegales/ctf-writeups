from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.padding import PKCS7

from hashlib import sha256
import os
import secrets


KEY = os.urandom(32)
MAC_KEY = os.urandom(32)

KEY = bytes.fromhex('156a25c14101f13aaef00357cbe5dd41820db6b6e7d09ee3d6952ffeef596f75')
MAC_KEY = bytes.fromhex('598421df1d54b782c43e8c34ef2eb7d9cfa8bc9e3b10550c5fcd5f3e14e1a547')

class FlagFound(Exception):
    pass

def encrypt_and_sign(msg):
    iv = os.urandom(16)
    
    padder = PKCS7(algorithms.AES256.block_size).padder()
    encryptor = Cipher(algorithms.AES256(KEY), modes.CBC(iv)).encryptor()
    
    padded_msg = padder.update(msg) + padder.finalize()
    encrypted_msg = encryptor.update(padded_msg) + encryptor.finalize()
    
    ciphertext = iv + encrypted_msg
    
    auth = sha256(MAC_KEY + ciphertext)
    
    return ciphertext + auth.digest()

def decrypt_signed(ct):
    # make sure all components are included
    if len(ct) < 64:
        raise ValueError("Ciphertext too short")

    iv, encrypted, auth = ct[:16], ct[16:-32], ct[-32:]
    print(iv, encrypted, auth)
    
    # ensure ciphertext hasn't been tampered with
    assert secrets.compare_digest(sha256(MAC_KEY + iv + encrypted).digest(), auth)
    
    decryptor = Cipher(algorithms.AES256(KEY), modes.CBC(iv)).decryptor()
    unpadder = PKCS7(algorithms.AES256.block_size).unpadder()
    
    print("decrypting")
    decrypted = decryptor.update(encrypted) + decryptor.finalize()
    print("unpadding")
    unpadded = unpadder.update(decrypted) + unpadder.finalize()
    print("done")
    
    # that would be too easy :)
    if FLAG in unpadded:
        raise FlagFound()
    
    return unpadded
    
if __name__ == "__main__":
    with open("flag", "rb") as f:
        FLAG = f.read()

    flag_enc = encrypt_and_sign(FLAG)
    print(flag_enc.hex())
    print("Oops, I dropped my flag! Good thing it's encrypted so there's no way you can figure out what it is :)")
    print("Anyways, I'm kinda bored so I'll let you encrypt and decrypt some stuff. I promise I won't read anything ;)")

    while True:
        try:
            print()
            action = input("What do you want to do? ([e]ncrypt, [d]ecrypt) ")
            if action == "e":
                msg = input("Enter the data you want to encrypt: ")
                encrypted = encrypt_and_sign(msg.encode())
                print(f"Here's your encrypted message: {encrypted.hex()}")
            elif action == "d":
                msg = bytes.fromhex(input("Enter the data you want me to decrypt (hex): "))
                decrypted = decrypt_signed(msg)
                print(f"Here's your decrypted message (in hex): {decrypted.hex()}")
            else:
                print("Um...I'm not sure what you mean by that?")
        except ValueError:
            print("I'm not sure what to do with that...?")
        except AssertionError:
            print("I'll only decrypt things that I've signed myself.")
        except FlagFound:
            print("Nice try, but I'm not decrypting the flag for you >:(")
        except:
            print("Sorry, something went wrong :(")
