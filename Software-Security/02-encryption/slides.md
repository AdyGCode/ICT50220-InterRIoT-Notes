---
theme: nmt
background: https://cover.sli.dev
title: Software Security - Encryption
class: text-left
drawings:
  persist: false
transition: fade
mdc: true
duration: 90min
---

# Software Security

## Encryption & Decryption

<div @click="$slidev.nav.next" class="mt-12 -mx-4 p-4" hover:bg="white op-10">
<p>Press <kbd>Space</kbd> or <kbd>RIGHT</kbd> for next slide/step <fa7-solid-arrow-right /></p>
</div>

<div class="abs-br m-6 text-xl">
  <a href="https://github.com/adygcode/SaaS-FED-Notes" target="_blank" class="slidev-icon-btn">
    <fa7-brands-github class="text-zinc-300 text-3xl -mr-2"/>
  </a>
</div>


<!--
The last comment block of each slide will be treated as slide notes. 

It will be visible and editable in Presenter Mode along with the slide.

[Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->


---
layout: default
level: 2
---

# Navigating Slides

Hover over the bottom-left corner to see the navigation's controls panel.

## Keyboard Shortcuts

|                                                     |                             |
|-----------------------------------------------------|-----------------------------|
| <kbd>right</kbd> / <kbd>space</kbd>                 | next animation or slide     |
| <kbd>left</kbd>  / <kbd>shift</kbd><kbd>space</kbd> | previous animation or slide |
| <kbd>up</kbd>                                       | previous slide              |
| <kbd>down</kbd>                                     | next slide                  |

---
layout: section
---

# Objectives

---
level: 2
layout: two-cols
---

# Objectives

::left::

::right::



---
level: 2
layout: figure-side
figureUrl: ./orly-book-cover-hoping-noone-hacks-you.jpg
---


# Contents

<Toc maxDepth="1"></Toc>

---
layout: section
---

# 🌟 Ice Breaker

## TODO: Add ice-breaker

---
layout: section
---

# Software Security - Encryption & Decryption

### Cryptography

---
level: 2
---

# Cryptography

What is cryptography?

Cryptography deals with the conversion of plain text into cipher text which is called encryption of data and cipher text
back to plain text which is called decryption of data.

There are different forms of cryptography:

- symmetrical
- asymmetrical

---
level: 2
---

# Cryptography

## What is asymmetric encryption?

There are two sides in an encrypted communication:

- the sender, who encrypts the data, and
- the recipient, who decrypts it.

As the name implies, asymmetric encryption is different on each side:

- the sender and the recipient use two different keys.

Asymmetric encryption, also known as public key encryption, uses a public key-private key pairing.

- data encrypted with the public key can only be decrypted with the private key.

Examples:

- TLS (or SSL), the protocol that makes HTTPS possible, relies partially on asymmetric encryption.

---
level: 2
---

# Cryptography

## What is symmetric encryption?

In symmetric encryption, the same key both encrypts and decrypts data.

For symmetric encryption to work, the two or more communicating parties must know what the key is.

- for it to remain secure, no third party should be able to guess or steal the key.

---
layout: section
---

# Code Fun: Secret Messages

- An exercise in simple cryptography
- Using groupwork and coding

---
level: 2
layout: two-cols
---

# Code Fun: Secret Messages

::left::

## Setting Up

You will require:

- Understanding of the Caesar Cypher
- Python
- Python IDE (Pref PyCharm)
- MQTT Server
- Bash CLI
    - Use the `bash.exe` from Laragon: `/c/laragon/bin/git/bin/bash.exe`

::right::

## In Class Specifics

| Item              | Details & Notes                                                                  |
|-------------------|----------------------------------------------------------------------------------|
| MQTT Server       | `10.25.35.225:1883` <br>Raspberry Pi4-25                                         |
| Topic             | `chat`                                                                           |
| Message Structure | JSON, example:<br>`{'GROUP': 'GROUPNAME', 'FROM': 'NAME', 'MESSAGE': 'CONTENT'}` |

---
level: 2
---

# Code Fun: Secret Messages

## Useful Python MQTT Resources

- Cope, S. (2016, August 20). Python MQTT Client Connections- Working with
  Connections. |. http://www.steves-internet-guide.com/client-connections-python-mqtt/
- Cope, S. (2016, August 23). How to Use The Paho MQTT Python Client for
  Beginners. |. http://www.steves-internet-guide.com/into-mqtt-python-client/
- SimonBirkenheuer/MQTT-Chat: A small MQTT based chat application. (2025).
  GitHub. https://github.com/SimonBirkenheuer/MQTT-Chat/tree/master
- EMQ. (2026, May 11). MQTT in Python with Paho Client: Beginner’s Guide 2026. Www.Emqx.Com;
  EMQ. https://www.emqx.com/en/blog/how-to-use-mqtt-in-python

---
level: 2
layout: two-cols
---

# Code Fun: Secret Messages

::left::

## Challenge Steps (1...3)

1. Create teams of 2 (or 3)
    - Give your team a name (`GROUPNAME`)
2. Create caesar_encrypt and caesar_decrypt functions
    - Your messages are limited to `A`-`Z` plus four punctuation items `!?. ` (space)
    - Total Characters 30
    - Offsets 1 to 29 (0 and 30 will be unencrypted)
3. Test the encrypt and decrypt functions
    - Suggest using offset of 1 or 29 for testing

::right::

## Challenge Steps (4...)

4. Write & test code to connect to MQTT
5. Once connected, add & test code to:
    - send to MQTT Topic (`chat`)
    - receive MQTT messages from Topic (`chat`)
6. Next ask user for a message, encrypt, & send
7. Final step is to listen for message, decrypt automatically and display locally
    - Suggest: Have separate Senders and Listeners

---
level: 2
layout: two-cols
---

# Code Fun: Secret Messages

## Summary Question

What type of encryption is the Caesar Cipher?

::left::

## Asymmetric?

- Why do you think the Caesar Cipher is an asymmetric algorithm?
- Justify your answer

::right::

## Symmetric?

- Why do you think the Caesar Cipher is a symmetric algorithm?
- Justify your answer

<!-- Presenter Notes

Legionnaire Cipher

What is it?

How to implement?

-->

---
layout: section
---

# Encryption Algorithms

---
level: 2
layout: two-cols
---

# Encryption Algorithms

## Exercise Part 1

Your lecturer will split you into groups of 3 or 4 people.

::left::

#### Class Research

Identify names of algorithms

- Note: We need at least one algorithm per student in the class
  In groups select an algorithm per person
- Lecturer may allocate some 'choices'

<br>

<Announcement type=important title="References">

Always note your resources, and use MyBib [https://mybib.com](https://mybib.com) to create APA6 or APA7 bibliographic
entries

</Announcement>

::right::

#### Individual Research

Research the algorithm you have selected looking for:

- **When** was it created & by **Whom**
- **What** is it (one way, two-way, hash, etc.)
- **How** it works (summary of algorithm)
- **When** (if it) was it broken ('hacked')
- **Where** is it used?
- **What** is its current status (current, theoretical, etc.)
- **Pros** and **Cons**

---
level: 2
layout: two-cols
---

# Encryption Algorithms

## Exercise Part 2

::left::

### Demonstration Code

- Create a small demonstration in at least one of:
    - **C++** <span class="text-orange-500">(MCU)</span>,
    - **Python** <span class="text-orange-500">(MCU/CPU)</span>,
    - **PHP** <span class="text-orange-500">(CPU)</span>,
    - **Rust** <span class="text-orange-500">(MCU)</span>,
    - **Go** <span class="text-orange-500">(CPU)</span>,
    - **C#** <span class="text-orange-500">(CPU)</span> or
    - **JavaScript**/**TypeScript** <span class="text-orange-500">(CPU/MCU)</span>

::right::

### Note

The <span class="text-orange-500">MCU</span>/<span class="text-orange-500">CPU</span> indicates the target architecture.

You must investigate at least C++, PHP or Python.

You may then add examples in other languages you are familiar with.

---
level: 2
layout: two-cols
---

# Encryption Algorithms

## Exercise Part 3

::left::

#### Combine Research

Create a Markdown document with your findings.

Use the headings (replace .... with the name):

- What is ....
- Creation Details
    - Include Who & When
- Where is .... used
- How does .... work?
- Status
    - Include if hacked, currency, version, etc.
- Pros and Cons

::right::

#### Create Presentation Slides

Prepare slides for a presentation

The presentation should be:

- Use Sli.dev Markdown to create the slides
- Between 4 and 6 slides
- Extra slide for Bibliographic References
- Extra slide for title slide, with your name

Between slides, use `---` at the start of the line.

---
layout: section
---

# Demonstrating Symmetrical Encryption

A Python example.

---
level: 2
---

# Demonstrating Symmetrical Encryption

We will be using the fernet module in the cryptography package to encrypt and decrypt data using Python.

While using the fernet module, a unique key is generated without which you cannot read or manipulate the encrypted data.

Now that you know what we will be dealing with, let’s get started.

## Create New Project

Start by creating a new project using PyCharm

- Hamburger Icon
    - File
        - New Project
            - Name: xxx-interriot-cryptography-1 (replace XXX with your initials)
            - Add Welcome Script
            - Initialise version control

---
level: 2
---

# Demonstrating Symmetrical Encryption

## CLI Time

- Open the Windows Terminal
- Change into the project folder

```shell
cd xxx-interriot-cryptography-1
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

---
level: 2
---

# Demonstrating Symmetrical Encryption

## Code Time

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

---
level: 2
---

# Demonstrating Symmetrical Encryption

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


---
level: 2
layout: two-cols
---

# Demonstrating Symmetrical Encryption

::left::

## Generating Encryption Keys

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

::right::

## Quick Code review:

- Generate a new "Fernet" key
    - `key = Fernet.generate_key()`
- Initialise the fernet engine with the key
    - `f = Fernet(key)`
- Show the key that is being used
    - `print(key.decode())`

---
level: 2
---

# Demonstrating Symmetrical Encryption

## Execute the code

```shell
python main.py
```

You will be given output similar to this:

```text
Afm8Zu0xeB5e8isOBd_3AwqPt5WhvJrMIkrlVrWyxOw=
```

This is the encryption key for the data.


---
level: 2
layout: two-cols
---

# Demonstrating Symmetrical Encryption

::left::

## Encrypting Data

To encrypt data we use the `encrypt` method from Fernet.

To do this we are going to create a new method: `encrypt_data`:

```python
def encrypt_data(data, fernet=None):
    byte_data = data.encode('utf-8')
    encrypted = fernet.encrypt(byte_data)
    return encrypted
```

::right::

To use this we now update the main code:

```python
def main():
    # ... existing code is unchanged ...

    message = "Hello World!"
    print(message)

    encrypted_text = encrypt_data(️↩️
                     ↪️ message,↩️
                     ↪️ fernet_engine)
    print(encrypted_text)
```

Running this will result in output similar to this:

```text
CYik3dmessEZ01kmCltvZS3I8VAHRNJ75aiF9Ea9inw=
Hello World!
b'gAAAAABoJD0jXYcM-VQVhkZ7o9Ri3CKvjd81Vn↩️
↪️DymwmboWjMNo️e6ENk️PvJdx5ifA↩️
↪️-YgR1l51ykXmVm_Qq2XWREvGTzIdldoWJA=='
```

<span class="text-xs">
Note: ↩️ and ️↪️ are used to show a single line split for readability
</span>

---
level: 2
---

# Demonstrating Symmetrical Encryption

## Decrypting Data

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


---
level: 2
---

# Demonstrating Symmetrical Encryption

Executing now produces the following output:

```text
CYik3dmessEZ01kmCltvZS3I8VAHRNJ75aiF9Ea9inw=
Plain Text Message:
Hello World!
b'gAAAAABoJD0jXYcM-VQVhkZ7o9Ri3CKvjd81VnDymwmboWjMNoe6ENkPvJdx5ifA-YgR1l51ykXmVm_Qq2XWREvGTzIdldoWJA=='
b'Hello World!'
Hello World!
```

---
level: 2
---

# Demonstrating Symmetrical Encryption

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

---
level: 2
layout: two-cols
---

# Demonstrating Symmetrical Encryption

Try it out and check you have a new file with the key.

::left::

The start of the output will be similar to this:

```text
Encryption Key:
8axs09Arzy2zsRwtiGrbzkPDoshqysvqSzKE9Tn7yoQ=
Key saved to key.file
```

::right::

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

<br>

## Exercise:

Use the new method to read the key, and then decode it and print to the screen.


---
level: 2
---

# Demonstrating Symmetrical Encryption II

## Keys from Secret Text

A common form of using keys is to create one from a password.

This could then be used to encrypt and decrypt data when passed between two people.

A classic example of this is compression applications that ask you for a password.

This encrypts the data, and at the other end the recipient will need the password to decrypt the file before accessing
the
data.

The password is often called the "salt" for the key.

For us to demonstrate this we will create a new Python Script.

First, rename `main.py` to `symmertical_encryption.py`.

Now duplicate the `symmetrical_encryption.py` file and name it: `salted_key.py`:



---
level: 2
---

# Demonstrating Symmetrical Encryption II

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

---
level: 2
---

# Demonstrating Symmetrical Encryption II

Now update the main code.

Quick outline of the code:

- We are using a "hard coded" password for this. In reality, you would ask the user for the password.
- We encode the password as bytes
- we define a 'salt' length, and then create a random string of 16 characters
- Next, we generate a key derivation function (KDF) which is a series of bytes used for cryptography
    - Read this: https://cryptography.io/en/latest/hazmat/primitives/key-derivation-functions/
- We use this KDF to encode the password, and generate a ASCII character safe version of the password to act as the key.

---
level: 2
---

# Demonstrating Symmetrical Encryption II

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

---
level: 2
---

# Demonstrating Symmetrical Encryption II

## Exercise

Identify some of the methods that can be used for KDF.


---
level: 2
---

# Demonstrating Symmetrical Encryption III

## Incorrect Keys

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

---
level: 2
---

# Demonstrating Symmetrical Encryption III

## Exercise

Duplicate the original `symmetrical_encryption.py` file, and rename the copy to `symmetrical_invalid_keys.py`

Use the above code, plus the symmetrical encryption code, to create your own example to test the exception out.

<Announcement type=warning title="WARNING">

As stated in Fernet docs, beware of large files; Fernet is ideal for encrypting data that easily fits in memory.

You may need to think of methods to split larger files up to use this encryption method on large files.
</Announcement>

---
level: 2
---

# Encrypting and Decrypting Files

We can also encrypt files using this method since files can be read as bytes.

The basic method is:

- Open the file
- Read the bytes
- Encrypt the data
- Write encrypted data to a new file.

---
level: 2
---

# Encrypting and Decrypting Files

## Encrypting a File

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

---
level: 2
---

# Encrypting and Decrypting Files

## Decrypt a File:

The process is very similar

- Open the file
- Read the bytes
- Decrypt the data
- Write decrypted data to a new file.

---
level: 2
---

# Encrypting and Decrypting Files

## Decrypting Files

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

---
level: 2
---

# Encrypting and Decrypting Files

## Exercise:

Create a new python script file, named `encrypt_decript_text_file.py`.

Create a main function where you:

- ask the user for an input filename
- ask teh user for an output filename
- ask the user for a temporary filename
- call a new methd `encrypt_file` to encrypt the input file and write to the temporary file.
- Call a new method `decrypt_file` to read the temporart file and write the decrypted data to the output file.

---
level: 2
---

# Encrypting and Decrypting Files

### Encrypt

Create a new method (function) called `encrypt_file` that:

- takes TWO filenames (input filename, temporary filename) as parameters,
- and a third parameter which is the encryption key.

The method then uses the sample code above to encrypt the file contents and write the new data to the new file.

### Decrypt

Create a new method (function) called `decrypt_file` that:

- takes two filenames (output filename, temporary filename),
- and the key used to encrypt the data.

The method then reads the temporary file, and decrypts the data and writes the results to the output file.

---
level: 2
---

# Encrypting and Decrypting Files

## The Source File

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

---
level: 2
---

# Encrypting and Decrypting Files

## Execution

Execute the script using the values:

| Input              | Value                     |
|--------------------|---------------------------|
| Input Filename     | quick-test-original.txt   |
| Temporary Filename | quick-test-encrypted.data |
| Output Filename    | quick-text-decrypted.txt  |

Verify that the code executed as expected.

Fix any errors encountered.


---
level: 2
layout: two-cols
---

# Superchallenge

## Code Fun: Secret Messages II

Create a text User Interface (TUI) for your secret message application.

::left::

The user interface will:

- allow the user to select the offset
- allow the user to type messages in and send to the chat
- allow messages to be received, decoded and displayed automatically
- does **not** stop the messages being displayed when waiting for input

Gain inspiration from systems such as IRC, SMS, etc.

_Next slide has useful resources._

::right::

![Sample of an IRC Screen](./irc-screen-itorresdelpaine.png)


---
level: 2
---

# Superchallenge

## Code Fun: Secret Messages II

### Useful resources

- Ahmed, N. (2024, November 9). 5 Best Python TUI Libraries for Building Text-Based User Interfaces. DEV
  Community. https://dev.to/lazy_code/5-best-python-tui-libraries-for-building-text-based-user-interfaces-5fdi
- Villiers, C. de. (2025, March 12). Python Textual: Build Beautiful UIs in the Terminal. Realpython.Com; Real
  Python. https://realpython.com/python-textual/
- Mehmet Öner Yalçın. (2024, November 8). Building a Responsive "Textual" Chat UI with Long-Running Processes.
  Medium. https://oneryalcin.medium.com/building-a-responsive-textual-chat-ui-with-long-running-processes-c0c53cd36224
- Textual - Home. (2025). Textual Documentation. https://textual.textualize.io/
- Welcome - PyTermGUI::docs. (2026). Bczsalba.Com. https://ptg.bczsalba.com/
- Welcome to Rich’s documentation! — Rich 14.1.0 documentation. (2026).
  Readthedocs.Io. https://rich.readthedocs.io/en/latest/

---

# Acknowledgements & References

> Some content was generated with the assistance of Microsoft Copilot

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

---
layout: end
---

# Remember: 🦆

Learning is an ACTIVE Sport

Read<br>
Understand<br>
Write Code<br>
Test<br>
Fix Errors<br>
Repeat

Use your Actual Intelligence, not the Mediochre Intelligence from AI


<!--
List of ports for scans

7,9,13,17,20,21,22,23,25,37,42,49,53,69,80,88,102,110,111,123,135,137,139,143,161,162,381-383,389,427,443,445,464,465,500,514,515,587,593,623,631,636,691,902,989,990,993,995,1024,1027,1080,1194,1234,1270,1293,1433,1434,1521,1550,1701,1707,1723,1801,1883,1900,2000,2019,2082,2083,2375-2377,3306,3389,4000,4444,4500,5060,5061,5269,5280,5281,5298,5351,5353,5355,5432,5500,5671,5672,5900,6660-6664,6665-6669,6679,6881-6999,7000,7400-7402,8000,8006,8007,8008,8086,8087,8332,8333,9000,9090,9100,9200,9800,10000,12345,15672,27017-27057,31337

-->