#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This utility function can be used to parse data separated by a using string delimiter.
 * 
 * @param data 
 * @param fields_count Maximum number of fields expected
 * @param separator 
 * @return int  NULL if the data is not in the correct format
 */
int parse_data(char *data, int fields_count, char *separator, char **fields) {
    int correct_format = 0, cpt = 0;
    fields = (char **)malloc(fields_count * sizeof(char *));
    if (fields == NULL) {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    char *field = strtok(data, separator);
    while (field != NULL && cpt < fields_count) {
        fields[cpt] = field;
        cpt++;
        field = strtok(NULL, separator);
    }
    //Check data
    if ((field == NULL) && (cpt == fields_count)) {
        correct_format = 1;
    }
    return (correct_format)? cpt : -1;
}