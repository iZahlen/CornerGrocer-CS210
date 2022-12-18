/*
* Author: Zahlen A.M. Jubilee
* Date Dec 11, 2022
*
* Write what program does here later numbers, if you remember lmao.
*
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python_modules.my_module");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
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
	pName = PyUnicode_FromString((char*)"python_modules.my_module");
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

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_modules.my_module");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
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


	return _PyLong_AsInt(presult);
}

/*
* Description:
*	Main driver of the program -
*	Display's Menu, prompts user for inputs, 
*	and calls python functions to execute requested actions.
*/
void menu()
{
	// Initialize all variables that will be needed.
	string foodItem;
	int tot = 0;
	int menuNavigation;

	// Boolean variables for exiting the loop and input validation.
	bool isFinished = false;
	bool validInput;

	cout << endl;
	cout << "What can I do for ya?" << endl;

	do // Do-While main loop.
	{
		cout << "____________________________________________________________________________________" << endl;
		cout << endl;
		cout << "1. Display list of all items purchased today and their respective amounts" << endl;
		cout << "2. Display how many times a given product was purchased today" << endl;
		cout << "3. Dislpay histogram of all items purchased today and their respective amounts" << endl;
		cout << "4. Exit" << endl;
		cout << "____________________________________________________________________________________" << endl;
		cout << endl;

		try // Input Validation (checks if input is an integer)
		{
			cin >> menuNavigation;
			while (std::cin.fail()) 
			{
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Invalid Entry. Please Try Again." << endl;

				cout << "I only accept numbers as valid options." << endl;
				std::cin >> menuNavigation;
				cout << endl;
			}
			if (menuNavigation >= 0) // More Input Validation (checks for positive integers)
			{ 
				validInput = true;
			}
			else
			{
				throw (menuNavigation);
			}
		}
		catch (...)
		{
			cout << "I only accept 1-4 as options!" << endl;
		}

		switch (menuNavigation) // Switch c case for the menu options. 
		{
		default:
			// Default catch for invalid options (numbers greater than 4)
			cout << "I only accept 1-4 as options!" << endl;
			cout << "Please try again." << endl;
			cout << endl;
			break;

		case 1:
			system("cls");
			cout << "Sure thing! Here's a list of all items purchased today with their respective quantities on the right." << endl;
			system("pause");
			CallProcedure("read_File");
			
			cout << endl;
			cout << "Do you need anything else?" << endl;
			break;

		case 2:
			system("cls");
			cout << "Sure thing. Which item would you like to view today?" << endl;
			cin >> foodItem;

			tot = callIntFunc("locate_Total_Product_Amount", foodItem);
			// Check for if item exists in the database.
			if (tot == -1)
			{
				cout << endl;
				cout << "The item could not be located within the data file. Make sure input is correct." << endl;
			}
			else
			{
				cout << endl;
				cout << "There were a total of " << tot << " " << foodItem << " sold today." << endl;
			}

			cout << endl;
			cout << "Can I do anything else for you?" << endl;
			break;

		case 3:
			system("cls");
			cout << "Coming right up!" << endl;
			cout << "Here's your histogram!" << endl;
			system("pause");
			CallProcedure("read_AND_Write_File");

			cout << "How else may I help you today?" << endl;
			break;

		case 4:

			system("cls");
			cout << endl;
			cout << "Thanks for using me! Enjoy the rest of your day!" << endl;
			isFinished = true;
			break;
		}
	} while (isFinished == false);
}

int main()
{
	menu();
	return 0;
}