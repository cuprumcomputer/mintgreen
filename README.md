# Mint Green Programming Language

Mint Green is a small and simplistic programming language. Its syntax is based off of C++ and JQuery. The attached sample program shows how to use all of the commands to fully take advantage of Mint Green. Mint Green is generally a loose language, but here are a few guidelines/bugs:

* Whenever using variables in expressions or if statements a variable must come first. 

* At the beginning of every Mint Green program you must declare the number of lines. 
You must include blank lines, the terminating “$” command, and the declaration “[8]” itself in the number of lines.

* In your program you can have only 100 character variables and 100 integer variables. (Unless you want to add more to the two variable arrays)

* You can use “~” to display a string, or make a variable equal to a character.

* A variable’s name can be virtually as long as you want, but must be only made up of the alphabet and no other characters.

* Your Mint Green program must be in the same folder as the compiler, and you may have to enter “.txt” at the end depending on the type of file.

* If when you try to run the Mint Green Compiler, it paused and declares a segmentation fault, quit your C++ compiler and retry. If it continues to happen, please note it in the issues.

‘’’
Mint Green Programming Language Command Key:
	Math:
		/, divide: x / 6
		*, multiply: y * 4
		+, add: x + 2
		-, subtract: x - 2
		>, greater than: ?(x > y)
		<, less than: ?(x < y)
		(), assign variable to expression: x = (y + 3)
		
	Variable:
		&, character variable: & x
		#, positive integer variable: # y
		
	Special:
		[], declare number of lines: [3]
		!(), display: !(2)
		@(), get input: @(x)
		^, new line: !(^)
		=, equals: x = 2
		>, go back to: > 0
		=, compare if equal: ?(x = y)
		?(), if statement: ?(x = y)
		~, not a variable: x = ~a, !(~mint green)
		$, end program: $
‘’’
