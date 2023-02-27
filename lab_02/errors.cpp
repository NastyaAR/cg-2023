#include "errors.h"

void error_handler(const err_t err)
{
    switch (err)
    {
    case FILE_OPEN_ERROR:
        QMessageBox::critical(NULL, TITLE, FILE_OPEN_MSG);
        break;
    case READ_NUMBER_ERROR:
        QMessageBox::critical(NULL, TITLE, READ_NUMBER_MSG);
        break;
    case INCORRECT_NUMBER:
        QMessageBox::critical(NULL, TITLE, INCORRECT_NUMBER_MSG);
        break;
    case READ_POINT_ERROR:
        QMessageBox::critical(NULL, TITLE, READ_POINT_MSG);
        break;
    case ALLOCATE_ERROR:
        QMessageBox::critical(NULL, TITLE, ALLOCATE_MSG);
        break;
    case READ_FACET_ERROR:
        QMessageBox::critical(NULL, TITLE, READ_FACET_MSG);
        break;
    case DRAW_LINKS_ERROR:
        QMessageBox::critical(NULL, TITLE, DRAW_LINKS_MSG);
        break;
    case FILE_NAME_ERROR:
        QMessageBox::critical(NULL, TITLE, FILE_NAME_MSG);
        break;
    case EMPTY_POINTS_ERROR:
        QMessageBox::critical(NULL, TITLE, EMPTY_POINTS_MSG);
        break;
    case NUMBER_EVENT_ERROR:
        QMessageBox::critical(NULL, TITLE, NUMBER_EVENT_MSG);
        break;
    case ANGLE_INPUT_ERROR:
        QMessageBox::critical(NULL, TITLE, ANGLE_INPUT_MSG);
        break;
    case TRANSFER_INPUT_ERROR:
        QMessageBox::critical(NULL, TITLE, TRANSFER_INPUT_MSG);
        break;
    case SCALE_INPUT_ERROR:
        QMessageBox::critical(NULL, TITLE, SCALE_INPUT_MSG);
    }
}
