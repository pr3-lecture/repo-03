#include "crypto.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENCRYPT_MODUS 0
#define DECRYPT_MODUS 1

int crypt(KEY key, const char* in, char* out, int modus)
{
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