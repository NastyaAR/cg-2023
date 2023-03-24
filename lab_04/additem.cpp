#include "additem.h"

AddItem::AddItem(state_t &state, QGraphicsScene *scene, commands command, QUndoCommand *parent)
	: QUndoCommand(parent), old_state(state), scene(scene), command(command)
{
}

static void draw_circle1(circle_t &circle, QGraphicsScene *scene)
{
	switch (circle.method) {
	case STANDART:
		lib_algorithm(circle, scene);
		break;
	case CANONICAL:
		canonical_algorithm(circle, scene);
		break;
	case PARAMETRIC:
		parametric_algorithm(circle, scene);
		break;
	case BRESENHAM:
		bresenham_circle(circle, scene);
		break;
	case MIDDLE_POINT:
		middle_point(circle, scene);
		break;
	}
}


static void draw_ellipse1(ellipse_t &ellipse, QGraphicsScene *scene)
{
	switch (ellipse.method) {
	case STANDART:
		lib_algorithm(ellipse, scene);
		break;
	case CANONICAL:
		canonical_algorithm(ellipse, scene);
		break;
	case PARAMETRIC:
		parametric_algorithm(ellipse, scene);
		break;
	case BRESENHAM:
		bresenham_ellipse(ellipse, scene);
		break;
	case MIDDLE_POINT:
		middle_point(ellipse, scene);
		break;
	}
}

static void draw_ellipse_spectre(ellipse_spectre_t &ellipse_spectre, QGraphicsScene *scene)
{
	ellipse_t ellipse;

	double step, A, B;

	switch (ellipse_spectre.variant) {
	case 1:
		for (double A = ellipse_spectre.beginA, B = ellipse_spectre.beginB; A < ellipse_spectre.variable.first.endA; \
			 A += ellipse_spectre.variable.first.step, B += ellipse_spectre.variable.first.step)
		{
			ellipse.a = A;
			ellipse.b = B;
			ellipse.centerX = ellipse_spectre.centerX;
			ellipse.centerY = ellipse_spectre.centerY;
			ellipse.color = ellipse_spectre.color;

			draw_ellipse1(ellipse, scene);
		}
		break;
	case 2:
		step = (ellipse_spectre.variable.second.endA - ellipse_spectre.beginA) / ellipse_spectre.variable.second.number;
		for (double A = ellipse_spectre.beginA, B = ellipse_spectre.beginB; A < ellipse_spectre.variable.second.endA; \
			 A += step, B += step)
		{
			ellipse.a = A;
			ellipse.b = B;
			ellipse.centerX = ellipse_spectre.centerX;
			ellipse.centerY = ellipse_spectre.centerY;
			ellipse.color = ellipse_spectre.color;

			draw_ellipse1(ellipse, scene);
		}
		break;
	case 3:
		A = ellipse_spectre.beginA;
		B = ellipse_spectre.beginB;
		for (int i = 0; i < ellipse_spectre.variable.third.number; i++)
		{
			A += (i * ellipse_spectre.variable.third.step);
			B += (i * ellipse_spectre.variable.third.step);
			ellipse.a = A;
			ellipse.b = B;
			ellipse.centerX = ellipse_spectre.centerX;
			ellipse.centerY = ellipse_spectre.centerY;
			ellipse.color = ellipse_spectre.color;

			draw_ellipse1(ellipse, scene);
		}
		break;
	}
}

static void draw_circle_spectre(circle_spectre_t &circle_spectre, QGraphicsScene *scene)
{
	circle_t circle;
	double R, step;

	switch (circle_spectre.variant)
	{
	case 1:
		for (R = circle_spectre.beginR; R < circle_spectre.variable.first.endR; R += circle_spectre.variable.first.step)
		{
			circle.centerX = circle_spectre.centerX;
			circle.centerY = circle_spectre.centerY;
			circle.color = circle_spectre.color;
			circle.r = R;

			draw_circle1(circle, scene);
		}
		break;
	case 2:
		step = (circle_spectre.variable.second.endR - circle_spectre.beginR) / circle_spectre.variable.second.number;
		for (R = circle_spectre.beginR; R < circle_spectre.variable.second.endR; R += step)
		{
			circle.centerX = circle_spectre.centerX;
			circle.centerY = circle_spectre.centerY;
			circle.color = circle_spectre.color;
			circle.r = R;

			draw_circle1(circle, scene);
		}
		break;
	case 3:
		R = circle_spectre.beginR;
		for (int i = 0; i < circle_spectre.variable.third.number; i++)
		{
			R += (i * circle_spectre.variable.third.step);
			circle.centerX = circle_spectre.centerX;
			circle.centerY = circle_spectre.centerY;
			circle.color = circle_spectre.color;
			circle.r = R;

			draw_circle1(circle, scene);
		}
		break;
	}
}


void AddItem::undo()
{
	switch (command) {
	case ADD_CIRCLE:
		old_state.circles.pop_back();
		break;
	case ADD_ELLIPSE:
		old_state.ellipses.pop_back();
		break;
	case ADD_CIRCLE_SPECTRE:
		old_state.circle_spectres.pop_back();
		break;
	case ADD_ELLIPSE_SPECTRE:
		old_state.ellipse_spectres.pop_back();
		break;
	}

	scene->clear();

	for (size_t i = 0; i < old_state.circles.size(); i++)
		draw_circle1(old_state.circles[i], scene);

	for (size_t i = 0; i < old_state.ellipses.size(); i++)
		draw_ellipse1(old_state.ellipses[i], scene);

	for (size_t i = 0; i < old_state.ellipse_spectres.size(); i++)
		draw_ellipse_spectre(old_state.ellipse_spectres[i], scene);

	for (size_t i = 0; i < old_state.circle_spectres.size(); i++)
		draw_circle_spectre(old_state.circle_spectres[i], scene);
}
