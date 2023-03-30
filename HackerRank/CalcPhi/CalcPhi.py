import cmath, math
AB = float(input())
BC = float(input())
AC = pow(AB**2+BC**2, 1/2)
theta = 0
if AB == BC:
    theta = 45
else:
    theta = math.acos(BC/AC) * 180 / cmath.pi
    if math.modf(theta)[0] > 0.5:
        theta = math.modf(theta)[1] + 1
    else:
        theta = math.modf(theta)[1]
    theta = int(theta)
print(f"{theta}\N{DEGREE SIGN}")
