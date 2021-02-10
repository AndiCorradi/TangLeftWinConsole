#include <iostream>
#include <time.h>
#include <string>

using namespace std;

int main()

{
	// declare Variables

	int Balance(0);
	string PayDayStr;
	PayDayStr = "24";
	int PayDay(0);

	// User Interface

	cout << "====================TangLeft====================" << endl;
	cout << " (calculates the daily budget until nex payday) " << endl;
	cout << "================================================" << endl;
	cout << endl;
	cout << "enter your payday [default = 24.]: ";
	getline(cin, PayDayStr);
	if (PayDayStr.size() == 0)
	{
		PayDayStr = "24";
	}
	PayDay = stoi(PayDayStr);
	system("cls");
	cout << "====================TangLeft====================" << endl;
	cout << " (calculates the daily budget until nex payday) " << endl;
	cout << "================================================" << endl;
	cout << endl;
	cout << "enter your balance: ";
	cin >> Balance;

	// current Day of the month

	struct tm nowlocal;
	time_t now;
	now = time(0);
	nowlocal = *localtime(&now);
	int DayOfMonth = nowlocal.tm_mday;

	// ammount of days current month (with LeapYear Detection)

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

	// Calculate Days to Payday


	int DaysToPayday(0);

	if (DayOfMonth < 24)
	{
		DaysToPayday = PayDay - DayOfMonth;
	}
	else
	{
		DaysToPayday = AmmountDaysOfCurrentMonth - DayOfMonth + 24;
	}

	// Calculate daily budget

	int DailyBudget(0);

	DailyBudget = Balance / DaysToPayday;
	system("cls");
	cout << "====================TangLeft====================" << endl;
	cout << " (calculates the daily budget until nex payday) " << endl;
	cout << "================================================" << endl;
	cout << endl;
	cout << "your daily budget until next payday: " << DailyBudget;
	cout << endl;
	cout << endl;
	cout << DaysToPayday << " days to go" << endl;


	cout << endl << endl;
	system("PAUSE");

	return 0;
}