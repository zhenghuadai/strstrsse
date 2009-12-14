#CMPCOUNT:=
include config.mk
Compiler=gcc
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif

ifeq ($(debug), yes)
Gflag= -O0 -g
libstrmatch=libstrmatchd.a
libstrmatchso=libstrmatchd.so
else 
libstrmatch=libstrmatch.a
libstrmatchso=libstrmatch.so
Gflag= -O3 
endif
Gflag+= -fPIC -msse2

ifeq ($(arch), x86)
Gflag+= -m32
endif

ifeq ($(arch), x64)
Gflag+= -m64
endif

sobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o dsor.o strstrsse.o lstrstr.o report.o 
ifeq ($(SSE42), yes)
sobj+=strstrsse42.o 
endif
mobj:= Msbom.o Mwm.o Mshiftor.o Mac.o
algobj:= ${sobj} ${mobj} 
matchmulobj:=matchmul.o  output.o extract.o Mtime.o acsmx.o snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
lib:${algobj}
	ar cur  $(libstrmatch) $^
	${Compiler} ${Gflag} -shared -fPIC -o $(libstrmatchso) $^
matchgene: ${matchgeneobj}
	${Compiler} ${Gflag} -o matchgene ${matchgeneobj}
matcho3: ${matchobj}
	${Compiler} ${Gflag} -O3 -o matcho3 ${matchobj}
matchmul:${matchmulobj} 
	${Compiler} ${Gflag} -O3 -o matchmul ${matchmulobj} 
matchasm:${matchasmobj}
	${Compiler} ${Gflag} -o matchasm ${matchasmobj}
%.o:%.c
	${Compiler} ${Gflag} -c $< 
strstrsse42.o:strstrsse42.c
	${Compiler} ${Gflag} -msse4  -c $< 
clean:
	rm -f *.o
	rm -f libstrmatch.a libstrmatch.so
