CC=gcc
ifeq ($(debug), yes)
CXXFLAG= -g -O0 #-fPIC
else
CXXFLAG= -O3 #-fPIC
endif

ifeq  "${CC}"  "gcc"  
CXXFLAG+=-msse2 
endif

test: strstr.o main.o lstrstr.o lstrlen.o lstrstrsse.o bmstrstr.o report.o
	${CC}  ${CXXFLAG}   -o teststrstr $^ 
run:
	./teststrstr

main.o:main.c
	${CC} ${CXXFLAG}  -c $<
strstr.o:strstr.c
	${CC} ${CXXFLAG}  -c $<
lstrstr.o:lstrstr.c
	${CC} ${CXXFLAG}  -c $<
%.o:%.c
	${CC} ${CXXFLAG}  -c $<
clean:	
	rm -f teststrstr *.o 
