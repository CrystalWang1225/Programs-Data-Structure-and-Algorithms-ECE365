## Dynamic Program Question
This question came from the 1998 regional ACM Programming Contest:
[Click here to checkout the Website](http://www.acmgnyr.org/year1998/prob_g.html)

The problem defines a "merge" of two strings as a third string containing all the characters from each of the original two strings mixed together. The two sets of characters can be interspersed, but the characters from each individual string cannot be permuted. For example, one possible merge of "hello" and "world" would be "wohrellold". However, the string "wohrelldol" is not a valid merge. Although this string contains all the correct characters, and "hello" and "world" are both subsequences, there is no way to select two subsequences with distinct characters to form both of the original two strings.

 The program accepts three strings at a time; we'll call them A, B, and C. All strings will consist of only lowercase letters. You can assume that A and B will contain at most 1000 letters, and C will contain at most 2000 letters. Your program should determine whether or not C is a valid merge of A and B. If so, the program should output C with the characters from A converted to uppercase. If more than one merge is possible, the letters of A should be made to occur as early as possible. If no merge is possible, the output should read "*** NOT A MERGE ***".
