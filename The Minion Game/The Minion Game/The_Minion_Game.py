import time
from itertools import combinations

def CountRepeatSubstr(substr, string, pos):
    cnt = 0
    while (pos < len(string) - 1): 
        res = string.find(substr, pos)
        if res != -1:
            cnt += 1
            pos = res + 1
        else:
            break
    return cnt

def CountPoint(gamer):
    sum = 0
    for key,val in gamer.items():
        sum += val
    return sum

def WhoWin(kevin, stuart):
    print("kevin ",CountPoint(kevin)) if CountPoint(kevin) > CountPoint(stuart) else print("stuart ",CountPoint(stuart))

def RunVer1(string):
    kevin = {}
    stuart = {}
    vowel_list = ['A', 'E', 'I', 'O', 'U',]
    for i in range(0,len(string)):
        if string[i] in vowel_list:
            k = i
            str = string[i]
            while k < len(string):
                if str not in kevin:
                    kevin[str] = CountRepeatSubstr(str, string, i)
                k += 1
                if k + 1 <= len(string):
                    str = string[i:k+1]
        else:
            if string[i] not in stuart:
                k = i
                str = string[i]
                while k < len(string):
                    if str not in stuart:
                        stuart[str] = CountRepeatSubstr(str, string, i)
                    k += 1
                    if k + 1 <= len(string):
                        str = string[i:k+1]
    WhoWin(kevin, stuart)

def RunVer2(string):
    kevin = {}
    stuart = {}
    vowel_list = ['A', 'E', 'I', 'O', 'U',]
    # Get all substrings of string
    # Using list comprehension + string slicing
    res = [string[i: j] for i in range(len(string))
          for j in range(i + 1, len(string) + 1)]
    #print("All substrings of string are : " + str(res))

def RunVer3(string):
    vow = "AEIOU"
    slen = len(string)
    tsub = int(slen * (slen + 1) / 2)
    k = sum(slen - i for i in range(slen) if string[i] in vow)   
    s = tsub - k

    if s > k: print(f"Stuart {s}")
    elif s < k: print(f"Kevin {k}")
    else: print("Draw")

def RunVer4(string):
    vowels = 'AEIOU'
    Stuart_score, Kevin_score = 0, 0
    length = len(string)
    for start_idx in range(length):
        score = length - start_idx
        if string[start_idx] in vowels:
            Kevin_score += score
        else:
            Stuart_score += score
    if Stuart_score == Kevin_score:
        print('Draw')
    if Stuart_score > Kevin_score:
        print('Stuart {}'.format(Stuart_score))
    if Stuart_score < Kevin_score:
        print('Kevin {}'.format(Kevin_score))

def minion_game(string):
    # your code goes here
    RunVer4(string)

if __name__ == '__main__':
    s = []
    s.append("BANANA")
    with open('data.txt', 'r') as file:
        s.append(file.read().replace('\n', ''))
    minion_game(s[0])
    start_time = time.time()
    minion_game(s[1])
    print("--- %s seconds ---" % (time.time() - start_time))