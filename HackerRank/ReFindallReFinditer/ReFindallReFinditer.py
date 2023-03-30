import re
#pattern = r'([^aoieu]{2})([aoieu]\1)([^aoieu]{2})'
pattern = r'[QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm]{1}([aeiouAEIOU]{2,})[QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm]{1}'
str = "rabcdeefgyYhFjkIoomnpOeorteeeeep954uuop riiitop"
print(re.findall(pattern, str))
