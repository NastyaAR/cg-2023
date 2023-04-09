#ifndef TABLE_H
#define TABLE_H


#include <QTableWidget>
#include "structures.h"

void addPointOnClick(QTableWidget *table, const point_t &point);
point_t removePointFromTable(QTableWidget *table);
void clearTable(QTableWidget *table);

#endif // TABLE_H
