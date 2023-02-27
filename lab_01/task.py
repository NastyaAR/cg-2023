from math import sqrt, isclose, acos, sin
import sympy as sp
from sympy.abc import x, y, a, b
from sympy.solvers.solveset import linsolve


def dist_between_points(p1x, p1y, p2x, p2y):
    return sqrt((p1x - p2x) ** 2 + (p1y - p2y) ** 2)


def get_center_points(p1x, p1y, p2x, p2y):
    return [(p1x + p2x) / 2, (p1y + p2y) / 2]


def make_disc2(p1x, p1y, p2x, p2y):
    radious = dist_between_points(p1x, p1y, p2x, p2y) / 2
    center = get_center_points(p1x, p1y, p2x, p2y)
    
    return radious, center


def get_slope(p1x, p1y, p2x, p2y):
    first_equation = sp.Eq(a * p1x + b, p1y)
    second_equation = sp.Eq(a * p2x + b, p2y)
    
    eqs = [first_equation, second_equation]
    res = linsolve(eqs, (a, b))
        
    return res.args[0][0], res.args[0][1]


def get_center(a_res1, b_res1, a_res2, b_res2):
    eq1 = sp.Eq(y - a_res1 * x, b_res1)
    eq2 = sp.Eq(y - a_res2 * x, b_res2)
    
    eqs = [eq1, eq2]
    res = linsolve(eqs, (x, y))
    
    return res.args[0][0], res.args[0][1]


def check_rectangular(p1x, p1y, p2x, p2y, p3x, p3y):
    a = dist_between_points(p1x, p1y, p2x, p2y)
    b = dist_between_points(p1x, p1y, p3x, p3y)
    c = dist_between_points(p2x, p2y, p3x, p3y)
    if isclose(a**2 + b**2, c**2):
        return get_center_points(p2x, p2y, p3x, p3y)
    elif isclose(a**2 + c**2, b**2):
        return get_center_points(p1x, p1y, p3x, p3y)
    elif isclose(b**2 + c**2, a**2):
        return get_center_points(p1x, p1y, p2x, p2y)
    else:
        return [None, None]
        

def make_disc(p1x, p1y, p2x, p2y, p3x, p3y):
    if (center := check_rectangular(p1x, p1y, p2x, p2y, p3x, p3y)) != [None, None]:
        return dist_between_points(center[0], center[1], p1x, p1y), center
    
    p12x, p12y = get_center_points(p1x, p1y, p2x, p2y)[0], get_center_points(p1x, p1y, p2x, p2y)[1]
    p13x, p13y = get_center_points(p1x, p1y, p3x, p3y)[0], get_center_points(p1x, p1y, p3x, p3y)[1]
    
    a1, b1 = get_slope(p1x, p1y, p2x, p2y)
    a2, b2 = get_slope(p1x, p1y, p3x, p3y)
    
    a_res1 = -1 / a1
    a_res2 = -1 / a2
    b_res1 = p12y - a_res1 * p12x
    b_res2 = p13y - a_res2 * p13x
    
    
    center_x, center_y = get_center(a_res1, b_res1, a_res2, b_res2)
    radious = dist_between_points(center_x, center_y, p1x, p1y)
    
    return radious, [center_x, center_y]
    
    
class disc: 
    def __init__(self, center=None, radious=None, points=None): 
        if points == None: 
            self.center = center 
            self.radious = radious 
        else: 
            if len(points) == 2:
                self.radious, self.center = make_disc2(points[0][0], points[0][1], points[1][0], points[1][1])
            elif len(points) == 3:
                self.radious, self.center = make_disc(points[0][0], points[0][1], points[1][0], points[1][1], points[2][0], points[2][1])
            else:
                self.radious, self.center = None, None
    
    def inside(self, point):
        distance = dist_between_points(self.center[0], self.center[1], point[0], point[1])
        if (distance < self.radious):
            return True
        return False
                

def minidisc(P): 
    n = len(P) 
    D = [disc() for i in range(n)] 
    D[1] = disc(points=[P[0], P[1]]) 
    for i in range(2, n): 
        if D[i-1].inside(P[i]): 
            D[i] = D[i-1] 
        else: 
            D[i] = minidiscwithpoint(P[:i], P[i], D) 
    return D[n-1] 


def minidiscwithpoint(P, q, D): 
    D[0] = disc(points = [P[0], q]) 
    n = len(P) 
    for j in range(1, n): 
        if D[j-1].inside(P[j]): 
            D[j] = D[j-1] 
        else: 
            D[j] = minidiscwith2points(P[:j], P[j], q, D) 
    return D[n-1] 


def minidiscwith2points(P, q1, q2, D): 
    D[0] = disc(points = [q1, q2]) 
    n = len(P) 
    for k in range(n): 
        if D[k].inside(P[k]): 
            D[k+1] = D[k] 
        else: 
            D[k+1] = disc(points=[q1, q2, P[k]]) 
    return D[n]


def count_f(r1, r2, d, r):
    return 2 * acos((r1**2 - r2**2 + d**2) / (2 * r * d))


def calc_segment(r, f):
    return (r**2 * (f - sin(f))) / 2


def calc_area(r1, r2, d):
    f1 = count_f(r1, r2, d, r1)
    f2 = count_f(r2, r1, d, r2)
    
    s1 = calc_segment(r1, f1)
    s2 = calc_segment(r2, f2)
    
    return s1 + s2

'''
def test(): 
    n = 5 
    points = [] 
    for i in range(n): 
        p = [random.randint(1, 10), random.randint(1, 10)]
        points.append(p)
    points = [[7, 4], [7, 4], [1, 1], [3, 8], [7, 7]]
    res = minidisc(points)
    

if __name__ == '__main__': 
    test()
'''