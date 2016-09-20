all : vimtweak64.dll vimtweak32.dll

vimtweak64.dll : vimtweak.c
	x86_64-w64-mingw32-gcc -shared -o $@ $<

vimtweak32.dll : vimtweak.c
	i686-w64-mingw32-gcc -shared -o $@ $<

clean:
	-rm *.dll
