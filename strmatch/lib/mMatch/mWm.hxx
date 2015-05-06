
#ifndef  MWM_HEADER__INC
#define  MWM_HEADER__INC

namespace dmMatch{

#define mWm_DEFINITION_HEADER( type ) template<int WM_BLOCK_WIDTH, wmHashFunc hash, int hashCompressRatio> type mWm<WM_BLOCK_WIDTH, hash, hashCompressRatio>
mWm_DEFINITION_HEADER(void)::compile()
{
	mMinPatLen=	minPatLen();
	matchList= (list<int>**) mMalloc( SHIFT_TABLE_SIZE* sizeof(list<int>*));
	memset(matchList, 0, SHIFT_TABLE_SIZE* sizeof(list<int>*));
	
	for(int i=0;i<SHIFT_TABLE_SIZE;i++) mShift[i] = mMinPatLen-WM_BLOCK_WIDTH+1;
	int tHash;
	for(int i=0;i<mPatNum; i++){
		int j=0;
		for(char* p = mPatterns[i] + mMinPatLen; p>= mPatterns[i] + WM_BLOCK_WIDTH; p--, j++){
			tHash =(int) hash((Uchar*)p);
			if(tHash<0 || tHash >SHIFT_TABLE_SIZE) printf("err\n");
			if( mShift[tHash] > j) mShift[tHash] = j;			
		}// end for p
		{
			tHash = hash((Uchar*)mPatterns[i] + mMinPatLen);
			if(matchList[tHash] ==NULL) {
				matchList[tHash] = new  list<int>;
			}
			matchList[tHash]->push_back(i);
		}
	}//end for i
    transList(matchList, matchArray, matchArrayMem, SHIFT_TABLE_SIZE);
	//printf("build Wm complete WM_BLOCK_WIDTH:%d, SHIFT_TABLE_SIZE:%d\n", WM_BLOCK_WIDTH,SHIFT_TABLE_SIZE);
}

mWm_DEFINITION_HEADER()::~mWm()
{
    mFree(matchArrayMem);
    mFree(matchArray);

}

mWm_DEFINITION_HEADER(void)::transList(list<int>**& matchList, int**& matchArray, int*& matchArrayMem, int n)
{
    int memSize = 0;
    for(int i=0;i<n;i++)
        if( matchList[i] != NULL)
            memSize +=( matchList[i]->size() + 1) ;
    matchArrayMem = (int*) mMalloc(memSize * sizeof(int));        
    matchArray = (int**) mMalloc(n * sizeof(int*));
	ASSERT(matchArrayMem && matchArray);
    int* pstart =matchArrayMem;
    for(int i=0; i<n;i++){
        if(matchList[i] ==NULL) continue;
        int k=1;
        pstart[0] = matchList[i]->size();
        for(typename list<int>::iterator it=matchList[i]->begin(); it!= matchList[i]->end(); it++,k++){ 
            pstart[k] = *it;
        }
        //delete matchList[i];
        //matchList[i]= 0;
        matchArray[i]= pstart;
        pstart += k;
    }
    //free(matchList);
    //matchList = 0;
    freeList(matchList, n);
}

mWm_DEFINITION_HEADER(void)::freeList(list<int>**& matchList,int n){
    for(int i=0;i<n;i++){
        if(matchList[i])
            delete matchList[i];
    }
    mFree(matchList);
    matchList=0;
}

mWm_DEFINITION_HEADER(int)::search(char* txt)
{
    int n = strlen(txt);
    return    mWm::search(txt,n);

}

mWm_DEFINITION_HEADER(int)::search(char* txt, int n)
{
    unsigned char* p = (Uchar*) txt + mMinPatLen;	
    unsigned char* pEnd = (Uchar*) txt + n;	
    int tHash;
    while(p <= pEnd){
        tHash= (int)hash(p);
		if(mShift[tHash] <0) { p+= (mMinPatLen-WM_BLOCK_WIDTH +1); continue;}
        if(mShift[tHash] > 0){
            p += mShift[tHash];
		}else{
            //! compare candidate
            //reportwmList(matchList[tHash],(char*)p-txt-mMinPatLen, txt);
            reportwmList(matchArray[tHash],(char*)p-txt-mMinPatLen, txt);
            p++;
        }
    }//! end while
    return 0;
}

}
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
