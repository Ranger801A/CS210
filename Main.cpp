/*
John Hanks
CS 210: 7-1 Project Three
10/17/2021
This is the program for the Corner Grocer project.  The user
will be be presented with menu options.  Depending on the choice
the code will either call a Python Function to complete
the task and return to the C++ code or use a file created
with the Python code.
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
This function will call the Python function.  In this program
the menu will be called. The code was provide by the starter
code. No changes were done to this block of code.
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
This function will call the Python function.  In this program
the menu will be called. The code was provide by the starter
code. No changes were done to this block of code.
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}
/*This function creates the histogram in C++.  This function
will open the "dat" file created by the call of the Python
function. */
void PrintHistorgram() {
	ifstream inFS; // Define the file input
	string produceName; //String for the produce names
	int frequencyProduce; // Define the frequency of the produce

	/* This section is opening of the frequency.dat file
	and checking that it opened.  The program will let the user know
	if the file opened or not.
	*/
	inFS.open("frequency.dat"); // opens frequency.dat file
	if (!inFS.is_open()) { // IF/ELSE statement to check file opened correctly
		cout << "Could not open file frequency.dat" << endl;
	}
	else {
		cout << endl;
	}
	cout << "Produce Histogram for Today's Purchases" << endl;
	cout << endl;
	while (!inFS.eof()) {
		inFS >> produceName; // reading the produce items from frequency.dat
		inFS >> frequencyProduce; // reading the frequency (integer) from frequency.dat
		cout << right;
		cout << setw(15) << produceName <<  " --> "; // displays the produce item
		//This creates a loop to add "*" for the frequency the produce item was purchased.
		//For example, a frequency of 5 will loop 5 time printing "*" on each pass.
		for (int i = 0; i < frequencyProduce; ++i) {
			cout << "*";
		}
		cout << endl;

	}
	cout << endl;
	inFS.close(); // closing frequency.dat
	cout << "End of Histogram File" << endl;
}

void main()
{
	/* This the main function for the program.  The user will be
	given 4 menu options.  The options will either call a 
	Python function and return the the C++ code.  Or it will
	call the C++ function.  Or will quit the program.
	*/

	int menuChoice; // variable for the user's menu
	bool runProgram; // variable for the while loop
	string userItem; // variable for the user's number input
	int returnValue; // variable for the value returned from Python for menu option 2

	runProgram = true;

	while (runProgram == true) { // The code will run until option 4 is selected by user
		system("Color 02"); // Change color to green on black
		CallProcedure("PrintMenu"); // Call to the Python function to display the menu
		cout << "Enter selection here: ";
		cin >> menuChoice; // Inputting the user's choice
		/* Use of switch to output base on user's menu choice.
		Default set to return user error and ask for the user
		to choose again.
		*/
		switch (menuChoice) {
		case 1:
			cout << endl;
			cout << "#################################" << endl;
			cout << endl;
			CallProcedure("GroceryListFreq"); //Calls the Python function to print table
			cout << endl;
			cout << "#################################" << endl;
			cout << endl;
			break;
		case 2:
			cout << endl;
			cout << "#################################" << endl;
			cout << endl;
			cout << "Which specific item would you like daily purchase number?" << endl;
			cout << endl;
			cout << "Type specific item here: ";
			cin >> userItem; // Inputs user's produc item choice to be displayed
			cout << endl;
			returnValue = callIntFunc("GroceryItemFreq", userItem); // Calling of the Python function for a single item.
			
																	/* This IF/ELSE statement will print the correct statement to user depending on if the item was 
			purchased or not in the day.  The return value of -1 from the Python code if the item was not
			purchased in the day
			*/

			if (returnValue != -1) {
				cout << ">>>Today the items, " << userItem << ", were purchased " << returnValue << " time(s).<<<" << endl; // Displays the produce item and frequency to user
				cout << endl;
				cout << "#################################" << endl;
				cout << endl;
			}
			else {
				cout << "Sorry, there were no " << userItem << " purchased today." << endl; // Else statement if produce item not found.
				cout << endl;
				cout << "#################################" << endl;
				cout << endl;
			}
			break;
		case 3:
			cout << endl;
			cout << "#################################" << endl;
			CallProcedure("GrocerHistogram"); // Overrides the function to call the Python code
			PrintHistorgram(); // Calls the C++ function to print the historgame
			cout << "#################################" << endl;
			cout << endl;
			break;
		case 4: // Option 4 will quit the program
			cout << endl;
			cout << endl;
			system("Color 0C"); // Changes the color to red on black, noting the program end
			cout << "#################################" << endl;
			cout << "_________________________________" << endl;
			cout << endl;
			cout << setw(20) << "Good-bye!" << endl;
			cout << setw(21) << "Come Again!" << endl;
			cout << "_________________________________" << endl;
			cout << endl;
			cout << "#################################" << endl;
			cout << endl;
			cout << endl;
			runProgram = false; // Ends WHILE loop
			break;
		default: // Default output for invalid user choice.
			cout << endl;
			cout << "#################################" << endl;
			cout << "Not a valid input. Try Again" << endl;
			cin.clear();
			cin.ignore(50, '\n');
			cout << "#################################" << endl;
			cout << endl;

		}

	}

}