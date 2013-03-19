#CMPCOUNT:=
include config.mk
Compiler=gcc
Inc=-I./
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif

ifeq ($(debug), yes)
Gflag= -O0 -g
libstrmatch=libstrmatchd.a
libstrmatchso=libstrmatchd.so
OBJ_DIR =debug/
else 
libstrmatch=libstrmatch.a
libstrmatchso=libstrmatch.so
Gflag= -O3 
OBJ_DIR =release/
endif
Gflag+= -fPIC -msse2 
Gflag+= -Wall -Wextra 

ifeq ($(arch), x86)
Gflag+= -m32
endif

$(shell mkdir -p $(OBJ_DIR))

ifeq ($(arch), x64)
Gflag+= -m64
endif

Gflag+= ${Inc}
ssrc:= Sbf.c Sbom.c Smp.c Skmp.c Sbm.c Sbmh.c Sbmhs.c Ssmith.c Sdfa.c Sbdm.c Sbndm.c Sshiftor.c Sshiftand.c Skr.c Sbyh.c Sskip.c Skmpskip.c dsor.c strstrsse.c lstrstr.c report.c  # strstrmmx.c strstrsse2.c 
ifeq ($(SSE42), yes)
ssrc+=strstrsse42.c strstrsse42a.c 
Gflag+= -msse4
endif
msrc:= Msbom.c Mwm.c Mshiftor.c Mac.c

sobj=$(foreach i, $(ssrc), $(OBJ_DIR)/${i}.o)
mobj=$(foreach i, $(msrc), $(OBJ_DIR)/${i}.o)

algobj:= ${sobj} ${mobj} 
matchmulobj:=matchmul.o  output.o extract.o Mtime.o acsmx.o snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
lib:${algobj}
	ar cur  $(libstrmatch) $^
	${Compiler} ${Gflag} -shared -fPIC -o $(libstrmatchso) $^
${OBJ_DIR}/%.c.o:%.c
	${Compiler} ${Gflag} -c $< -o $@ 
${OBJ_DIR}/%strstrsse42.c.o:strstrsse42.c
	${Compiler} ${Gflag} -msse4  -c $<  -o $@ 
${OBJ_DIR}/%strstrmmx.c.o:strstrmmx.c	
	icc -use-msasm -c -O3 $<  -o $@ 
clean:
	rm -f *.o
	rm -f *.a *.so
	rm -f libstrmatch.a libstrmatch.so
	rm -rf debug release
