#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Check_setup();
void Set_Up();
void Register();
void Product_Add();
void Price_Change();
void Check_Money();
void Poweroff();
void Format();
void Print_Product();

struct data{
    char name[20];
    int price;
    int stock;
    struct data *next;
    struct data *prev;
};

struct money{
    char money_name[10];
    int money_num;
};

int main(){

    int i;

    struct data *root;
    struct data *product;
    struct money mon[8];

    root = (struct data *) malloc (sizeof (struct data));

    product = root;

    Check_setup(product, mon);

    while(1){
        printf("\nMODE SELECT\n");
        printf("1:Register, 2:Produt Add, 3:Price Change, 4:Check money, 5:poweroff, 6:Reset : ");
        scanf("%d", &i);

        switch (i){
            case 1:
                Register(product);
                break;

            case 2:
                Product_Add(root);
                break;

            case 3:
                Price_Change(product);
                break;

            case 4:
                Check_Money(mon);
                break;

            case 5:
                Poweroff(root);
                break;

            case 6:
                Format(root);
                break;

            default:
                printf("error");
                Poweroff(root);
                exit(1);
        }
    }

    return 0;
}

void Check_setup(void){

    int check;
    FILE *check_setupfile;

    check_setupfile = fopen("setup.txt", "r");
    if(check_setupfile == NULL) {
        printf("OK\n");
        check_setupfile = fopen("setup.txt", "w");
        fprintf(check_setupfile, "0\n");
        fclose(check_setupfile);
        check_setupfile = fopen("setup.txt", "r");
    }
    fscanf(check_setupfile, "%d", &check);
    fclose(check_setupfile);

    printf("%d",check);

    if(check==0){
        Set_Up();
        return;
    }else if(check==1){
        return;
    }else{
        printf("Error\n");
        exit(0);
    }
}


void Set_Up(struct data *product, struct money mon[]){

    Product_Add(product);

    FILE *fpw = fopen("struct.dat", "wb");
    fwrite(product, sizeof(product), 1, fpw);
    fclose(fpw);

    FILE *setupfile;
    setupfile = fopen("setup.txt", "w");
    if(setupfile == NULL) {
        printf("cannot open\n");
        exit(1);
    }
    fprintf(setupfile, "1\n");
    fclose(setupfile);

    strcpy(mon[0].money_name, "one");
    strcpy(mon[1].money_name, "five");
    strcpy(mon[2].money_name, "ten");
    strcpy(mon[3].money_name, "fifty");
    strcpy(mon[4].money_name, "one hundred");
    strcpy(mon[5].money_name, "five hundred");
    strcpy(mon[6].money_name, "one thousand");
    strcpy(mon[7].money_name, "five thousand");
    strcpy(mon[8].money_name, "ten thousand");

    printf("1");

    for (int i = 0; i < 8; i++){

        printf("How Many %s Yen : ", mon[i].money_name);
        scanf("%d", &mon[i].money_num);
    }

    Print_Product(product);

    return;
}

void Register(){
    return;
}

void Product_Add(struct data *product){

    int price;
    int stock;
    char name[20];
    int i;
    struct data *stor = product ;

    while (1){

        product -> next = (struct data *) malloc (sizeof (struct data));
        product -> next -> prev = product;
        product = product -> next;

        printf("Input Product Name : ");
        scanf("%s", name);
        printf("\n");

        printf("Input Product Value : ");
        scanf("%d", &price);

        printf("Input Value of Stock : ");
        scanf("%d", &stock);

        product ->  price = price;
        strcpy(product -> name, name);
        product -> stock = stock;

        printf("Continue ? 1.yes 2.no : ");
        scanf("%d", &i);
        printf("\n");

        if (i == 2) break;
    }

    product -> next = stor;
    stor -> prev = product;

    /* Print_Product(stor); */

    return;
}

void Price_Change(){
    return;
}

void Check_Money(){
    return;
}

void Poweroff(struct data *root){

    root -> prev -> next = NULL;

    for(; root != NULL; root = root -> next){
        free(root);
    }

    exit (0);
}

void Format(struct data *root){
    FILE *format_setup;

    format_setup = fopen("setup.txt", "w");
    fprintf(format_setup, "0\n");
    fclose(format_setup);

    return;
}

void Print_Product(struct data *root){


    struct data *product = root;

    for(int i = 0; product != root; product = product -> next, i++){

        printf("%d , Name %s , Price %d , Stock %d\n", i, product -> name, product -> price, product -> stock);

    }

    return;
}
