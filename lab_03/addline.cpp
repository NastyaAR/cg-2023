#include "addline.h"

AddLine::AddLine(state_t &state, QGraphicsScene *scene, QUndoCommand *parent)
	: QUndoCommand(parent), old_state(state), scene(scene)
{
}

void AddLine::undo()
{
	old_state.lines.pop_back();

	scene->clear();

	for (size_t i = 0; i < old_state.lines.size(); i++)
		switch (old_state.lines[i].method) {
		case STANDART:
			lib_algorithm(old_state.lines[i], scene);
			break;
		case DDA:
			dda_algorithm(old_state.lines[i], scene);
			break;
		case BRESENHAM_REAL:
			double_bresenham_algorithm(old_state.lines[i], scene);
			break;
		case BRESENHAM_INT:
			int_bresenham_algorithm(old_state.lines[i], scene);
			break;
		case BRESENHAM_NO_GRADATION:
			bresenham_without_gradation(old_state.lines[i], scene, false);
			break;
		case WU:
			wu_algorithm(old_state.lines[i], scene, false);
			break;
		}
}
