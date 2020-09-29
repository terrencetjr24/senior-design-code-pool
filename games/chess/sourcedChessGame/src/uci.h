#ifndef UCI_H
#define UCI_H

void uci_main();
int getInput();
typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;

#endif
