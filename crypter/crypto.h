#ifndef __CRYPTO_H__
#define __CRYPTO_H__

/** Length of key not sufficient. */
#define E_KEY_TOO_SHORT 1

/** Key contains illegal characters. */
#define E_KEY_ILLEGAL_CHAR 2

/** Message contains illegal characters. */
#define E_MESSAGE_ILLEGAL_CHAR 3

/** Cypher text contains illegal characters. */
#define E_CYPHER_ILLEGAL_CHAR 4

#define KEY_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define MESSAGE_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CYPHER_CHARACTERS "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"

/**
 * Key used in de- and encryption.
 */
typedef struct {
    int type; /* Type of the key. */
    char* chars; /* Key characters. */
} KEY;

/**
 * Encrypt the given text and return the encrypted version. The input text
 * may only contain the letters A-Z. No space or other characters are
 * allowed. In case of illegal characters in the text, the function
 * returns E_MESSAGE_ILLEGAL_CHAR. The key must contain a valid character set
 * and have a sufficient length. For XOR encryption only the characters
 * A-Z are valid in the key. The key must have at least a length of 1.
 *
 * @param key Key to be used for the encryption
 * @param input Clear text
 * @param output Encrypted text
 * @return 0 on success, otherwise error code
 */
int encrypt(KEY key, const char* input, char* output);

/**
 * Decrypt the given text and return the decrypted version. The cypher text
 * may only contain the characters defined as output of the encrypt function.
 * For other characters the function will return E_CYPHER_ILLEGAL_CHAR.
 * The key must contain a valid character set
 * and have a sufficient length. For XOR encryption only the characters
 * A-Z are valid in the key. The key must have at least a length of 1.
 *
 * @param key Key to be used for the decryption
 * @param cypherText Cypher text
 * @param output Decrypted text
 * @return 0 on success, otherwise error code
 */
int decrypt(KEY key, const char* cypherText, char* output);

#endif /* __CRYPTO_H__ */
