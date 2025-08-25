---
theme: default
paginate: true
footer: © Copyright 2024, Adrian Gould & NM TAFE
header: "![NMTAFE](../images/Black-Red-Banner.svg)"
auto-scaling: true
size: 4k
color: "#ccc"
backgroundColor: "#060606"
tags:
  - Internet of Things
  - InterRIoT
  - IoT
  - Robotics
  - Python
  - Arduino
  - ESP-32
  - C
  - C++

date created: 03 July 2024
date modified: 10 July 2024
---

# Python & Cryptography 1

## Intermediate RIoT

### Cryptography

Developed by Adrian Gould

---

```table-of-contents
title: # Contents
style: nestedList
minLevel: 0
maxLevel: 3
includeLinks: true
```

---

# Acknowledgemetns

These notes and practical tutorial is based on:

- ByteScrum Technologies. (2023, October 20). Encrypting and Decrypting Data with Fernet in Python. ByteScrum
  Technologies. https://blog.bytescrum.com/encrypting-and-decrypting-data-with-fernet-in-python
- Ali, M. A. (2023, December 5). Unlocking Cryptography: A Hands-On Guide to Encrypting and Decrypting Files Using
  Python.
  Medium. https://medium.com/@madeenali2003/unlocking-cryptography-a-hands-on-guide-to-encrypting-and-decrypting-files-using-python-611766e73f7a
- Encrypt and Decrypt Data in Python. (2021).
  Tutorialspoint.com. https://www.tutorialspoint.com/how-to-encrypt-and-decrypt-data-in-python
- The Intect. (2024, August 6). How to Encrypt and Decrypt Data in Python | Medium.
  Medium. https://medium.com/@info_82002/a-beginners-guide-to-encryption-and-decryption-in-python-12d81f6a9eac
- Codementor. (2025). Simple Python Encryption: How to Encrypt a Message | Codementor.
  Codementor.io. https://www.codementor.io/python/tutorial/python-encryption-message-in-python-via-reverse-cipher
- Novixys Software Dev Blog. (2018, February 8). Novixys Software Dev
  Blog. https://www.novixys.com/blog/using-aes-encryption-decryption-python-pycrypto/
- Python Programming Tutorials. (2025).
  Pythonprogramming.net. https://pythonprogramming.net/encryption-and-decryption-in-python-code-example-with-explanation/
- Bekker, R. (2018, April 29). Encryption and Decryption with Simple Crypt using Python. Ruan Bekker’s
  Blog. https://ruan.dev/blog/2018/04/29/encryption-and-decryption-with-simple-crypt-using-python
- Vollebregt, B. (2018b). Encryption and Decryption in Python.
  Nitratine.net. https://nitratine.net/blog/post/encryption-and-decryption-in-python/
- What is asymmetric encryption? | Asymmetric vs. symmetric encryption. (2025).
  Cloudflare.com. https://www.cloudflare.com/learning/ssl/what-is-asymmetric-encryption/

# Resources Needed

- Python 3.10+
- PyCharm Professional 2024.2+

# Setting Up

# Cryptography

What is cryptography?

Cryptography deals with the conversion of plain text into cipher text which is called encryption of data and cipher text
back to plain text which is called decryption of data.

There are different forms of cryptography:

- symmetrical
- asymmetrical

## What is asymmetric encryption?

There are two sides in an encrypted communication:

- the sender, who encrypts the data, and
- the recipient, who decrypts it.

As the name implies, asymmetric encryption is different on each side:

- the sender and the recipient use two different keys.

Asymmetric encryption, also known as public key encryption, uses a public key-private key pairing.

- data encrypted with the public key can only be decrypted with the private key.

An example of this in the real world is TLS (or SSL), the protocol that makes HTTPS possible, relies partially on
asymmetric encryption.

## What is symmetric encryption?

In symmetric encryption, the same key both encrypts and decrypts data.

For symmetric encryption to work, the two or more communicating parties must know what the key is.

- for it to remain secure, no third party should be able to guess or steal the key.

## Demonstrating Symmetrical Encryption

We will be using the fernet module in the cryptography package to encrypt and decrypt data using Python. While using the
fernet module, a unique key is generated without which you cannot read or manipulate the encrypted data.

Now that you know what we will be dealing with, let’s get started.

### Create New Project

Start by creating a new project using PyCharm

- Hamburger Icon
- File
- New Project
- Name: XXX-InterRiot-Cryptography-1 (replace XXX with your initials)
- Add Welcome Script
- Initialise version control

### CLI Time

- Open the Windows Terminal
- Change into the project folder

```shell
cd XXX-InterRiot-Cryptography-1
```

- Activate the Python Virtual Environment and update pip

