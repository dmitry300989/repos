import re

line_list = ["4123456789123456", "5123-4567-8912-3456", "61234-567-8912-3456", "4123356789123456", "5133-3367-8912-3456", "5123 - 3567 - 8912 - 3456"];
pattern_list = [r"[456][0-9]{3}-[0-9]{4}-[0-9]{4}-[0-9]{4}", r"([456][0-9]{15})"]
isValid = False
for line in line_list:
    isValid = False
    if len(line) != 19 and len(line) != 16:
        print("Invalid")
        continue
    else:
        for i in range(len(pattern_list)):
            m = re.match(pattern_list[i], line)
            if m:
                if i == 0:
                    line = line.replace('-',"")
                    m = re.match(r"(\d){4}\1",line)
                    if not m:
                        print("Valid")
                        isValid = True
                else:
                    m = re.match(r"(\d{4})\1",line)
                    if not m:
                        print("Valid")
                        isValid = True
                break
    if not isValid:
        print("Invalid")
