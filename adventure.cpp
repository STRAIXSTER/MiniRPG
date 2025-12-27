#include <iostream>
#include <ctime>

class Fighter{
    private:
    std::string name;
    int health;

    public:
    Fighter(std::string Name, int Health){
        if(Health > 0){
            this-> health = Health;
        }
        if(!Name.empty()){
            this-> name = Name;
        }
    }

    int TakeDamage(int damage){
        return health -= damage;
    }

    bool IsDead(){
        if(health <= 0){
            return true;
        }
        else{
            return false;
        }
    }

};

class Monster{
    private:
    std::string name;
    double HP;
    int level;

    public:
    void setMonster(std::string &Name, double &Hp, int Level){
        name = Name;
        HP = Hp;
        level = Level;
    }

    double getHEALTH(){
        return HP;
    }

    int getLevel(){
        return level;
    }

    std::string getNAME(){
        return name;
    }
   
    void printMonster(){
        std::cout << "You encounter a level: " << level << " " << name << '\n';
    }

    int TakeDamage(int damage){
        return HP -= damage;
    }

    bool IsDead(){
        if(HP <= 0){
            return true;
        }
        else{
            return false;
        }
    }
        
};

class Boss: public Monster{};

class Ending{
    public:

    void printNeutralEnding(){
        //Homeowner in the BIG 25 ?!
        std::cout << "        ##### " << '\n';
        std::cout << "          | ## " << '\n';
        std::cout << "  /-\\    |/ * " << '\n';
        std::cout << " | = | $  |    " << '\n';
        std::cout << "---------------" << '\n';
        std::cout << "You decided to live as a farmer after your journey... " << '\n';
    }

    void printGood(){
        //This is you with a crown btw...
        std::cout << "     |>>>  " << '\n';
        std::cout << "     |     " << '\n';
        std::cout << "! !  |  ! !" << '\n';
        std::cout << "|==========| " << '\n';
        std::cout << "|**********|" << '\n';
        std::cout << "| (*)  (*) |" << '\n';
        std::cout << "|    []    |" << '\n';
        std::cout << "|__________|" << '\n';
        std::cout << "For your bravery, you were crowned !" << '\n';
    }

    void printBad(){
        //This is a gravestone if it wasn't THAT obvious...
        std::cout <<"  ---------" << '\n';
        std::cout <<" /        \\" << '\n';
        std::cout <<"/    RIP   \\" << '\n';
        std::cout <<"|           |" << '\n';
        std::cout <<"|           |" << '\n';
        std::cout <<"|     *     |" << '\n';
        std::cout <<"|     | /#  |" << '\n';
        std::cout <<"|    #|/    |" << '\n';
        std::cout <<"|===========|" << '\n';
        std::cout << "Here lies our unfortunate hero :(" << '\n';

    }
};

int EnemyDamage(int xp);
int BossDamage(int xp);

