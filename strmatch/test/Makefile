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
OBJ_DIR = .debug/
else 
Gflag=-O3 #-fPIC 
LIBSTRMATCH= -lstrmatch
OBJ_DIR = .release/
endif

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(OBJ_DIR)/others)

LIB=$(LIBSTRMATCH)
EXT:=

ifeq ($(SSE42), yes)
Gflag+= -DSSE4 
endif
Gflag+= -Wall -Wextra

ifeq ($(arch), x86)
Gflag+= -m32
endif

ifeq ($(arch), x64)
Gflag+= -m64
endif

Gflag+= -std=c++11

INC_PATH= -I../lib -I../others -I../lib/mMatch
THREAD_INC=../../..//codelibrarydzh/include
LIBPATH= -L../lib -L../lib/mMatch
#Gflag= -O0 -g
#algobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
utilobj:= $(OBJ_DIR)/Mtime.o $(OBJ_DIR)/extract.o #utilobj=$(foreach i, $(utilobj), $(OBJ_DIR)/${i}.o)
matchobj:=$(OBJ_DIR)/match.o    ${utilobj} ../lib/strstrsse2.o $(OBJ_DIR)/io.o strstr-sse2-unaligned.o   # ${algobj} 
matchthreadobj:=$(OBJ_DIR)/matchthread.o    ${utilobj} ../lib/strstrsse2.o  # ${algobj} 
matchgeneobj:=$(OBJ_DIR)/match.o ${utilobj} ${algobj} 
matchmulobj:=$(OBJ_DIR)/matchmul.o $(utilobj)  $(OBJ_DIR)/others/acsmx.o $(OBJ_DIR)/others/snortmwm.o
matchasmobj:=$(OBJ_DIR)/matchasm.o Ady.o $(OBJ_DIR)/extract.o  $(OBJ_DIR)/Mtime.o


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
mmatch${EXT}:$(OBJ_DIR)/mmatch.o ${utilobj}
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}
genematch${EXT}:$(OBJ_DIR)/genematch.o ${utilobj} $(OBJ_DIR)/io.o
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}
strstrtest${EXT}:$(OBJ_DIR)/strstrtest.o
	${CXX} ${Gflag} ${INC_PATH} -static  -o $@ $<  ${LIB} ${LIBPATH} 
mmatchtest${EXT}:$(OBJ_DIR)/mmatchtest.o ${utilobj}
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}
genematchtest${EXT}:$(OBJ_DIR)/genematchtest.o ${utilobj} $(OBJ_DIR)/io.o 
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}

mmatchtest.testcases.create:mmatchtest.testcases.create.cpp ${utilobj} $(OBJ_DIR)/io.o 
	g++ -o $@ $^ -std=c++11  ${INC_PATH}
strstrtest.testcases.create:strstrtest.testcases.create.cpp
	g++ -o $@ $< -std=c++11

$(OBJ_DIR)/%.o:%.c
	${Compiler} ${Gflag} ${INC_PATH} -c $< -o $@ -I${THREAD_INC} 
$(OBJ_DIR)/%.o:%.cpp
	${CXX} ${Gflag} ${INC_PATH} -c $< -o $@ -I${THREAD_INC}
$(OBJ_DIR)/others/%.o $(OBJ_DIR)/others/%.o:../others/%.c
	${Compiler} ${Gflag} ${INC_PATH} -c $< -o $@ -I${THREAD_INC} 
../lib/strstrsse2.o:../lib/strstrsse2.c
	${Compiler} ${Gflag} ${INC_PATH} -msse2  -c $< -o $@ 
../lib/libstrmatch.a:
	make -C ../lib
../lib/libstrmatchd.a:
	make -C ../lib debug=yes
../lib/mMatch/libmmatch.a:
	make -C ../lib/mMatch
../lib/mMatch/libmmatchd.a:
	make -C ../lib/mMatch debug=yes
clean:
	rm -f *.o
	rm -f match
	rm -f mmatch
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
	rm -f *.exe 
	rm -f ${matchmulobj}
	rm -rf .debug .release 


$(OBJ_DIR)/mmatch.o: mmatch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
$(OBJ_DIR)/genematch.o: genematch.cpp ../lib/mMatch/mAc.h  ../lib/mMatch/mMatch.h ../lib/mMatch/mAc.hxx  ../lib/mMatch/mWm.h ../lib/mMatch/mWm.hxx
ifeq ($(debug), yes)
$(OBJ_DIR)/match.o:match.c ../lib/match.h ../lib/libstrmatchd.a 
$(OBJ_DIR)/mmatch.o:mmatch.cpp ../lib/match.h ../lib/mMatch/libmmatchd.a 
$(OBJ_DIR)/mmatchtest.o:mmatchtest.cpp ../lib/match.h ../lib/mMatch/libmmatchd.a 
else
$(OBJ_DIR)/match.o:match.c ../lib/match.h ../lib/libstrmatch.a 
$(OBJ_DIR)/mmatch.o:mmatch.cpp ../lib/match.h ../lib/mMatch/libmmatch.a 
$(OBJ_DIR)/mmatchtest.o:mmatchtest.cpp ../lib/match.h ../lib/mMatch/libmmatch.a 

endif
