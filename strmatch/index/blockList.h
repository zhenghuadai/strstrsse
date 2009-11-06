/*
 * =====================================================================================
 *
 *       Filename:  blockList.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/2009 03:24:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

template<typename T, int blockSize=32>
class blockData{
	public:
		blockData* next;
		t data[blockSize];
};

template<typename T, int blockSize=32>
class blockList{
	private:
		size_t n;
		blockData* firstBlock;
		blockData* lastBlock;
	public:
		blockList(){}
	public:
		size_t size(){return n;}
		int empty(){ return n==0;}
		int full(){ return ( (firstBlock==0) || ( ( size() &(blockSize-1) ) ==0)) ;}
		void push_back(T t){}


};
