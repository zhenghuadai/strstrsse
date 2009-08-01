#CMPCOUNT:=
CC=gcc
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3 -fPIC 
#Gflag= -O0 -g
sobj:= Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o 
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
#ac.o:ac.c
#	${CC} ${Gflag} $(DFLAGS) ac.c
#match.o:match.c
#	${CC} ${Gflag} $(DFLAGS) match.c
#Sbf.o:Sbf.c
#	${CC} ${Gflag} $(DFLAGS) Sbf.c
#Smp.o:Smp.c
#	${CC} ${Gflag} $(DFLAGS) Smp.c	 
#Skmp.o:Skmp.c
#	${CC} ${Gflag} $(DFLAGS) Skmp.c
#Sbm.o:Sbm.c
#	${CC} ${Gflag} $(DFLAGS) Sbm.c
#Sbmh.o:Sbmh.c
#	${CC} ${Gflag} $(DFLAGS) Sbmh.c
#Sbmhs.o:Sbmhs.c
#	${CC} ${Gflag} $(DFLAGS) Sbmhs.c
#Ssmith.o:Ssmith.c
#	${CC} ${Gflag} $(DFLAGS) Ssmith.c
#Sdaf.o:Sdfa.c
#	${CC} ${Gflag} $(DFLAGS) Sdfa.c
#Sbdm.o:Sbdm.c
#	${CC} ${Gflag} $(DFLAGS) Sbdm.c
#Sbndm:Sbndm.c
#	${CC} ${Gflag} $(DFLAGS) Sbndm.c
#Sshiftor.o:Sshiftor.c
#	${CC} ${Gflag} $(DFLAGS) Sshiftor.c
#Sshiftand.o:Sshiftand.c
#	${CC} ${Gflag} $(DFLAGS) Sshiftand.c
#Skr.o:Skr.c
#	${CC} ${Gflag} $(DFLAGS) Skr.c
#Sbyh.o:Sbyh.c
#	${CC} ${Gflag} $(DFLAGS) Sbyh.c 
#Sskip.o:Sskip.c
#	${CC} ${Gflag} $(DFLAGS) Sskip.c 
#Skmpskip.o:Skmpskip.c
#	${CC} ${Gflag} $(DFLAGS) Skmpskip.c
#Mac.o:Mac.c
#	${CC} ${Gflag} $(DFLAGS) Mac.c
#matchmul.o:matchmul.c
#	${CC} ${Gflag} $(DFLAGS) matchmul.c
#Msbom.o:Msbom.c
#	${CC} ${Gflag} $(DFLAGS) Msbom.c
#Mwm.o:Mwm.c
#	${CC} ${Gflag} $(DFLAGS) Mwm.c
#Mshiftor.o:Mshiftor.c
#	${CC} ${Gflag} $(DFLAGS) Mshiftor.c
#output.o:output.c
#	${CC} ${Gflag} $(DFLAGS) output.c
#Mtime.o:Mtime.c
#	${CC} ${Gflag} $(DFLAGS) Mtime.c
#matchasm.o:matchasm.c
#	${CC} ${Gflag} -c matchasm.c
#Ady.o:Ady.c
#	${CC} ${Gflag} -c Ady.c
#acsmx.o:acsmx.c acsmx.h
#	${CC} ${Gflag} -c acsmx.c
#snortmwm.o:snortmwm.c
#	${CC} ${Gflag} -c snortmwm.c
%.o:%.c
	${CC} ${Gflag} -c $< 
	
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
