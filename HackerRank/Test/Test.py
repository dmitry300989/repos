class Complex(object):
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary
        
    def __add__(self, no):
        a = self.real + no.real
        b = self.imaginary + no.imaginary
        res = f"{a:.2f}+{b:.2f}i" if b >= 0 else f"{a:.2f}{b:.2f}i"
        return res
        
    def __sub__(self, no):
        a = self.real - no.real
        b = self.imaginary - no.imaginary
        res = f"{a:.2f}+{b:.2f}i" if b >= 0 else f"{a:.2f}{b:.2f}i"
        return res
        
    def __mul__(self, no):
        a = self.real * no.real - self.imaginary * no.imaginary
        b = self.real * no.imaginary + no.real * self.imaginary
        res = f"{a:.2f}+{b:.2f}i" if b >= 0 else f"{a:.2f}{b:.2f}i"
        return res

    def __truediv__(self, no):
        t = no.real**2 + no.imaginary**2
        a = (self.real * no.real + self.imaginary * no.imaginary) / t
        b = (no.real * self.imaginary - self.real * no.imaginary) / t
        res = f"{a:.2f}+{b:.2f}i" if b >= 0 else f"{a:.2f}{b:.2f}i"
        return res

    def mod(self):
        a = (self.real**2 + self.imaginary**2)**0.5
        res = f"{a:.2f}+0.00i"
        return res

    def __str__(self):
        if self.imaginary == 0:
            result = "%.2f+0.00i" % (self.real)
        elif self.real == 0:
            if self.imaginary >= 0:
                result = "0.00+%.2fi" % (self.imaginary)
            else:
                result = "0.00-%.2fi" % (abs(self.imaginary))
        elif self.imaginary > 0:
            result = "%.2f+%.2fi" % (self.real, self.imaginary)
        else:
            result = "%.2f-%.2fi" % (self.real, abs(self.imaginary))
        return result

import numpy as np
import math

def f(z):
    return 1 / (1 + math.exp(-z))

if __name__ == '__main__':
    c = map(float, [-10,0])
    d = map(float, [5,-6.7])
    x = Complex(*c)
    y = Complex(*d)
    #print(*map(str, [x+y, x-y, x*y, x/y, x.mod(), y.mod()]), sep='\n')
    arr = np.array([1, 2, 3, 4, 5])
    arr = np.array(list(map(f, arr)))