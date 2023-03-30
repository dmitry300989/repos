# Enter your code here. Read input from STDIN. Print output to STDOUT
from html.parser import HTMLParser
import re

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print("Start :", tag)
        for attr in attrs:
            attr_name = attr[0]
            attr_val = attr[1]
            print(f"-> {attr_name} > {attr_val}")
    def handle_endtag(self, tag):
        print("End   :", tag)
    def handle_startendtag(self, tag, attrs):
        print("Empty :", tag)
        for attr in attrs:
            attr_name = attr[0]
            attr_val = attr[1]
            print(f"-> {attr_name} > {attr_val}")
        
# instantiate the parser and fed it some HTML
parser = MyHTMLParser()

N = int(input())
cnt = 0
for _ in range(N):
    line = input()
    if cnt == 0:
        parser.feed(line)
