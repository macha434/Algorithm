#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Check_setup();
void Set_Up();
void Register();
struct data *Product_Add();
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
};

struct money{
    char money_name[10];
    int money_num;
};

int main(){

    int i;

    struct data *head;
    struct data *product;
    struct data *tail;
    struct money mon[8];

    head = (struct data *) malloc (sizeof (struct data));

    product = head;
    tail = head;

    Check_setup(product, mon);

    while(1){
        printf("\nMODE SELECT\n");
        printf("1:Register, 2:Produt Add, 3:Price Change, 4:Check money, 5:poweroff, 6:Reset : ");
        scanf("%d", &i);

        switch (i){
            case 1:
                Register(head);
                break;

            case 2:
                tail = Product_Add(tail);
                break;

            case 3:
                Price_Change(head);
                break;

            case 4:
                Check_Money(mon);
                break;

            case 5:
                Poweroff(head -> next);
                break;

            case 6:
                Format();
                Poweroff(head -> next);
                break;

            default:
                printf("error");
                Poweroff(head);
                exit(1);
        }
    }

    return 0;
}

void Check_setup(struct data *product, struct money mon[]){

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
        Set_Up(product, mon);
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

    for (int i = 0; i < 8; i++){
        mon[i].money_num = 10;
    }

    return;
}

void Register(){
    return;
}

struct data *Product_Add(struct data *product){

    int price;
    int stock;
    char name[20];
    int i;
    struct data *head = product ;
    struct data *tail;

    while (1){

        product -> next = (struct data *) malloc (sizeof (struct data));
        product = product -> next;

        printf("Input Product Name : ");
        scanf("%s", name);

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

    product -> next = NULL;

    Print_Product(head -> next);

    tail = product;

    return tail;
}

void Price_Change(){
    return;
}

void Check_Money(){
    return;
}

void Poweroff(struct data *root){

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

    for(int i = 1; root != NULL; root = root -> next, i++){

        printf("%d , Name %s , Price %d , Stock %d\n", i, root -> name, root -> price, root -> stock);

    }

    return;
}
