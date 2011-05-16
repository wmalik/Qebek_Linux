import sys
from time import strftime

def getTime():
	return strftime("%Y-%m-%d %H:%M:%S")

stdin = ""

while True:
	s = sys.stdin.readline()
	if(not s):
		break
	else:
		if(s.startswith("stdin")):
			char = s.replace("stdin","")
			if(char == '\b'):
				stdin = stdin + "<bak>"
			elif(char == '\n'):
				print '[%s|STDIN] %s' % (getTime(),stdin),
				stdin = ""
			else:
				stdin = stdin + char
		else:
			print '[%s|STDOUT] %s' % (getTime(),s),


