#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QMessageBox>

#define TITLE "Ошибка!"

#define FILE_OPEN_MSG "Ошибка открытия файла!"
#define INCORRECT_CIRCLE_MSG "Некорректные данные для построения окружности!"
#define INCORRECT_ELLIPSE_MSG "Некорректные данные для построения эллипса!"
#define INCORRECT_CIRCLE_SPECTRE_MSG "Некорректные данные для построения спектра окружностей!"
#define INCORRECT_ELLIPSE_SPECTRE_MSG "Некорректные данные для построения спектра эллипсов!"
#define NULLR_MSG "Нулевой радиус!"
#define NULLAB_MSG "Нулевые полуоси"

enum err_t
{
	SUCCESS,
	FILE_OPEN_ERROR,
	INCORRECT_CIRCLE,
	INCORRECT_ELLIPSE,
	INCORRECT_CIRCLE_SPECTRE,
	INCORRECT_ELLIPSE_SPECTRE,
	NULLR,
	NULLAB,
};


void handle_error(err_t code);

#endif // ERROR_HANDLER_H

