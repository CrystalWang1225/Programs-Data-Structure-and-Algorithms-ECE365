## Stacks & Queues

This is a program that manipulates stacks and queues.

### Introduction

The program asks the user for the name of an input text file and an output text file. The input file will contain a list of commands, one per line. Each command will direct the program to create a stack or a queue, to push a value onto a stack or a queue, or to pop a value from a stack or a queue. (Most modern sources use the terms "enqueue" and "dequeue" to indicate insertions into and deletions from queues, but we will use "push" and "pop" for both stacks and queues.)

The input file must contain one command per line. To be valid, a command must follow a very specific format. The command must consist of two or three words, depending on the type of command, separated by single spaces. The line must have no leading whitespace before the first word or trailing whitespace after the last word. For the purposes of this assignment, a "word" is defined to be a sequence of letters and digits, except for words representing values of integers or doubles, which might also contain a single negative sign, and/or in the case of doubles, a single decimal point. All commands (i.e., all lines in the text file) will end with a single Unix-style newline character ('\n').

The first word of each command must be "create", "push", or "pop" (all lowercase letters). The second word must be a valid name for a stack or a queue. The first character of every name must be one of 'i', 'd', or 's' (all lowercase), standing for integer, double, or string; this represents the data type that is stored in the particular stack or queue. The rest of the name must consist of only letters and digits. Both uppercase and lowercase letters are allowed, and the program should be case sensitive.

If the first word is "create", there must be a third word that will be either "stack" or "queue" (all lowercase letters). This represents the type of list being created. No two lists may have the same name. However, two lists storing different data types (e.g., one list storing integers and another storing strings) may have the same name other than the first characters (in this case, 'i' or 's'). There cannot be a stack and a queue of the same data type that share the same name.

If the first word is "push", there must be a third word representing a value to be pushed onto the stack or queue. This value must match the appropriate type of the specified stack or queue, and it must fit into a single variable (e.g., an integer will fit in a 32-bit signed int); if the value is a string, it must be a single word, as defined above (i.e., containing only letters and digits).

If the first word is "pop", there must not be a third word.

You may assume that all commands in the input file will be valid! In other words, your program does not have to check that the lines in the text file represent valid commands; you may assume that this will be the case.

The program reads and process the commands in the text file. After each command is read, the program should output the string "PROCESSING COMMAND: " followed by the text of the command and then a single Unix-style newline character. There should be exactly one space in between the ':' and text of the command. All output should be written to the specified output file.

If the command is a "create" command, and the name of the stack or queue that is specified has already been created (whether it was created as a stack or a queue), the program should output the string "ERROR: This name already exists!" using the same casing as is displayed here. If the name is new, the stack or queue should be created, and no additional output should be written.

If the command is a "push" command, and the specified name does not exist, the program should output the string "ERROR: This name does not exist!" using the same casing as is displayed here. If the stack or queue does exist, the push operation should be applied, and no additional output should be written.

If the command is a "pop" command, and the specified name does not exist, the program should output the string "ERROR: This name does not exist!" using the same casing as is displayed here. If the stack or queue does exist, but it is empty, the program should output the string "ERROR: This list is empty!" using the same casing as is displayed here. If the stack or queue does exist and is not empty, the pop operation should be applied, and the program should output "Value popped: ", using the same casing as is displayed here, followed by the value that is popped from the stack or queue. There should be exactly one space in between the ':' and the value. For this assignment, a "pop" is assumed to both remove and return the appropriate value from the stack or queue.
