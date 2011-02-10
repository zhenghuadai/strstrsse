/**
 * =====================================================================================
 *       @file    io.h
 *
 *       @brief   '
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    02/06/2011 07:21:22 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */
#ifndef  IO_HEADER__INC
#define  IO_HEADER__INC
#include <list>
typedef enum{ NORMAL_CASE, LOWER_CASE, UPPER_CASE} CASE_TYPE;
template< CASE_TYPE t>
struct case_num{};
template<> struct case_num< NORMAL_CASE>{enum{ low_case=0, upper_case=0};};
template<> struct case_num< LOWER_CASE >{enum{ low_case=32, upper_case=0};};
template<> struct case_num< UPPER_CASE >{enum{ low_case=0, upper_case=32};};

/**
 * @brief read one fasta gene from file 
 *
 * @param pfname
 *
 * @return 
 */
template<CASE_TYPE case_type>
Pattern_fasta* loadGene_fasta(char *pfname);
#define loadGeneFastaU loadGene_fasta<UPPER_CASE>
#define loadGeneFastaL loadGene_fasta<LOWER_CASE>
#define loadGeneFasta  loadGene_fasta<NORMAL_CASE>

/**
 * @brief read all fasta genes in file 
 *
 * @param pfname
 * @param patts
 *
 * @return 
 */
template<CASE_TYPE case_type>
int loadGenePattern_Fasta(char *pfname, std::list<Pattern_fasta>* patts);
#define loadGenePatternFastaU loadGenePattern_Fasta<UPPER_CASE>
#define loadGenePatternFastaL loadGenePattern_Fasta<LOWER_CASE>
#define loadGenePatternFasta  loadGenePattern_Fasta<NORMAL_CASE>

#endif   /* ----- #ifndef IO_HEADER__INC  ----- */
