#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QMessageBox>

#define TITLE "Ошибка!"

#define FILE_OPEN_MSG "Ошибка открытия файла!"
#define INCORRECT_POINT_MSG "Некорректная точка!"
#define NO_FIGURES_MSG "Фигуры отсутствуют!"
#define NO_POINTS_MSG "Точки не выбраны!"

enum err_t
{
	SUCCESS,
	FILE_OPEN_ERROR,
	INCORRECT_POINT,
	NO_FIGURES,
	NO_POINTS,
};


void handle_error(err_t code);

#endif // ERROR_HANDLER_H

