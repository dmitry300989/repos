from itertools import combinations
s = "HACK"
s = list(s)
s.sort()
k = 4
for i in range(1,k):
    combList = list(map(''.join,list(combinations(s,i))))
    for el in combList:
        print(el)