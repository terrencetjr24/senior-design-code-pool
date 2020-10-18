#ifndef UCI_H
#define UCI_H

typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;
typedef enum buttonPress {APress, BPress, StPress, SePress, LPress, RPress, UPress, DPress, SamePress} buttonPress;

void uci_main();
buttonPress getInput();
int getInput_DEMO();

#endif
