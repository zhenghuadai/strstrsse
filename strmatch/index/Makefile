#CMPCOUNT:=
CC=gcc
CXX=g++ 
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
ifeq ($(debug), yes)
Gflag= -g -O0 #-fPIC 
else 
Gflag= -O3 #-fPIC 
endif
INC_PATH= -I../lib -I../others -I../lib/mMatch -I../test
LIB= -lstrmatch
LIBPATH= -L../lib -L../lib/mMatch
#Gflag= -O0 -g
utilobj:= Mtime.o  io.o 

all:  test

test:test.o ${utilobj}
	${CXX} ${Gflag}  ${INC_PATH} -static -o $@ $^  -lmmatch  ${LIBPATH}

%.o:%.c
	${CC} ${Gflag} ${INC_PATH} -c $< -o $@ 
%.o:%.cpp
	${CXX} ${Gflag} ${INC_PATH} -c $< -o $@ 
io.o:../test/io.cpp
	${CXX} ${Gflag} ${INC_PATH} -c $< -o $@ 
Mtime.o:../test/Mtime.c
	${CC} ${Gflag} ${INC_PATH} -c $< -o $@ 
chrM.fa:
	ln -s ../test/chrM.fa
test.cpp:chrM.fa	
clean:
	rm -f *.o test

