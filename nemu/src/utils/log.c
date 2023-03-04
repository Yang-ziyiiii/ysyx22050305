/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>
#include <elf.h>


extern uint64_t g_nr_guest_inst;
FILE *log_fp = NULL;
FILE *elf_fp = NULL;
//SYBTAB mysym;

void init_log(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}

bool log_enable() {
  return MUXDEF(CONFIG_TRACE, (g_nr_guest_inst >= CONFIG_TRACE_START) &&
         (g_nr_guest_inst <= CONFIG_TRACE_END), false);
}

// void init_elf(const char *elf_file) {
//   void tableheader(FILE  *pbuff);
//   callnum = 0;
//   elf_fp = stdout;
//   if (elf_file != NULL) {
//     FILE *fp = fopen(elf_file, "rb");
//     elf_fp = fp;
//   }
//     Log("Elf is open  %s", elf_file ? elf_file : "stdout");
//     tableheader(elf_fp);
// }

// void tableheader(FILE *elf_fp)
// {

// 	int len;
// 	char *pbuff;
// 	fseek(elf_fp,0,SEEK_END);
// 	len = ftell(elf_fp);
// 	pbuff=(char *)malloc(len*sizeof(char));
// 	memset(pbuff,'\0',len*sizeof(char));
// 	fseek(elf_fp,0,SEEK_SET);
// 	if(fread(pbuff,sizeof(char),len,elf_fp)!=0)printf("success!\n");
// 	//从节区里面定位到偏移
// 	Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;

// 	for(int i = 0;i<EI_NIDENT;++i) //e_ident[EI_NIDENT]
// 	{
// 		printf("%02X", pbuff[i]);
// 		putchar(' ');
// 		if((i+1)%16 == 0)printf("\n");
// 	}
// 	printf("\r\n");
// 	Elf64_Half eshstrndx = pfilehead->e_shstrndx;	
//       	printf("e_shstrndx:%d,eshnum:%d\n", pfilehead->e_shstrndx,pfilehead->e_shnum);
// 	Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
// //  	printf("pbuff location%ld\n",(long) pbuff);
// 	printf("e_shoff:%ld\n", pfilehead->e_shoff);
//        	Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + eshstrndx);
// //	printf("psecheader location%ld\n",(long) psecheader);
// //	printf("pshstr location%ld\n",(long) pshstr);
// 	printf("pshstr->shoffset:%ld\n", pshstr->sh_offset);

// 	char* pshstrbuff = (char *)(pbuff + pshstr->sh_offset);
// 	printf("%s\n",pshstrbuff);
// 	int m = 0;
// 	for(int i = 0;i<pfilehead->e_shnum;++i)
// 	{ 
// 		printf("psecheader[i].sh_name + pshstrbuff:%s\n",psecheader[i].sh_name + pshstrbuff);
// 		if(!strcmp(psecheader[i].sh_name + pshstrbuff, ".dynsym") || !strcmp(psecheader[i].sh_name + pshstrbuff, ".symtab"))
// 		{
// 			Elf64_Sym* psym = (Elf64_Sym*)(pbuff + psecheader[i].sh_offset);
// 			int ncount = psecheader[i].sh_size / psecheader[i].sh_entsize;
// 			char* pbuffstr = (char*)((psecheader + psecheader[i].sh_link)->sh_offset + pbuff);
// 			printf("Symbol table '%s' contains %d entries:\r\n", psecheader[i].sh_name + pshstrbuff, ncount);
//  			for(int p=0;p<ncount;p++) {
		
// 			//	printf("num:%d,value:%016lx,size:%ld,type:%d,name:%s\n",p,psym->st_value,psym->st_size,psym->st_info,pbuffstr+psym->st_name);
// 			        if(psym->st_info == 18){
// 					printf("save %s\n",pbuffstr+psym->st_name);
// 					mysym.value[m] = psym->st_value;
// 					mysym.size[m]  = psym->st_size;
// 					char *namebuff = (char *)pbuffstr+psym->st_name;
// 					mysym.name[m]  = namebuff;
// 					m++;
// 				}
// 				psym ++;
// 			mysym.ncount=m;		
// 			}
// 			//outputsyminfo(psym, pbuffstr, ncount);
//        			 //continue;
// 		}
// 	}

// }
