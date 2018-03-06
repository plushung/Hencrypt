#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int encrypt(FILE *f);
int decrypt(FILE *fd);
int encryptMenu(int func(FILE *));
int randnum();
int menu();
int cp(char *src,char *tar);
int addFunction(int func(FILE *,FILE *));
int catFunc(FILE *exeF,FILE *src);
void decor(int tar(void));
char inputfile[256];
char outfile[256]="d:\\~$.~$";
char buf[1024*1024*5];
char bufd[1024*1024*5];
long long int totalsize=0;
#define SIGN -619904620
typedef struct {
	long isEncrypted;
	char prebuf[2];
	char password[128];
}head;

int main(){
	decor(menu);
}


void decor(int tar(void)){
	int stop=0;
	while(!stop){
		stop=tar();
		getchar();
	}
	

}

int menu(){
	char n=' ';
	char stop=0;
	printf("\n================================================================================"); 
	printf("\t\t#################################################\n");
	printf("\t\t#                 selection:                    #\n");
	printf("\t\t#              [1]:encrypt                      #\n"); 
	printf("\t\t#              [2]:decrypt                      #\n"); 
	printf("\t\t#              [3]:exit                         #\n");
	printf("\t\t#################################################\n"); 
	printf("================================================================================"); 
	printf("Root:~$ ");
	scanf("%c",&n);
//	system("cls");
	switch(n){
		case '1':{
			encryptMenu(encrypt);
			break;
		}
		case '2':{
			encryptMenu(decrypt);
			break;
		}
		case 'q':
		case '3':{
			stop=1;
			break;
		}
		case 't':{
			char j[128];
			scanf("%s",j);
			FILE *ff=fopen(j,"rb");
			if(!feof(ff)){
				printf("rrrr");
			}
			fseek(ff,0,SEEK_END);
				printf("tel%d",ftell(ff));
				
			break;
		}
		case 'a':{
			addFunction(catFunc);
			break;
		}
		case 'r':{
			FILE *d=fopen("kokok.txt","rb+");
			int po=ftell(d);
			fclose(d);
			printf("%drand number:%d\n",po,randnum());
			break;
		}
		case 'c':{
			system("cls");
			break;
		}
		default :break;
	}
	return stop;
}

int addFunction(int func(FILE *,FILE *)){
	char fn[128];
	char fsrc[128];
	printf("input .exe filename:");
	scanf("%s",fn);
	printf("input source filename:");
	scanf("%s",fsrc);
	getchar();
	FILE *exef=fopen(fn,"rb");
	FILE *src=fopen(fsrc,"rb");
	if(ftell(exef)==-1&&ftell(src)==-1){
		printf("filename:%s and %s not exist",fn,fsrc);
	}else if(ftell(src)==-1){
		printf("filename:%s not exist",fsrc);
		fclose(exef);
	}else if(ftell(exef)==-1){
		printf("filename:%s not exist",fn);
		fclose(src);
	}else{
		printf("adding function....\n");
		func(exef,src);
		fclose(exef);
		fclose(src);
	}
}

int catFunc(FILE *exeF,FILE *src){
	char tempBuf[1024*1024];
	int readsize=-1;
	char fn[128]={'\0'};
	char tar='p';
	int c=0;
	printf("save as file:");
	scanf("%s",fn);
	FILE *tempFile=fopen(fn,"wb+");
	while(!feof(exeF)){
		printf("file 1 ...\n");
		readsize=fread(tempBuf,sizeof(char),sizeof(tempBuf)/sizeof(char),exeF);
		for(int i=0;i<strlen(tempBuf);i++){
			if(tempBuf[i]==tar)
				c++;
		}
		fwrite(tempBuf,sizeof(char),readsize,tempFile);
		readsize=-1;
	}
	printf("PPP : %d",c);
	while(!feof(src)){
		printf("file 2 ...\n");
		readsize=fread(tempBuf,sizeof(char),sizeof(tempBuf)/sizeof(char),src);
		fwrite(tempBuf,sizeof(char),readsize,tempFile);
		readsize=-1;
	}
	fclose(tempFile);
}



int mixFunc(FILE *exeF,FILE *src){
	char tempBuf[2][1024*1024];
	int readsize=-1;
	char fn[128]={'\0'};
	int offset=0;
	printf("save as file:");
	scanf("%s",fn);
	FILE *tempFile=fopen(fn,"wb+");
	while(!feof(exeF)&&!feof(src)){
		printf("file 1 ...\n");
		readsize=fread(tempBuf[0],sizeof(char),sizeof(tempBuf)/sizeof(char),exeF);
		readsize=fread(tempBuf,sizeof(char),sizeof(tempBuf)/sizeof(char),src);
		fwrite(tempBuf,sizeof(char),readsize,tempFile);
		readsize=-1;
	}
//	while(){
//		printf("file 2 ...\n");
//		readsize=fread(tempBuf,sizeof(char),sizeof(tempBuf)/sizeof(char),src);
//		fwrite(tempBuf,sizeof(char),readsize,tempFile);
//		readsize=-1;
//	}
	fclose(tempFile);
}


