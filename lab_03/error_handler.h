#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <QMessageBox>

#define TITLE "Ошибка!"

#define FILE_OPEN_MSG "Ошибка открытия файла!"
#define INCORRECT_LINE_MSG "Некорректные данные для построения линии!"
#define INCORRECT_SPECTRE_MSG "Некорректные данные для построения спектра!"
#define MATCHING_POINTS_MSG "Начало и конец линии совпадают!"

enum err_t
{
	SUCCESS,
	FILE_OPEN_ERROR,
	INCORRECT_LINE,
	INCORRECT_SPECTRE,
	MATCHING_POINTS_ERR,
};


void handle_error(err_t code);

#endif // ERROR_HANDLER_H
