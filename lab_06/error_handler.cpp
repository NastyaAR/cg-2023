#include "error_handler.h"

void handle_error(err_t code)
{
	switch (code) {
	case FILE_OPEN_ERROR:
		QMessageBox::critical(NULL, TITLE, FILE_OPEN_MSG);
		break;
	case INCORRECT_POINT:
		QMessageBox::critical(NULL, TITLE, INCORRECT_POINT_MSG);
		break;
	case NO_FIGURES:
		QMessageBox::critical(NULL, TITLE, NO_FIGURES_MSG);
		break;
	case NO_POINTS:
		QMessageBox::critical(NULL, TITLE, NO_POINTS_MSG);
		break;
	}
}
