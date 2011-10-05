all : vimtweak.dll

vimtweak.dll : vimtweak.c
	gcc -shared -o $@ $<
