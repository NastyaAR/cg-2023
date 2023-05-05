#include "clip.h"

static int sign(int arg)
{
	if (arg < 0)
		return -1;
	else if (arg > 0)
		return 1;

	return 0;
}

int isVisible(Point point, Line line) //видимость вычисляется с помощью векторного произведения
{
	int R1 = (point.getX() - line.getStart().getX()) * (line.getFinish().getY() - line.getStart().getY());
	int R2 = (point.getY() - line.getStart().getY()) * (line.getFinish().getX() - line.getStart().getX());

	int R3 = R1 - R2;
	return sign(R3);
}

static void getReverseMatrix(double coef[MATRIX_SIZE][MATRIX_SIZE])
{
	double tmp[MATRIX_SIZE * MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; ++i)
		for (int j = 0; j < MATRIX_SIZE * MATRIX_SIZE; ++j)
		tmp[i] = coef[i][j];

	coef[0][0] = tmp[3];
	coef[0][1] = -1*tmp[1];
	coef[1][0] = -1*tmp[2];
	coef[1][1] = tmp[0];

	int det = tmp[0] * tmp[3] - tmp[1] * tmp[2];

	for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; ++i)
		for (int j = 0; j < MATRIX_SIZE * MATRIX_SIZE; ++j)
		coef[i][j] = 1/det * coef[i][j];
}


Point getInterPoint(Line line1 , Line line2)
{
	double coef[MATRIX_SIZE][MATRIX_SIZE];
	double param[MATRIX_SIZE][PARAM_SIZE];
	int right[MATRIX_SIZE][PARAM_SIZE];

	coef[0][0] = line1.getFinish().getX() - line1.getStart().getX();
	coef[0][1] = line2.getStart().getX() - line2.getFinish().getX();
	coef[1][0] = line1.getFinish().getY() - line1.getStart().getY();
	coef[1][1] = line2.getStart().getY() - line1.getFinish().getY();

	right[0][0] = line2.getStart().getX() - line1.getStart().getX();
	right[1][0] = line2.getStart().getY() - line1.getStart().getY();

	getReverseMatrix(coef);

	param[0][0] = coef[0][0] * right[0][0] + coef[0][1] * right[1][0];
	param[1][0] = coef[1][0] * right[0][0] + coef[1][1] * right[1][0];

	Point point(line1.getStart().getX() + (line1.getFinish().getX() - line1.getStart().getX()) * param[1][0], \
			line1.getStart().getY() + (line1.getFinish().getY() - line1.getStart().getY()) * param[1][0]);

	return point;
}

bool isInter(Line line1, Line line2)
{
	int isVis1 = isVisible(line1.getStart(), line2);
	int isVis2 = isVisible(line1.getFinish(), line2);

	if ((isVis1 < 0 && isVis2 > 0) || (isVis1 > 0 && isVis2 < 0))
		return true;

	return false;
}

void addInterPoint(points_t *result, int *nRes, Point interP)
{
	result->push_back(interP);
	(*nRes)++;
	return;
}

void copyResult(points_t &poly, points_t &result)
{
	for (size_t i = 0; i < result.size(); ++i)
		poly.push_back(result[i]);
}

points_t clip(points_t &poly, points_t &clipper)
{
	int nPoly = poly.size();
	int nClipper = clipper.size();
	int nRes;
	Point F;
	points_t result;

	for (int i = 0; i < nClipper; ++i)
	{
		result.clear();
		nRes = 0;
		Point S = poly[0];

		for (int j = 0; j < nPoly; ++j)
		{
			if (j != 0)
			{
				if (isInter(Line(S, poly[j]), Line(clipper[i], clipper[i + 1])))
				{
					Point interP = getInterPoint(Line(S, poly[j]), Line(clipper[i], clipper[i + 1]));
					addInterPoint(&result, &nRes, interP);
				}
			}
			else
				F = poly[j];
			S = poly[j];
			if (isVisible(S, Line(clipper[i], clipper[i + 1])) >= 0)
					addInterPoint(&result, &nRes, S);
		}
		if (nRes != 0)
		{
			if (isInter(Line(S, F), Line(clipper[i], clipper[i + 1])))
			{
				Point interP = getInterPoint(Line(S, F), Line(clipper[i], clipper[i + 1]));
				addInterPoint(&result, &nRes, interP);
			}
		}
		nPoly = nRes;
		poly.clear();
		copyResult(poly, result);
	}

	return result;
}
