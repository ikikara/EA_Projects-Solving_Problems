# <p align="center">H - Inventory Management</p>
### Description
You are responsible for the software that manages the inventory for your company. To do this, you need to quickly process three types of instructions:<br>

  ADD x y   ---> you add `x` copies of the item with id `y` to the inventory<br>
  REM x y   ---> you remove `x` copies of the item `y` from the inventory<br>
  QUERY y   ---> you print how many items with id `y` exist in the inventory<br>
  
Note that, if not enough items exist in the inventory for the remove instruction you print "removal refused" and do not remove any item.
##
### Input
List of instructions, one per line, until EOF. All ids and quantities are positive integers. There are at most 500000 instructions.
##
### Output
When a query instruction appears, print the number of items available for the queried item id. For the remove instruction, if there are not enough items to remove print "removal refused".
##
### Example
#### Input
ADD 10 1<br>
ADD 5 2<br>
REM 4 2<br>
REM 2 2<br>
QUERY 2<br>
REM 2 1<br>
QUERY 1<br>
QUERY 3
#### Output
removal refused<br>
1<br>
8<br>
0
