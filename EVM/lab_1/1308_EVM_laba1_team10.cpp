#include <iostream>
#include <cstdlib>
#include <limits>
#include <string.h>
#include <bitset>
#include <math.h>
using namespace std;

union un{
	    double num_double;
	    long long bit_double;
};

bool is_sym_in_str(char sym, char* str);
char* check_integer(char* inpt);
char* check_double(char* inpt);
bool check_sign(char* str);
bool check_point(char* str);
un change_double(un my_double, short *digits, bool *value, int n);
int change_int(int my_int, short *digits, bool *value, int n);

char int_symb[] = {'+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
char double_symb[] = {'+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '\0'};
const double MAX_DOUBLE = 1.7 * pow(10, 308);
const double MIN_DOUBLE = -1.7 * pow(10, 308);
int main() {
	int my_int;
	short* position = NULL;
	bool mdf, flag_digit = true, flag_range  = true, *value = NULL;
	un my_double;
	int n, bit_number;
	char* inpt = new char[80];
	cout << "Enter type of number to input(0 - integer, 1 - double): ";
	cin >> inpt;
	if(strlen(inpt) > 1)	flag_digit = false;
	else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
	while(!flag_digit){
		flag_digit = true;
		cout << "Entered value isn't 0 or 1. Please, try again!" << endl;
		cout << "\nEnter type of number to input(0 - integer, 1 - double): ";
		cin >> inpt;
		if(strlen(inpt) > 1)	flag_digit = false;
		else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
	}
	mdf = atoi(inpt);
	cout << endl;
	if(mdf){
		cout << "Enter number of double (Interval [-1.7E+308 to 1.7E-308]): ";
		cin >> inpt;
		inpt = check_double(inpt);
		my_double.num_double = strtod(inpt, NULL);
		printf("Double value: %.16lf\n", my_double.num_double);
		cout << "Binary representation entered value of double: ";
		for(int i = sizeof(my_double.num_double) * 8 - 1;i >= 0;--i){
			cout << (int)((my_double.bit_double >> i) & 1);
		}
		cout << endl;
		cout << "\nEnter amount of digits to change: ";
		cin >> inpt;
		cout << endl;
		flag_digit = true;
		for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
		while(!flag_digit){
			flag_digit = true;
			cout << "Entered value isn't unsigned integer number. Please, try again!" << endl;
			cout << "\nEnter amount of digits to change: ";
			cin >> inpt;
			cout << endl;
			for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
		}
		cout << endl;
		n = atoi(inpt);
		cout << endl;
		position = new short[n];
		value = new bool[n];
		for(int i = 0;i < n;i++){
			flag_digit = true;
			flag_range = true;
			cout << "Enter " << i+1;
			i+1 == 1 ? cout << "st" : (i+1 == 2 ? cout << "nd" : (i+1 == 3 ? cout << "rd" : cout << "th"));
			cout << " digit number: ";
			cin >> inpt;
			for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
			if(flag_digit)	if(atoi(inpt) > 64 || atoi(inpt) < 1)		flag_range = false;
			while(!flag_digit || !flag_range){
				if(!flag_range)	cout << "Entered value out of range [1 to 64]" << endl;
				else if(!flag_digit)		cout << "Entered value isn't unsigned integer number. Please, try again!" << endl;
				flag_digit = true;
				flag_range = true;
				cout << "\nEnter " << i+1;
				i+1 == 1 ? cout << "st" : (i+1 == 2 ? cout << "nd" : (i+1 == 3 ? cout << "rd" : cout << "th"));
				cout << " digit number: ";
				cin >> inpt;
				for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
				if(flag_digit)	if(atoi(inpt) > 64 || atoi(inpt) < 1)		flag_range = false;
			}
			position[i] = atoi(inpt);
			cout << "Enter value of bit " << position[i]<<": ";
			cin >> inpt;
			if(strlen(inpt) > 1)	flag_digit = false;
			else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
			while(!flag_digit){
				flag_digit = true;
				cout << "Entered value isn't 0 or 1. Please, try again!" << endl;
				cout << "\nEnter value of bit " << position[i] << ": ";
				cin >> inpt;
				cout << endl;
				if(strlen(inpt) > 1)	flag_digit = false;
				else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
			}
			value[i] = atoi(inpt);
		}
		
		my_double = change_double(my_double, position, value, n);
		cout << "Binary representation changed value of double: ";
		for(int i = sizeof(my_double.num_double) * 8 - 1;i >= 0;--i){
			cout << (int)((my_double.bit_double >> i) & 1);
		}
		
		cout << endl;
		printf("Changed value of double: %.16lf\n", my_double.num_double);
		cout << endl;

		
	} else {
		cout << "Enter number of integer (Interval [-2 147 483 648 to 2 147 483 647]): ";
		cin >> inpt;
		inpt = check_integer(inpt);
		my_int = atoi(inpt);
		cout << "Binary representation entered value of integer: ";
		for(int i = sizeof(my_int) * 8 - 1;i >= 0;--i){
			cout << (int)((my_int >> i) & 1);
		}
		cout << endl;
		
		cout << "\nEnter amount of digits to change: ";
		cin >> inpt;
		flag_digit = true;
		for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
		while(!flag_digit){
			flag_digit = true;
			cout << "Entered value isn't unsigned integer number. Please, try again!" << endl;
			cout << "\nEnter amount of digits to change: ";
			cin >> inpt;
			for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
		}
		cout << endl;
		n = atoi(inpt);
		position = new short[n];
		value = new bool[n];
		for(int i = 0;i < n;i++){
			flag_digit = true;
			flag_range = true;
			cout << "Enter " << i+1;
			i+1 == 1 ? cout << "st" : (i+1 == 2 ? cout << "nd" : (i+1 == 3 ? cout << "rd" : cout << "th"));
			cout << " digit number: ";
			cin >> inpt;
			for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
			if(flag_digit)	if(atoi(inpt) > 32 || atoi(inpt) < 1)		flag_range = false;
			while(!flag_digit || !flag_range){
				if(!flag_range)	cout << "Entered value out of range [1 to 32]" << endl;
				else if(!flag_digit)		cout << "Entered value isn't unsigned integer number. Please, try again!" << endl;
				flag_digit = true;
				flag_range = true;
				cout << endl;
				cout << "Enter " << i+1;
				i+1 == 1 ? cout << "st" : (i+1 == 2 ? cout << "nd" : (i+1 == 3 ? cout << "rd" : cout << "th"));
				cout << " digit number: ";
				cin >> inpt;
				for(int j = 0;j < strlen(inpt);j++)		if((int)inpt[j] < 48 || (int)inpt[j] > 57)	flag_digit = false;
				if(flag_digit)	if(atoi(inpt) > 32 || atoi(inpt) < 1)		flag_range = false;
			}
			position[i] = atoi(inpt);
			cout << "Enter value of bit " << position[i]<<": ";
			cin >> inpt;
			if(strlen(inpt) > 1)	flag_digit = false;
			else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
			while(!flag_digit){
				flag_digit = true;
				cout << "Entered value isn't 0 or 1. Please, try again!" << endl;
				cout << "\nEnter value of bit " << position[i] << ": ";
				cin >> inpt;
				cout << endl;
				if(strlen(inpt) > 1)	flag_digit = false;
				else if(inpt[0] != '0' && inpt[0] != '1')	flag_digit = false;
			}
			value[i] = atoi(inpt);
		}
		
		my_int = change_int(my_int, position, value, n);
		cout << "Binary representation changed value of double: ";
		for(int i = sizeof(my_int) * 8 - 1;i >= 0;--i){
			cout << (int)((my_int >> i) & 1);
		}
		cout << endl;
		cout << "Changed value of integer: " << my_int << endl;
		cout << endl;
	}
	delete[] inpt;
	delete[] position;
	delete[] value;
	return 0;
}

char* check_integer(char* inpt){
	bool digit_flag = true, range_flag = true;
	char* res = NULL;
	for(int i = 0;i < strlen(inpt);i++)	if(!is_sym_in_str(inpt[i], int_symb))	digit_flag = false;
	range_flag = !(atoll(inpt) < INT_MIN || atoll(inpt) > INT_MAX);
	if(check_sign(inpt))	digit_flag = false;
	res = inpt;
	while(!digit_flag || !range_flag){
		digit_flag = true;
		range_flag = true;

		for(int i = 0;i < strlen(res);i++)	if(!is_sym_in_str(res[i], int_symb))	digit_flag = false;
		if(check_sign(res))	digit_flag = false;
		range_flag = (atoll(res) >= INT_MIN && atoll(res) <= INT_MAX);
		if(!digit_flag && !range_flag){
			cout << "The entered value isn't integer number! Repeat input!\n";
			cout << "The entered value out of range! Repeat input!\n";
			cout << "\nEnter number of integer (Interval [-2 147 483 648; 2 147 483 647]): ";
			cin >> res;
		} else if(!range_flag){
			cout << "The entered value out of range! Repeat input!\n";
			cout << "\nEnter number of integer (Interval [-2 147 483 648; 2 147 483 647]): ";
			cin >> res;
		} else if(!digit_flag){
			cout << "The entered value isn't integer number! Repeat input!\n";
			cout << "\nEnter number of integer (Interval [-2 147 483 648; 2 147 483 647]): ";
			cin >> res;
		}

		for(int i = 0;i < strlen(res);i++)	if(!is_sym_in_str(res[i], int_symb))	digit_flag = false;
		if(check_sign(res))	digit_flag = false;
		range_flag = !(atoll(res) < INT_MIN || atoll(res) > INT_MAX);
	}
	return res;
}

char* check_double(char* inpt){
	bool digit_flag = true, range_flag = true;
	char* res = NULL;
	for(int i = 0;i < strlen(inpt);i++)	if(!is_sym_in_str(inpt[i], double_symb))	digit_flag = false;
	range_flag = !(strtod(inpt, NULL) < MIN_DOUBLE || strtod(inpt, NULL) > MAX_DOUBLE);
	if(check_point(inpt))	digit_flag = false;
	res = inpt;
	while(!digit_flag || !range_flag){
		digit_flag = true;
		range_flag = true;

		for(int i = 0;i < strlen(res);i++)	if(!is_sym_in_str(res[i], double_symb))	digit_flag = false;
		if(check_point(res))	digit_flag = false;
		range_flag = (strtod(res, NULL) >= MIN_DOUBLE && strtod(res, NULL) <= MAX_DOUBLE);

		if(!digit_flag && ! range_flag){
			cout << "The entered value isn't double number! Repeat input!\n";
			cout << "The entered value out of range! Repeat input!\n";
			cout << "\nEnter number of double (Interval [-1.7E+308 to 1.7E-308]): ";
			cin >> res;
		} else if(!digit_flag){
			cout << "The entered value isn't double number! Repeat input!\n";
			cout << "\nEnter number of double (Interval [-1.7E+308 to 1.7E-308]): ";
			cin >> res;
		} else if(!range_flag){
			cout << "The entered value out of range! Repeat input!\n";
			cout << "\nEnter number of double (Interval [-1.7E+308 to 1.7E-308]): ";
			cin >> res;
		}

		for(int i = 0;i < strlen(res);i++)	if(!is_sym_in_str(res[i], double_symb))	digit_flag = false;
		if(check_point(res))	digit_flag = false;
		range_flag = !(strtod(res, NULL) < MIN_DOUBLE || strtod(res, NULL) > MAX_DOUBLE);
	}
	return res;
}

bool is_sym_in_str(char sym, char* str){
	bool flag = false;
	for(int i = 0;i < strlen(str);i++)	if(str[i] == sym)	flag = true;
	return flag;
}

bool check_sign(char* str){
	bool flag = false;
	for(int i = 0;i < strlen(str);i++)	if((str[i] == '-' || str[i] == '+') && i != 0)	flag = true;
	return flag;
}

bool check_point(char* str){
	int count = 0;
	for(int i = 0;i < strlen(str);i++)	if(str[i] == '.')	count++;
	return count > 1;
}

un change_double(un my_double, short *digits, bool *value, int n)
{
    for(int i = 0; i < n; i++)
    {
        if((my_double.bit_double >> (digits[i] - 1)) & 1)
        {
            my_double.bit_double -= 1LL << (digits[i] - 1);
        }
        my_double.bit_double = my_double.bit_double | ((long long)value[i] << (digits[i] - 1));
    }
    return my_double;
}

int change_int(int my_int, short *digits, bool *value, int n)
{
    for(int i = 0; i < n; i++)
    {
        if((my_int >> (digits[i] - 1)) & 1)
        {
            my_int -= 1 << (digits[i] - 1);
        }
        my_int = my_int | ((int)value[i] << (digits[i] - 1));
    }
    return my_int;
}

