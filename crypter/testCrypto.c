#include "crypto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                 if (message) return message; } while (0)

#define INIT_KEY char *key = "TPERULES"; \
    KEY ckey; \
    ckey.type = 1; \
    ckey.chars = key
#define INIT_INPUT char *input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define INIT_OUTPUT char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1))
#define DEINIT_INPUT
#define DEINIT_OUTPUT free(output)
#define DEINIT_KEY

static int tests_run = 0;


static char* test_encrypt_output() {
	char *key = "TPERULES";
    KEY ckey;
    ckey.type = 1;
    ckey.chars = key;

	char *input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1));
    
    encrypt(ckey, input, output);
    mu_assert("output should equal to expected output", strcmp(output, "URFVPJB[]ZN^XBJCEBVF@ZRKMJ") == 0);
    free(output);
    return 0;
}

static char* test_decrypt_output() {
	char *key = "TPERULES";
    KEY ckey;
    ckey.type = 1;
    ckey.chars = key;

	char *input = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ";
    char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

    decrypt(ckey, input, output);
    mu_assert("output should equal to expected output", strcmp(output, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
    free(output);
    return 0;
}

static char* test_invalid_key_type_error() {
	char *key = "TPERULES";
    KEY ckey;
    ckey.type = 0;
    ckey.chars = key;

    INIT_INPUT;
    INIT_OUTPUT;

    int result = encrypt(ckey, input, output);
    mu_assert("encrypt should fail because of invalid key type", result == E_KEY_ILLEGAL_TYPE);

    result = decrypt(ckey, input, output);
    mu_assert("decrypt should fail because of invalid key type", result == E_KEY_ILLEGAL_TYPE);

    DEINIT_INPUT;
    DEINIT_OUTPUT;
    return 0;
}

static char* test_key_too_short_error() {
	char *key = "";
    KEY ckey;
    ckey.type = 1;
    ckey.chars = key;

    INIT_INPUT;
    INIT_OUTPUT;
    
    int result = encrypt(ckey, input, output);
    mu_assert("encrypt should fail because key is too short", result == E_KEY_TOO_SHORT);

    result = decrypt(ckey, input, output);
    mu_assert("decrypt should fail because key is too short", result == E_KEY_TOO_SHORT);

    DEINIT_INPUT;
    DEINIT_OUTPUT;
    return 0;
}

static char* test_key_contains_illegal_char_error() {
	char *key = "`";
    KEY ckey;
    ckey.type = 1;
    ckey.chars = key;

    INIT_INPUT;
    INIT_OUTPUT;
    
    int result = encrypt(ckey, input, output);
    printf("%i\n", result);
    mu_assert("encrypt should fail because key contains an illiegal char", result == E_KEY_ILLEGAL_CHAR);

    result = decrypt(ckey, input, output);
    mu_assert("decrypt should fail because key contains an illiegal char", result == E_KEY_ILLEGAL_CHAR);

    DEINIT_INPUT;
    DEINIT_OUTPUT;
    return 0;
}

static char* test_encrypt_input_contians_illegal_char() {
	INIT_KEY;
    char *input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[";
    INIT_OUTPUT;
    
    int result = encrypt(ckey, input, output);
    printf("%i\n", result);
    mu_assert("encrypt should fail because input contains an illiegal char", result == E_MESSAGE_ILLEGAL_CHAR);

    DEINIT_INPUT;
    DEINIT_OUTPUT;
    DEINIT_KEY;
    return 0;
}

static char* test_decrypt_input_contians_illegal_char() {
	INIT_KEY;
    char *input = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ`";
    INIT_OUTPUT;
    
    int result = decrypt(ckey, input, output);
    printf("%i\n", result);
    mu_assert("decrypt should fail because input contains an illiegal char", result == E_CYPHER_ILLEGAL_CHAR);

    DEINIT_INPUT;
    DEINIT_OUTPUT;
    DEINIT_KEY;
    return 0;
}

static char* allTests() {
    mu_run_test(test_encrypt_output);
    mu_run_test(test_decrypt_output);
    mu_run_test(test_invalid_key_type_error);
    mu_run_test(test_key_too_short_error);
    mu_run_test(test_key_contains_illegal_char_error);
    mu_run_test(test_encrypt_input_contians_illegal_char);
    mu_run_test(test_decrypt_input_contians_illegal_char);
    /* weitere Tests */
    return 0;
}

int main() {
    char *result = allTests();

    if (result != 0) printf("%s\n", result);
    else             printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}