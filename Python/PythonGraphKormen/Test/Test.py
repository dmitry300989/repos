N = 5
lst = list(map(int,['1', '2','3','4','5','-9']))
#print([r for r in lst if ((r % 11 == 0) or ((r >= 0) and (r < 10)))])
if all([r > 0 for r in lst]):
    print(any([((r % 11 == 0) or ((r >= 0) and (r < 10))) for r in lst]))
else:
    print('False')