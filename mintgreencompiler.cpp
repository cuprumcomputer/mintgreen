// Mint Green Programming Languge Compiler
// Developed By CUPRUM[]

#include <iostream>
#include <fstream>

using namespace std;

extern "C" { 
	void * __dso_handle = NULL;
}

static string * program;
int line_number;

string isolated;
int position;

int current_int;
int current_char;

bool type;

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

void CreateInt(int);
void CreateChar(int);
int GoTo(int);
int IfStatement(int);
void AssignValue(int);
void Display(int);
int FindPosition(int);
bool FindType(int);
void GetInput(int);

int main() {
	const int NAME_SIZE = 100; // Number of Characters in File Name
	char file_name[NAME_SIZE]; // String that Holds File Name
	
	current_int = 0;
	current_char = 0;
	
	string temp;
	
// GET INPUT
	cout << "Mint Green Programming Language Compiler" << endl;
	cout << "Developed By CUPRUM[]" << endl << endl;
	
	cout << "Enter the Name of your Mint Green Program: ";
	cin.getline(file_name, NAME_SIZE); // Get File Name

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
			
		line_number = stoi(isolated);
	} else {
		cout << "FATAL ERROR AT LINE 1: MUST DECLARE NUMBER OF LINES!" << endl; // Display Error
		file.close();
		exit(EXIT_FAILURE); // Quit
	}
		
// COPY LINES
	program = new string[line_number];
	
	for (int i = 1; i < line_number; i++)
		getline(file, program[i]);

	file.close();
		
