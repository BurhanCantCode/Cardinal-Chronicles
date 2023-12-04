#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct cards
{
    char element[10];
    int damage;
    int manacost;
};
struct player_cards
{
    char element[10];
    int damage;
    int manacost;
};
struct bot_cards
{
    char element[10];
    int damage;
    int manacost;
};
struct player
{
    int mana;
    int health;
};
struct bot
{
    int mana;
    int health;
};

int player_turn(struct player* ptr_to_player , struct bot* ptr_to_bot , struct player_cards* ptr_to_player_cards , struct bot_cards* ptr_to_bot_cards , int player_element )
{
    int i;
    if (ptr_to_player->mana < 10)
    {
        printf("bot won the match");
        return 1;
    }
    do{
    printf("%d , %d \n" , ptr_to_bot->health , ptr_to_player ->mana);
    printf("select the card u want to choose");
    scanf("%d" , &i);
    
    if(ptr_to_player->mana < (ptr_to_player_cards + i)->manacost)
    {
        printf("your mana is not enough choose another card");
        continue;
        // return player_turn(ptr_to_player , ptr_to_bot , ptr_to_player_cards , ptr_to_bot_cards , player_element);
    }
    else{
        break;
    }
    }while(i<5);
    
    if(i == player_element)
    {
        (ptr_to_player_cards + i)->damage += (0.1 * (ptr_to_player_cards + i)->damage);
    }
    ptr_to_bot->health = ptr_to_bot->health - (ptr_to_player_cards + i)->damage;
    ptr_to_player->mana = ptr_to_player->mana - (ptr_to_player_cards + i)->manacost;
    printf("remaining  pbot health : %d\n"  , ptr_to_bot->health);
    printf("how much mana is left for the  : %d\n" , ptr_to_player->mana);

    if (ptr_to_bot->health < 1)
    {
        printf("congrats u have won the match");
        return 1;
    }
    else{
        return 0;
    }
    
}
int bot_turn(struct player* ptr_to_player , struct bot* ptr_to_bot , struct player_cards* ptr_to_player_cards , struct bot_cards* ptr_to_bot_cards , int bot_element )
{
    printf("%d , %d \n" , ptr_to_player->health , ptr_to_bot ->mana);
    int i;
    if (ptr_to_bot->mana < 10)
    {
        printf("player won the match");
        return 1;
    }
    do{
    printf("select the card bot want to choose");
    scanf("%d" , &i);
    if (ptr_to_bot->mana < 10)
    {
        printf("player won the match");
        return 1;
    }

    if(ptr_to_bot->mana < (ptr_to_bot_cards + i)->manacost)
    {
        printf("your mana is not enough choose another card");
        continue;
        // return bot_turn(ptr_to_player , ptr_to_bot , ptr_to_player_cards , ptr_to_bot_cards , bot_element);
    }
    else{
        break;
    }
    }while(i<5);
    if(i == bot_element)
    {
        (ptr_to_bot_cards + i)->damage += (0.1 * (ptr_to_bot_cards + i)->damage);
    }
    ptr_to_player->health = ptr_to_player->health - (ptr_to_bot_cards + i)->damage;
    ptr_to_bot->mana = ptr_to_bot->mana - (ptr_to_bot_cards + i)->manacost;
    printf("remaining  player health : %d\n"  , ptr_to_player->health);
    printf("how much mana is left for the bot : %d\n" , ptr_to_bot->mana);
    if (ptr_to_player->health < 1)
    {
        printf("congrats bot have won the match");
        return 1;
    }
    else{
        return 0;
    }
}
void player_cards_assigning(struct cards *ptr_to_all_cards , struct player_cards *ptr_to_player_cards , char elements[4][10], int player_element)
{
    int i , k;
    k= 0;
    i = player_element;
    strcpy((ptr_to_player_cards + k)->element, elements[i]);
    (ptr_to_player_cards + k)->damage = (rand() % 60) + 40;
    (ptr_to_player_cards + k)->manacost = 65;
    for ( k = 1; k < 4; k++)
    {
        i = rand() % 12;
        strcpy((ptr_to_player_cards + k)->element, (ptr_to_all_cards + i)->element);
        (ptr_to_player_cards + k)->damage = (ptr_to_all_cards + i)->damage;
        (ptr_to_player_cards + k)->manacost = (ptr_to_all_cards + i)->manacost;
    }
}
void bot_cards_assigning(struct cards *ptr_to_all_cards , struct bot_cards *ptr_to_bot_cards , char elements[4][10], int bot_element)
{
    int i , k;
    k= 0;
    i = bot_element;
    strcpy((ptr_to_bot_cards + k)->element, elements[i]);
    (ptr_to_bot_cards + k)->damage = rand() % 60;
    (ptr_to_bot_cards + k)->manacost = 65;
    for ( k = 1; k < 4; k++)
    {
        i = rand() % 12;
        strcpy((ptr_to_bot_cards + k)->element, (ptr_to_all_cards + i)->element);
        (ptr_to_bot_cards + k)->damage = (ptr_to_all_cards + i)->damage;
        (ptr_to_bot_cards + k)->manacost = (ptr_to_all_cards + i)->manacost;
    }
}
void card_making(struct cards *ptr_to_all_cards)
{
    int i, j, k = 0;
    char elements[4][10] = {"Earth", "Water", "Fire", "Air"};
    int damage[3] = {(rand() % 10) , (rand() % 20) + 20,( rand() % 30) + 30};
    int mana[3] = {10, 20, 30};
    // -> sign just mean that *(ptr).damage ok

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            strcpy((ptr_to_all_cards + k)->element, elements[i]);
            (ptr_to_all_cards + k)->damage = damage[j];
            (ptr_to_all_cards + k)->manacost = mana[j];

            k++;
        }
    }
}

