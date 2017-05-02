#include "AI.h"

/* This function returns a decision
There are two possible set of decision:
1) when no one has bet, so AI has the option to fold, check or bet
2) when someone has bet/raised, so AI has the option to fold, call, raise

The return value can be 0, 1, 2 where:
0 always represent fold
1 can represent check or call
2 represent bet or raise
*/ 
int AI_determine(double handStrength, int bet, int pot) { 

    // calculate pot odd
    double sum = bet + pot;
    double potOdd = (double)bet/sum;


    // calculate rate of return
    double RR = handStrength/potOdd;

    /* Now with the pot odd and rate of return, a decision can be made based
    on that using percentage and chance:
    Let follow this initial logic:
    If RR < 0.8 then 95% fold, 0 % call, 5% raise (bluff)
    If RR < 1.0 then 80%, fold 5% call, 15% raise (bluff)
    If RR <1.3 the 0% fold, 60% call, 40% raise
    Else (RR >= 1.3) 0% fold, 30% call, 70% raise
    If fold and amount to call is zero, then call.*/
    
    cout << "bet: " << bet << ", pot: " << pot << endl;
    cout << "sum: " << sum << endl;
    cout << "potOdd: " << potOdd << endl;
    cout << "handStrength: " << handStrength << endl;
    cout << "RR: " << RR << endl;

    
    // generate a random number between 0-99
    int randNum = rand() % 100;
    

    /* deals with the case when no one has bet other rounds*/
    if (potOdd == 0) {
        if (handStrength > 0.5)
            if (randNum < 70)
                return 2;
            else
                return 1;
        else
            return 1;
    }

    // assign 0-94 to fold, 95-99 to raise and likewise for others
    if (RR < 0.8) {
        if (randNum < 95)
            return 0;
        else
            return 2;
    } else if (RR < 1.0) {
        if (randNum < 80)
            return 0;
        else if (randNum >= 80 && randNum <85)
            return 1;
        else
            return 2;
    } else if (RR < 1.3) {
        if (randNum < 60)
            return 1;
        else
            return 2;
    } else { 
        if (randNum < 30)
            return 1;
        else
            return 2;
    } 

}