// DECODE AND RUN EACH LINE
	for (int x = 1; x < line_number; x++) { // Run Through Every Line
		switch (program[x][0]) {
			case '#': // Creating Integer
				CreateInt(x);
			break;
			
			case '&': // Creating Character
				CreateChar(x);
			break;
			
			case '!': // Display
				Display(x);
			break;
				
			case '@': // Get Input
				GetInput(x);
			break;
				
			case '?': // If Statement
				x = IfStatement(x);
			break;
			
			case '>': // Going Back
				x = GoTo(x);
			break;
					
			case '$': // End Program
				delete [] program;
				exit(EXIT_SUCCESS);
			break;
			
			default:
				if (isalpha(program[x][0])) // Assigning Value
					AssignValue(x);
		}
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
	
	position = stoi(isolated); // Convert isolated into an Integer and Assign it to position
	
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
		
	position = FindPosition(x);
	type = FindType(x);

// GET INPUT	
	cin.get(input);

// ASSIGN INPUT TO VARIABLE
	if (type) {
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
	bool type; // type is True if Variable is a Character, False if Integer
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
		
		position = FindPosition(x);
		type = FindType(x);

		if (type) { // If Variable is a Character
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
	
	char isolated_char; // Used Instead of isolated so it can be Typecast into Integer
	
// FIND AND PROCESS VARIABLE
	if (isalpha(program[x][2])) { 
		isolated = program[x][2];
		
		for (int i = 3; isalpha(program[x][i]); i++) // Copy Down Characters
			isolated += program[x][i];
		
		name_size = isolated.length();
		
		position = FindPosition(x);
		type = FindType(x);
		
		if (type) {
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
		
		factor = stoi(isolated);
		
		is_factor_found = true;
	}
	
	if (program[x][2 + name_size + 3] == '~') { // If Factor is a Character
		isolated_char = program[x][2 + name_size + 3 + 1];
		
		factor = int(isolated_char); // Turn Character in isolated to int
		
		is_factor_found = true;
	}
	
	if (isalpha(program[x][2 + name_size + 3])) { // If Factor is a Variable
		isolated = program[x][2 + name_size + 3];
		
		for (int i = 1; isalpha(program[x][2 + name_size + 3 + i]); i++)
			isolated += program[x][2 + name_size + 3 + i];
		
		position = FindPosition(x);
		type = FindType(x);
		
		if (type) {
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
	
	int reciever; // Variable being Assinged a Value
	int transmitter; // Variable being Used to Find Value of reciever
	
	int reciever_name_size; // Size of Vaiable being Assigned a Value
	int transmitter_name_size; // Size of Variable's Name being Used to Find Value of reciever
	
	int factor; // Integer of Integer Variable being Assigned
	int operation; // Type of Four Operations being Used

// FIND VARIABLE BEING REFERENCED
	if (isalpha(program[x][0])) {
		isolated = program[x][0];

		for (int i = 1; isalpha(program[x][i]); i++) // Copy Down Other Characters
				isolated += program[x][i];
		
		reciever = FindPosition(x);
		type = FindType(x);
		
		if (type) {
			reciever_name_size = chardex[reciever].name.length();
		} else {
			reciever_name_size = intdex[reciever].name.length();
		}
	
	
// ASSIGN IF MAKING VARIABLE EQUAL TO AN INTEGER
		if (isdigit(program[x][reciever_name_size + 3])) {
			isolated = program[x][reciever_name_size + 3];
	
			for (int i = 4; isdigit(program[x][reciever_name_size + i]); i++) // Go Through the Following Digits and Add them to isolated
				isolated += program[x][reciever_name_size + i];
			
			intdex[reciever].value = stoi(isolated); // Convert String to Integer and Assign it to a Variable in the intdex
		
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
				
			position = FindPosition(x);
			type = FindType(x);
			
			if (type) {
				chardex[reciever].value = chardex[transmitter].value;
			} else {
				intdex[reciever].value = intdex[transmitter].value;
			}
			
			is_assigned = true;
		}
		
// ASSIGN IF MAKING VARIABLE EQUAL TO AN EXPRESSION
		if (program[x][reciever_name_size + 3] == '(') {
			if (type) { // If Trying to Assign Character Variable to an Mathematic Expression
				cout << "FATAL ERROR AT LINE " << x + 1 << ": CANNOT ASSIGN EXPRESSION TO CHAR!" << endl; // Display Error
				delete [] program;
				exit(EXIT_FAILURE); // Quit
			}
			
			if (isalpha(program[x][reciever_name_size + 4])) { // Find Variable in Expression
				isolated = program[x][reciever_name_size + 4];
			
				for (int i = 5; isalpha(program[x][reciever_name_size + 5]); i++) // Copy Down Other Characters
					isolated += program[x][reciever_name_size + i];
				
				transmitter = intdex[FindPosition(x)].value; // Find Variable in intdex and Copy Value to transmitter
				
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
					
				factor = stoi(isolated); // Turn String to Integer and Copy it to Factor
			} else {
				if (isalpha(program[x][reciever_name_size + 4 + transmitter_name_size + 3])) { // If factor is a Variable
					isolated = program[x][reciever_name_size + 4 + transmitter_name_size + 3];
					
					for (int i = 5; isalpha(program[x][reciever_name_size + i + transmitter_name_size + 3]); i++) // Copy Down Other Characters
						isolated += program[x][reciever_name_size + i + transmitter_name_size + 3];
					
					type = FindType(x);
					
					factor = intdex[FindPosition(x)].value; // Copy Down Value of Variable to Factor
					
					if (type) {
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
int FindPosition(int x) {
	for (int i = 0; i < VARIABLE_NUMBER; i++) { // Go Through chardex and intdex to Return True If Variable is Found
		if(isolated == chardex[i].name || isolated == intdex[i].name)
			return(i);
	}
	
	cout << "FATAL ERROR AT LINE " << x + 1 << ": CAN NOT FIND VARIABLE!" << endl; // Display Error
	delete [] program;
	exit(EXIT_FAILURE); // Quit
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool FindType(int x) {
	for (int i = 0; i < VARIABLE_NUMBER; i++) { // Go Through chardex and Return true If Variable is Found
		if(isolated == chardex[i].name)
			return(true);
	}
	
	for (int i = 0; i < VARIABLE_NUMBER; i++) { // Go Through intdex and Return True If Variable is Found
		if(isolated == intdex[i].name) 
			return(false);
	}
	
	cout << "FATAL ERROR AT LINE " << x + 1 << ": CAN NOT FIND VARIABLE!" << endl; // Display Error
	delete [] program;
	exit(EXIT_FAILURE); // Quit
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
*/















