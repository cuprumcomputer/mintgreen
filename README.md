# Mint Green Programming Language
Mint Green is a super simple programming language, great for beginners into programming. It is based off of C++, and is not a really serious programming language, but more of a simple facade to begin programming in.

Math:
   */, divide: x / 6
   **, multiply: y * 4
   *+, add: x + 2
   *-, subtract: x - 2
		
Variable:
   *&, character variable: & x
   *#, positive integer variable: # y
   *=, equals: x = 2
   *(), assign varaible to expression: x = (y + 3)

Basic:
   *[], number of lines: [3]
   *!(), display: !(2)
   *^, new line: !(^)
   *>, go back to: > 0
   *?(), if statement: ?(x = y)
   *>, greater than: ?(x > y)
   *<, less than: ?(x < y)
   *=, compare if equal: ?(x = y)
   *~, not a variable, a string: x = ~a, !(~mint green)
   *$, end program: $

The attached sample programs show how to use these commands to fully take advantage of Mint Green. Mint Green is generally a loose language, but here are a few rules/issues you must follow:

* Whenever using variables in expressions or if statements a variable must come first. 
  For Example:
	?(x < 6) … Correct!
	?(6 > x) … Wrong!
	x = (y + 1) … Correct!
	y = (1 + y) … Wrong!

* At the beginning of every Mint Green program you must declare the number of lines. 
You must include blank lines, the terminating “$” command, and the declaration “[8]” in the number of lines.
For Example:
	[3] … line 1
	!(~hi) … line 2
	$ … line 3

* There is a fixed array that hold 100 integer variables and 100 character variables. I have not found a way to create an infinite number of variables.

* You can use “~” to display strings of letters and symbols, but you can’t make character variables equal to strings.
For Example:
	!(~hello, hi) … Correct!
	x = ~hello … Wrong!

* Your Mint Green program must be on a blank text file, and when asked for the name of it, you may or may not have to type “.txt” at the end. Also the program must be in the same folder as the compiler. I recommend just editing the sample programs to create your program.

Thank you and I hope you enjoy Mint Green Programming Language!