int main()
{
    int i = 0; //this is not part of the code will be removed
    srand(time(NULL));
    struct cards card_s[12];
    //yahaan pointer to structre array ko initialize kara hai
    struct cards* ptr_to_all_cards = (struct cards*)calloc(12,sizeof(struct cards));
    card_making(ptr_to_all_cards);
    
    //this block is like the element deciding block
    char elements[4][10] = {"earth" , "water" , "fire" , "air"};
    int player_element , bot_element;
    printf("choose your main element\n1-Earth\n2-water\n3-Fire\n4-air ");
    scanf("%d" , &player_element);
    player_element -= 1;
    bot_element = rand() % 4;

    //give the player its cards
    struct player_cards player_card_s[4];
    struct player_cards* ptr_to_player_cards = (struct player_cards*)calloc(4,sizeof(struct player_cards));
    player_cards_assigning(ptr_to_all_cards , ptr_to_player_cards , elements , player_element);

    //give the bot its card
    struct bot_cards bot_card_s[4];
    struct bot_cards* ptr_to_bot_cards = (struct bot_cards*)calloc(4,sizeof(struct bot_cards));
    bot_cards_assigning(ptr_to_all_cards , ptr_to_bot_cards , elements , bot_element);

    //initialize the structs for player and the bot
    struct player p1;
    struct player* ptr_to_player = &p1;
    p1.mana = 100;
    p1.health = 100;
    struct bot b1;
    struct bot* ptr_to_bot = &b1;
    b1.mana=100;
    b1.health = 100;
    i = 0;


    while (i == 0)//set the winning conditions here
    {
        i =player_turn(ptr_to_player , ptr_to_bot , ptr_to_player_cards , ptr_to_bot_cards , player_element);
        if (i == 1)
        {
            break;
        }
        i = bot_turn(ptr_to_player , ptr_to_bot , ptr_to_player_cards , ptr_to_bot_cards , bot_element);
        if (i == 1)
        {
            break;
        }
        
    }
    free(ptr_to_all_cards);
    free(ptr_to_player_cards);
    free(ptr_to_bot_cards);

    

}
