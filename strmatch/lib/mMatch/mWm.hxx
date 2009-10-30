
#ifndef  MWM_HEADER__INC
#define  MWM_HEADER__INC

namespace dmMatch{

void mWm::compile()
{
	mMinPatLen=	minPatLen();
	for(int i=0;i<mPatNum; i++){
		int j=0;
		for(char* p = mPatterns[i] + mMinPatLen; p>= mPatterns[i] + WM_BLOCK_WIDTH; p--, j++){
			tHash = hash(p);
			if( mShift[tHash] > j) mShift[tHash] = j;			
		}// end for p
		if(j ==0){
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


			p++;
		}
	}//! end while
}

}
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
