#CMPCOUNT:=
CC=gcc
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3 -fPIC 
#Gflag= -O0 -g
sobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o dsor.o strstrsse.o lstrstr.o 
mobj:= Msbom.o Mwm.o Mshiftor.o Mac.o
algobj:= ${sobj} ${mobj} 
matchmulobj:=matchmul.o  output.o extract.o Mtime.o acsmx.o snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
lib:${algobj}
	ar cur  libstrmatch.a $^
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
	${CC} ${Gflag} -c $< 
	
clean:
	rm -f *.o
	rm -f libstrmatch.a libstrmatch.so
