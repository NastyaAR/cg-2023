#ifndef DELETEALL_H
#define DELETEALL_H

#include <QUndoCommand>
#include "line_segment.h"

class DeleteAll : public QUndoCommand
{
public:
	DeleteAll(state_t &old_state, QGraphicsScene *scene, QUndoCommand *parent = nullptr);

	int Id = 2;

	void undo() override;
	int id() const override { return Id; };
private:
	state_t &old_state;
	QGraphicsScene *scene;
};

#endif // DELETEALL_H
