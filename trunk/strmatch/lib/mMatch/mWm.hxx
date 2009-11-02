
#ifndef  MWM_HEADER__INC
#define  MWM_HEADER__INC

namespace dmMatch{

void mWm::compile()
{
	mMinPatLen=	minPatLen();
	matchList= (list<int>**) malloc( mPatNum * sizeof(list<int>*));
	memset(matchList, 0, mPatNum * sizeof(list<int>*));
	
	for(int i=0;i<SHIFT_TABLE_SIZE;i++) mShift[i] = mMinPatLen-WM_BLOCK_WIDTH+1;
	Uint tHash;
	for(int i=0;i<mPatNum; i++){
		int j=0;
		for(char* p = mPatterns[i] + mMinPatLen; p>= mPatterns[i] + WM_BLOCK_WIDTH; p--, j++){
			tHash = hash((Uchar*)p);
			if( mShift[tHash] > j) mShift[tHash] = j;			
		}// end for p
		{
			tHash = hash((Uchar*)mPatterns[i] + mMinPatLen);
			if(matchList[tHash] ==NULL) {
				matchList[tHash] = new list<int>;
			}
			matchList[tHash]->push_back(i);
		}
	}//end for i
}

int mWm::search(char* txt)
{
	int n = strlen(txt);
	mWm::search(txt,n);
}

int mWm::search(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt + mMinPatLen;	
	unsigned char* pEnd = (Uchar*) txt + n;	
	Uint tHash;
	while(p < pEnd){
		tHash= hash(p);
		if(mShift[tHash] > 0){
			p += mShift[tHash];
		}else{
			//! compare candidate
			reportwmList(matchList[tHash],(char*)p-txt-mMinPatLen, txt);
			p++;
		}
	}//! end while
}

}
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
