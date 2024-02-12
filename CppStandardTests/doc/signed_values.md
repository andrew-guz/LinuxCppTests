## How sign is stored and what are the range values

If we have n bits we have 2^n different values we can store.

So we can have -(2^n-1) to 2^n-1 - 1. 0 will be "taken" from "positive" part of a digit.

### Old way

First bit presents 0 + 1 -

0110 = 6

1110 = -6

### New way

To represent negative numbers, Two’s Complement employs a clever technique. The negation of a number x in Two’s Complement is achieved by inverting all the bits (changing 0s to 1s and vice versa) and then adding 1.

For example, to represent -6 in a 4-bit Two’s Complement system, we need to start with the binary representation of 6: 0110.

Then, we invert all the bits: 1001. Finally, we add 1: 1010.
