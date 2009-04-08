#CMPCOUNT:=
ifeq ($(CMPCOUNT),y)
	DFLAGS:=-c -DCMPCOUNT
else
	DFLAGS:=-c 
endif
Gflag= -O3  
matchobj:=match.o Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o output.o  Mtime.o  extract.o 
matchgeneobj:=match.o Sbf.o Sbom.o Smp.o Skmp.o Sbm.o Sbmh.o Sbmhs.o Ssmith.o Sdfa.o Sbdm.o Sbndm.o Sshiftor.o Sshiftand.o Skr.o Sbyh.o Sskip.o Skmpskip.o output.o  Mtime.o 
matchmulobj:=matchmul.o Msbom.o Mwm.o Mshiftor.o Mac.o output.o extract.o Mtime.o acsmx.o snortmwm.o
matchasmobj:=matchasm.o Ady.o extract.o output.o Mtime.o
match: ${matchobj}
	gcc ${Gflag} -o match ${matchobj}
matchgene: ${matchgeneobj}
	gcc ${Gflag} -o matchgene ${matchgeneobj}
matcho3: ${matchobj}
	gcc ${Gflag} -O3 -o matcho3 ${matchobj}
matchmul:${matchmulobj} 
	gcc ${Gflag} -O3 -o matchmul ${matchmulobj} 
matchasm:${matchasmobj}
	gcc ${Gflag} -o matchasm ${matchasmobj}
ac.o:ac.c
	gcc ${Gflag} $(DFLAGS) ac.c
match.o:match.c
	gcc ${Gflag} $(DFLAGS) match.c
Sbf.o:Sbf.c
	gcc ${Gflag} $(DFLAGS) Sbf.c
Smp.o:Smp.c
	gcc ${Gflag} $(DFLAGS) Smp.c	 
Skmp.o:Skmp.c
	gcc ${Gflag} $(DFLAGS) Skmp.c
Sbm.o:Sbm.c
	gcc ${Gflag} $(DFLAGS) Sbm.c
Sbmh.o:Sbmh.c
	gcc ${Gflag} $(DFLAGS) Sbmh.c
Sbmhs.o:Sbmhs.c
	gcc ${Gflag} $(DFLAGS) Sbmhs.c
Ssmith.o:Ssmith.c
	gcc ${Gflag} $(DFLAGS) Ssmith.c
Sdaf.o:Sdfa.c
	gcc ${Gflag} $(DFLAGS) Sdfa.c
Sbdm.o:Sbdm.c
	gcc ${Gflag} $(DFLAGS) Sbdm.c
Sbndm:Sbndm.c
	gcc ${Gflag} $(DFLAGS) Sbndm.c
Sshiftor.o:Sshiftor.c
	gcc ${Gflag} $(DFLAGS) Sshiftor.c
Sshiftand.o:Sshiftand.c
	gcc ${Gflag} $(DFLAGS) Sshiftand.c
Skr.o:Skr.c
	gcc ${Gflag} $(DFLAGS) Skr.c
Sbyh.o:Sbyh.c
	gcc ${Gflag} $(DFLAGS) Sbyh.c 
Sskip.o:Sskip.c
	gcc ${Gflag} $(DFLAGS) Sskip.c 
Skmpskip.o:Skmpskip.c
	gcc ${Gflag} $(DFLAGS) Skmpskip.c
Mac.o:Mac.c
	gcc ${Gflag} $(DFLAGS) Mac.c
matchmul.o:matchmul.c
	gcc ${Gflag} $(DFLAGS) matchmul.c
Msbom.o:Msbom.c
	gcc ${Gflag} $(DFLAGS) Msbom.c
Mwm.o:Mwm.c
	gcc ${Gflag} $(DFLAGS) Mwm.c
Mshiftor.o:Mshiftor.c
	gcc ${Gflag} $(DFLAGS) Mshiftor.c
output.o:output.c
	gcc ${Gflag} $(DFLAGS) output.c
Mtime.o:Mtime.c
	gcc ${Gflag} $(DFLAGS) Mtime.c
matchasm.o:matchasm.c
	gcc ${Gflag} -c matchasm.c
Ady.o:Ady.c
	gcc ${Gflag} -c Ady.c
acsmx.o:acsmx.c acsmx.h
	gcc ${Gflag} -c acsmx.c
snortmwm.o:snortmwm.c
	gcc ${Gflag} -c snortmwm.c
%.o:%.c
	gcc ${Gflag} -c $< 
	
clean:
	rm -f *.o
	rm -f match
	rm -f matchmul
	rm -f matcho3
	rm -f matchgene
