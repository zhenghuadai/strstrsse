#CMPCOUNT:=
include ../lib/config.mk
Compiler?=gcc
CXX=g++ 
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif

ifeq ($(debug), yes)
Gflag= -g -O0 #-fPIC 
LIBSTRMATCH= -lstrmatchd
else 
Gflag=-O3 #-fPIC 
LIBSTRMATCH= -lstrmatch
endif

LIB=$(LIBSTRMATCH)
EXT:=

ifeq ($(SSE42), yes)
Gflag+= -DSSE4 
endif
#Gflag+= -Wall

ifeq ($(arch), x86)
Gflag+= -m32
endif

ifeq ($(arch), x64)
Gflag+= -m64
endif


INC_PATH= -I../lib -I../others -I../lib/mMatch
THREAD_INC=../../..//codelibrarydzh/include
LIBPATH= -L../lib -L../lib/mMatch
#Gflag= -O0 -g
#algobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
utilobj:= Mtime.o extract.o 
matchobj:=match.o    ${utilobj} ../lib/strstrsse2.o io.o  # ${algobj} 
matchthreadobj:=matchthread.o    ${utilobj} ../lib/strstrsse2.o io.o  # ${algobj} 
matchgeneobj:=match.o ${utilobj} ${algobj} 
matchmulobj:=matchmul.o   extract.o Mtime.o ../others/acsmx.o ../others/snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o  Mtime.o
all: match${EXT} matchmul${EXT} 

match${EXT}: ${matchobj}
	${Compiler} ${Gflag} ${INC_PATH} -static  -o match ${matchobj} ${LIB} ${LIBPATH} -lstdc++
matchthread${EXT}: ${matchthreadobj}
	${Compiler} ${Gflag} ${INC_PATH} -static  -o $@ $^  ${LIB} ${LIBPATH} -lstdc++ -lpthread -I${THREAD_INC}
#matchgene: ${matchgeneobj}
#	${Compiler} ${Gflag} ${INC_PATH} -static -o matchgene ${matchgeneobj} ${LIB} ${LIBPATH} 
matcho3${EXT}: ${matchobj}
	${Compiler} ${Gflag}  -o matcho3 ${matchobj}
matchmul${EXT}:${matchmulobj} 
	${Compiler} ${Gflag}  ${INC_PATH} -static -o matchmul ${matchmulobj}  ${LIB} ${LIBPATH}
matchasm${EXT}:${matchasmobj}
	${Compiler} ${Gflag} -o matchasm ${matchasmobj}
mmatch${EXT}:mmatch.o ${utilobj}
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}
genematch${EXT}:genematch.o ${utilobj} io.o
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}

%.o:%.c
	${Compiler} ${Gflag} ${INC_PATH} -c $< -o $@ -I${THREAD_INC}
%.o:%.cpp
	${CXX} ${Gflag} ${INC_PATH} -c $< -o $@ -I${THREAD_INC}
../lib/strstrsse2.o:../lib/strstrsse2.c
	${Compiler} ${Gflag} ${INC_PATH} -msse2  -c $< -o $@ 
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
	rm -f *.exe 
	rm -f ${matchmulobj}

mmatch.o: mmatch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
genematch.o: genematch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
ifeq ($(debug), yes)
match.o:match.c ../lib/match.h ../lib/libstrmatchd.a 
else
match.o:match.c ../lib/match.h ../lib/libstrmatch.a 
endif
