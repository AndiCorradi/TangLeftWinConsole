// this console programm calculates the daily budget left until next payday based on your balance and payday input.
// Version: 1.2
// author: andi@corradi.ch release Date: 16.feb 2021

// Load header files

#include <iostream> // req. for cout (Console output)
#include <time.h> // req. to calculate "AmmountOfDaysOfCurrentMonth" and "CalcCurrentDaysOfMonth"
#include <string> // req. for getline (read userinput as string)
#include <conio.h> // req. for_get(ch) (returns ASCI int value of a keypress 
#include <iomanip> // req. to format console output (setw)

using namespace std; // define standard namespace

// declare variables

string PayDayStr("24");
int Balance(0);
int PayDay(0);
int DaysToPayday(0);
int DailyBudget(0);
char escape;

// declare funktion prototypes

void ConsoleBanner();
int UserInputPayDay();
int UserInputBalance();
int CalcDaysToPayday(int);
int CalculateDailyBudget(int, int);
void ResultConsoleOutput();
int AmmountOfDaysOfCurrentMonth();
int CalcCurrentDaysOfMonth();


int main() // main programm entry point

{
	while (escape != 27) // while loop to keep the programm repeat itself until escape keypress is detected at the end of the loop
	{
		PayDay = UserInputPayDay(); // Get UserInput
		Balance = UserInputBalance(); // Get UserInput
		DaysToPayday = CalcDaysToPayday(PayDay); // Calculate Days to Payday
		DailyBudget = CalculateDailyBudget(Balance, DaysToPayday); // Calculate daily budget
		ResultConsoleOutput(); // Result Console Output
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the Input Buffer
		escape = _getch(); // returns ASCI Int value of a keypress to decide if the while loop should run again
	}
}

// Console Banner

void ConsoleBanner() // void function with no return and no input parameters

{
	system("cls"); // clear console ("cls" is dedicated to windows, change to "clear" for Linux)
	cout << "====================TangLeft====================" << endl; //console output
	cout << " (calculates the daily budget until nex payday) " << endl;
	cout << "================================================" << endl;
	cout << endl;
}

// UserInput

int UserInputPayDay() // datatype integer function without input parameters 
{
	InputPayDay: // goto marker
	int AmmountDaysOfCurrentMonth = AmmountOfDaysOfCurrentMonth(); //call function "AmmountOfDaysOfCurrentMonth" and define and initialze local variable
	int CurrentDayOfMonth = CalcCurrentDaysOfMonth(); // call function "CalcCurrentDayOfMonth" and define and initialize local variable
	ConsoleBanner(); // call void function
	cout << "enter your payday [default = 24.]: "; //console output
	getline(cin, PayDayStr); // get input as string and store in variable "PayDayStr".
	if (PayDayStr.size() == 0) //check if the user did not input anything.
	{
		PayDayStr = "24"; //if so, fill variable with string "24" (default value implementation)
	}
	try // user input error handling: try if the string can convert to int 
	{
		PayDay = stoi(PayDayStr); // convert string to int (int needed for calculation)
	}
	catch (exception& err) // if it fails, proceed with console output to inform user.
	{
		ConsoleBanner(); // call void function
		cout << "\ninvalid input. Please enter the payday as number\n\n(press Enter to continue)"; // console output
		getchar(); // wait for user press any key before proceed
		goto InputPayDay; // go to marker InputPayDay to repeat user input
	}

	if (PayDay < 1 || PayDay > 31) // user input error handling: check if PayDay is a vaild date
	{
		ConsoleBanner(); // call void function
		cout << "\n" << "invalid input. Please enter the payday as number >1 <31\n\n(press Enter to continue)"; // console output
		getchar(); // wait for user press any key before proceed
		goto InputPayDay; // go to marker InputPayDay to repeat user input
	}

	else if (PayDay > AmmountDaysOfCurrentMonth) // user input error handling: check if the date is within range of current month
	{
		ConsoleBanner(); // call void function
		cout << "\n" << "This Month has less days than your input. Please enter again.\n\n(press Enter to continue)"; // console output
		getchar(); // wati for user press any key before proceed
		goto InputPayDay; // go to marker InputPayDay to repeat user input
	}
	else if (PayDay == CurrentDayOfMonth) // user input error handilng: check if payday is current date (Division / 0 is not allowed)
	{
		ConsoleBanner(); // call void function
		cout << "\n" << "Payday can't be current date.\nPlease try again tomorrow\n\n(press Enter to Exit)"; // console output
		getchar(); // wait for user press any key before proceed
		exit(0); // stop the programm
	}
	
	return PayDay; // return result PayDay to Main function
}

