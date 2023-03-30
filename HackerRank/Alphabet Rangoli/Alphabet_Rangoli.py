def print_rangoli(size):
    alpha = "abcdefghijklmnopqrstuvwxyz"
    maxWidth = 4 * size - 3
    numAlpha = 0
    rangoli = []
    for i in range(size - 1, -1, -1):
        lst = []
        for j in range(size - 1, size - 2 - numAlpha, -1):
            lst.append(alpha[j])
        l = len(lst)
        for j in range(l - 2, -1, -1):
            lst.append(lst[j])
        rangoli.append(('-'.join(lst)).center(maxWidth,'-'))
        #print(('-'.join(lst)).center(maxWidth,'-'))
        numAlpha += 1
    l = len(rangoli)
    for j in range(l - 2, -1, -1):
        rangoli.append(rangoli[j])
    print('\n'.join(rangoli))
    # your code goes here

if __name__ == '__main__':
    n = int(input())
    print_rangoli(n)