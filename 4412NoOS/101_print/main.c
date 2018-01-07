// uboot中print函数的地址
void (*printf)(char *, ...) = 0x43e11a2c;

#define 	PRO_ID 	(*(volatile unsigned int *) 0x10000000)
#define 	PACKAGE_ID 	(*(volatile unsigned int *) 0x10000004)


// 打印芯片的Chip ID
int main(void)
{
	printf("this string printf from 101_print programe\n");
	printf("101_print: [PRO_ID_Value = 0x%x]\n", PRO_ID);
	printf("101_print: [PACKAGE_ID_Value = 0x%x]\n", PACKAGE_ID);
	return 0;
}
