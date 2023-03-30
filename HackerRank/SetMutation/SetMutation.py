def iu(s1,s2):
    s1 &= s2
    return s1

n = 1
a = set([1,2,3,4,5,6,7,8,9,10,11,12,13,14,24,52])
m = 1
d = {"intersection_update" : iu}
for _ in range(m):
    args = ["intersection_update","10"]
    b = set([2,3,5,6,8,9,1,4,7,11])
    command = args[0]
    N = int(args[1])
    a = d[command](a,b)

