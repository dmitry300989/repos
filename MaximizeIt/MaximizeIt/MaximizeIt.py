nameFile = 'data.txt'
listInput = []
with open(nameFile) as f:
    lines = f.readlines()
    listInput= [line.strip() for line in lines]
print(listInput)
k,m = list(map(int,listInput[0].split()))
datList = []
for i in range(k):
    datList.append(list(map(int,listInput[i + 1].split())))

for i in range(len(datList)):
    datList[i] = list(map(lambda el: el ** 2, datList[i]))
print("datLsit = ", datList)

for i in range(len(datList)):
    datList[i] = list(map(lambda el: el % m, datList[i]))
print(datList)

res = []
t = 0
for i in range(len(datList)):
    for j in range(len(datList[i])):
        if i == 0:
            t = 0
            res.append(datList[i][j] + t)
        else:
            t = res[]
            res.append(datList[i][j] + t)

sum = 0
for lst in datList:
    sum += max(lst) ** 2
print(sum % m)  
'''
k,m = list(map(int,input().split()))
datList = []
for i in range(k):
    datList.append(list(map(int,input().split())))
sum = 0
for lst in datList:
    sum += max(lst) ** 2
print(sum % m)
'''