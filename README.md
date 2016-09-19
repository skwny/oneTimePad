This program encrypts and decrypts plaintext into ciphertext using a key. Plaintext is the term for the information that you wish to encrypt and protect. It is human readable. Ciphertext is the term for the plaintext after it has been encrypted by your programs. Ciphertext is not human-readable, and in fact cannot be cracked, if the OTP system is used correctly. A key is the random sequence of characters that will be used to convert Plaintext to Ciphertext, and back again. It must not be re-used, or else the encryption is in danger of being broken.


How to use:

When encrypting plaintext files, files must be within the same directory as the encryption program.

1. Run the encryption program:

	otp_enc_d \<encryptionPort\> &

2. Run the decryption program:

	otp_dec_d \<decryptionPort\> &

3. Generate a key greater than or equal to the plaintext length and save it to a file within the same directory:

	keygen \<length\> > \<keyFileName\>

4. Encrypt the plaintext into a new ciphertext file:

	otp_enc \<plainTextFile\> \<keyFileName\> \<encryptionPort\> > \<cipherTextFile\>

5. Decrypt the ciphertext file:

	otp dec \<cipherTextFile\> \<keyFileName\> \<decryptionPort\> \<newPlainTextFile\>




Example:

$ cat plaintext1

THE RED GOOSE FLIES AT MIDNIGHT

$ otp_enc_d 57171 &

$ otp_dec_d 57172 &

$ keygen 10 > myshortkey

$ otp_enc plaintext1 myshortkey 57171 > ciphertext1

Error: key ‘myshortkey’ is too short

$ echo $?

1
$ keygen 1024 > mykey

$ otp_enc plaintext1 mykey 57171 > ciphertext1

$ cat ciphertext1

GU WIRGEWOMGRIFOENBYIWUG T WOFL

$ keygen 1024 > mykey2

$ otp_dec ciphertext1 mykey 57172 > plaintext1_a

$ otp_dec ciphertext1 mykey2 57172 > plaintext1_b

$ cat plaintext1_a

THE RED GOOSE FLIES AT MIDNIGHT

$ cat plaintext1_b

WVIOWBTUEIOBC  FVTROIROUXA JBWE

$ cmp plaintext1 plaintext1_a

$ echo $?

0

$ cmp plaintext1 plaintext1_b

plaintext1 plaintext1_b differ: byte 1, line 1

$ echo $?

1

$ otp_enc plaintext5 mykey 57171

otp_enc_d error: input contains bad characters

$ otp_enc plaintext3 mykey 57172

Error: could not contact otp_enc_d on port 57172

$ echo $?

2