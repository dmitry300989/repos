import numpy

def LinearSearch(A, n, x):
    answer = "Not Found"
    for i in range(0,n):
        if A[i] == x:
            answer = i
    return answer

def BetterLinearSearch(A, n, x):
    answer = "Not Found"
    for i in range(0,n):
        if A[i] == x:
            return i
    return answer

def SentinelLinearSearch(A, n, x):
    last = A[n-1]
    A[n-1] = x
    i = 0
    while A[i] != x:
        i = i + 1
    A[n-1] = last
    if i < n-1 or A[n-1] == x:
        return i
    return "Not found"

def BinarySearch(A, n, x):
    p = 0
    r = n - 1
    while p <= n-1:
        q = int((p + r) / 2)
        if A[q] == x:
            return q
        else:
            if A[q] > x:
                r = q - 1
            else:
                p = q + 1
    return "Not Found"

def RecursiveBinarySearch(A, p, r, x):
    p = 0
    r = n - 1
    if p > r:
         return "Not Found"
    else:
        q = int((p + r) / 2)
        if A[q] == x:
            return q
        else:
            if A[q] > x:
                RecursiveBinarySearch(A, p, q - 1, x)
            else:
                RecursiveBinarySearch(A, q + 1, q, x)

def SelectionSort(A, n):
    for i in range(0,n):
        smallest = i
        for j in range(i+1, n):
            if A[j] < A[smallest]:
                smallest = j
        A[i], A[smallest] = A[smallest], A[i]

def InsertionSort(A, n):
    for i in range(1, n):
        key = A[i]
        j = i - 1
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j = j - 1
        A[j + 1] = key

def Merge(A, p, q, r):
    n1 = q - p + 1
    n2 = r - q
    B = [0] * (n1 + 1)
    C = [0] * (n2 + 1)
    for i in range(0,n1):
        B[i] = A[p + i]
    for j in range(0,n2):
        C[j] = A[q + j + 1]
    B[n1] = 1000
    C[n2] = 1000
    i,j = 0,0
    for k in range(p,r + 1):
        if B[i] <= C[j]:
            A[k] = B[i]
            i = i + 1
        else:
            A[k] = C[j]
            j = j + 1

def MergeSort(A, p, r):
    if p >= r:
        return
    else:
        q = (p + r) // 2
        MergeSort(A, p, q)
        MergeSort(A, q + 1, r)
        Merge(A, p, q, r)

def Partition(A, p, r):
    q = p
    for u in range(p, r):
        if A[u] <= A[r]:
            A[q], A[u] = A[u], A[q]
            q = q + 1
    A[q], A[r] = A[r], A[q]
    return q

def QuickSort(A, p, r):
    if p >= r:
        return
    else:
        q = Partition(A, p, r)
        QuickSort(A, p, q - 1)
        QuickSort(A, q + 1, r)

def ReallySimpleSort(A,n):
    k = 0
    for i in range(0,n):
        if A[i] == 1:
            k = k + 1
    for i in range(0, k):
        A[i] = 1
    for i in range(k,n):
        A[i] = 2

def CountKeysEqual(A, n, m):
    equal = [0] * m
    for i in range(0,n):
        key = A[i]
        equal[key] = equal[key] + 1
    return equal

def CountKeysLess(equal, m):
    less = [0] * m
    for j in range(1,m):
        less[j] = less[j - 1] + equal[j - 1]
    return less

def Rearrange(A, less, n, m):
    B = [0] * n
    next = [0] * m
    for j in range(0, m):
        next[j] = less[j] + 1
    for i in range(0, n):
        key = A[i]
        index = next[key]
        B[index-1] = A[i]
        next[key] = next[key] + 1
    return B

def CountingSort(A, n, m):
    equal = CountKeysEqual(A, len(A), m)
    less = CountKeysLess(equal, m)
    B = Rearrange(A, less, n, m)
    return B

A = [9,5,2,1,6,4,1,9]
AA = [2,2,1,2,1,1,1,2,1,2]
#print(CountingSort(A, len(A), 11))

x = 2
y = 2
z = 2
for i,j,k in zip(range(0,x), range(0,y), range(0,z)):
    print(i,j,k)