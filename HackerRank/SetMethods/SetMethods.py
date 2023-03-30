#n = int(input())
#s = set(map(int,input().split()))
n = 10
s = {1,2,3,4,5,6,7,8,9}
#print(s)
N = int(input())
for _ in range(N):
    args = input().split()
    try:
        if len(args) < 2:
            s.pop()
        else:
            if args[0] == 'remove':
                s.remove(int(args[1]))
            elif args[0] == 'discard':
                s.discard(int(args[1]))
    except KeyError as ke:
        pass
print(sum(s))

s = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
s.pop()
print(list(s))