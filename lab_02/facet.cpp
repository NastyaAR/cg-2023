#include "facet.h"

err_t read_facet(facet_t &facet, FILE *file)
{
    err_t rc = SUCCESS;

    if (file == NULL)
        rc = FILE_OPEN_ERROR;
    else if (fscanf(file, "%d %d", &facet.point_1, &facet.point_2) != 2)
        rc = READ_FACET_ERROR;

    return rc;
}
