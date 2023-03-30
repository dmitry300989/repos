import re
pattern = r'([0-9a-zA-Z])\1'
s = "sdddgssdg6"
m = re.search(pattern, s)
if m:
    print(m[1])
