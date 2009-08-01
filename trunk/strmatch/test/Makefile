#CMPCOUNT:=
CC=gcc
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3 -fPIC 
INC_PATH= -I../lib
LIB= -lstrmatch
LIBPATH= -L../lib
#Gflag= -O0 -g
#algobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
matchobj:=match.o Mtime.o output.o  extract.o # ${algobj} 
matchgeneobj:=match.o ${algobj} 
matchmulobj:=matchmul.o Msbom.o Mwm.o Mshiftor.o Mac.o output.o extract.o Mtime.o acsmx.o snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
match: ${matchobj}
	${CC} ${Gflag} ${INC_PATH} -static  -o match ${matchobj} ${LIB} ${LIBPATH}
lib:${algobj}
	ar cur  strmatch.a $^
	gcc -shared -fPIC -o libstrmatch.so $^
matchgene: ${matchgeneobj}
	${CC} ${Gflag} -o matchgene ${matchgeneobj}
matcho3: ${matchobj}
	${CC} ${Gflag} -O3 -o matcho3 ${matchobj}
matchmul:${matchmulobj} 
	${CC} ${Gflag} -O3 -o matchmul ${matchmulobj} 
matchasm:${matchasmobj}
	${CC} ${Gflag} -o matchasm ${matchasmobj}
%.o:%.c
	${CC} ${Gflag} ${INC_PATH} -c $< 
	
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
