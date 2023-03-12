#ifndef ADDSPECTRE_H
#define ADDSPECTRE_H

#include <QUndoCommand>
#include "line_segment.h"

class AddSpectre : public QUndoCommand
{
public:
	AddSpectre(state_t &old_state, QGraphicsScene *scene, QUndoCommand *parent = nullptr);
	int Id = 1;

	void undo() override;
	int id() const override { return Id; };
private:
	state_t &old_state;
	QGraphicsScene *scene;
};

#endif // ADDSPECTRE_H
