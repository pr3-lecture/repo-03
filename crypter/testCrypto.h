#ifndef TEXT_CRYPTO_H
#define TEXT_CRYPTO_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { const char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

#define OUTPUT_SIZE 255

static int initTest();

static const char* testToShortKeyEncrypt();

static const char* testToShortKeyDecrypt();

static const char* testEncrypt();

static const char* testDecrypt();

static const char* testKeyIllegalCharsEncrypt();

static const char* testKeyIllegalCharsDecrypt();

static const char* testMessageIllegalChars();

static const char* testCypherIllegalChars();

static const char* allTests();

#endif
