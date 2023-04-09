#include "table.h"


static void addItem(int number, int column, QTableWidget *table)
{
	QTableWidgetItem *item = new QTableWidgetItem();

	item->setText(QString("%1").arg(number));
	table->setItem(table->rowCount() - 2, column, item);
}

void addPointOnClick(QTableWidget *table, const point_t &point)
{
	table->insertRow(table->rowCount() - 1);
	addItem(point.x, 0, table);
	addItem(point.y, 1, table);
}

point_t removePointFromTable(QTableWidget *table)
{
	point_t point = {table->item(table->currentRow(), 0)->text().toInt(), table->item(table->currentRow(), 1)->text().toInt()};
	table->removeRow(table->currentRow());

	return point;
}

static void clearItem(QTableWidgetItem *item)
{
	item->setText(QString(""));
}

void clearTable(QTableWidget *table)
{
	while (table->rowCount() != 1)
		table->removeRow(table->rowCount() - 1);

	clearItem(table->item(0, 0));
	clearItem(table->item(0, 1));

}

