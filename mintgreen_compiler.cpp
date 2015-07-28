// Mint Green Programming Languge
// Developedd By CUPRUM[]

#include <iostream>
#include <fstream> 

using namespace std;

static string * program;
int line_number;

string isolated;
int position;


const int VARIABLE_NUMBER = 100;

struct character { // Character Struct Holds Character Name and Value
	string name;
	char value;
};

struct integer { // Integer Struct Holds Integer Name and Value
	string name;
	int value;
};

static integer intdex[VARIABLE_NUMBER]; // Holds All Integer Values
static character chardex[VARIABLE_NUMBER]; // Holds All Character Values

int current_int = 0;
int current_char = 0;

bool is_char;

void CreateInt(int);
void CreateChar(int);
int GoTo(int);
int IfStatement(int);
void AssignValue(int);
void Display(int);
int FindVariable(int);
bool IsChar(int);
void GetInput(int);

int main() {
	const int size = 30; // Number of Characters in File Name
	char file_name[size]; // String that Holds File Name
	
	int line = 1;
	
	string temp;
	
// GET INPUT
	cout << "Mint Green Programming Language" << endl;
	cout << "Developed By CUPRUM[]" << endl << endl;
	
	cout << "Enter the Name of your Mint Green Program: ";
	cin.getline(file_name, size); // Get File Name

// OPEN AND CHECK FILE
	ifstream file; // Create Input File
	file.open(file_name); // Associate File with Input File
	
	if (file.is_open()) { // If File Cannot be Opened
		cout << file_name << " Sucessfuly Found!" << endl << endl;
	} else {
		cout << "FATAL ERROR: COULD NOT OPEN " << file_name << "!" << endl; // Display Error
		file.close();
		exit(EXIT_FAILURE); // Quit
	}

// GET NUMBER OF LINES
	getline(file, temp);
	
	if (temp[0] == '[') {
		for (int i = 1; isdigit(temp[i]); i++)
			isolated += temp[i];
			
		line_number = atoi(isolated.c_str());
	} else {
		cout << "FATAL ERROR AT LINE 1: MUST DECLARE NUMBER OF LINES!" << endl; // Display Error
		file.close();
		exit(EXIT_FAILURE); // Quit
	}
	
// COPY LINES
	program = new string[line_number];
	
	while (getline(file, program[line]))
		line++;
	
	file.close();
	
// DECODE AND RUN EACH LINE
	for (int x = 1; x < line_number; x++) { // Run Through Every Line
		if (program[x][0] == '#') { // Creating Integer
			CreateInt(x);
			goto bottom;
		}
		
		if (program[x][0] == '&') { // Creating Character
			CreateChar(x);
			goto bottom;
		}
		
		if (isalpha(program[x][0])) { // Assigning Value
			AssignValue(x);
			goto bottom;	
		}
		
		if (program[x][0] == '!') { // Display
			Display(x);
			goto bottom;
		}
		
		if (program[x][0] == '@') { // Get Input
			GetInput(x);
			goto bottom;
		}
		
		if (program[x][0] == '?') { // If Statement
			x = IfStatement(x);
			goto bottom;
		}
			
		if (program[x][0] == '>') { // Going Back
			x = GoTo(x);
			goto bottom;
		}
		
		if (program[x][0] == '*') {
			cout << "CHERRY🍒BOMB" << endl;
			goto bottom;
		}
		
		if (program[x][0] == '$') { // End Program
			delete [] program;
			exit(EXIT_SUCCESS);
		}
		
		bottom: cout << ""; // Do Nothing At Bottom
	}		
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int GoTo(int x) {		
	if (isdigit(program[x][2])) { 
		isolated = program[x][2]; // Copy First Digit of GoTo Command
	} else {	
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
	for (int i = 3; isdigit(program[x][i]); i++) // Go Through the Following Digits and Add them to isolated
		isolated += program[x][i];
	
	position = atoi(isolated.c_str()); // Convert isolated into an Integer and Assign it to position
	
	if ((position - 2) < 0 || (position - 2) > line_number) { // Check if Number is Invalid
		cout << "FATAL ERROR AT LINE " << x + 1 << ": INVALID LINE NUMBER!" << endl;
		delete [] program;
		exit(EXIT_FAILURE);
	}

	return(position - 2); // Go Back 2 Because 1 is Added at End of For Loop, and Line Numbers Start at 1
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void GetInput(int x) {
	char input;
	
// FIND VARIABLE BEING REFERENCED
	if (isalpha(program[x][2])) { // Copy First Letter of Character Variable Name
		isolated = program[x][2];
	} else {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
	for (int i = 3; isalpha(program[x][i]); i++) // Copy Each Letter of Character Variable Name
		isolated += program[x][i];
		
	position = FindVariable(x);
	is_char = IsChar(x);

// GET ACTUAL INPUT	
	cin.get(input);

// ASSIGN INPUT TO VARIABLE
	if (is_char) {
		chardex[position].value = input;
	} else {
		intdex[position].value = (int)input - 48;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CreateInt(int x) {
	if (isalpha(program[x][2])) { // Copy First Letter of Create int Name
		isolated = program[x][2];
	} else {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
	for (int i = 3; isalpha(program[x][i]); i++) // Copy Each Letter of int Name
		isolated += program[x][i];
		
	intdex[current_int].name = isolated; // Copy Name to an int struct's Name
	
	current_int++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CreateChar(int x) {
	if (isalpha(program[x][2])) { // Copy First Letter of Create char Name
		isolated = program[x][2];
	} else {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
	for (int i = 3; isalpha(program[x][i]); i++) // Copy Each Letter of char Name
		isolated += program[x][i];
			
	chardex[current_char].name = isolated; // Copy Name to an int struct's Name
	
	current_char++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Display(int x) {
	bool is_char; // is_char is True if Variable is a Character, False if Integer
	bool is_type_found = false; // is_type_found is True if Display Type is Found, False if not
	
	position = 0;
	
// DISPLAY A STRING
	if (program[x][2] == '~') { // If the Display Type is a String
		isolated = program[x][3]; // Copy Down First Character
		
		for (int i = 4; program[x][i] != ')'; i++) // Copy Down the Other Characters
			isolated += program[x][i];
		
		cout << isolated;
		
		is_type_found = true;
	}
	
// DISPLAY NEW LINE
	if (program[x][2] == '^') {
		cout << endl;
		
		is_type_found = true;
	}
	
// DISPLAY A VARIABLE
	if (isalpha(program[x][2])) { // If the Display Type is a Variable
		isolated = program[x][2]; // Copy Down First Character of Variable's Name
		
		for (int i = 3; isalpha(program[x][i]); i++) // Copy Down Other Characters
			isolated += program[x][i];
		
		position = FindVariable(x);
		is_char = IsChar(x);

		if (is_char) { // If Variable is a Character
			cout << chardex[position].value; 		
		} else { // If Variable is an Integer
			cout << intdex[position].value;
		}
		
		is_type_found = true;
	}
	
	if (!is_type_found) {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int IfStatement(int x) {
	int name_size; // Size of Variable's Name
	
	int value; // Value of Variable
	int factor; // Value of Factor
	
	bool is_factor_found = false;
	bool is_operation_found = false;
	
// FIND AND PROCESS VARIABLE
	if (isalpha(program[x][2])) { 
		isolated = program[x][2];
		
		for (int i = 3; isalpha(program[x][i]); i++) // Copy Down Characters
			isolated += program[x][i];
		
		name_size = isolated.length();
		
		position = FindVariable(x);
		is_char = IsChar(x);
		
		if (is_char) {
			value = int(chardex[position].value); // Convert char to int for Easier Comparing
		} else {
			value = intdex[position].value; 
		}
			
	} else {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}

// FIND FACTOR
	if (isdigit(program[x][2 + name_size + 3])) { // If Factor is an Integer
		isolated = program[x][2 + name_size + 3];
		
		for (int i = 1; isdigit(program[x][2 + name_size + 3 + i]); i++) 
			isolated += program[x][2 + name_size + 3 + i];
		
		factor = atoi(isolated.c_str());
		
		is_factor_found = true;
	}
	
	if (program[x][2 + name_size + 3] == '~') { // If Factor is a Character
		isolated = program[x][2 + name_size + 3 + 1];
		
		factor = atoi(isolated.c_str()); // Turn Character in isolated to int
		
		is_factor_found = true;
	}
	
	if (isalpha(program[x][2 + name_size + 3])) { // If Factor is a Variable
		isolated = program[x][2 + name_size + 3];
		
		for (int i = 1; isalpha(program[x][2 + name_size + 3 + i]); i++)
			isolated += program[x][2 + name_size + 3 + i];
		
		position = FindVariable(x);
		is_char = IsChar(x);
		
		if (is_char) {
			factor = int(chardex[position].value); // Convert char to int for Easier Comparing
		} else {
			factor = intdex[position].value;
		}
		
		is_factor_found = true;
	}
	
	if (!is_factor_found) {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
// FIND OPERATION BEING USED
	if (program[x][2 + name_size + 1] == '=') { // If Seeing if factor and value are Equal
		if (!(value == factor)) 
			return(x + 1);
		
		is_operation_found = true;
	}
	
	if (program[x][2 + name_size + 1] == '<') { // If Seeing if value is Less than factor
		if (!(value < factor)) 
			return(x + 1);
		
		is_operation_found = true;
	}
	
	if (program[x][2 + name_size + 1] == '>') { // If Seeing if value is Greater than factor
		if (!(value > factor))
			return(x + 1);
		
		is_operation_found = true;
	}
	
	if (!is_operation_found) {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
	
	return(x);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void AssignValue(int x) {
	bool is_assigned = false;
	
	int reciever_name_size; // Size of Vaiable being Assigned a Value
	
	int reciever; // Variable being Assinged a Value
	int transmitter; // Variable being Used to Find Value of reciever
	
	int transmitter_name_size; // Size of Variable's Name being Used to Find Value of reciever
	int factor; // Integer of Integer Variable being Assigned
	int operation; // Type of Four Operations being Used

// FIND VARIABLE BEING REFERENCED
	if (isalpha(program[x][0])) {
		isolated = program[x][0];

		for (int i = 1; isalpha(program[x][i]); i++) // Copy Down Other Characters
				isolated += program[x][i];
		
		reciever = FindVariable(x);
		is_char = IsChar(x);
		
		if (is_char) {
			reciever_name_size = chardex[reciever].name.length();
		} else {
			reciever_name_size = intdex[reciever].name.length();
		}
	
// ASSIGN IF MAKING VARIABLE EQUAL TO AN INTEGER
		if (isdigit(program[x][reciever_name_size + 3])) {
			isolated = program[x][reciever_name_size + 3];
	
			for (int i = 4; isdigit(program[x][reciever_name_size + i]); i++) // Go Through the Following Digits and Add them to isolated
				isolated += program[x][reciever_name_size + i];
			
			intdex[reciever].value = atoi(isolated.c_str()); // Convert String to Integer and Assign it to a Variable in the intdex
		
			is_assigned = true;
		} 
	
// ASSIGN IF MAKING VARIABLE EQUAL TO A CHARACTER
		if (program[x][reciever_name_size + 3] == '~' && isalpha(program[x][reciever_name_size + 4])) {
			isolated = program[x][reciever_name_size + 4];
			
			chardex[reciever].value = isolated[0]; // Assign Character to a Variable in the chardex
			
			is_assigned = true;
		}
		
// ASSIGN IF MAKING VARIABLE EQUAL TO ANOTHER VARIABLE
		if (isalpha(program[x][reciever_name_size + 3])) {
			isolated = program[x][reciever_name_size + 3];
			
			for (int i = 4; isalpha(program[x][reciever_name_size + i]); i++) // Go Through the Following Characters and Add them to isolated
				isolated += program[x][reciever_name_size + i];
				
			position = FindVariable(x);
			is_char = IsChar(x);
			
			if (is_char) {
				chardex[reciever].value = chardex[transmitter].value;
			} else {
				intdex[reciever].value = intdex[transmitter].value;
			}
			
			is_assigned = true;
		}
		
// ASSIGN IF MAKING VARIABLE EQUAL TO AN EXPRESSION
		if (program[x][reciever_name_size + 3] == '(') {
			if (is_char) { // If Trying to Assign Character Variable to an Mathematic Expression
				cout << "FATAL ERROR AT LINE " << x + 1 << ": CANNOT ASSIGN EXPRESSION TO CHAR!" << endl; // Display Error
				delete [] program;
				exit(EXIT_FAILURE); // Quit
			}
			
			if (isalpha(program[x][reciever_name_size + 4])) { // Find Variable in Expression
				isolated = program[x][reciever_name_size + 4];
			
				for (int i = 5; isalpha(program[x][reciever_name_size + 5]); i++) // Copy Down Other Characters
					isolated += program[x][reciever_name_size + i];
				
				transmitter = intdex[FindVariable(x)].value; // Find Variable in intdex and Copy Value to transmitter
				
			} else {
				cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
				delete [] program;
				exit(EXIT_FAILURE); // Quit
			}
						
			transmitter_name_size = isolated.length();
			
			switch (program[x][reciever_name_size + 4 + transmitter_name_size + 1]) { // Find which Operation is being Used
				case '+':
					operation = 1;
					break;
				case '-':
					operation = 2;
					break;
				case '*':
					operation = 3;
					break;
				case '/':
					operation = 4;
					break;
				default:
					cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER OPERATOR!" << endl; // Display Error
					delete [] program;
					exit(EXIT_FAILURE); // Quit
			}
			
			if (isdigit(program[x][reciever_name_size + 4 + transmitter_name_size + 3])) { // If factor is a Constant Number
				isolated = program[x][reciever_name_size + 4 + transmitter_name_size + 3];
				
				for (int i = 4; isdigit(program[x][reciever_name_size + 4 + transmitter_name_size + i]); i++) // Copy Down Other Characters
					isolated += program[x][reciever_name_size + i + transmitter_name_size + i];
					
				factor = atoi(isolated.c_str()); // Turn String to Integer and Copy it to Factor
			} else {
				if (isalpha(program[x][reciever_name_size + 4 + transmitter_name_size + 3])) { // If factor is a Variable
					isolated = program[x][reciever_name_size + 4 + transmitter_name_size + 3];
					
					for (int i = 5; isalpha(program[x][reciever_name_size + i + transmitter_name_size + 3]); i++) // Copy Down Other Characters
						isolated += program[x][reciever_name_size + i + transmitter_name_size + 3];
					
					is_char = IsChar(x);
					
					factor = intdex[FindVariable(x)].value; // Copy Down Value of Variable to Factor
					
					if (is_char) {
						cout << "FATAL ERROR AT LINE " << x + 1 << ": CANNOT USE CHAR IN EXPRESSION!" << endl; // Display Error
						delete [] program;
						exit(EXIT_FAILURE); // Quit
					}
				} else {
					cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
					delete [] program;
					exit(EXIT_FAILURE); // Quit
				}
			}
			
			switch (operation) { // Do Operation Based on Operator
				case 1:
					intdex[reciever].value = transmitter + factor;
					break;
				case 2:
					intdex[reciever].value = transmitter - factor;
					break;
				case 3:
					intdex[reciever].value = transmitter * factor;
					break;
				case 4:
					intdex[reciever].value = transmitter / factor;
					break;
				default:
					cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER OPERATOR!" << endl; // Display Error
					delete [] program;
					exit(EXIT_FAILURE); // Quit
			}
			
			is_assigned = true;
		}
		
		if (!is_assigned) {
			cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER VALUE!" << endl; // Display Error
			delete [] program;
			exit(EXIT_FAILURE); // Quit
		}
		
	} else {
		cout << "FATAL ERROR AT LINE " << x + 1 << ": IMPROPER SYNTAX!" << endl; // Display Error
		delete [] program;
		exit(EXIT_FAILURE); // Quit
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int FindVariable(int x) {
	int pos = 0;
	
	char_top: cout << ""; 
	
	if (isolated != chardex[pos].name) { // If Variable not Found, Search through chardex
		if (pos > (current_char - 1)) { // If Searched Through All Initialized Variables in chardex
			pos = 0;
			
			int_top: cout << ""; 	
			
			if (isolated != intdex[pos].name) { // Search through intdex
				if (pos > (current_int - 1)) { // If Searched through All Initialized Variables in intdex and chardex
					cout << "FATAL ERROR AT LINE " << x + 1 << ": CAN NOT FIND VARIABLE!" << endl; // Display Error
					delete [] program;
					exit(EXIT_FAILURE); // Quit
				}
				
				pos++; // Add One to Number
				goto int_top; // Search through Next Variable in intdex
				
			} else {
				goto done; // If Variable Found, Leave if Statement
			}
		} 
		
		pos++; // Add One to Number
		goto char_top; // Search through Next Variable in chardex
	}
	
	done: cout << "";
	
	return(pos);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool IsChar(int x) {
	int pos = 0;
	
	bool is_char;
	
	char_top: cout << ""; 
	
	if (isolated != chardex[pos].name) { // If Variable not Found, Search through chardex
		if (pos > (current_char - 1)) { // If Searched through All Initialized Variables in chardex
			pos = 0;
			
			int_top: cout << ""; 	
			
			if (isolated != intdex[pos].name) { // Search through intdex
				if (pos > (current_int - 1)) { // If Searched through All Initialized Variables in intdex and chardex
					cout << "FATAL ERROR AT LINE " << x + 1 << ": CAN NOT FIND VARIABLE!" << endl; // Display Error
					delete [] program;
					exit(EXIT_FAILURE); // Quit
				}
				
				pos++; // Add One to Number
				goto int_top; // Search through Next Variable in intdex
				
			} else {
				goto done; // If Variable Found, Leave if Statement
			}
		} 
		pos++; // Add One to Number
		goto char_top; // Search through Next Variable in chardex
	}
	
	done: cout << "";
	
	if (isolated == chardex[pos].name) {
		is_char = true;
	} else {
		is_char = false;
	}
	
	return(is_char);
}

/*
Mint Green Programming Language
	Math:
		/, divide: x / 6
		*, multiply: y * 4
		+, add: x + 2
		-, subtract: x - 2
		>, greater than: ?(x > y)
		<, less than: ?(x < y)
		(), assign varaible to expression: x = (y + 3)
		
	Variable:
		&, character variable: & x
		#, positive integer variable: # y
		
	Basic:
		[], number of lines: [3]
		!(), display: !(2)
		@(), get input: @(x)
		^, new line: !(^)
		=, equals: x = 2
		>, go back to: > 0
		=, compare if equal: ?(x = y)
		?(), if statement: ?(x = y)
		~, not a variable: x = ~a, !(~mint green)
		$, end program: $
*/















