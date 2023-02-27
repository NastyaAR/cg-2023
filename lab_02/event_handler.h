#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "canvas.h"

enum event_number_t
{
    LOAD,
    TRANSFER,
    SCALE,
    TURN,
    DRAW,
    CANCEL,
    QUIT
};

struct event
{
    event_number_t number;

    union
    {
        const char *filename;
        turn_t turn;
        scale_t scale;
        transfer_t transfer;
        canvas_t canvas;
    };
};

using event_t = struct event;

err_t event_handler(const event_t &event);

#endif // EVENT_HANDLER_H
