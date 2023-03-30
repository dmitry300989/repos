regex_integer_in_range = r"[1-9][0-9]{5}"	# Do not delete 'r'.
regex_alternating_repetitive_digit_pair = r"(?s)([0][\d][0])+\1"	# Do not delete 'r'.

import re
P = "110000"

print (bool(re.match(regex_integer_in_range, P)) 
and len(re.findall(regex_alternating_repetitive_digit_pair, P)) < 2)


res = re.findall(regex_alternating_repetitive_digit_pair, P)
print(res)

pattern = r"aa"
S = "aaadaa"
m = re.search(pattern, S)
k = 0
tmpS = S
if m:
    correction = (0 if len(pattern) == 1 else 1)
    while m:
        print((m.start()+k, m.end() + k - 1))
        k += m.end() - correction
        tmpS = S[k:]
        m = re.search(pattern, tmpS)
else:
    print((-1,-1))   