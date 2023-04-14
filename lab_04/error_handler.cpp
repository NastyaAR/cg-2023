#include "error_handler.h"

void handle_error(err_t code)
{
	switch (code) {
	case FILE_OPEN_ERROR:
		QMessageBox::critical(NULL, TITLE, FILE_OPEN_MSG);
		break;
	case INCORRECT_CIRCLE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_CIRCLE_MSG);
		break;
	case INCORRECT_ELLIPSE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_ELLIPSE_MSG);
		break;
	case INCORRECT_CIRCLE_SPECTRE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_CIRCLE_SPECTRE_MSG);
		break;
	case INCORRECT_ELLIPSE_SPECTRE:
		QMessageBox::critical(NULL, TITLE, INCORRECT_ELLIPSE_SPECTRE_MSG);
		break;
	case NULLR:
		QMessageBox::critical(NULL, TITLE, NULLR_MSG);
		break;
	case NULLAB:
		QMessageBox::critical(NULL, TITLE, NULLAB_MSG);
		break;
	}
}
