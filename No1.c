#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Set_Up();
void Register();
void Product_Add();
void Price_Change();
void Check_Money();
void Poweroff();

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

    Set_Up(product, mon);

    while(1){
        printf("\n\nMODE SELECT\n");
        printf("1:Register, 2:Produt Add, 3:Price Change, 4:Check money, 5:poweroff : ");
        scanf("%d", &i);

        switch (i){
            case 1:
                Register(product);
                break;

            case 2:
                Product_Add(root, product);
                break;

            case 3:
                Price_Change(product);
                break;

            case 4:
                Check_Money(mon);
                break;

            case 5:
                Poweroff(product, mon);
                break;

            default:
                printf("error");
                Poweroff(product, mon);
                exit(1);
        }
    }

    return 0;
}

void Set_Up(struct data *product, struct money mon[]){

    Product_Add(product);

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

        printf("How Many %s Yen : ", mon[i].money_name);
        scanf("%d", &mon[i].money_num);
    }

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

    return;
}

void Price_Change(){
    return;
}

void Check_Money(){
    return;
}

void Poweroff(struct data *root, struct data *product){

    root -> prev -> next = NULL;

    for(product = root; product != NULL; product = product -> next){
        free(product);
    }

    exit (0);
}
