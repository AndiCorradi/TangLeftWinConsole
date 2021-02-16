#include <iostream>
#include <time.h>
#include <string>
#include <conio.h> // req for_get(ch)
#include <iomanip>

using namespace std;

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


int main()

{
	while (escape != 27)
	{
		PayDay = UserInputPayDay(); // Get UserInput
		Balance = UserInputBalance(); // Get UserInput
		DaysToPayday = CalcDaysToPayday(PayDay); // Calculate Days to Payday
		DailyBudget = CalculateDailyBudget(Balance, DaysToPayday); // Calculate daily budget
		ResultConsoleOutput(); // Result Console Output
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the Input Buffer
		escape = _getch(); // returns ASCI value of a keypress to decide if the while loop should run again
	}

	return 0;
}

// Console Banner

void ConsoleBanner()

{
	system("cls");
	cout << "====================TangLeft====================" << endl;
	cout << " (calculates the daily budget until nex payday) " << endl;
	cout << "================================================" << endl;
	cout << endl;
}

//{
//	system("cls");
//	cout << "====================TangLeft====================" << endl;
//	cout << " (calculates the daily budget until nex payday) " << endl;
//	cout << "================================================" << endl;
//	cout << endl;
//}

// UserInput

int UserInputPayDay()
{
	InputPayDay:
	int AmmountDaysOfCurrentMonth = AmmountOfDaysOfCurrentMonth();
	int CurrentDayOfMonth = CalcCurrentDaysOfMonth();
	ConsoleBanner();
	cout << "enter your payday [default = 24.]: ";
	getline(cin, PayDayStr);
	if (PayDayStr.size() == 0)
	{
		PayDayStr = "24";
	}
	try
	{
		PayDay = stoi(PayDayStr);
	}
	catch (exception& err)
	{
		ConsoleBanner();
		cout << "\ninvalid input. Please enter the payday as number\n\n(press Enter to continue)";
		getchar();
		goto InputPayDay;
	}

	if (PayDay < 1 || PayDay > 31)
	{
		ConsoleBanner();
		cout << "\n" << "invalid input. Please enter the payday as number >1 <31\n\n(press Enter to continue)";
		getchar();
		goto InputPayDay;
	}

	else if (PayDay > AmmountDaysOfCurrentMonth)
	{
		ConsoleBanner();
		cout << "\n" << "This Month has less days than your input. Please enter again.\n\n(press Enter to continue)";
		getchar();
		goto InputPayDay;
	}
	else if (PayDay == CurrentDayOfMonth)
	{
		ConsoleBanner();
		cout << "\n" << "Payday can't be current date.\nPlease try again tomorrow\n\n(press Enter to Exit)";
		getchar();
		exit(0);
		//goto InputPayDay;
	}
	

	return PayDay;
}

int UserInputBalance()
{
	InputBalance:
	ConsoleBanner();
	cout << "enter your balance: ";
	cin >> Balance;
	if (cin.fail())
	{
		ConsoleBanner();
		cin.clear();
		cout << "Input invalid. Please enter a positive number.\n\n(press Enter to continue)";
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the Input Buffer
		getchar();
		goto InputBalance;
		
	}
	else
	{
		if (Balance < 1)
		{
			ConsoleBanner();
			cout << "Balance can't be below 1 for this calculation.\nPlease enter again.\n\n(press Enter to continue)";
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the Input Buffer
			getchar();
			goto InputBalance;
		}

	}

	return Balance;
}

// Calculate Days to Payday

int CalcDaysToPayday(int Payday)
{
	// Calculate Days to Payday

	int DayOfMonth = CalcCurrentDaysOfMonth();
	int AmmountDaysOfCurrentMonth = AmmountOfDaysOfCurrentMonth();

	if (DayOfMonth < 24)
	{
		DaysToPayday = PayDay - DayOfMonth;
	}
	else
	{
		DaysToPayday = AmmountDaysOfCurrentMonth - DayOfMonth + 24;
	}

	return DaysToPayday;
}

// Calculate Daily Busget

int CalculateDailyBudget(int Balance, int DaysToPayday)
{
DailyBudget = Balance / DaysToPayday;

return DailyBudget;
}

// Result Console Output

void ResultConsoleOutput()

{
	ConsoleBanner();
	cout << "   your daily budget until next payday: " << DailyBudget << "\n" <<endl;
	cout << setw(18) << DaysToPayday << " days to go" << endl;
	cout << endl;
	cout << "   Esc to Exit or anykey to restart programm" << endl;
}

int AmmountOfDaysOfCurrentMonth()
{
	// ammount of days current month (with LeapYear Detection)

	struct tm nowlocal;
	time_t now;
	now = time(0);
	nowlocal = *localtime(&now);
	int currentMonth = nowlocal.tm_mon + 1;
	int currentYear = nowlocal.tm_year + 1900;
	int DaysOfMonthsLeap[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int DaysOfMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int AmmountDaysOfCurrentMonth(0);

	if (currentYear % 4 == 0) // detect LeapYear
	{
		AmmountDaysOfCurrentMonth = DaysOfMonthsLeap[currentMonth - 1];

	}
	else
	{
		AmmountDaysOfCurrentMonth = DaysOfMonths[currentMonth - 1];

	}

	return AmmountDaysOfCurrentMonth;
}

int CalcCurrentDaysOfMonth()
{
	// current Day of the month

	struct tm nowlocal;
	time_t now;
	now = time(0);
	nowlocal = *localtime(&now);
	int DayOfMonth = nowlocal.tm_mday;

	return DayOfMonth;
}