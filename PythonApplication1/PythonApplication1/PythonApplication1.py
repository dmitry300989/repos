import sys
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def nextMove(n,r,c,grid):
    pPos = []
    for y in range(0,len(grid)):
        for x in range(0,len(grid[0])):
            if grid[y][x] == 'p':
                pPos = [x,y]
    diffX = c - pPos[0]
    diffY = r - pPos[1];
    eprint(pPos)
    move = "LEFT"
    if diffX < 0:
        move = "RIGHT"
    elif diffX == 0:
        if diffY < 0:
            move = "DOWN"
        else:
            move = "UP"
    return move

n = int(input())
r,c = [int(i) for i in input().strip().split()]
grid = []
for i in range(0, n):
    grid.append(input())

print(nextMove(n,r,c,grid))