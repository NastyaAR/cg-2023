#ifndef FILLCOMMAND_H
#define FILLCOMMAND_H

#include <QUndoCommand>
#include "fill.h"

class fillCommand: public QUndoCommand
{
public:
	fillCommand(figures_t figures, QGraphicsScene *scene, QUndoCommand *parent = nullptr);
	void undo() override;
private:
	QGraphicsScene *scene;
	figures_t figures;
};

#endif // FILLCOMMAND_H
