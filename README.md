# Texas-Hold-em-Game

This is a fully implemented command-line based Texas-Hold-em-Game with odd 
calculation, ASCII graphics and AI players. It follows the fixed limited 
betting and ante rules.

All the source files for this project are stored in the src folder.

## How to run the game:

To run the game, simply run the following commands in the command line.

##### $ make
##### $ ./play_game



To play the game, enter your decision to **bet, raise, check, call or fold**
when prompted to. If you enter an invalid decision, the program will tell you
that your command is invalid. Then simply enter a correct decision after. Any
other information will be displayed on your window.


### How hands are compared

Comparing hands in poker is not a trivial task.  Since there are almost 2.6 
million different possible poker hands, it is impractical to simply store a 
ranking of all 2.6 million of these hands.  Luckily, there are only 7,462 
different “equivalence classes” of hands, meaning that there are only 7,462 
different groupings of hands that have the same rank.  This fact greatly 
simplifies our calculations by allowing us to use these equivalence classes to 
compare hands.  We pulled these equivalence classes from 
http://www.rpbridge.net/d/pkh.dta. Our program uses std::unordered map to store 
precalculated rankings of each of the possible hands. The key for each hand is 
the prime multiplication of the cards and the value is the ranking. Each card 
is represented by a struct which contains the value, suit, and prime number. The 
prime number is assigned according to the value of the card. Each card is 
represented by a struct which contains the value, suit, and prime number. The 
prime number is assigned according to the value of the card.

A: 41  
2: 2  
3: 3  
4: 5  
5: 7  
6: 11  
7: 13  
8: 17  
9: 19  
10: 23  
J: 29  
Q: 31  
K: 37  

Since multiples of primes are always unique, prime multiplication of 5 cards
would result in a unique number and this is the reason why we chose the prime
multiplication as the key.



### How odds are calculated

We use the Monte Carlo approach to estimate the odds. When getOdds function is
called, the program simulates how the game may end by dealing out cards to other
players and record the winner. This is done repeated for 10,000 times and the
percentage of winning is the estimation of the odds.



### How the AI works

The AI program utilizes the odds(hand strength) calculated by the getOdds
function and the pot odds where

pot odds = bet/pot

The hand strength and pot odds are then used to calculate the rate of return 

rate of return = hand strength/ pot odds

The rate of return is then used as a parameter to make a decision. With different 
values of rate of return, there are different probabilities for the AI to check, 
call, fold, bet or raise.
