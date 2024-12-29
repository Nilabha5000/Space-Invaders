#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>
# define LEN 25
# define WIDTH 25
# define STOCK 100  // represents the Maximum number of bullets
int playerLife = 30;
int enemyLife = 30;
int gameOver = 0;
// this variable calculates the number of presses of SPACE BAR button
int countSpaceBar = -1;
struct spaceship{
      int x;
      int y;
      char name[50];
};
struct bullet{
    int x;
    int y;
     int speed;
     bool is_fire;
};
void setposition(int x , int y){
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void playShootSound() {
    PlaySound(TEXT("sounds/shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
// these two functions are use to display life of both spaceships
void DisplayEnemylife(){
    setposition(55,12);
    printf("Oponent's life ");
    setposition(55,13);
    for(int i = 0; i<enemyLife; ++i){
        printf("#");
    }
}
void Displayplayerlife(struct spaceship *s){
    setposition(55,2);
    printf("%s's life ",s->name);
    setposition(55,3);
    for(int i = 0; i<playerLife; ++i){
        printf("#");
    }
}
void help(){
    system("cls");
    FILE *file = fopen("instructions.txt","r");
    if(file == NULL){
        printf("No help found !\n");
        getch();
        return;
    }
    char content;
    content = fgetc(file);
    while(content != EOF){
        printf("%c",content);
        content = fgetc(file);
    }
    printf("\npress e for ecape : ");
    content = getch();
    if(content == 'e' || content == 'E')
    {
        system("cls");
    }
}
void who_win(){
    if(enemyLife == 0){
        printf("YOU WIN\n");
    }
    else if((enemyLife == 0 && playerLife == 0)){
        printf("Game Draw\n");
    }
    else{
        printf("YOU LOOSE\n");
    }
}
// this function is use to fill the bullets in stock i.e array
void fillstock(struct bullet stock[],struct spaceship s){
       for(int i = 0; i < STOCK; i++)
       {
            stock[i].x = s.x;
            stock[i].y = s.y;
            stock[i].is_fire = false;
            stock[i].speed = 4;
       }   
}

void displayPlayersPosition(struct spaceship *s, struct spaceship *enemy){
    setposition(55, 0);
    printf(" X position of %s : %d \n",s->name,s->x);
    setposition(55,1);
    printf(" Y position of %s : %d \n",s->name,s->y);
    setposition(55,10);
    printf(" X position of oponent : %d \n",enemy->x);
    setposition(55,11);
    printf(" Y position of oppnent : %d \n",enemy->y);
}
//this isEmpty function determines that if the bullets are present in stock or not
int isEmpty(struct bullet *b,struct spaceship *enemy){
    for (int i = 0; i < countSpaceBar+1; i++)
    {
        if((b[i].y >= 4 || b[i].y >= enemy->y)  && b[i].is_fire != false){
            return 0;
        }
    }
    return 1;
    
}
void logic(struct spaceship *player,struct spaceship *enemy,struct bullet playerBullets[], struct bullet *oponentBullet){
    // this condition executed when player spaceship go beyond the border
    if(player->x <= 3 || player->x >= (WIDTH-4)){
        if(player->x <= 3){
            player->x+=1;
        }
        else if(player->x>= (WIDTH-4)){
            player->x-= 1;
        }
    }
    // this condition executed when player bullets hit with some obstecles
        for(int i = 0; i<countSpaceBar+1; ++i){
           if(playerBullets[i].y <= enemy->y  || playerBullets[i].y <= 4){
                  playerBullets[i].y = player->y;
                  playerBullets[i].is_fire = false;
                  // condition if ship hits the to other ship
                  if(playerBullets[i].y >= enemy->y && playerBullets[i].x >= enemy->x){
                        enemyLife--; // oponent ship looses its by 1
                    } 
            }
        }
        if(isEmpty(playerBullets,enemy)){
            countSpaceBar = -1;
        }
        // this condition executes when the oponent buttlet hit with obstecle
         if(oponentBullet->y >= player->y || oponentBullet->y >= 80)
        {
               oponentBullet->y = enemy->y;
               oponentBullet->is_fire = false;
               if(oponentBullet->y <= player->y && oponentBullet->x <= player->x){
                     playerLife--; // player ship looses its by 1
                } 
        }
    if(enemyLife == 0 || playerLife == 0){
        gameOver = 1;
    }
}
void ReinitializeSpaceBar(){
    // this condition works when number of firering are more that the maximum stock
    if(countSpaceBar >= STOCK){
        countSpaceBar = (STOCK-1);
        return;
    }
    return;
}
void set_player_bulletposition(struct bullet *b,struct spaceship *player){
    for(int i = 0; i < countSpaceBar+1; ++i){
       b[i].x = player->x;
        if(b[i].is_fire){
          setposition(b[i].x,b[i].y-1);
          printf("0");
          b[i].y-= b[i].speed;
        }
    }
}
void set_enemy_bullet_position(struct bullet *b,struct spaceship *enemy){
    b->x = enemy->x;
     if(b->is_fire){
        setposition(b->x,b->y-1);
        printf("0");
        b->y+= b->speed;
     }
}
// close_option funtion does 
// pause the game and ask for close or continue
void close_option(){
    char option;
    system("cls");
    printf("Are you sure y/n ");
    option = getchar();
    if(option == 'y') gameOver = 1;
    else gameOver = 0;
}
void control(struct spaceship *S, struct bullet * b){
    if(kbhit()){
        char Button;Button = getch();
        switch(Button){
           case 'a': // for LEFT
            S->x-=3;
            break;
            case 'd': // for RIGHT
            S->x+=3;
            break;
            case (char)32: // this condition is use for firing bullets
            countSpaceBar++;
             b[countSpaceBar].is_fire = true;
             playShootSound();
             break;
            case 'q': // for QUITING
            close_option();
            break;
            case 'h': // for HELP
            help();
            break;
        }
    }
}

void Display_Spaceship(int x, int y){
   setposition(x+2,y);
    printf("[x]");
    setposition(x,y+1);
    printf("[x x x]");

}
void Display_Eneny_Spaceship(int x , int y){
    setposition(x,y);
    printf("[x x x]");
    setposition(x+2,y+1);
    printf("[x]");
}
void set_Enemy_Spaceship_Position(struct spaceship *enemy){
    int x = enemy->x;
    int y = enemy->y;
    Display_Eneny_Spaceship(x,y);
}
void Set_Random_position_of_Enemy(struct spaceship *enemy,struct bullet *enemyBullet){
    if(enemyBullet->is_fire == false){
        int givenXpostion[5]= {5,10,15,20,25};
        int r = rand()%5;
       enemy->x = givenXpostion[r];
       enemyBullet->is_fire = true;
       playShootSound();
    }
     set_Enemy_Spaceship_Position(enemy); 
}
void set_Spaceship_Position(struct spaceship *S){
    int x = S->x;
    int y = S->y;
     Display_Spaceship(x,y);
}
void border(int X , int Y){
    // this loop to draw a upper border line
     for(int i = 0; i<WIDTH; ++i){
           setposition((i+X)+1, Y);
           printf("*");
     }
     //this loop to draw lower border line
     for(int i = 0; i<WIDTH; i++){
          setposition((i+X)+1,(LEN+4));
          printf("*");
     }
     // this loop to draw a left border line
     for(int i = 0; i<LEN; ++i){
        setposition(X,(Y+i));
        printf("*");
     }
     // this loop to draw a right border line
     for(int i = 0; i<LEN; ++i){
         setposition((X+WIDTH),Y+i);
         printf("*");
     }
}
void Give_player_name(struct spaceship *player){
    char name[50];
    printf("Enter your name : ");
    scanf("%s",name);
    strcpy(player->name,name);

}
int main(){
    // initialising position of player spaceship
    struct spaceship S1;
    S1.x = 12;
    S1.y = 24;
    // initailising position of enemies spaceship
     struct spaceship S2;
     S2.x = 12;
     S2.y = 7;
     // setting player bullet positon and filling the bullets
     struct bullet B1[STOCK];
     fillstock(B1,S1);
     //seting enemy bullet position
     struct bullet B2;
     B2.x = S2.x;
     B2.y = S2.y;
     B2.speed = 2;
     B2.is_fire = true;
     Give_player_name(&S1);
     help();
     system("cls");
    while(!gameOver){
        printf("                          SPACE INVADERS                ");
        border(5,5);
        displayPlayersPosition(&S1,&S2);
        Displayplayerlife(&S1);
        DisplayEnemylife();
        Set_Random_position_of_Enemy(&S2,&B2);
        set_Spaceship_Position(&S1);
        control(&S1,B1);
        logic(&S1,&S2,B1,&B2);
        ReinitializeSpaceBar();
        set_player_bulletposition(B1,&S1);
        set_enemy_bullet_position(&B2,&S2);
        Sleep(100);
        system("cls");
    }
    who_win();
    printf("         GAME OVER \n");
    getch();
    return 0;
}