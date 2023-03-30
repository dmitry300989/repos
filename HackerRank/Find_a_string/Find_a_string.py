def count_substring(string, sub_string):
    cnt = 0;
    for i in range(len(string)):
        j = 0
        k = i
        while (j < len(sub_string) and k < len(string)) and (string[k] == sub_string[j]):
            k += 1
            j += 1
        if j == len(sub_string):
            cnt += 1
    return cnt

if __name__ == '__main__':
    string = input().strip()
    sub_string = input().strip()
    
    count = count_substring(string, sub_string)
    print(count)