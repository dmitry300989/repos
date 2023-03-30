import math
import os
import random
import re
import sys

# Complete the solve function below.
def solve(s):
    start = 0
    res = list(s)
    for i in range(len(res)):
        if res[i] != ' ' and start == 0:
            start = 1
            res[i] = res[i].upper()
        else:
            if res[i] == ' ':
                start = 0
    #return ' '.join([str[0].upper() + str[1:] for str in s.split()])
    return res

if __name__ == '__main__':

    s = input()
    s = "dmitry menshov maria  elizarova"
    result = solve(s)

    print(result)