int UserInputBalance() // datatype integer function without argument
{
	InputBalance: // goto marker
	ConsoleBanner(); // call void function
	cout << "enter your balance: "; // console output
	cin >> Balance; // get input as integer and store it in variable Balance
	if (cin.fail()) // user input error handilng. Check if input is an integer 
	{
		ConsoleBanner(); // call void function
		cin.clear(); // clears the error flag on cin (needed to re run user input)
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the whole Input Buffer (needed to re-run user input, without programm will crash in loop)
		cout << "Input invalid. Please enter a positive number.\n\n(press Enter to continue)"; // console output
		getchar(); // wait for user press any key berfore proceed
		goto InputBalance; // go to marker InputBalance to re-run user input
		
	}
	else // if input is an integer, proceed
	{
		if (Balance < 1) // user input error handling: check if input is below 1
		{
			ConsoleBanner(); // call void function
			cout << "Balance can't be below 1 for this calculation.\nPlease enter again.\n\n(press Enter to continue)"; // console output
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the whole Input Buffer (needed to re-run user input, without programm will crash in loop)
			getchar(); // wait for user press any key before proceed
			goto InputBalance; // goto marker InputBalance to re-run user input
		}

	}

	return Balance; // returns the user input to main function
}

// Calculate Days to Payday

int CalcDaysToPayday(int Payday) // integer function with argument (integer parameter)
{
	// Calculate Days to Payday

	int DayOfMonth = CalcCurrentDaysOfMonth(); // set and initialize local variable with result of function "CalcCurrentDayOfMonth"
	int AmmountDaysOfCurrentMonth = AmmountOfDaysOfCurrentMonth(); //set and initialize local variable with result of function "AmmountOfDaysOfCurrentMonth"

	if (DayOfMonth < 24) // check if DayOfMonth is below 24
	{
		DaysToPayday = PayDay - DayOfMonth; // subtract DayOfMonth from PayDay to get DaysToPayDay
	}
	else // if DayOfMonth is higher then 24:
	{
		DaysToPayday = AmmountDaysOfCurrentMonth - DayOfMonth + 24; // subtract DayOfMonth from AmmountDaysOfCurrentMonth and add 24 to ger DaysToPayday
	}

	return DaysToPayday; // returns the result to the main function
}

// Calculate Daily Budget

int CalculateDailyBudget(int Balance, int DaysToPayday) // datatype integer function with argument (2 integer parameters)
{
DailyBudget = Balance / DaysToPayday; // divide Balance thrue DaysToPayday to get the daily budget until payday

return DailyBudget; // returns the result to main function.
}

// Result Console Output

void ResultConsoleOutput() // console output to present the result

{
	ConsoleBanner(); // call void function
	cout << "   your daily budget until next payday: " << DailyBudget << "\n" <<endl; //console output
	cout << setw(18) << DaysToPayday << " days to go" << endl; // use setw() to tab text
	cout << endl;
	cout << "   Esc to Exit or anykey to restart programm" << endl;
}

int AmmountOfDaysOfCurrentMonth() // datatype integer function without argument
{
	// ammount of days current month (with LeapYear Detection)

	struct tm nowlocal; // set variable/instance "nowlocal" using the predefined structure "tm" as defined in time.h
	time_t now; // set variable now: datatype "time_t" (as defined in "time.h")
	now = time(0); // initialize variable now with "time(0)" The function "time(0) delivers passed seconds since 1.1.1970
	nowlocal = *localtime(&now); // functionpointer that converts calendartime to localtime Parameter (&now) = pointer to memory address of the variable now (& = Addressoperator)
	int currentMonth = nowlocal.tm_mon + 1; //set and initialize variable with structure.datafield "month" and add 1 as the month start with 0
	int currentYear = nowlocal.tm_year + 1900; // set and initialize variable with structure.datafield "tm_year" and add +1900 to get the right year
	int DaysOfMonthsLeap[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // set and initialize array with ammount of days for every month of a leap year
	int DaysOfMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // set and initialize array with ammount of days for every month of a regular year
	int AmmountDaysOfCurrentMonth(0); // set and initialize variable

	if (currentYear % 4 == 0) // detect LeapYear
	{
		AmmountDaysOfCurrentMonth = DaysOfMonthsLeap[currentMonth - 1]; // set and initialize variable in leap year

	}
	else //if it is a regular year:
	{
		AmmountDaysOfCurrentMonth = DaysOfMonths[currentMonth - 1]; // set and initialize variable for a regular year

	}

	return AmmountDaysOfCurrentMonth; // returns the result to the main method
}

int CalcCurrentDaysOfMonth() // datatype integer function without argument
{
	// current Day of the month

	struct tm nowlocal; // set variable/instance "nowlocal" using the predefined structure "tm" as defined in time.h
	time_t now; // set variable now: datatype "time_t" (as defined in "time.h")
	now = time(0); // initialize variable now with "time(0)" The function "time(0) delivers passed seconds since 1.1.1970
	nowlocal = *localtime(&now); // functionpointer that converts calendartime to localtime Parameter (&now) = pointer to memory address of the variable now (& = Addressoperator)
	int DayOfMonth = nowlocal.tm_mday; // set and initialize variable with structure.datafield "tm_mday" (current day of the month)

	return DayOfMonth; // returns the result to the main method
}