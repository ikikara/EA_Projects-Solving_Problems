# <p align="center">D - Building a list</p>
### Description
You start with a list that contains a single value 0, and a pointer to that value. Then you receive a list of instructions that can take the following values:
<br><br>
  MOVE LEFT<br>
  MOVE RIGHT<br>
  INSERT LEFT int<br>
  INSERT RIGHT int<br>
<br>
The first two instruct you to move the pointer to the left or to the right respectively. It is guaranteed that you will never move beyond the limits of the list. The last two instructions tells you to insert a new integer before or after the current pointer. Note that, when you insert an element, the pointer does not move.

When there are no more instructions you should print the list, one value per line.
##
### Input
List of instructions, one per line, until EOF. There are at most 100000 instructions.
##
### Output
The final list, starting from the leftmost value.
##
### Example
#### Input
INSERT RIGHT 2<br>
INSERT LEFT -1<br>
MOVE RIGHT<br>
INSERT LEFT 1<br>
INSERT RIGHT 3<br>
MOVE LEFT<br>
MOVE LEFT<br>
MOVE LEFT<br>
INSERT LEFT -3<br>
INSERT LEFT -2
#### Output
-3<br>
-2<br>
-1<br>
0<br>
1<br>
2<br>
3
#### Explanation
Note: parenthesis denote the element where the pointer is.<br>
List before any instruction: (0)<br>
List after instruction #1:   (0) 2  <br>
List after instruction #2:   -1 (0) 2  <br>
List after instruction #3:   -1 0 (2)<br>
List after instruction #4:   -1 0 1 (2)<br>
List after instruction #5:   -1 0 1 (2) 3<br>
List after instruction #6:   -1 0 (1) 2 3<br>
List after instruction #7:   -1 (0) 1 2 3<br>
List after instruction #8:   (-1) 0 1 2 3<br>
List after instruction #9:   -3 (-1) 0 1 2 3<br>
List after instruction #10:  -3 -2 (-1) 0 1 2 3<br>
Final list:                  -3 -2 -1 0 1 2 3<br>
