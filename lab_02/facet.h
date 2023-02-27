#ifndef FACET_H
#define FACET_H

#include <cstdio>
#include <cstdlib>
#include "errors.h"

struct facet
{
    int point_1;
    int point_2;
};

using facet_t = struct facet;

err_t read_facet(facet_t &facet, FILE *file);

#endif // FACET_H
