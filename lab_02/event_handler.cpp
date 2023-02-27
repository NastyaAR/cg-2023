#include "event_handler.h"

err_t event_handler(const event_t &event)
{
    static model_t model = model_init();
    err_t rc = SUCCESS;

    switch (event.number)
    {
    case LOAD:
        rc = load_model(model, event.filename);
        break;
    case TRANSFER:
        save_model(model);
        rc = transfer_model(model, event.transfer);
        break;
    case SCALE:
        save_model(model);
        rc = scale_model(model, event.scale);
        break;
    case TURN:
        save_model(model);
        rc = turn_model(model, event.turn);
        break;
    case DRAW:
        rc = draw_model(event.canvas, model);
        break;
    case CANCEL:
        rc = load_model(model, event.filename);
        break;
    case QUIT:
        delete_model(model);
        break;
    default:
        rc = NUMBER_EVENT_ERROR;
    }

    return rc;
}
