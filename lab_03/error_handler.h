#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QMessageBox>

enum err_t
{
	SUCCESS,
};


void handle_error(err_t code);

#endif // ERROR_HANDLER_H