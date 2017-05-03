# Texas-Hold-em-Game

This is a fully implemented command-line based Texas-Hold-em-Game with odd 
calculation, ASCII graphics and AI players. It follows the fixed limited 
betting and ante rules.


####How hands are compared?

It uses STL::unordered map to store precalculated ranking of each possible
hands. The key for each hand is the prime multiplication of the cards and the
value is the ranking.

Each card is represented by a struct which contains the value, suit, and prime
number. The prime number is assigned according to the value of the card.
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



####How are the odd calculated?

We use the Monte Carlo approach to estimate the odds. When getOdds function is
called, the program simulates how the game may end by dealing out cards to other
players and record the winner. This is done repeated for 10,000 times and the
percentage of winning is the estimation of the odd.



####How the AI works?

The AI program utilizes the odd(hand strength) calculated by the getOdds
function and the pot odd where

pot odd = bet/pot

The hand strength and pot odd are then used to calculate the rate of return 

rate of return = hand strength/ pot odd

The rate of return is then used as a parameter to make a decision. With different 
values of rate of return, there's are different probabilities for the AI to check, 
call, fold, bet or raise.
