import sys
from time import strftime

# Defines sets of files which are flagged
NOACCESS = set()
NOACCESS.add("private.txt")
HIGH = set()
HIGH.add("/root/high_profile.txt")
MEDIUM = set()
MEDIUM.add("/home/medium/high_profile.txt")
LOW = set()
LOW.add("/home/low/high_profile.txt")


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
    print "[" + str(getTime()) + "|" + logtype + "] " + comment

def getTime():
	return strftime("%Y-%m-%d %H:%M:%S")


stdin = open("stdin.log", "a")
stdout = open("stdout.log", "a")
stderr = open("stderr.log", "a")

while True:
	line = sys.stdin.readline()
	if(not line):
		break

	charsToRead = 0

	try:
		charsToRead = int(line)
	except ValueError:
		if(line.startswith("open-")):
				line = line.replace("open-","")
				line = line.replace("\n","")
				#print "Opened file: " + line
				is_illegal_access(line.strip())
		elif(line.startswith("cp-")):
			line = line.replace("cp-","")
			line = line.replace("\n","")
			spl = line.split(";")
			log("Copied file " + spl[0] + " to " + spl[1],"copy")
			is_cp_ok(spl[0].strip(),spl[1].strip())
		else:
			print line,
			continue

	s = sys.stdin.read(charsToRead)	
	s = s.replace("\b","<backspace>",1)
	
	if(s.startswith("stdinp-")):
		s = s.replace("stdinp-","",1)
		s = s.replace(chr(13),"\n")
		s = s.replace(chr(127),"<backspace>")
		s = s.replace("\n", "\n[" + str(getTime()) + "] ")
		stdin.write(s)
		stdin.flush()
	elif(s.startswith("stdout-")):
		s = s.replace("stdout-","",1)
		s = s.replace("\n", "\n[" + str(getTime()) + "] ")
		stdout.write(s)
		stdout.flush()
	elif(s.startswith("stderr-")):
		s = s.replace("stderr-","",1)
		s = s.replace("\n", "\n[" + str(getTime()) + "] ")
		stderr.write(s)
		stderr.flush()


stdin.close()
stdout.close()
stderr.close()
