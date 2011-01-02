#pragma warning(disable : 4035) 
//reference : 基于 MMX的高效字符串搜索
//谭章熹 (xtan@263.net) 
static __int64 mask=0x07; 
char *strstrmmx(const char *TxtBuff, const char *SearchStr) 
{ 
    //Txtbuff为缓冲区,SearchStr为待查串 
    if (SearchStr[1] == 0) 
        return strstr(TxtBuff, SearchStr); 
    else 
    { 
        __asm 
        { 
            //初始化 
            mov edi,SearchStr //保存SearchStr地址 
                mov esi,TxtBuff //保存TxtBuff地址 
                xor ecx,ecx //将ecx清零代表继续查找 
                movq mm0,dword ptr[edi] //从SearchStr中读入前8个字符 
                movd mm7,esi //为对齐TxtBuff做准备 
                punpcklbw mm0,mm0 
                punpcklwd mm0,mm0 //为SearchStr[0]、SearchStr[1]存入mmx寄存器做准备 
                pand mm7,mask //mm7为TxtBuff起始地址模8的值 
                lea edx,[edi+2] //保留SearchStr[2]的地址 
                movq mm1, mm0 //复制SearchStr 
                movq mm4,dword ptr[edi] //从SearchStr中继续读入8个字符到mm4 
                punpckldq mm0,mm0 //将SearchStr[0]存入mmx寄存器 
                punpckhdq mm1,mm1 //将SearchStr[1]存入mmx寄存器 
                movq mm2,mm0 //备份searchstr[0]到mm2 
                psllq mm7,3 
                pxor mm5,mm5 
                movq mm3,mm1 //备份searchstr[1]到mm3 
                psllq mm4,mm7 //左移前8字节，mm4为对齐后的数据 
                and esi,0FFFFFFF8h //对齐TxtBuff指针 
                //查找前两个字符 
                MATCH_2_CHARS: 
                pcmpeqb mm0,mm4 //将TxtBuff中的8个字符与SearchStr[0]比较 
                pcmpeqb mm1,mm4 //将TxtBuff中的8个字符与SearchStr[1]比较 
                movq mm6,mm0 //SearchStr[0]的比较结果复制到mm6 
                psllq mm0,8 //将本次SearchStr[0]的比较结果左移1字节 
                por mm0,mm5//将本次SearchStr[0]的比较结果和上次SearchStr[0]的比较结果的最后一位组合 
                psrlq mm6,56 //取上次循环保留的SearchStr[0]的比较结果的最低位 
                pand mm0,mm1 //比较组合过SearchStr[0]的比较结果和SearchStr[1]的比较结果 
                lea edi,[edi+1] //保存TxtBuff的指针用于接下来的逐字符比较 
                packsswb mm0,mm0 //将结果压缩到32bits 
                push ecx //ecx = 1代表停止查找 ecx = 0代表继续 
                movd eax,mm0 //将mm0的低32位复制到eax 
                movq mm5,mm6 //保留本次SearchStr[0]比较结果的最后一位,用于下次循环 
                test eax,eax 
                jz NO_MATCH_FOUND //没有匹配 
                FIND_MATCHES: 
                test al,1000b //判断当前四位中是否有匹配 
                jz NEXT_BYTE //没有匹配 
                mov ecx,edi //将TxtBuff的地址复制到ecx 
                push edx //保留SearchStr[2]的地址 
                mainlupe: 
                mov bl,[edx] //将SearchStr[i]存入bl 
                inc edx 
                or bl,bl //如果到达待配串的末尾，则成功找到子串 
                jz short success 
                mov bh,[ecx] //将TxtBuff[i]存入blbh 
                inc ecx 
                cmp bl,bh //两个字符是否匹配 
                je short mainlupe //不匹配则恢复指针到SearchStr＋1,继续进行 
                pop edx 
                jmp NEXT_BYTE 
                success: 
                lea eax,[edi-2] //edi中存放的是除去前两个字符后的匹配结果,因此[edi－2]为最终匹配结果 
                pop edx 
                pop ecx 
                jmp DONE 
                NEXT_BYTE: 
                shr eax,4 //右移4 bits 
                inc edi //TxtBuff指针加1 
                cmp eax, 08h //是否还需要继续处理? 
                jae FIND_MATCHES 
                NO_MATCH_FOUND: 
                add esi,8 //TxtBuff指针加8 
                pop ecx //还原TxtBuff剩余字节数 
                test ecx,ecx //是否到了TxtBuff结尾 
                jnz DONE_NOT_FOUND//如果ecx不是零则推出 
                movq mm4,dword ptr[esi] //从TxtBuff中继续读8字节到mm4 
                psubb mm0,mm0 //将mm0至零 
                movq mm1,mm4 //复制mm4到mm1 
                pcmpeqb mm1,mm0 //将mm1和零比较判断是否到达了结尾的空字符 
                packsswb mm1,mm1 //将比较结果压缩到32bits 
                movq mm0,mm2 //还原SearchStr[0]到mm0 
                movd ecx,mm1 //将判断结尾的比较结果存到ecx 
                movq mm1,mm3 //还原SearchStr[1]到mm1 
                jmp MATCH_2_CHARS //继续循环 
                DONE_NOT_FOUND: 
                xor eax,eax //没有匹配串则返回零 
                DONE: 
                emms 
        } 
    }//返回eax 
} 
