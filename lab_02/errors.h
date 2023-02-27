#ifndef ERRORS_H
#define ERRORS_H

#include <QMessageBox>

#define TITLE "Ошибка"
#define FILE_OPEN_MSG "Невозможно открыть файл!"
#define READ_NUMBER_MSG "Некорректное количество точек или граней в файле!"
#define INCORRECT_NUMBER_MSG "Ошибка считывания количества точек или граней!"
#define READ_POINT_MSG "Ошибка считывания точки!"
#define ALLOCATE_MSG "Ошибка выделения памяти!"
#define READ_FACET_MSG "Ошибка считывания грани!"
#define DRAW_LINKS_MSG "Ошибка отрисовки!"
#define FILE_NAME_MSG "Файла с таким именем не существует!"
#define EMPTY_POINTS_MSG "Массив точек пуст!"
#define NUMBER_EVENT_MSG "Ошибка обработки команды!"
#define ANGLE_INPUT_MSG "Ошибка ввода угла!"
#define TRANSFER_INPUT_MSG "Ошибка ввода приращений координат для переноса!"
#define SCALE_INPUT_MSG "Ошибка ввода коэффициентов для масштабирования!"

enum err_t
{
    SUCCESS,
    FILE_OPEN_ERROR,
    READ_NUMBER_ERROR,
    INCORRECT_NUMBER,
    READ_POINT_ERROR,
    ALLOCATE_ERROR,
    READ_FACET_ERROR,
    DRAW_LINKS_ERROR,
    FILE_NAME_ERROR,
    EMPTY_POINTS_ERROR,
    NUMBER_EVENT_ERROR,
    ANGLE_INPUT_ERROR,
    TRANSFER_INPUT_ERROR,
    SCALE_INPUT_ERROR,
};

void error_handler(const err_t err);

#endif // ERRORS_H
