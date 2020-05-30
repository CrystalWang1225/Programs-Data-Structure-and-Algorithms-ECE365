## Hash Table - Spell Check
This program creates a hash table and then use the hash table class to read in a "dictionary" and "spell check" a document

### Introduction
For the purposes of this assignment, a valid word is defined as any sequence of valid characters, and the valid characters are letters (capital and lowercase), digits (0 - 9), dashes (-), and apostrophes ('). Every other character is considered a word separator.

A dictionary is defined as a list of recognized words. The dictionary is guaranteed to contain exactly one word per line, with no leading or trailing spaces, followed by a single, Unix-style newline character (\n). Some of the words in the dictionary might not be valid (i.e., they may contain invalid characters). When loading the dictionary, invalid words, and also words that are too long (see below), can optionally be ignored. The dictionary does not specify the meanings of words; it just lists them.

The document to spell check may be any valid text file. Each line in the document will end with a single, Unix-style newline character. When spell checking the document, your program should indicate every unrecognized word, including the line number on which it occurs. Words should only be allowed to grow up to 20 characters. If a word in the document is too long, you should indicate the line number on which this occurs along with the first 20 characters of the word. The first line in the document is line 1. Words in the document that include digits (perhaps in addition to other valid characters) are technically valid but should not be spell checked (i.e., your program should ignore them). In the document, as previously stated, every character that is not a valid word character is a word separator; e.g., the string "abc@def" represents two valid words, "abc" and "def". Therefore, there cannot be invalid words in the document.

The program is case insensitive, and all capital letters in both the dictionary and the document should be converted to lowercase immediately upon seeing them.
