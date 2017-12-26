#include "crypto.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENCRYPT_MODUS 0
#define DECRYPT_MODUS 1

int crypt(KEY key, const char* in, char* out, int modus)
{
    const char* inPos;
    const char* keyPos = key.chars;
    char* outPos = out;
    int pos = -1;
    int firstKeyRun = 1;

    /** Check if the key is to short **/
    if(!strlen(key.chars))
    {
        return E_KEY_TOO_SHORT;
    }

    for(inPos = in; *inPos; ++inPos)
    {
        /** Reuse the key, if the input is longer than the key **/
        if(!*keyPos)
        {
            keyPos = key.chars;
            /** We do not have to check the key again **/
            firstKeyRun = 0;
        }

        /** Check on the first run, if the key contain illegal characters **/
        if(firstKeyRun && !strchr(KEY_CHARACTERS, *keyPos))
        {
            return E_KEY_ILLEGAL_CHAR;
        }

        if(modus == ENCRYPT_MODUS)
        {
            /** Check if the message contain illegal characters **/
            if(!strchr(MESSAGE_CHARACTERS, *inPos))
            {
                return E_MESSAGE_ILLEGAL_CHAR;
            }

            /** Xor the message position with the key position **/
            pos = ((strchr(MESSAGE_CHARACTERS, *inPos) - (MESSAGE_CHARACTERS)) + 1) ^
                  ((strchr(KEY_CHARACTERS, *keyPos) - (KEY_CHARACTERS)) + 1);
            *outPos = CYPHER_CHARACTERS[pos];
        }
        else
        {
            /** Check if the cypher contain illegal characters **/
            if(!strchr(CYPHER_CHARACTERS, *inPos))
            {
                return E_CYPHER_ILLEGAL_CHAR;
            }

            /** Xor the cypher position with the key position **/
            pos = ((strchr(CYPHER_CHARACTERS, *inPos) - (CYPHER_CHARACTERS))) ^
                  ((strchr(KEY_CHARACTERS, *keyPos) - (KEY_CHARACTERS)) + 1);
            *outPos = MESSAGE_CHARACTERS[pos - 1];
        }

        ++outPos;
        ++keyPos;
    }

    return 0;
}

int encrypt(KEY key, const char* input, char* output)
{
    return crypt(key, input, output, ENCRYPT_MODUS);
}

int decrypt(KEY key, const char* cypherText, char* output)
{
    return crypt(key, cypherText, output, DECRYPT_MODUS);
}
