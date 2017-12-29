#include "run.h"
#include "crypto.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* copyString(const char* input, size_t length)
{
    char* copy = NULL;
    copy = (char*) malloc ((length +1)* sizeof(char));

    if(!copy)
    {
        return NULL;
    }
    if(!strncpy(copy, input, length))
    {
        return NULL;
    }
    copy[length] = '\0';

    return copy;
}
char* readLineFrom(FILE* in)
{
    return NULL;
}
char* getFilename(char* path){
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
    return 0;
}
int main(int argc, char** argv)
{
    char* filename = NULL;
    KEY key;
    char* input = NULL;
    char* output = NULL;

    filename = getFilename(argv[0]);

    if(!filename){
        cleanUp(filename, key, input, output);
        return exitWithError("");
    }
    return 0;
}
