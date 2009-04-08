CC = icc
test: strstr.o main.o lstrstr.o lstrlen.o lstrstrsse.o bmstrstr.o
	${CC} -g  -O3 -o teststrstr $^ 
run:
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
