# Texas-Hold-em-Game

This is a poker simulator with odd calculation. 

How hands are compared?

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

How are the odd calculated?

We use the Monte Carlo approach to estimate the odds
