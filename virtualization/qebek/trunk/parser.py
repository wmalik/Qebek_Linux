import sys
from time import strftime

# Defines sets of files which are flagged
NOACCESS = set()
HIGH = set()
MEDIUM = set()
LOW = set()


def is_illegal_access(afile): 
    if afile in NOACCESS:
        log_illegal(afile)

def is_cp_ok(fromfile, tofile=None):
    if not tofile is None:
        check_high_to_low_copy(fromfile, tofile)
        return

    if fromfile in HIGH:
        log_copy(fromfile + " High Priv file")
        return

def check_high_to_low_copy(fromfile, tofile):
    if fromfile in HIGH and (tofile in MEDIUM or tofile in LOW):
        log_copy("High Priv file: " + fromfile + " copied to: " + tofile)
    elif fromfile in MEDIUM and tofile in LOW:
        log_copy("Medium Priv file: " + fromfile + " copied to: " + tofile)

def log_illegal(comment):
    log(comment, "Illegal_access")
def log_copy(comment):
    log(comment, "Illegal_copy")
def log(comment, logtype): 
    print "[" + str(datetime.datetime.now()) + "|" + logtype + "] " + comment

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


