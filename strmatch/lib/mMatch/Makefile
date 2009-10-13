#CMPCOUNT:=
CC=g++ -g 
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3 -fPIC 
#Gflag= -O0 -g
mobj:= mAc.o mMatch.o 
algobj:=  ${mobj} 

all: libmmatch

libmmatch:${algobj}
	ar cur  $@.a $^
	${CC} -shared -fPIC -o $@.so $^
%.o:%.cpp
	${CC} ${Gflag} -c $< 
	
clean:
	rm -f *.o
	rm -f *.a *.so
