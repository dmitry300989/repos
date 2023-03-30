if __name__ == '__main__':
    s = "#$%@^&*kjnk svskjnbui h 4oi3hheuh /dfh uidshvhdsuihv suihc 0hrem89m4c02mw4xo;,wh fwhncoishmxlxfkjsahnxu83v 08 n8OHOIHIOMOICWHOFCMHEOFMCOEJMC0J09C 03J"
    answer = ["False"] * 5
    if s.isalnum():
        answer[0] = "True"
    for i in range(len(s)):
        if s[i].isalnum():
            answer[0] = "True"
        if s[i].isalpha():
            answer[1] = "True"
        if s[i].isdigit():
            answer[2] = "True"
        if s[i].islower():
            answer[3] = "True"
        if s[i].isupper():
            answer[4] = "True"
    print('\n'.join(answer))
