#include "crypto.h"
#include "testCrypto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* output = NULL;
int tests_run = 0;
KEY key;

static int initTest()
{
    output = malloc(OUTPUT_SIZE * sizeof(char));
    if(!output)
    {
        return 0;
    }

    output[OUTPUT_SIZE - 1] = '\0';

    return 1;
}

static const char* testToShortKeyEncrypt()
{
    key.chars = "";

    mu_assert("Key is to short on encrypt failed", encrypt(key, "HALLO", output) == E_KEY_TOO_SHORT);

    return NULL;
}

static const char* testToShortKeyDecrypt()
{
    key.chars = "";

    mu_assert("Key is to short on decrypt failed", decrypt(key, "HALLO", output) == E_KEY_TOO_SHORT);

    return NULL;
}

static const char* testEncrypt()
{
    memset(output, 0, strlen(output));
    key.chars = "MYKEY";
    int result = encrypt(key, "HALLO", output);

    mu_assert("Encrypt HELLO with MYKEY failed", strcmp("EXGIV", output) == 0 && result == 0);

    return NULL;
}

static const char* testDecrypt()
{
    memset(output, 0, strlen(output));
    key.chars = "MYKEY";
    int result = decrypt(key, "EXGIV", output);

    mu_assert("Decrypt EXGIV with MYKEY failed", strcmp("HALLO", output) == 0 && result == 0);

    return NULL;
}

static const char* testKeyIllegalCharsEncrypt()
{
    key.chars = "MyKEY";

    mu_assert("Key is illegal on encrypt failed", encrypt(key, "WAFFEL", output) == E_KEY_ILLEGAL_CHAR);

    return NULL;
}

static const char* testKeyIllegalCharsDecrypt()
{
    key.chars = "MYKEy";

    mu_assert("Key is illegal on decrypt failed", decrypt(key, "PAPPEL", output) == E_KEY_ILLEGAL_CHAR);

    return NULL;
}

static const char* testMessageIllegalChars()
{
    key.chars = "PPPP";
    mu_assert("Message have illegal characters failed", encrypt(key, "WaFFeL", output) == E_MESSAGE_ILLEGAL_CHAR);

    return NULL;
}

static const char* testCypherIllegalChars()
{
    key.chars = "HELLO";

    mu_assert("Cypher have illegal characters failed", decrypt(key, "H$223", output) == E_CYPHER_ILLEGAL_CHAR);

    return NULL;
}

static const char* allTests()
{
    mu_run_test(testToShortKeyEncrypt);
    mu_run_test(testToShortKeyDecrypt);
    mu_run_test(testEncrypt);
    mu_run_test(testDecrypt);
    mu_run_test(testKeyIllegalCharsEncrypt);
    mu_run_test(testKeyIllegalCharsDecrypt);
    mu_run_test(testMessageIllegalChars);
    mu_run_test(testCypherIllegalChars);

    return NULL;
}

int main()
{
    if(!initTest())
    {
        printf("Memory error\n");
        return EXIT_FAILURE;
    }

    const char *result = allTests();

    if (result)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }

    if(output)
    {
        free(output);
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
