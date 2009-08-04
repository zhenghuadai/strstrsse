#CMPCOUNT:=
CC=gcc
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3 -fPIC 
INC_PATH= -I../lib -I../others
LIB= -lstrmatch
LIBPATH= -L../lib
#Gflag= -O0 -g
#algobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
matchobj:=match.o Mtime.o output.o  extract.o # ${algobj} 
matchgeneobj:=match.o ${algobj} 
matchmulobj:=matchmul.o  output.o extract.o Mtime.o ../others/acsmx.o ../others/snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
match: ${matchobj}
	${CC} ${Gflag} ${INC_PATH} -static  -o match ${matchobj} ${LIB} ${LIBPATH}
matchgene: ${matchgeneobj}
	${CC} ${Gflag} -o matchgene ${matchgeneobj}
matcho3: ${matchobj}
	${CC} ${Gflag}  -o matcho3 ${matchobj}
matchmul:${matchmulobj} 
	${CC} ${Gflag}  ${INC_PATH} -static -o matchmul ${matchmulobj}  ${LIB} ${LIBPATH}
matchasm:${matchasmobj}
	${CC} ${Gflag} -o matchasm ${matchasmobj}
%.o:%.c
	${CC} ${Gflag} ${INC_PATH} -c $< -o $@ 
	
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
	rm -f ${matchmulobj}
