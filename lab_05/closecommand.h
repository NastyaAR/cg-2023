#ifndef CLOSECOMMAND_H
#define CLOSECOMMAND_H

#include <QUndoCommand>
#include "fill.h"

class closeCommand: public QUndoCommand
{
public:
	closeCommand(int indexFigure, line_segment_t &closeLine, figures_t &figures, QGraphicsScene *scene, QUndoCommand *parent=nullptr);
	void undo() override;
private:
	QGraphicsScene *scene;
	line_segment_t &closeLine;
	int indexFigure;
	figures_t &figures;
};

#endif // CLOSECOMMAND_H
