#include "facets.h"

void facets_init(facets_t &facets)
{
    facets.len = 0;
    facets.facets_array = NULL;
}

err_t read_number_of_facets(facets_t &facets, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (fscanf(file, "%zu", &facets.len) != 1)
        rc = READ_NUMBER_ERROR;
    else if (facets.len <= 0)
        rc = INCORRECT_NUMBER;

    return rc;
}

err_t read_facets(facets_t &facets, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (facets.len <= 0)
        rc = INCORRECT_NUMBER;
    else if (facets.facets_array == NULL)
        rc = ALLOCATE_ERROR;
    else
        for (size_t i = 0; i < facets.len; i++)
            rc = read_facet(facets.facets_array[i], file);

    return rc;
}

err_t allocate_array_of_facets(facets_t &facets)
{
    err_t rc = SUCCESS;

    if (facets.len <= 0)
        rc = INCORRECT_NUMBER;
    else if ((facets.facets_array = (facet_t *) malloc(sizeof(facet_t) * facets.len)) == NULL)
        rc = ALLOCATE_ERROR;

    return rc;
}

void free_array_of_facets(facets_t &facets)
{
    free(facets.facets_array);
}

err_t read_all_facets(facets_t &facets, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    if (! rc)
    {
        rc = read_number_of_facets(facets, file);
        if (! rc)
        {
            rc = allocate_array_of_facets(facets);
            if (rc)
                free_array_of_facets(facets);
            else
                rc = read_facets(facets, file);
           }
    }

    return rc;
}