int main(){
    //Game variables
    char play;
    srand(time(NULL));
    int wins = 0; //W or L
    int dead = 0; //F
    int check = 0; // So I don't the enemy 6 - 7 times when I play
    int gold = 0; //cauta un job part-time bro :/
    int loot; //temporary variable to show the gold you get per kill
    int encounter = 0; //this defines if you fight a boss after the enemies or you jsut skip to the ending
    int champion = 0;
    int TotalDamage = 0; //sa vezi cat ti-o dat de te-o julit
    int TotalAttack = 0; //cat le-ai dat TU de i-ai julit
    std::string Monsters[6] = {"Slime" , "Bat" , "Wolf" , "Goblin" , "Snake" , "Troll"};
    std::string Big[6] = {"King " , "Vampire " , "Alpha " , "Chieftain " , "Queen " , "Giant "};

    //Player variables
    int HEALTH;
    std::string NAME;
    char Move;

    //Enemy Variables
    int xp = rand() % 10 +1;
    int mon = rand() % 5;
    double Hel = 1.2 * xp;
    std::string ster = Monsters[mon];
    
    std::cout << "Welcome adventurer !" << '\n';
    std::cout << "Do you want to play ? (Y/N) " <<'\n';
    
    do{
        std::cin >> play;
        play = toupper(play);
        if(play == 'Y'){
        continue;
    }
        else if(play == 'N'){
        std::cout << " Ah... the illusion... of free choice... " << '\n';
    }

        else{
        std::cout << "Please try again..." << '\n';
    }
    }while(play != 'Y' && play != 'N');

    std::cout << "Enter your name and HP !" << '\n';

    std::cin >> NAME;
    std::cin >> HEALTH;

    Fighter Player(NAME, HEALTH);

    Monster Enemy;
    Enemy.setMonster(ster,Hel, xp);
    // BIG BOSS !!
    Boss finalBoss;
    int XP = rand() % 20 + 1;
    int MON = rand() % 6;
    std::string bossName = Big[MON] + Monsters[MON];
    double bossHel = 2.0 * xp;
    finalBoss.setMonster(bossName, bossHel, XP);

    Ending End;

    do{
        if(check == 0){
        Enemy.printMonster();
        check++;
        }

        std::cout << "Press A to fight !";
        std::cin >> Move;
        //Universal damage
        int dmg = rand() % 6 ;
        Enemy.TakeDamage(dmg);
        int enemyDMG = EnemyDamage(xp);
        std::cout << "You did " << dmg << " damage" << '\n';
        TotalAttack += dmg;

        std::cout << "The enemy prepares to move... " << '\n';
        Player.TakeDamage(enemyDMG);
        std::cout << "You got hurt : " << enemyDMG << " HP" << '\n';
        TotalDamage += enemyDMG;

        if(Enemy.IsDead() == true){
            loot = 1.5* xp;
            std::cout << "You defeated the foe and found : " << loot << " gold !" << '\n';
            wins++;
            check = 0;
            gold += loot;
            loot = 0; 

            xp = rand() % 10 +1;
            mon = rand() % 5;
            Hel = 1.2 * xp;
            ster = Monsters[mon];
            Enemy.setMonster(ster,Hel, xp);
        }
        else if(Player.IsDead() == true){
            dead = 1;
            std::cout << "You perished..." << '\n';
        }
    }while(dead != 1 && wins < 3);

    if(wins == 3){
        encounter = rand() % 2;
    }

    if(encounter == 1){
        std::cout << "You feel like you are gonna have a bad time..." << '\n';
        finalBoss.printMonster();
        do{
            std::cout << "Press any key to attack !";
            std::cin >> Move;
            int dmg = rand() % 12;
            finalBoss.TakeDamage(dmg);
            std::cout << "You scratched the entity for: " << dmg << " damage" << '\n';
            TotalAttack +=dmg;

            if(finalBoss.IsDead() == true){
            loot = 25* XP;
            std::cout << "You defeated the dark entity and found : " << loot << " gold !" << '\n';
            champion++;
            gold +=loot;
            break;
            } 

            std::cout << "The ABOBINATION prepares to move... " << '\n';
            int enemyDMG = BossDamage(XP);
            Player.TakeDamage(enemyDMG);
            std::cout << "You got hurt : " << enemyDMG << " HP" << '\n';
            TotalDamage += enemyDMG;

            if(Player.IsDead() == true){
            dead = 1;
            std::cout << "You perished and your body was never found..." << '\n';
        }

        }while(dead != 1 && champion == 0);
    }

    if(dead == 1){
        End.printBad();
    }

    else if(play == 'N'){
        End.printNeutralEnding();
        std::cout << "You managed to hoard : " << gold << " coins." << '\n';
        std::cout << "You hurt the mosters for merely : " << TotalAttack << " HP." << '\n';
        std::cout <<"You got hurt for a total of : " << TotalDamage << " HP." << '\n';
    }

    else{
        End.printGood();
        std::cout << "You managed to collect : " << gold << " gold." << '\n';
        std::cout << "You damaged the foes for a total of : " << TotalAttack << " HP." << '\n';
        std::cout <<"You got hurt for a total of : " << TotalDamage << " HP." << '\n';
    }

    std::cout << "And so... your jurney ends here..." << '\n';

    return 0;
}

int EnemyDamage(int xp){
    int move = 0;
    move = (rand() % 5 + 1 ) * xp ;

    return move;
}
int BossDamage(int XP){
    int move = 0;
    move = (rand() % 10 + 1 ) * XP ;

    return move;
}

