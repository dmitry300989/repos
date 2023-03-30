import cmath, re
complexNumber = "2-5j"
#complexNumber = input()
complexNumber = re.split('{+-}',complexNumber)
if len(complexNumber) == 2:
    x = int(complexNumber[0])
    y = int(complexNumber[1][:-1])
elif len(complexNumber) == 1:
    if 'j' in complexNumber[0]:
        y = int(complexNumber[0][:-1])
        x = 0
    else:
        y = 0
        x = int(complexNumber[0])
else:
    y = x = 0
print(abs(complex(x,y)),cmath.phase(complex(x,y)), sep='\n')