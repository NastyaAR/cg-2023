#include "clip.h"

static int sign(int arg)
{
	if (arg < 0)
		return -1;
	else if (arg > 0)
		return 1;

	return 0;
}

static int vectorProduct(Point v1, Point v2)
{
	return v1.getX() * v2.getY() - v1.getY() * v2.getX();
}

bool isVisible(Line src, Point p, int norm)
{
	Point v1 = src.getFinish() - src.getStart();
	Point v2 = p - src.getFinish();

	int pr = vectorProduct(v1, v2);

	if (pr * norm >= 0)
		return true;

	return false;
}

bool findInter(Point &p, Line src, Line sec, int norm)
{
	bool vis1 = isVisible(src, sec.getStart(), norm);
	bool vis2 = isVisible(src, sec.getFinish(), norm);
	bool is_inter = (vis1 || vis2) && (!(vis1 && vis2));

	if (is_inter) {
		Point cut_vec = src.getFinish() - src.getStart();
		Point pol_vec = sec.getFinish() - sec.getStart();

		long nominator = cut_vec.getY() * (sec.getStart().getX() - src.getStart().getX()) - cut_vec.getX() * (sec.getStart().getY() - src.getStart().getY());
		long denomanator = pol_vec.getY() * cut_vec.getX() - pol_vec.getX() * cut_vec.getY();

		if (denomanator == 0)
			p = sec.getFinish();
		else {
			double t = (double)nominator / denomanator;
			Point tmp = sec.getFinish() - sec.getStart();
			tmp.setX(tmp.getX() * t);
			tmp.setY(tmp.getY() * t);
			p = sec.getStart() + tmp;
		}
	}

	return is_inter;
}

void addInterPoint(points_t *result, int *nRes, Point interP)
{
	result->push_back(interP);
	(*nRes)++;
	return;
}

static Point getVector(Line l)
{
	return Point(l.getFinish().getX() - l.getStart().getX(), l.getFinish().getY() - l.getStart().getY());
}

int checkConvex(figure_t &cut)
{
	size_t size = cut.points.size();
	if (size < 3)
		return false;

	Point v1 = getVector(cut.lines[cut.lines.size() - 1]);
	Point v2 = getVector(cut.lines[0]);

	int prev = sign(vectorProduct(v1, v2));

	for (size_t i = 0; i < cut.lines.size() - 1; i++)
	{
		v1 = getVector(cut.lines[i]);
		v2 = getVector(cut.lines[i + 1]);

		int cur = sign(vectorProduct(v1, v2));

		if (cur == 0 || prev == 0)
			continue;
		if (prev != cur)
			return 0;
		prev = cur;
	}

	return prev;
}


points_t clip(points_t &poly, figure_t &clipper)
{
	int nPoly = poly.size();
	int nClipper = clipper.points.size();
	int nRes;
	Point F;
	points_t result;
	Point S = poly[0];

	int normal = checkConvex(clipper);
	for (int i = 0; i < nClipper - 1; ++i)
	{
		result.clear();
		nRes = 0;

		for (int j = 0; j < nPoly; ++j)
		{
			if (j != 0)
			{
				Point interP;
				if (findInter(interP, Line(clipper.points[i], clipper.points[i + 1]), Line(S, poly[j]), normal))
					addInterPoint(&result, &nRes, interP);
			}
			else
				F = poly[j];
			S = poly[j];
			if (isVisible(Line(clipper.points[i], clipper.points[i + 1]), S, normal))
					addInterPoint(&result, &nRes, S);
		}
		if (nRes != 0)
		{
			Point interP;
			if (findInter(interP, Line(clipper.points[i], clipper.points[i + 1]), Line(S, F), normal))
				addInterPoint(&result, &nRes, interP);
		}
		nPoly = nRes;
		poly = result;
	}

	return result;
}
