import re
import email.utils
#n = int(input())
pattern = r"([\w]+[-.]?[\w]+)[@]{1}(\w+[-]?\w+)[.]{1}(\w{2,3})"
listEmail = ["very.com3mon@example.c_m", "user.name+tag+sorting@example.com"]
for email in listEmail:
    m = re.match(pattern, email)
    if m:
        print(email)
