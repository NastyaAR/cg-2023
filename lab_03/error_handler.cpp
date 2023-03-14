#include "error_handler.h"

void handle_error(err_t code)
{
	switch (code) {
	case FILE_OPEN_ERROR:
		QMessageBox::critical(NULL, TITLE, FILE_OPEN_MSG);
		break;
	case INCORRECT_LINE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_LINE_MSG);
		break;
	case INCORRECT_SPECTRE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_SPECTRE_MSG);
		break;
	case MATCHING_POINTS_ERR:
		QMessageBox::critical(NULL, TITLE, MATCHING_POINTS_MSG);
		break;
	}
}
