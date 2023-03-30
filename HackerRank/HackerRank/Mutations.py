def mutate_string(string, position, character):
    lstString = list(string)
    lstString[position] = character
    return ''.join(lstString)

if __name__ == '__main__':
    s = input()
    i, c = input().split()
    s_new = mutate_string(s, int(i), c)
    print(s_new)
