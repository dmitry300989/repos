import re
pattern = r'^[+-]{0,1}[0-9]*[.][0-9]+$'
str = "-4.2"
m = re.match(pattern, str)
if m:
    print(m[0])