int randnum(){
	static int ss=rand();
	time_t tt;
	srand((unsigned) time(NULL));
	ss=rand()%100+ss%100;
	srand((unsigned) time(&tt)+(unsigned)rand()+ss);
	return ((rand()%10+1)+rand())%256;
}

int encryptMenu(int func(FILE *)){
	printf("源文件名:\n"); 
	printf("Root:~$ ");
	scanf("%s",inputfile);
	FILE *f=fopen(inputfile,"rb+");
	int type=0;
	if(ftell(f)!=-1){
		fseek(f,0,SEEK_END);
		totalsize=ftell(f);
		fseek(f,0,SEEK_SET);
		type=func(f);
		fclose(f);
		if(!type){
		printf("\nreplacing source file..... .Don\'t close window!");
		cp(outfile,inputfile);	
		}
		printf("\ndone!!!");
	}else{
		printf("file not exist!!!!\n");
		fclose(f);
	}
	return 0;
}

int cp(char *src,char *tar){
	char bufff[1024*1024];
	int ch=0;
	FILE *s=fopen(src,"rb");
	long long pos=ftell(s);
	if(pos!=-1){
		fseek(s,0,SEEK_END);
		totalsize=ftell(s);
		fseek(s,0,SEEK_SET);
		FILE *t=fopen(tar,"wb");
		printf("\n");
		while(!feof(s)&&(pos!=-1)){
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			ch=fread(bufff,sizeof(char),sizeof(bufff)/sizeof(char),s);
			fwrite(bufff,sizeof(char),ch,t);
			pos=ftell(s);
			printf("%.2f %%",(pos+0.0)/totalsize*100);
		}
		fclose(t);	
	}else{
		printf("no file!");
	}
	fclose(s);
	return 0;
}

void encryptStr(char *strbuf,int ch,char pre[2]){
	for(int i=0;i<ch;i++){
		strbuf[i]+=pre[0];
		strbuf[i]%=256;
		strbuf[i]^=pre[1];
	}
}
void decryptStr(char *strbuf,int ch,char pre[2]){
	for(int i=0;i<ch;i++){
		strbuf[i]^=pre[1];
		strbuf[i]+=256-pre[0];
		strbuf[i]%=256;
	}
}

int encrypt(FILE *f){
	int ch=0;
	long long pos=0;
	char pass[128];
	head *he=(head *)malloc(sizeof(head));
//	pos=ftell(f);
//	if(pos!=-1){
		printf("please input password:");
		scanf("%s",pass);
		FILE *fc=fopen(outfile,"wb+");
		int size=sizeof(char);
		int numb=sizeof(buf)/sizeof(char);
		he->prebuf[0]=randnum();
		he->prebuf[1]=randnum();
		he->isEncrypted=SIGN;
		encryptStr(pass,strlen(pass),he->prebuf);
		strcpy(he->password,pass);
		if(!feof(f)){
			fwrite(he,sizeof(head),1,fc);
			printf("encrypting.......!");
			printf("\n%.2f",(pos+0.0)/totalsize*100);
			while(!feof(f)&&(pos!=-1)){
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				ch=fread(buf,size,numb,f);
				encryptStr(buf,ch,he->prebuf);
				fwrite(buf,size,ch,fc);
				pos=ftell(f);
				printf("%.2f %%",(pos+0.0)/totalsize*100);
			}
		}
		fclose(fc);
		printf("\nencrypt sucessfully!");
//	}
	free(he);
	return 0;
}

int decrypt(FILE *fd){
	char pass[128];
	int size=sizeof(char);
	int numb=sizeof(bufd)/sizeof(char);
	int ch=0;
	int ret=0;
	int correct=-1;
	head *he=(head *)malloc(sizeof(head));
	long long pos=ftell(fd);
	fread(he,sizeof(head),1,fd);
	printf("please input password:");
	scanf("%s",pass);
	encryptStr(pass,strlen(pass),he->prebuf);
	correct=strcmp(he->password,pass);
	if((he->isEncrypted==SIGN)&&(correct==0)){
		FILE *fc1=fopen(outfile,"wb+");
		if(!feof(fd)){
			printf("decrypting.......!");
			printf("\n%.2f",(pos+0.0)/totalsize*100);
			while(!feof(fd)){
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				ch=fread(bufd,size,numb,fd);
				decryptStr(bufd,ch,he->prebuf);
				fwrite(bufd,size,ch,fc1);
				pos=ftell(fd);
				printf("%.2f %%",(pos+0.0)/totalsize*100);
			}
		}
		fclose(fc1);
		printf("\ndecrypt sucessfully!");	
	}else if(he->isEncrypted!=SIGN){
		ret=1;
		printf("文件未经加密") ;
	}else if(correct!=0){
		ret=1;
		printf("password error!!") ;
	}
	free(he);
	return ret;
}
