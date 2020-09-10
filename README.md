# Expression-Evaluator
A program that transforms a given postfix expression into a binary tree such that the traversal of the tree will yield the postfix, infix and prefix equivalents of the algebraic expression. 

The program uses recursion, but iterative methods can be found commented in the code.
The infix expression will need parentheses to avoid generating ambiguous expressions. In the inOrder() method, display an opening parenthesis before the first recursive call and a closing parenthesis after the second recursive call. 

Example:
Postfix: ABC+*
Infix: A*(B+C)
Prefix: \*A+BC 
