#include <stdio.h>
#include <stdlib.h>

struct regi{
	char name[20];
	int price;
	int stock;
};

int check_setup(void){
	int check;
	FILE *check_setupfile;

	check_setupfile = fopen("setup.txt", "r");
	if(check_setupfile == NULL) {
		check_setupfile = fopen("setup.txt", "w");
		fprintf(check_setupfile, "0\n");
		fclose(check_setupfile);
		check_setupfile = fopen("setup.txt", "r");
	}
	fscanf(check_setupfile, "%d", &check);
	fclose(check_setupfile);
	
	if(check==0){
		return 0;
	}else if(check==1){
		return 1;
	}else{
		printf("Error\n");
		exit(0);
	}
}

void setup(void){
	
	struct regi set[] = {
		{"おにぎり", 150, 30},
		{"緑茶", 100, 20},
		{"ガム", 50, 10},
	};

	FILE *fpw = fopen("struct.dat", "wb");
	fwrite(&set, sizeof(set), 1, fpw);
	fclose(fpw);

	FILE *setupfile;
	setupfile = fopen("setup.txt", "w");
	if(setupfile == NULL) {
		printf("cannot open\n");
		exit(1);
	}
	fprintf(setupfile, "1\n");
	fclose(setupfile);
}

void accounting(int a){
	
	if(a==1){
		printf("1!\n");
	}
}

void stock(int s){

	int i;

	struct regi stock[100];

	FILE *fpr = fopen("struct.dat", "rb");
	fread(&stock, sizeof(stock), 1, fpr);
	fclose(fpr);

	struct regi *print;
	print = stock;
	for(i=0; i<3; i++){
	printf("%s, %d, %d\n", (print+i)->name, (print+i)->price, (print+i)->stock);
	}
}

void balance(int b){

	if(b==1){
		printf("3!\n");
	}
}

void record(int r){

	if(r==1){
		printf("4!\n");
	}
}

void format(int f){
	FILE *format_setup;

	format_setup = fopen("setup.txt", "w");
	fprintf(format_setup, "0\n");
	fclose(format_setup);
}

int main(void)
{
	int mode;
	int check;
	int check_num;

	check_num=check_setup();
	if(check_num==0){
		setup();
	}

	for(check=0; check!=1; check++){
		printf("モードを選択してください\n");
		printf("1.会計, 2.在庫&値段管理, 3.レジ残高管理, 4.販売明細, 5.初期化\n");
		scanf("%d", &mode);
		switch (mode){
			case 1:
				accounting(1);
				break;
			case 2:
				stock(1);
				break;
			case 3:
				balance(1);
				break;
			case 4:
				record(1);
				break;
			case 5:
				format(1);
				break;
			default:
				printf("エラー\n");
				break;
		}
	}

	return 0;
}
