#ifndef ADDITEM_H
#define ADDITEM_H

#include <QUndoCommand>
#include "algorithms.h"

class AddItem : public QUndoCommand
{
public:
	AddItem(state_t &old_state, QGraphicsScene *scene, commands command, QUndoCommand *parent = nullptr);
	void undo() override;

private:
	state_t &old_state;
	QGraphicsScene *scene;
	commands command;
};

#endif // ADDITEM_H