```shell
source .venv/Scripts/activate
python.exe -m pip install --upgrade pip
```` 

Add the cryptography package, and freeze requirements

```shell
pip install cryptography
pip freeze > requirements.txt
```

### Code Time

Open the `main.py` file and you should see:

```python
# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('PyCharm')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
```

Edit the code by replacing the comments up to the `def` line with:

```python
"""
 Project Title:    Cryptography Learning 1
 Name:             YOUR NAME

 YOUR SUMMARY OF THE ACTIVITY
 GOES HERE

"""
```

Fill out the details as needed.

### Generating Encryption Keys

Update remaining code:

```python
# Imports
from cryptography.fernet import Fernet

# Global CONSTANTS

## Global Variables

# Functions/Methods
def main():
    key = Fernet.generate_key()
    f = Fernet(key)
    print(key.decode())


# Main Code
if __name__ == '__main__':
    main()
```

#### Quick Code review:

- `key = Fernet.generate_key()` Generates a new "Fernet" key
- `f = Fernet(key)` Initialises the fernet engine with the key
- `print(key.decode())` Shows the key that isd being used

### Execute the code

You will be given output similar to this:

```text
Afm8Zu0xeB5e8isOBd_3AwqPt5WhvJrMIkrlVrWyxOw=
```

This is the encryption key for the data.

### Encrypting Data

To encrypt data we use the `encrypt` method from Fernet.

To do this we are going to create a new method: `encrypt_data`:

```python
def encrypt_data(data, fernet=None):
    byte_data = data.encode('utf-8')
    encrypted = fernet.encrypt(byte_data)
    return encrypted
```

To use this we now update the main code:

```python
def main():
    # ... existing code is unchanged ...

    message = "Hello World!"
    print(message)

    encrypted_text = encrypt_data(message, fernet_engine)
    print(encrypted_text)
```

Running this will result in output similar to this:

```text
CYik3dmessEZ01kmCltvZS3I8VAHRNJ75aiF9Ea9inw=
Hello World!
b'gAAAAABoJD0jXYcM-VQVhkZ7o9Ri3CKvjd81VnDymwmboWjMNoe6ENkPvJdx5ifA-YgR1l51ykXmVm_Qq2XWREvGTzIdldoWJA=='
```

### Decrypting Data

Just like when we encrypt we will use the `decrypt` method to reverse the process.

Add the following method to the code:

```python
def decrypt_data(data, fernet=None):
    decrypted = fernet.decrypt(data)
    return decrypted
```

Update the main method by adding the following after the `encrypt_data` call:

```python
decrypted_text = decrypt_data(encrypted_text, fernet_engine)
print(decrypted_text)
print(decrypted_text.decode())
```

The `decrypted_text.decode()` converts the byte 'string' to a standard Python String.

Executing now produces the following output:

```text
CYik3dmessEZ01kmCltvZS3I8VAHRNJ75aiF9Ea9inw=
Plain Text Message:
Hello World!
b'gAAAAABoJD0jXYcM-VQVhkZ7o9Ri3CKvjd81VnDymwmboWjMNoe6ENkPvJdx5ifA-YgR1l51ykXmVm_Qq2XWREvGTzIdldoWJA=='
b'Hello World!'
Hello World!
```

## Storing Keys

Keys can be saved and written to files.

For example, we could add a new method, `save_key` that saves the key to a given filename.

First let's add the code that uses the key to the main method.

Add this line just after printing the key:

```python
save_key(key)
```

Now create a new method, `save_key` that takes the key and an optional filename:

```python
def save_key(key, filename="key.file"):
    with open(filename, "wb") as file:
        file.write(key)
        print("Key saved to " + filename)
    return True
```

Try it out and check you have a new file with the key.

The start of the output will be similar to this:

```text
Encryption Key:
8axs09Arzy2zsRwtiGrbzkPDoshqysvqSzKE9Tn7yoQ=
Key saved to key.file
```

### Reading Keys

Likewise, having the ability to read a key is very useful.

To do so we may use a new method `read_key`...

```python
def read_key(filename="key.file"):
    key = None
    with open(filename, "rb") as file:
        key = file.read()
        print("Key loaded from " + filename)
    return key
```

#### Exercise:

Use the new method to read the key, and then decode it and print to the screen.

### Keys from Secret Text

A common form of using keys is to create one from a password. This could then be used to encrypt and decrypt data when
passed between two people. A classic example of this is compression applications that ask you for a password. This
encrypts the data, and at the other end the recipient will need the password to decrypt the file before accessing the
data.

The password is often called the "salt" for the key.

For us to demonstrate this we will create a new Python Script.

First, rename main.py to `symmertical_encryption.py`.

Now duplicate the `symmetrical_encryption.py` file and name it: `salted_key.py`:

Starting at the top, edit the code to read, making sure you update the project title, and summary of the code.

```python
"""
 Project Title:    Cryptography Learning 1
 Name:             YOUR NAME

 YOUR SUMMARY OF THE ACTIVITY
 GOES HERE

"""
# Imports
import base64
import os
from cryptography.fernet import Fernet
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
```

Here we import a number of modules/packages to use.

- base 64 to encode data into a base64 string
- primitives to gain access to hash types and methods

Now update the main code.

Quick outline of the code:

- We are using a "hard coded" password for this. In reality, you would ask the user for the password.
- We encode the password as bytes
- we define a 'salt' length, and then create a random string of 16 characters
- Next, we generate a key derivation function (KDF) which is a series of bytes used for cryptography
    - Read this: https://cryptography.io/en/latest/hazmat/primitives/key-derivation-functions/
- We use this KDF to encode the password, and generate a ASCII character safe version of the password to act as the key.

```python
def main():
    password = "<PASSWORD>"
    password_bytes = password.encode()

    salt_length = 16
    salt_shaker = base64.b64encode(os.urandom(salt_length)).decode('utf-8')[:salt_length]
    salt = f"salt_{salt_shaker}"
    salt_bytes = salt.encode()

    key_derivation_function = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt_bytes,
        iterations=100000,
        backend=default_backend()
    )
    key = base64.urlsafe_b64encode(key_derivation_function.derive(password_bytes))

    fernet_engine = Fernet(key)

    print(f"Encryption Key: {key.decode()}")
    print(f"Encryption Salt: {salt}")

