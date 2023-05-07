#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H


#include <QUndoCommand>
#include <QListWidget>
#include <QMainWindow>
#include "clip.h"
#include "draw.h"
#include "figure.h"

class drawCommand : public QUndoCommand
{
public:
	drawCommand(figure_t srcFigure, figure_t clipper, currentColors_t c, QGraphicsScene *scene, QListWidget *list1, QListWidget *list2, QUndoCommand *parent = nullptr);
	void undo() override;
private:
	QGraphicsScene *scene;
	figure_t clipper;
	figure_t srcFigure;
	currentColors_t c;
	QListWidget *list1;
	QListWidget *list2;
};

#endif // DRAWCOMMAND_H
