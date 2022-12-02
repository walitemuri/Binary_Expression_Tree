# Project Title

Binary Expression Tree 

## Description

The program that takes as input a fully parenthesized, arithmetic expression of
binary operators +, −, ∗, /, and converts the expression into a binary expression tree. The
program takes input from the command line. The entire expression should be in a
character string without any space in it.

An input string only includes floating numbers in the format of Y.YY, that is, one digit to the
left of the decimal point and two digits to the right of the decimal point, and variables of the
form of x1, x2, ....

The leaves in the expression tree store floating values but also to store variables of the form 
x1, x2, x3, ..., which are initially 0.0 and can be updated interactively by the user. 

```
For example, expression:

(((x1 + 5.12) ∗ (x2 − 7.68))/x3)

will be converted into a binary expression tree like:




                                  /
                            ______|______
                            |           |
                            *           x3
                      ______|______
                      |           |
                      +           -
                  ____|____   ____|____
                  |       |   |       |
                  x1    5.12  x2     7.68
```

The program should then show a menu with the following options:
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

## Author Information

Contact: walitemuri@gmail.com

## Getting Started

### Dependencies

* GCC Compiler
* Ubuntu, MacOS

### Executing program 

```
    make
```

```
    running: ./A4
```
## Limitations

Current Version does not have options 1,3,5,6 implemented, the expression should be limited to under 26 components

## Development History

* 0.1.0
    * Initial Inception - Expression Post Order, Pre Order 

## Sample Output
![Screen Shot 2022-11-12 at 9 15 23 PM](https://user-images.githubusercontent.com/108627530/201502484-cd58615a-d0f3-45dd-a43c-572fd3178230.png)
![Screen Shot 2022-11-12 at 9 15 45 PM](https://user-images.githubusercontent.com/108627530/201502497-207a0ac3-491c-4450-bfd1-173f0c88fdf0.png)
![Screen Shot 2022-11-12 at 9 16 12 PM](https://user-images.githubusercontent.com/108627530/201502492-43a87df8-03a2-4bf3-b5c6-3df10626da85.png)