```

#### Exercise

Identify some of the methods that can be used for KDF.

### Incorrect Keys

If a different key to the one used to encrypt is provided when decrypting, an `InvalidToken` will be raised.

- More precisely a ` cryptography.fernet.InvalidToken`

Catching this error will allow you to tell if the incorrect key was provided.

Here is an example:

```python
from cryptography.fernet import Fernet, InvalidToken

encrypted = b"...encrypted bytes..."

f = Fernet(incorrect_key)  # An example of providing the incorrect key
try:
    decrypted = f.decrypt(encrypted)
    print("Valid Key - Successfully decrypted")
except InvalidToken as e:  # Catch any InvalidToken exceptions if the correct key was not provided
    print("Invalid Key - Unsuccessfully decrypted")
```

### Exercise

Duplicate the original `symmetrical_encryption.py` file, and rename the copy to `symmetrical_invalid_keys.py`

Use the above code, plus the symmetrical encryption code, to create your own example to test the exception out.

> #### ⚠️ WARNING:
> As stated in Fernet docs, beware of large files; Fernet is ideal for encrypting data that easily fits in memory. You
> may need to think of methods to split larger files up to use this encryption method on large files.

## Encrypting and Decrypting Files

We can also encrypt files using this method since files can be read as bytes.

The basic method is:

- Open the file
- Read the bytes
- Encrypt the data
- Write encrypted data to a new file.

### Encrypting a File

```python
from cryptography.fernet import Fernet

# The method used to create a key must be the same for decrypting
key = b'Some Key'
input_file = 'test.txt'
output_file = 'encrypted.data'
with open(input_file, 'rb') as f:
    data = f.read()
fernet = Fernet(key)
encrypted = fernet.encrypt(data)
with open(output_file, 'wb') as f:
    f.write(encrypted)
    # Note: You can delete input_file here if you want
```

### Decrypt a File:

The process is very similar

- Open the file
- Read the bytes
- Decrypt the data
- Write decrypted data to a new file.

```python
from cryptography.fernet import Fernet, InvalidToken

# The method used to create a key must be the same for decrypting
key = b''
input_file = 'encrypted.data'
output_file = 'decrypted.txt'
with open(input_file, 'rb') as f:
    data = f.read()
fernet = Fernet(key)
try:
    decrypted = fernet.decrypt(data)
    with open(output_file, 'wb') as f:
        f.write(decrypted)
    # Note: You can delete input_file here if you want
except InvalidToken as e:
    print("Invalid Key - Unsuccessfully decrypted")
```

#### Exercise:

Create a new python script file, named `encrypt_decript_text_file.py`.

Create a main function where you:

- ask the user for an input filename
- ask teh user for an output filename
- ask the user for a temporary filename
- call a new methd `encrypt_file` to encrypt the input file and write to the temporary file.
- Call a new method `decrypt_file` to read the temporart file and write the decrypted data to the output file.

Create a new method (function) called `encrypt_file` that takes TWO filenames (input filename, temporary filename) as
parameters, and an encryption key as the third parameter.
The method then uses the sample code above to encrypt the file contents and write the new data to the new file.

Create a new method (function) called `decrypt_file` that takes two filenames (output filename, temporary filename), and
the key used to encrypt the data.
The method then reads the temporary file, and decrypts the data and writes the results to the output file.

Create a plain text file called "quick-test-original.txt" and add the following text:

```text
My code fails.
I do not know why.
My code works.
I do not know why.

I'm a nice guy, but
write CSS in JS?
I'll lose my damn mind.

A crash reduces
Your expensive computer
To a simple stone.

Serious error.
All shortcuts have disappeared.
Screen. Mind. Both are blank.
```

Execute the script using the values:

| Input              | Value                     |
|--------------------|---------------------------|
| Input Filename     | quick-test-original.txt   |
| Temporary Filename | quick-test-encrypted.data |
| Output Filename    | quick-text-decrypted.txt  |


Verify that the code executed as expected.

Fix any errors encountered.

# END

Next up - [LINK TEXT](#)
