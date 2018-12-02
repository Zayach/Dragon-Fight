/* Play out a simple fight between a character and a dragon, using dice rolls
 * @author Zachary Young, Marcus Coleman, Trey
 * @date 12/2/2018
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

int diceRoll(int x, int y);

int main(){
    srand(time(NULL));
    while(true){
        string charName = "";
        int playerHealth = 200;
        int playerAC = 16;
        int buff = 0;
        int dragonHealth = 300;
        int dragonAC = 15;
        int gameState = 0;
        while(gameState == 0){
            cout << R"(
                                                  _          _
                                                 _/|    _   |\_
                                               _/_ |   _|\\ | _\
                                             _/_/| /  /   \|\ |\_\_
                                           _/_/  |/  /  _  \/\|  \_\_
                                         _/_/    ||  | | \o/ ||    \_\_
                                        /_/  | | |\  | \_ V  /| | |  \_\
                                       //    ||| | \_/   \__/ | |||    \\
                                      // __| ||\  \          /  /|| |__ \\
                                     //_/ \|||| \/\\        //\/ ||||/ \_\\
                                    ///    \\\\/   /        \   \////    \\\
                                    |/      \/    |    |    |     \/      \|
                                                  /_|  | |_  \
                                                 ///_| |_||\_ \
                                                 |//||/||\/||\|
                                                  / \/|||/||/\/
                                                    /|/\| \/
                                                    \/  |

     ______   _______  _______  _______  _______  _          _______ _________ _______          _________
    (  __  \ (  ____ )(  ___  )(  ____ \(  ___  )( (    /|  (  ____ \\__   __/(  ____ \|\     /|\__   __/
    | (  \  )| (    )|| (   ) || (    \/| (   ) ||  \  ( |  | (    \/   ) (   | (    \/| )   ( |   ) (
    | |   ) || (____)|| (___) || |      | |   | ||   \ | |  | (__       | |   | |      | (___) |   | |
    | |   | ||     __)|  ___  || | ____ | |   | || (\ \) |  |  __)      | |   | | ____ |  ___  |   | |
    | |   ) || (\ (   | (   ) || | \_  )| |   | || | \   |  | (         | |   | | \_  )| (   ) |   | |
    | (__/  )| ) \ \__| )   ( || (___) || (___) || )  \  |  | )      ___) (___| (___) || )   ( |   | |
    (______/ |/   \__/|/     \|(_______)(_______)|/    )_)  |/       \_______/(_______)|/     \|   )_(

                                            Type any character to start
========================================================================================================================
        )";
        getch();
        system ("CLS");
        cout << "The King: \"You are a talented warrior... What is your name?\"\n";
        cin >> charName;
        cout << "The King: \"Wonderful name, indeed. Good, good. Now, there happens to be a dragon attacking the keep currently and well ... We could use your help!\"\n";
        cout << "Press any key to begin the assault!";
        getch();
        cout << endl << R"(========================================================================================================================

        Of course, being the daring adventurer you are, you accept the king's quest. You quickly grab your gear and make your way up onto the castle walls where you are met face-to-face with a massive dragon that you are unsure how you missed on your way in. Or, how you didn't know about it until the king told you in the first place. Nevertheless, there was no time to think on it too much! The dragon was there, and with the help of the king's men, you begin to attack!

========================================================================================================================

    Press any key to continue)" << endl;
        getch();
        gameState = 1;
        }
        while (gameState == 1){
            //top of the round, clear the screen and reset actions
            system ("CLS");
            int playerAction = 0;
            int dragonAction = 0;
            cout << "It comes to the top of the round, and you're first up! What would you like to do?\n";

            //Start of the player's turn
            cout << "Type 1 to attack, 2 to defend, or 3 to buff yourself\n";
            while (true){
                cin >> playerAction;
                if (cin.fail() || playerAction > 3 || playerAction < 1){
                    cin.clear();
                    cin.ignore(200, '\n');
                    cout << "Come on, adventurer! Enter a valid action! 1 - 3!\n";
                }
                else{
                    break;
                }
            }
            //if the player chooses to attack, roll to attack the dragon. If they 'hit' then deal appropriate damage.
            if (playerAction == 1){
                int toHit = 0;
                cout << "You move to make a mighty attack with your bulbously large, finely crafted greatsword!\n";
                toHit = diceRoll(1,20) + buff/2;
                if (toHit < dragonAC){
                    cout << "You rolled a total of " << toHit << " to hit but missed! The dragon is unharmed!\n";
                }
                else{
                    cout << "With a total roll of " << toHit << " you hit the dragon! You make three, huge swings and deal some damage!\n";
                    dragonHealth = dragonHealth - diceRoll(3,8) - buff;
                    //cout << "The dragon has: " << dragonHealth << " health remaining" << endl; // uncomment this to see the dragon's remaining health after each attack
                }
            }
            //if the player chooses to defend, gain some temporary ac until the end of the turn and heal
            if (playerAction == 2){
                cout << "You prepare yourself for the dragon's incoming attacks. You raise your AC by 5 and heal slightly!\n";
                playerAC = playerAC + 5;
                playerHealth = playerHealth + diceRoll(2,8) + buff;
                //cout << "Your health is now: " << playerHealth << endl; //uncomment this to see your health after buff
                //cout << "Your AC is now: " << playerAC << endl; //uncomment this to see your AC after buff
            }
            //if the player chooses to buff, raise the buff amount by 1d4/2
            if (playerAction == 3){
                cout << "You take a moment to sharpen your blade against the rough stone walling that surrounds you. SCREEEEEE. It looks sharper, now!\n";
                buff = buff + diceRoll(1,2);
                //cout << "current total buff is: " << buff << endl; //uncomment this to see your total buff each time
            }

            //if the dragon is dead, go to the win screen
            if (dragonHealth < 1){
                cout << "You deal the fatal blow!\n";
                gameState = 2;
                break;
            }

            //Dragon's actions
            dragonAction = diceRoll(1,3);
            cout << "\n\nThe dragon readies himself for his turn, and will take " << dragonAction << " actions this turn!\n";
            for (int i = 1; i <= dragonAction; i++){
                int toHit = 0;
                //breath attack
                if (i == 3){
                    cout << "The dragon breathes in and attempts to blow fire at you!\n";
                    toHit = diceRoll(1,20) + 5;
                    if (toHit < playerAC){
                        cout << "The dragon breathes out a mighty bellow, but the flames lick only the stone wall!\n\n\n";
                        //cout << "The dragon's total to hit was: " << toHit << endl; //uncomment this to see what the dragon rolled to hit you with fire!
                    }
                    else{
                        int dmg = diceRoll(3, 10) + 2;
                        playerHealth = playerHealth - dmg;
                        cout << "The dragon engulfs you with flames! You take " << dmg << " damage!\n\n\n";
                        cout << "You now have " << playerHealth << " left!\n";
                    }
                }
                //claw attack
                if (i == 2){
                   cout << "The dragon raises its fierce talons\n";
                    toHit = diceRoll(1,20) + 8;
                    if (toHit < playerAC){
                        cout << "The dragon makes to strike you, but its claws scrape off your glorious armor!\n\n\n";
                        //cout << "The dragon's total to hit was: " << toHit << endl; //uncomment this to see what the dragon rolled to hit you with fire!
                    }
                    else{
                        int dmg = diceRoll(1,10) + 5;
                        playerHealth = playerHealth - dmg;
                        cout << "The dragon vicously slashes you with its claws! You take " << dmg << " damage!\n";
                        cout << "You now have " << playerHealth << " left!\n\n\n";
                    }
                }
                //Tail attack
                if (i == 1){
                    cout << "The dragon reels its tail back in an attempt to bash you with it!\n";
                    toHit = diceRoll(1,20) + 4;
                    if (toHit < playerAC){
                        cout << "The dragon slams its tail forward! But alas! It hits only the wall beside you!\n\n\n";
                        //cout << "The dragon's total to hit was: " << toHit << endl; //uncomment this to see what the dragon rolled to hit you with fire!
                    }
                    else{
                        int dmg = diceRoll(3,6);
                        playerHealth = playerHealth - dmg;
                        cout << "The dragon strikes you with his tail! You take " << dmg << " damage!\n";
                        cout << "You now have " << playerHealth << " left!\n\n\n";
                    }
                }
            }

            //check if the player is dead
            if (playerHealth < 1){
                gameState = 3;
                break;
            }

            //Archers make attacks
            cout << "The castle archers from the leftmost tower ready their bows\n";
            if (diceRoll(1,20)-1 < dragonAC){
                cout << "The archers release their volley, but the arrows bounce off the dragons thick hide!\n\n\n";
            }
            else{
                int dmg = diceRoll(1,4) + 3;
                cout << "Some of the archer's arrows meet their mark!\n\n\n";
                dragonHealth = dragonHealth - dmg;
            }
            cout << "The castle archers from the rightmost tower ready their bows\n";
            if (diceRoll(1,20)-1 < dragonAC){
                cout << "The archers release their volley, but the arrows bounce off the dragons thick hide!\n\n\n";
            }
            else{
                int dmg = diceRoll(1,4) + 3;
                cout << "Some of the archer's arrows meet their mark!\n\n\n";
                dragonHealth = dragonHealth - dmg;
            }

            //check if the dragon is dead again
            if (dragonHealth < 1){
                cout << "The archers deal the fatal blow!\n";
                gameState = 2;
                break;
            }

            //end of the round. offer player a chance to read on what has happened, then start next round
            playerAC = 16;
            cout << "And that is the end of the round! Press any key to continue! (Remember, moving on will clear the screen)";
            getch();
        }

        //Victory screen
        while (gameState == 2){
            cout << "\n\n\n\n\nYou have won... press any key to go back to the main menu";
            getch();
            system ("CLS");
            gameState = 0;
            break;

        }

        //Death screen
        while (gameState == 3){
            cout << "\n\n\n\n\nYou have died... press any key to go back to the main menu";
            getch();
            system ("CLS");
            gameState = 0;
            break;
        }
    }
}
//function to roll x dice with y sides and return the total
int diceRoll(int x, int y){
    int rollSum = 0;
    for(int i = 0; i < x; i++){
        int roll = rand() % y + 1;
        //cout << "Roll: " << roll << endl; // uncomment this to see the results of each roll
        rollSum = rollSum + roll;
        //cout << "Total so far: " << rollSum << endl; // uncomment this to see the total after each roll
    }
    return rollSum;
}
