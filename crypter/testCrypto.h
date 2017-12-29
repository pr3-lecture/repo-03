#ifndef TEXT_CRYPTO_H
#define TEXT_CRYPTO_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { const char *message = test(); tests_run++; \
                                if (message) return message; } while (0)


#endif