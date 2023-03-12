#include "deleteall.h"

DeleteAll::DeleteAll(state_t &state, QGraphicsScene *scene, QUndoCommand *parent)
	: QUndoCommand(parent), old_state(state), scene(scene)
{
}

static double to_radians(double angle)
{
	return M_PI / 180 * angle;
}

void DeleteAll::undo()
{
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
			bresenham_without_gradation(old_state.lines[i], scene);
			break;
		case WU:
			wu_algorithm(old_state.lines[i], scene);
			break;
		}

	for (size_t i = 0; i < old_state.spectres.size(); i++)
	{
		line_segment_t line;

		line.color = old_state.spectres[i].color;
		line.start_x = old_state.spectres[i].center_x;
		line.start_y = old_state.spectres[i].center_y;
		line.method = old_state.spectres[i].method;

		double x = line.start_x + old_state.spectres[i].len;
		double y = line.start_y;

		for (double angle = 0; angle < 360; angle += old_state.spectres[i].angle)
		{
			x = old_state.spectres[i].len * cos(to_radians(angle)) + line.start_x;
			y = old_state.spectres[i].len * sin(to_radians(angle)) + line.start_y;

			line.finish_x = x;
			line.finish_y = y;

			switch (line.method) {
			case STANDART:
				lib_algorithm(line, scene);
				break;
			case DDA:
				dda_algorithm(line, scene);
				break;
			case BRESENHAM_REAL:
				double_bresenham_algorithm(line, scene);
				break;
			case BRESENHAM_INT:
				int_bresenham_algorithm(line, scene);
				break;
			case BRESENHAM_NO_GRADATION:
				bresenham_without_gradation(line, scene);
				break;
			case WU:
				wu_algorithm(line, scene);
				break;
			}
	}
	}
}
