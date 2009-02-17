CC = icc
test: strstr.o main.o lstrstr.o lstrlen.o lstrstrsse.o
	${CC} -O3 -o teststrstr $^ 
	./teststrstr

main.o:main.c
	${CC} -O3 -c $<
strstr.o:strstr.c
	${CC} -O3 -c $<
lstrstr.o:lstrstr.c
	${CC} -O3 -c $<
%.o:%.c
	${CC} -O3 -c $<
clean:	
	rm -f teststrstr *.o 
