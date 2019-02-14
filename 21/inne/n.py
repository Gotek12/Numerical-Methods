from __future__ import division
import numpy as np
import math
import matplotlib.pylab as plt
import sympy as sp
from numpy.linalg import inv

# initial guesses
x = -2
y = -2.5
i1 = 0

while i1 < 5:
    F = np.matrix([[(x**2)+(x*y**3)-9], [(3*y*x**2)-(y**3)-4]])
    theta = np.sum(F)
    J = np.matrix([[(2*x)+y**3, 3*x*y**2], [6*x*y, (3*x**2)-(3*y**2)]])
    Jinv = inv(J)
    xn = np.array([[x], [y]])
    xn_1 = xn - (Jinv*F)
    x = xn_1.item(0)
    y = xn_1.item(1)
    print(xn)
    i1 = i1+1
