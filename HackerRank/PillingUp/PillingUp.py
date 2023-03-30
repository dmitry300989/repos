from collections import deque
T = 1
res = 'Yes'
for _ in range(T):
    n = 3
    blocks = deque([6,5,2, 1,3, 1,2,5,6])
    pile = []
    while blocks:
        if blocks[0] > blocks[-1]:
            val = blocks.popleft()
            if pile:
                if val > pile[-1]:
                    res = 'No'
                    break;
            pile.append(val)
        else:
            val = blocks.pop()
            if pile:
                if val > pile[-1]:
                    res = 'No'
                    break;
            pile.append(val)
    print(res)