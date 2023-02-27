#ifndef MODEL_H_H
#define MODEL_H_H

#include "points.h"
#include "facets.h"


struct model
{
    point_t center;
    points_t points;
    facets_t facets;
};

using model_t = struct model;

model_t &model_init(void);
err_t load_model(model_t &model, const char *filename);
err_t read_model(model_t &model, FILE *file);
void free_model(model_t &model);
err_t transfer_model(model_t &model, const transfer_t &transfer);
err_t scale_model(model_t &model, const scale_t &scale);
err_t turn_model(model_t &model, const turn_t &turn);
void delete_model(model_t &model);
point_t save_model(model_t &model);

#endif // MODEL_H_H
