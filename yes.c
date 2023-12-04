#include <stdio.h>//burhan ke ppas nhi hai
#include <stdlib.h>//hola soy dora
#include <string.h>
#include <time.h>

struct cards
{
    char element[10];
    int damage;
    int manacost;
    int isblocked;
    char name[30];
};
struct player_cards
{
    char element[10];
    int damage;
    int manacost;
    int isblocked;
    char name[30];
};
struct bot_cards
{
    char element[10];
    int damage;
    int manacost;
    int isblocked;
    char name[30];
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

typedef void (*ptr_to_spells)(struct player_cards *, struct bot_cards *, struct bot *, struct player *, int);

void health_steal(struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, struct bot *ptr_to_bot, struct player *ptr_to_player, int who)
{
    if (who == 1)
    {
        ptr_to_player->health += 15;
        ptr_to_bot->health -= 15;
    }
    if (who == 2)
    {
        ptr_to_player->health -= 15;
        ptr_to_bot->health += 15;
    }
}
void mana_steal(struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, struct bot *ptr_to_bot, struct player *ptr_to_player, int who)
{
    if (who == 1)
    {
        ptr_to_player->mana += 15;
        ptr_to_bot->mana -= 15;
    }
    if (who == 2)
    {
        ptr_to_player->mana -= 15;
        ptr_to_bot->mana += 15;
    }
}
void heal(struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, struct bot *ptr_to_bot, struct player *ptr_to_player, int who)
{
    if (who == 1)
    {
        ptr_to_player->health += 20;
    }
    if (who == 2)
    {
        ptr_to_bot->health += 20;
    }
}
void block_card(struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, struct bot *ptr_to_bot, struct player *ptr_to_player, int who)
{
    int i;
    printf("select the card you want to block");
    scanf("%d", &i);
    i--;
    if (who == 1)
    {
        (ptr_to_bot_cards + i)->isblocked = 1;
    }
    if (who == 2)
    {
        (ptr_to_player_cards + i)->isblocked = 1;
    }
}
int player_turn(struct player *ptr_to_player, struct bot *ptr_to_bot, struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, int player_element, ptr_to_spells *player_spells)
{
    int i, type;
    int who = 1;
    if (ptr_to_player->mana < 10)
    {
        printf("bot won the match");
        return 1;
    }
    printf("which type of card do u want to choose\n1-Attack Card \n2-SpellCard");
    scanf("%d", &type);
    if (type == 2)
    {
        printf("choose the spell card u want to use");
        scanf("%d", &i);
        i--;
        player_spells[i](ptr_to_player_cards, ptr_to_bot_cards, ptr_to_bot, ptr_to_player, who);
    }
    if (type == 1)
    {
        do
        {
            // Add the printf statements to show cards
            //  printf("%d , %d \n" , ptr_to_bot->health , ptr_to_player ->mana);
            printf("select the attack card u want to choose\n1.%s\n2.%s\n3.%s\n4.%s\n",ptr_to_player_cards->name,(ptr_to_player_cards+1)->name,(ptr_to_player_cards+2)->name,(ptr_to_player_cards+3)->name);
            scanf("%d", &i);
            i--;
            if (i < 0 && i > 3)
            {
                printf("invalid move , try again");
                continue;
            }
            if ((ptr_to_player_cards + i)->isblocked == 1)
            {
                printf("this card is blocked for this turn");
                continue;
            }

            if (ptr_to_player->mana < (ptr_to_player_cards + i)->manacost)
            {
                printf("your mana is not enough choose another card");
                continue;
            }
            else
            {
                break;
            }
        } while (i < 5);

        if (i == player_element) // fix this code
        {
            (ptr_to_player_cards + i)->damage += (0.1 * (ptr_to_player_cards + i)->damage);
        }
        ptr_to_bot->health = ptr_to_bot->health - (ptr_to_player_cards + i)->damage;
        ptr_to_player->mana = ptr_to_player->mana - (ptr_to_player_cards + i)->manacost;
    }
    printf("remaining  bot health : %d\n", ptr_to_bot->health);
    printf("how much mana is left for the  : %d\n", ptr_to_player->mana);

    if (ptr_to_bot->health < 1)
    {
        printf("congrats u have won the match");
        return 1;
    }
    else
    {
        return 0;
    }
    for (i = 0; i < 4; i++)
    {
        (ptr_to_player_cards + i)->isblocked = 0;
    }
}
int bot_turn(struct player *ptr_to_player, struct bot *ptr_to_bot, struct player_cards *ptr_to_player_cards, struct bot_cards *ptr_to_bot_cards, int bot_element, ptr_to_spells *bot_spells)
{
    int i, type;
    int who = 2;
    if (ptr_to_bot->mana < 10)
    {
        printf("player won the match");
        return 1;
    }
    printf("which type of card do u want to choose\n1-Attack Card \n2-SpellCard\n");
    scanf("%d", &type);
    if (type == 2)
    {
        printf("choose the spell card u want to use");
        scanf("%d", &i);
        i--;
        bot_spells[i](ptr_to_player_cards, ptr_to_bot_cards, ptr_to_bot, ptr_to_player, who);
    }
    if (type == 1)
    {
        do
        {
            // Add the printf statements to show cards
            //  printf("%d , %d \n" , ptr_to_bot->health , ptr_to_player ->mana);
            printf("select the attack card u want to choose\n1.%s\n2.%s\n3.%s\n4.%s\n",ptr_to_bot_cards->name,(ptr_to_bot_cards+1)->name,(ptr_to_bot_cards+2)->name,(ptr_to_bot_cards+3)->name);
            scanf("%d", &i);
            i--;
            if (i < 0 && i > 3)
            {
                printf("invalid move , try again");
                continue;
            }
            if ((ptr_to_bot_cards + i)->isblocked == 1)
            {
                printf("this card is blocked for this turn");
                continue;
            }

            if (ptr_to_bot->mana < (ptr_to_bot_cards + i)->manacost)
            {
                printf("your mana is not enough choose another card");
                continue;
                // return player_turn(ptr_to_player , ptr_to_bot , ptr_to_player_cards , ptr_to_bot_cards , player_element);
            }
            else
            {
                break;
            }
        } while (i < 5);

        if (i == bot_element) // fix this code
        {
            (ptr_to_bot_cards + i)->damage += (0.1 * (ptr_to_bot_cards + i)->damage);
        }
        ptr_to_player->health = ptr_to_player->health - (ptr_to_bot_cards + i)->damage;
        ptr_to_bot->mana = ptr_to_bot->mana - (ptr_to_bot_cards + i)->manacost;
    }
    printf("remaining  player health : %d\n", ptr_to_player->health);
    printf("how much mana is left for the bot  : %d\n", ptr_to_bot->mana);

    if (ptr_to_player->health < 1)
    {
        printf("congrats bot have won the match");
        return 1;
    }
    else
    {
        return 0;
    }
    for (i = 0; i < 4; i++)
    {
        (ptr_to_bot_cards + i)->isblocked = 0;
    }
}
void player_cards_assigning(struct cards *ptr_to_all_cards, struct player_cards *ptr_to_player_cards, char elements[4][10], int player_element, ptr_to_spells *player_spell, ptr_to_spells spell_cards[4])
{
    int i, k;
    k = 0;
    i = player_element;
    strcpy((ptr_to_player_cards + k)->element, elements[i]);
    (ptr_to_player_cards + k)->damage = (rand() % 60) + 40;
    (ptr_to_player_cards + k)->manacost = 65;
    strcpy((ptr_to_player_cards + k)->name, (ptr_to_all_cards + i)->name);

    for (k = 1; k < 4; k++)
    {
        i = rand() % 12;
        strcpy((ptr_to_player_cards + k)->element, (ptr_to_all_cards + i)->element);
        (ptr_to_player_cards + k)->damage = (ptr_to_all_cards + i)->damage;
        (ptr_to_player_cards + k)->manacost = (ptr_to_all_cards + i)->manacost;
        strcpy((ptr_to_player_cards + k)->name, (ptr_to_all_cards + i)->name);
    }
    player_spell[0] = spell_cards[rand() % 4];
}
void bot_cards_assigning(struct cards *ptr_to_all_cards, struct bot_cards *ptr_to_bot_cards, char elements[4][10], int bot_element, ptr_to_spells *bot_spells, ptr_to_spells spell_cards[4])
{
    int i, k;
    k = 0;
    i = bot_element;
    strcpy((ptr_to_bot_cards + k)->element, elements[i]);
    (ptr_to_bot_cards + k)->damage = (rand() % 60) + 40;
    (ptr_to_bot_cards + k)->manacost = 65;
    strcpy((ptr_to_bot_cards + k)->name, (ptr_to_all_cards + i)->name);

    for (k = 1; k < 4; k++)
    {
        i = rand() % 12;
        strcpy((ptr_to_bot_cards + k)->element, (ptr_to_all_cards + i)->element);
        (ptr_to_bot_cards + k)->damage = (ptr_to_all_cards + i)->damage;
        (ptr_to_bot_cards + k)->manacost = (ptr_to_all_cards + i)->manacost;
        strcpy((ptr_to_bot_cards + k)->name, (ptr_to_all_cards + i)->name);
    }
    bot_spells[0] = spell_cards[rand() % 4];
}
void card_making(struct cards *ptr_to_all_cards)
{
    int i, j, k = 0;
    char elements[4][10] = {"Earth", "Water", "Fire", "Air"};
    char type[3][20] = {"Spark", "Flame", "Inferno"};
    char mana_type[3][10] = {"sip", "gulp", "chug"};
    int damage[3] = {(rand() % 10), (rand() % 20) + 20, (rand() % 30) + 30};
    int mana[3] = {10, 20, 30};

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            strcpy((ptr_to_all_cards + k)->element, elements[i]);
            (ptr_to_all_cards + k)->damage = damage[j];
            (ptr_to_all_cards + k)->manacost = mana[j];
            strcpy((ptr_to_all_cards + k)->name, elements[i]);
            strcat((ptr_to_all_cards + k)->name, " - ");
            strcat((ptr_to_all_cards + k)->name, type[j]);
            strcat((ptr_to_all_cards + k)->name, " - ");
            strcat((ptr_to_all_cards + k)->name, mana_type[j]);
            k++;
        }
    }
}
void upgrade_attributes(struct player *ptr_to_player, struct player_cards *ptr_to_player_cards, int points)
{
    int choice, upgrade_amount, card_index;
    ptr_to_player->health = 100;
    ptr_to_player->mana = 100;
    while (points > 0)
    {
        printf("You have %d points. Choose an option:\n", points);
        printf("1. Increase health\n");
        printf("2. Increase card damage\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the amount of health to increase (up to your total points of %d): ", points);
            scanf("%d", &upgrade_amount);
            if (upgrade_amount > points)
            {
                printf("You don't have enough points to increase health by this amount. Try again.\n");
                continue;
            }
            ptr_to_player->health += upgrade_amount;
            points -= upgrade_amount;
            printf("Your health is now %d and you have %d points left.\n", ptr_to_player->health, points);
            break;
        case 2:
            printf("Enter the index of the card to upgrade (1 to 4): ");
            scanf("%d", &card_index);
            card_index--;
            if (card_index < 0 || card_index > 3)
            {
                printf("Invalid card index. Try again.\n");
                continue;
            }
            printf("Enter the amount of damage to add to the card '%s' (up to your total points of %d): ", (ptr_to_player_cards + card_index)->name, points);
            scanf("%d", &upgrade_amount);
            if (upgrade_amount > points)
            {
                printf("You don't have enough points to increase card damage by this amount. Try again.\n");
                continue;
            }
            (ptr_to_player_cards + card_index)->damage += upgrade_amount;
            points -= upgrade_amount;
            printf("The damage of your card '%s' is now %d and you have %d points left.\n", (ptr_to_player_cards + card_index)->name, (ptr_to_player_cards + card_index)->damage, points);
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

int main()
{
    int i = 0; // this is not part of the code will be removed
    srand(time(NULL));
    struct cards card_s[12];
    // yahaan pointer to structre array ko initialize kara hai
    struct cards *ptr_to_all_cards = (struct cards *)calloc(12, sizeof(struct cards));
    card_making(ptr_to_all_cards);

    ptr_to_spells spell_cards[4] = {health_steal, mana_steal, heal, block_card};

    // this block is like the element deciding block
    char elements[4][10] = {"earth", "water", "fire", "air"};
    int player_element, bot_element;
    printf("choose your main element\n1-Earth\n2-water\n3-Fire\n4-air\n");
    scanf("%d", &player_element);
    player_element -= 1;
    bot_element = rand() % 4;
    // give the player its cards
    struct player_cards player_card_s[4];
    struct player_cards *ptr_to_player_cards = (struct player_cards *)calloc(4, sizeof(struct player_cards));
    ptr_to_spells *player_spells = (ptr_to_spells *)calloc(1, sizeof(ptr_to_spells));
    player_cards_assigning(ptr_to_all_cards, ptr_to_player_cards, elements, player_element, player_spells, spell_cards);

    // give the bot its card
    struct bot_cards bot_card_s[4];
    struct bot_cards *ptr_to_bot_cards = (struct bot_cards *)calloc(4, sizeof(struct bot_cards));
    ptr_to_spells *bot_spells = (ptr_to_spells *)calloc(1, sizeof(ptr_to_spells));
    bot_cards_assigning(ptr_to_all_cards, ptr_to_bot_cards, elements, bot_element, bot_spells, spell_cards);

    // initialize the structs for player and the bot
    struct player p1;
    struct player *ptr_to_player = &p1;
    p1.mana = 100;
    p1.health = 100;
    struct bot b1;
    struct bot *ptr_to_bot = &b1;
    b1.mana = 100;
    b1.health = 100;
    i = 0;

    while (i == 0) // set the winning conditions here
    {
        i = player_turn(ptr_to_player, ptr_to_bot, ptr_to_player_cards, ptr_to_bot_cards, player_element, player_spells);
        if (i == 1)
        {
            int points = 100;
            upgrade_attributes(ptr_to_player, ptr_to_player_cards, points);
            break;
        }
        i = bot_turn(ptr_to_player, ptr_to_bot, ptr_to_player_cards, ptr_to_bot_cards, bot_element, bot_spells);
        if (i == 1)
        {
            break;
        }
    }
    free(ptr_to_all_cards);
    free(ptr_to_player_cards);
    free(ptr_to_bot_cards);
}
