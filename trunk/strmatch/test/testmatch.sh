echo "" > testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a the >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a the >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a the >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a the >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a The >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a love >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a would >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a Atlanta >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a Scarlett >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a wholeheartedness >> testmatch.res


./match -t genome/chr1.fa -a TATAA >> testmatch.res
./match -t genome/chr1.fa -a TTGACA >> testmatch.res
./match -t genome/chr1.fa -a TATAAAAG >> testmatch.res
./match -t genome/chr1.fa -a GCCACACCC >> testmatch.res
./match -t genome/chr1.fa -a TTGACATATATT >> testmatch.res
./match -t genome/chr1.fa -a AATGTGTGGAAT >> testmatch.res

./match -t genome/chr1.fa -a CCAAT >> testmatch.res



./match -t MMitchell.Gonewiththewind.txt -a "tomorrow is another day" -v 0 >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a "My dear, I don't give a damn" -v 0 >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" -v 0 >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" -v 0 >> testmatch.res
./match -t MMitchell.Gonewiththewind.txt -a "000000000000000000000000000000000" -v 0 >> testmatch.res



./match -t genome/chr1.fa -a AGGCAGTGTGGTTAGCTGGT >> testmatch.res #mir-34
./match -t genome/chr1.fa -a TGGAATGTAAAGAAGTATGTA >> testmatch.res #mir-1
./match -t genome/chr1.fa -a TCACCGGGTGTACATCAGCTAA >> testmatch.res #mir-40
./match -t genome/chr1.fa -a TGAGGTAGTAGGTTGTATAGTT >> testmatch.res #let-7
./match -t genome/chr1.fa -a TATCACAGCCAGCTTTGATGTGC >> testmatch.res #mir-2


