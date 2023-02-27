#ifndef FACETS_H
#define FACETS_H

#include <cstdio>
#include "facet.h"

struct facets_t
{
    facet_t *facets_array;
    size_t len;
};

void facets_init(facets_t &facets);
err_t read_number_of_facets(facets_t &facets, FILE *file);
err_t read_facets(facets_t &facets, FILE *file);
err_t allocate_array_of_facets(facets_t &facets);
void free_array_of_facets(facets_t &facets);
err_t read_all_facets(facets_t &facets, FILE *file);

#endif // FACETS_H
