#ifndef JOINCOMMAND_H
#define JOINCOMMAND_H

#include <QUndoCommand>
#include "fill.h"

class joinCommand: public QUndoCommand
{
public:
	joinCommand(int indexFigure, lines_t &joinLines, figures_t &figures, QGraphicsScene *scene, QUndoCommand *parent = nullptr);
	void undo() override;
private:
	QGraphicsScene *scene;
	int indexFigure;
	figures_t &figures;
	lines_t &joinLines;
};

#endif // JOINCOMMAND_H
