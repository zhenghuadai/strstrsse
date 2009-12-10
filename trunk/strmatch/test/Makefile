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
LIB= -lstrmatchd
else 
Gflag= -O3 #-fPIC 
LIB= -lstrmatch
endif

ifeq ($(SSE42), yes)
Gflag+= -DSSE4 
endif
#Gflag+= -Wall

INC_PATH= -I../lib -I../others -I../lib/mMatch
LIBPATH= -L../lib -L../lib/mMatch
#Gflag= -O0 -g
#algobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
utilobj:= Mtime.o extract.o 
matchobj:=match.o  output.o  ${utilobj} ../lib/strstrsse2.o io.o  # ${algobj} 
matchgeneobj:=match.o ${algobj} 
matchmulobj:=matchmul.o  output.o extract.o Mtime.o ../others/acsmx.o ../others/snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
all: match matchmul 

match: ${matchobj}
	${Compiler} ${Gflag} ${INC_PATH} -static  -o match ${matchobj} ${LIB} ${LIBPATH} -lstdc++
matchgene: ${matchgeneobj}
	${Compiler} ${Gflag} -o matchgene ${matchgeneobj}
matcho3: ${matchobj}
	${Compiler} ${Gflag}  -o matcho3 ${matchobj}
matchmul:${matchmulobj} 
	${Compiler} ${Gflag}  ${INC_PATH} -static -o matchmul ${matchmulobj}  ${LIB} ${LIBPATH}
matchasm:${matchasmobj}
	${Compiler} ${Gflag} -o matchasm ${matchasmobj}
mmatch:mmatch.o ${utilobj}
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}
genematch:genematch.o ${utilobj} io.o
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}

%.o:%.c
	${Compiler} ${Gflag} ${INC_PATH} -c $< -o $@ 
%.o:%.cpp
	${CXX} ${Gflag} ${INC_PATH} -c $< -o $@ 
../lib/strstrsse2.o:../lib/strstrsse2.c
	${Compiler} ${Gflag} ${INC_PATH} -msse2  -c $< -o $@ 
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
	rm -f ${matchmulobj}

mmatch.o: mmatch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
genematch.o: genematch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
match.o:match.c ../lib/match.h 
