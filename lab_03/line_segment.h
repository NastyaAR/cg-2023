#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include <QColor>
#include <QGraphicsScene>
#include <vector>
#include <math.h>

enum Method_t
{
	STANDART,
	DDA,
	BRESENHAM_INT,
	BRESENHAM_REAL,
	BRESENHAM_NO_GRADATION,
	WU,
};

struct line_segment
{
    double start_x;
    double start_y;
    double finish_x;
    double finish_y;
	Method_t method;
    QColor color;
};

using line_segment_t = struct line_segment;

struct spectre
{
    double center_x;
    double center_y;
    double angle;
    double len;
	Method_t method;
    QColor color;
};

using spectre_t = struct spectre;

struct state
{
    std::vector <line_segment_t> lines;
    std::vector <spectre_t> spectres;
	QColor line_color;
    QColor sceneColor;
};

using state_t = struct state;

void lib_algorithm(const line_segment_t &line, QGraphicsScene *scene);
void dda_algorithm(const line_segment_t &line, QGraphicsScene *scene);
void double_bresenham_algorithm(const line_segment_t &line, QGraphicsScene *scene);
void int_bresenham_algorithm(const line_segment_t &line, QGraphicsScene *scene);
void bresenham_without_gradation(const line_segment_t &line, QGraphicsScene *scene, bool deleted);
void wu_algorithm(const line_segment_t &line, QGraphicsScene *scene, bool deleted);

#endif // LINE_SEGMENT_H
