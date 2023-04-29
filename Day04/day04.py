#!/usr/bin/env python3

import hashlib

# Define the message or file you want to hash
secret_key = "ckczppom"
number = 0

while True:
    # Convert the message into a sequence of bytes
    full_key = secret_key + str(number)
    message_bytes = full_key.encode('utf-8')

    # Create an MD5 hash object
    hash_object = hashlib.md5()

    # Update the hash object with the byte sequence
    hash_object.update(message_bytes)

    # Get the hash value as a hexadecimal string
    hash_hex = hash_object.hexdigest()

    if hash_hex.startswith("000000"):
        print("number: {}".format(number))
        break
    else:
        number = number + 1

print("MD5 hash of the message:", hash_hex)
