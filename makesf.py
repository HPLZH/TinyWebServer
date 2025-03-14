import re


def readfile(fn: str):
    f = open(fn, "r", encoding="gb2312" if fn.endswith(".c") else "utf-8")
    head = f.readline()
    content = f.read().lstrip()
    f.close()
    return head, content


def repl(match):
    fn = match.group(1)
    return readfile(fn)[1]


h, c = readfile("main.c")
text = h + "\n" + c
ptext = ""

while text != ptext:
    ptext = text
    text = re.sub(r"#include \"(.+?)\"", repl, text)
    text = re.sub(r"// #copy \"(.+?)\"", repl, text)

of = open("webServer.c", "w", encoding="gb2312")
of.write(text)
