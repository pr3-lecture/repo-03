#include "run.h"
#include "crypto.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* copyString(const char* input, size_t length)
{
    char* destination = NULL;
    destination = (char*) malloc((length + 1) * sizeof(char));

    if(!destination)
    {
        return NULL;
    }

    if(!strncpy(destination, input, length))
    {
        return NULL;
    }
    destination[length] = '\0';

    return destination;
}

char* readLineFrom(FILE* in)
{
    const int readSize = 1024;
    char* destination;

    destination = (char*) malloc(readSize * sizeof(char));

    if(!destination)
    {
        return NULL;
    }

    destination = fgets(destination, readSize - 1, in);
    if(destination)
    {
        char *pos;
        if ((pos=strchr(destination, '\n')) != NULL)
        {
            *pos = '\0';
        }
        else
        {
            destination[readSize] = '\0';
        }
    }

    return destination;
}

char* getFilename(char* path)
{
    size_t size = 0;
    char* p;

    /** Check if it is only the name or a path  **/
    if(!strchr(path, '\\'))
    {
        return path;
    }

    /** Find the begin of the name **/
    p = &path[strlen(path) - 1];
    for(; *p != '\\'; p--)
    {
        ++size;
    }

    /** Return the name of the file **/
    return copyString(p + 1, size);
}

void cleanUp(char* filename, KEY key, char* input, char* output)
{
    if(filename)
    {
        free(filename);
    }
    if(key.chars)
    {
        free(key.chars);
    }
    if(input)
    {
        free(input);
    }
    if(output)
    {
        free(output);
    }
}

int exitWithError(char* msg)
{
    fprintf(stderr, msg);
    fprintf(stderr, "\n");

    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    int (*crypt) (KEY, const char*, char*);
    char* filename = NULL;
    KEY key;
    char* input = NULL;
    char* output = NULL;
    int result = -1;
    key.chars = NULL;

    filename = getFilename(argv[0]);

    if(!filename)
    {
        cleanUp(filename, key, input, output);
        return exitWithError("Error: Failed to allocate memory");
    }
    else if(strcmp(filename, "encrypt.exe") == 0 || strcmp(filename, "encrypt") == 0)
    {
        crypt = encrypt;
    }
    else if(strcmp(filename, "decrypt.exe") == 0 || strcmp(filename, "decrypt") == 0)
    {
        crypt = decrypt;
    }
    else
    {
        cleanUp(filename, key, input, output);
        return exitWithError("Error: Unsupported filename");
    }

    if(argc == 2 || argc == 3)
    {
        key.chars = copyString(argv[1], strlen(argv[1]));

        if(key.chars == NULL)
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Error: Failed to allocate memory");
        }

        if(argc == 2)
        {
            input = readLineFrom(stdin);

            if(!input)
            {
                cleanUp(filename, key, input, output);
                return exitWithError("Error: An input error occured");
            }

            output = (char*) malloc((strlen(input) + 1) * sizeof(char));

            if(!output)
            {
                cleanUp(filename, key, input, output);
                return exitWithError("Error: Failed to allocate memory");
            }
            output[strlen(input)] = '\0';

            result = (*crypt) (key, input, output);

            if(!result)
            {
                printf("%s\n", output);
            }
        }
        else
        {
            FILE* file = NULL;
            file = fopen(argv[2], "r");

            if(!file)
            {
                cleanUp(filename, key, input, output);
                return exitWithError("Error: Failed to open file");
            }

            do {
                input = readLineFrom(file);

                /** Check if it means an error, or end of file out of the loop **/
                if(!input)
                {
                    break;
                }

                if(output)
                {
                    free(output);
                }

                output = (char*) malloc((strlen(input) + 1) * sizeof(char));

                if(!output)
                {
                    fclose(file);
                    cleanUp(filename, key, input, output);
                    return exitWithError("Error: Failed to allocate memory");
                }
                output[strlen(input)] = '\0';

                result = (*crypt) (key, input, output);

                if(!result)
                {
                    printf("%s\n", output);
                }
                else
                {
                    break;
                }
            } while(1);

            /** Check if we reach the end of the file, or the encryption returned an error **/
            if(!result && !feof(file))
            {
                fclose(file);
                cleanUp(filename, key, input, output);
                return exitWithError("Error: Failed to read from file");
            }

            fclose(file);
        }

        if(result == 0)
        {
            /*All done, free the memory we allocated*/
            cleanUp(filename, key, input, output);
        }
        else if(result == E_KEY_TOO_SHORT)
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Error: Key is to short");
        }
        else if(result == E_KEY_ILLEGAL_CHAR)
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Error: Key contains illegal characters");
        }
        else if(result == E_MESSAGE_ILLEGAL_CHAR)
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Error: Message contains illegal characters");
        }
        else if(result == E_CYPHER_ILLEGAL_CHAR)
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Cypher text contains illegal characters");
        }
        else
        {
            cleanUp(filename, key, input, output);
            return exitWithError("Error: An unknown error has occurred");
        }
    }
    else
    {
        cleanUp(filename, key, input, output);
        return exitWithError("Usage: KEY [file name]");
    }

    return 0;
}
