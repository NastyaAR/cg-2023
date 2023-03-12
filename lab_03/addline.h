#ifndef ADDLINE_H
#define ADDLINE_H

#include <QUndoCommand>
#include "line_segment.h"


class AddLine : public QUndoCommand
{
public:
	AddLine(state_t &old_state, QGraphicsScene *scene, QUndoCommand *parent = nullptr);

	int Id = 0;

	void undo() override;
	int id() const override { return Id; };
private:
	state_t &old_state;
	QGraphicsScene *scene;
};

#endif // ADDLINE_H
