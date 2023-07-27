#include <stdio.h>
#include <string.h>

//파일의 내용을 넣는 부분
static int create_file(void)
{
	FILE *fp;

	if(!(fp = fopen("datafile", "w"))){
		printf("fopen() fail\n");
		return -1;
	}
	
	//파일 포지션을 읽어주는 api: ftell
	//반환값 :long type
	printf("after fopen(), offset = %ld\n", ftell(fp));
	
	fputs("hello world\n", fp);
	fputs("hello world!\n", fp);
	fputs("hello world!!\n", fp);
	fputs("hello world!!!\n", fp);

	printf("after fopen(), offset = %ld\n", ftell(fp));
	printf("-----------------------------------\n");
	fclose(fp);
	return 0;
}


static int read_file(void)
{
	FILE *fp;
	//fgets를 위해서 버서 생성
	char buf[1024];

	if(!(fp = fopen("datafile", "r+"))){
		printf("fopen() fail\n");
		return -1;
	}
	
	//파일 포지션을 읽어주는 api: ftell
	//반환값 :long type
	printf("after fopen(), offset = %ld\n", ftell(fp));
	
	//buffer를 0으로 초기화 
	memset(buf, 0, sizeof(buf));
	
	//한 줄 읽어오기 
	fgets(buf, sizeof(buf), fp);

	printf("after fgets(), offset = %ld\n", ftell(fp));
	
	fseek(fp, 0, SEEK_END);

	printf("after fseek(), offset = %ld\n", ftell(fp));
	fputs("final\n", fp);
	printf("before fclose(), offset = %ld\n", ftell(fp));

	printf("-----------------------------------\n");
	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{
	create_file();

	read_file();

	return 0;
}
