Parity check lookup table generator. 
====================================

A project I was working on required me to check that the 7th parity bit was valid. I decided to use a lookup table to
accomplish this. I realised that it might be fun to create a little proggy that would generate the values
required for the lookup table. This program does that. 

The parity bit was an odd parity bit, so this program can either produce even/odd parity tables depending on the flags you send it

Running 
./parlooktblgen -b 6 -o 
Would give me a 6bit (64 different values) table, where the parity bit is ODD (-o)

If I were to run

./parlooktblgen -b 6

Then I would get 64 values, where the parity bit is even.

I'm aware that I could have just googled for a lookup table or used someone elses no doubt better implementation, but that would have robbed me of a chance to mess around :D 
