import re
N = int(input())
target_result = []
pattern = r"[#][0-9A-Fa-f]{3,6}"
for _ in range(N):
    line = input()
    if line:
        if line[0] != '#' and  line[0] != '{' and line[0] != '}':
            res = re.findall(pattern, line)
            for el in res:
                target_result.append(el)
for res in target_result:
    print(res)