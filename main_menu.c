#include <stdio.h>
#include <stdlib.h>
int audio_level; //Audio: 0 - low; 1 - med; 2 - high

void launch_game1(){
    printf("Launching Game 1");
    while(0);
}

void launch_game2(){
    printf("Launching Game 2");
    while(0);
}

void state_func(int state)
{
    switch(state) {
        case 0: {
            printf("Welcome!\n");
            printf("Choose Game |\n");
            printf("Audio Settings\n");
            printf("Quit\n");
            break;
        }
        
        case 1: {
            printf("Welcome!\n");
            printf("Choose Game\n");
            printf("Audio Settings |\n");
            printf("Quit\n");
            break;
        }
        
        case 2: {
            printf("Welcome!\n");
            printf("Choose Game\n");
            printf("Audio Settings\n");
            printf("Quit |\n");
            break;
        }
        
        case 3: {
            printf("Choose Game\n");
            printf("Game choice 1 |\n");
            printf("Game choice 2\n");
            printf("Back\n");
            break;
        }
        
        case 4: {
            printf("Choose Game\n");
            printf("Game choice 1\n");
            printf("Game choice 2 |\n");
            printf("Back\n");
            break;
        }
        
        case 5: {
            printf("Choose Game\n");
            printf("Game choice 1\n");
            printf("Game choice 2\n");
            printf("Back |\n");
            break;
        }
        
        case 6: {
            printf("Audio Settings\n");
            printf("Set audio low |\n");
            printf("Set audio med\n");
            printf("Set audio high\n");
            break;
        }
        
        case 7: {
            printf("Audio Settings\n");
            printf("Set audio low\n");
            printf("Set audio med |\n");
            printf("Set audio high\n");
            break;
        }
        
        case 8: {
            printf("Audio Settings\n");
            printf("Set audio low\n");
            printf("Set audio med\n");
            printf("Set audio high |\n");
            break;
        }
        
        case 9: break;
        
        case 10: {
            launch_game1();
            break;
        }
        
        case 11: {
            launch_game2();
            break;
        }
        
        case 12: {
            audio_level = 0;
            break;
        }
        
        case 13: {
            audio_level = 1;
            break;
        }
        
        case 14: {
            audio_level = 2;
            break;
        }
    }
}

char get_input()
{
    char inp;
    scanf("%c", &inp);
    return inp;
}

int state_change(int curr_state, char inp)
{
    switch(curr_state){
        case 0: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 3;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 1: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 6;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 2: {
            switch(inp){
                case 'x': {
                    curr_state = 9;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 3: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 10;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 4: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 11;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 5: {
            switch(inp){
                case 'x': {
                    curr_state = 0;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 6: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 12;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 7: {
            switch(inp){
                case 's': {
                    curr_state+=1;
                    break;
                }
                case 'x': {
                    curr_state = 13;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 8: {
            switch(inp){
                case 'x': {
                    curr_state = 14;
                    break;
                }
                case 'w': {
                    curr_state-=1;
                    break;
                }
                default : break;
            }
            break;
        }
        
        case 12: {
            curr_state = 0;
            break;
        }
        
        case 13: {
            curr_state = 0;
            break;
        }
        
        case 14: {
            curr_state = 0;
            break;
        }
        
    }
    
    return curr_state;
}



int main()
{
    int state = 0;
    state_func(state);
    
    while(state != 9){
        char inp = get_input(); // w - up; s - down; e - error; x - select
        state = state_change(state, inp);
        system("clear");
        state_func(state);
    }

    return 0;
}
