# <p align="center">E - Postfix calculator</p>
### Description
Given a set of mathematical expression in postfix notation, such that each operand/operator is separated by a space, print the result of that expression. To simplify, only the '+' and '-' operators are considered.

Example of a postfix expression:

2 3 4 - +<br><br>
To compute the result process the expression from the left to the right, then:

- If the next token is a number, push it into the stack

- If the next token is an operator, pop the two top numbers from the stack, perform the computation with that operator, and put the result back into the top of the stack. Note that the order is important, so for example: "3 4 -" should be evaluated as "3 - 4 = -1".

Once the expression is fully processed the result will be the only element left in the stack.

So the contents of the stack for the processing of that expression would be

After push operation: 2<br>
After push operation: 2 3<br>
After push operation: 2 3 4<br>
After '-' operation:  2 -1<br>
After '+' operation:  1 

##
### Input
The first line contains the number of postfix expressions to process. Then, each line of the following lines contains a postfix expression to evaluate.
##
### Output
For each expression print the result of the evaluation.
##
### Example
#### Input
3<br>
2 3 4 - +<br>
10 82 - 12 +<br>
-1 2 + 1 -
#### Output
1<br>
-60<br>
0
