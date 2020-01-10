#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <functional>
using namespace std;


struct Subscriber
{
	int id = 1;
	string firstname;
	string secondname;
	string lastname;
	string phonenumber;
	int connectionyear = 2019;
	string tariff;
};


struct User
{
	int id = 1;
	string login;
	string password;
	string role;
};


size_t split(const string& txt, vector<string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();
	while (pos != string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));
	return strs.size();
}


User* createUserList(int countusers)
{
	ifstream file("users.txt");
	string str;
	vector<string> data;
	User* users = new User[countusers];
	int i = 0;
	while (getline(file, str))
	{
		split(str, data, '|');
		users[i].id = stoi(data[0]);
		users[i].login = data[1];
		users[i].password = data[2];
		users[i].role = data[3];
		i++;
	}
	file.close();
	return users;
}


Subscriber* createSubscriberList(int countsubscribers)
{
	ifstream file("subscribers.txt");
	string str;
	vector<string> data;
	vector<string> name;
	Subscriber* subscribers = new Subscriber[countsubscribers];
	int i = 0;
	while (getline(file, str))
	{
		data.clear();
		name.clear();
		split(str, data, '|');
		split(data[1], name, ' ');
		subscribers[i].id = stoi(data[0]);
		subscribers[i].firstname = name[1];
		subscribers[i].secondname = name[2];
		subscribers[i].lastname = name[0];
		subscribers[i].phonenumber = data[2];
		subscribers[i].connectionyear = stoi(data[3]);
		subscribers[i].tariff = data[4];
		i++;
	}
	file.close();
	return subscribers;
}


bool logIn(string login, string password, User users[], int countusers)
{
	hash<string> passwordhash;
	for (int i = 0; i < countusers; i++)
	{
		if (users[i].login == login && users[i].password == (to_string(passwordhash(password)) + "1a2hkvghggvgv6hjbjhvbh8j"))
		{
			return true;
		}
	}
	return false;
}


string checkRole(string login, User users[], int countusers)
{
	for (int i = 0; i < countusers; i++)
	{
		if (users[i].login == login)
		{
			return users[i].role;
		}
	}
}


void showUsers(User users[], int countusers)
{
	for (int i = 0; i < countusers; i++)
		cout << "Id: " << users[i].id << "login: " << users[i].login << "\trole: " << users[i].role
		<< "\n-------------------------------------\n";
	system("pause");
}


void showSubscribers(Subscriber subscribers[], int countsubscribers)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		cout <<"Id: "<<subscribers[i].id
			<< "Last name: " << subscribers[i].lastname
			<< "\nFirst name: " << subscribers[i].firstname
			<< "\nSecond name: " << subscribers[i].secondname
			<< "\nPhone number: " << subscribers[i].phonenumber
			<< "\nConnection year: " << subscribers[i].connectionyear
			<< "\nTariff: " << subscribers[i].tariff << endl;
		cout << "----------------------------\n";
	}
	system("pause");
}


void showSubscribersSinceYear(Subscriber subscribers[], int countsubscribers, int year)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].connectionyear >= year)
		{
			cout << "Last name: " << subscribers[i].lastname
				<< "\nFirst name: " << subscribers[i].firstname
				<< "\nSecond name: " << subscribers[i].secondname
				<< "\nPhone number: " << subscribers[i].phonenumber
				<< "\nConnection year: " << subscribers[i].connectionyear
				<< "\nTariff: " << subscribers[i].tariff << endl;
			cout << "----------------------------\n";
		}
	}
	system("pause");
}


int addNewSubscriber(string lastname, string firstname, string secondname, string phonenumber, int connectionyear, string tariff, Subscriber subscribers[], int &countsubscribers)
{
	string newname = lastname + " " + firstname + " " + secondname;
	for (int i = 0; i < countsubscribers; i++)
	{
		string name = subscribers[i].lastname + " " + subscribers[i].firstname + " " + subscribers[i].secondname;
		if (name == newname)
		{
			cout << "Such a subscriber is already in the database";
			return -1;
		}
	}
	int maxid = 1;
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].id > maxid)
			maxid = subscribers[i].id;
	}
	string newsubscriber = to_string(maxid + 1) + "|" + newname + "|" +
		phonenumber + "|" + to_string(connectionyear) + "|" + tariff + "\n";
	ofstream file("subscribers.txt", ios_base::app);
	file << newsubscriber;
	file.close();
	countsubscribers++;
	return 0;
}


int addNewUser(string login, string role, string password, User users[], int& countusers)
{
	for (int i = 0; i < countusers; i++)
	{
		if (login == users[i].login)
		{
			cout << "Such a user is already in the database";
			return -1;
		}
	}
	int maxid = 0;
	for (int i = 0; i < countusers; i++)
	{
		if (users[i].id > maxid)
			maxid = users[i].id;
	}
	hash<string> passwordhash;
	string newuser;
	if (maxid == 0)
		newuser = to_string(maxid + 1) + "|" + login + "|"
		+ to_string(passwordhash(password)) + "1a2hkvghggvgv6hjbjhvbh8j" + "|" + role;
	else
		newuser = "\n" + to_string(maxid + 1) + "|" + login + "|"
		+ to_string(passwordhash(password)) + "1a2hkvghggvgv6hjbjhvbh8j" + "|" + role;
	ofstream file("users.txt", ios_base::app);
	file << newuser;
	file.close();
	countusers++;
	return 0;
}


void changeSubscriberFile(Subscriber subscribers[], int countsubscribers)
{
	string tofile;
	for (int i = 0; i < countsubscribers; i++)
	{
		tofile += to_string(subscribers[i].id) + "|" + subscribers[i].lastname + " " + subscribers[i].firstname + " " + subscribers[i].secondname + "|"
			+ subscribers[i].phonenumber + "|" + to_string(subscribers[i].connectionyear) + "|" + subscribers[i].tariff + "\n";
	}
	ofstream file("subscribers.txt");
	file << tofile;
	file.close();
}


void changeUserFile(User users[], int countusers)
{
	string tofile;
	for (int i = 0; i < countusers; i++)
	{
		tofile += to_string(users[i].id) + "|" + users[i].login + "|" + users[i].password + "|" + users[i].role + "\n";
	}
	ofstream file("users.txt");
	file << tofile;
	file.close();
}


void deleteSubscriber(Subscriber subscribers[], int &countsubscribers, int id)
{
	string tofile;
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].id != id)
			tofile += to_string(subscribers[i].id) + "|" + subscribers[i].lastname + " " + subscribers[i].firstname + " " + subscribers[i].secondname + "|"
			+ subscribers[i].phonenumber + "|" + to_string(subscribers[i].connectionyear) + "|" + subscribers[i].tariff + "\n";
	}
	ofstream file("subscribers.txt");
	file << tofile;
	file.close();
	countsubscribers--;
}


void deleteUser(User users[], int& countusers, int id)
{
	string tofile;
	for (int i = 0; i < countusers; i++)
	{
		if (users[i].id != id)
			tofile += to_string(users[i].id) + "|" + users[i].login + "|" +
			users[i].role + "\n";
	}
	ofstream file("users.txt");
	file << tofile;
	file.close();
	countusers--;
}


Subscriber* changeSubscriber(Subscriber subscribers[], int id, int countsubscribers)
{
	bool findsubscriber = false;
	int indsubscriber;
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].id == id)
		{
			findsubscriber = true;
			indsubscriber = i;
		}
	}
	if (findsubscriber)
	{
		string lastname, firstname, secondname, phonenumber, tariff;
		int connectionyear;
		cout << "Input last name: ";
		cin >> lastname;
		cout << "Input first name: ";
		cin >> firstname;
		cout << "Input second name: ";
		cin >> secondname;
		cout << "Input  phone number: ";
		cin >> phonenumber;
		cout << "Input connection year: ";
		cin >> connectionyear;
		cout << "Input tariff: ";
		cin >> tariff;
		subscribers[indsubscriber].lastname = lastname;
		subscribers[indsubscriber].firstname = firstname;
		subscribers[indsubscriber].secondname = secondname;
		subscribers[indsubscriber].phonenumber = phonenumber;
		subscribers[indsubscriber].connectionyear = connectionyear;
		subscribers[indsubscriber].tariff = tariff;
		changeSubscriberFile(subscribers, countsubscribers);
		cout << "Subscriber data changed successfully\n";
	}
	else
		cout << "There is no such subscriber\n";
	system("pause");
	return subscribers;
}


User* changeUser(User users[], int id, int countusers)
{
	bool finduser = false;
	int induser;
	for (int i = 0; i < countusers; i++)
	{
		if (users[i].id == id)
		{
			finduser = true;
			induser = i;
		}
	}
	if (finduser)
	{
		string login, password, role;
		cout << "Input login: ";
		cin >> login;
		cout << "Input role: ";
		cin >> role;
		cout << "Input password: ";
		cin >> password;
		users[induser].login = login;
		users[induser].password = password;
		users[induser].role = role;
		changeUserFile(users, countusers);
		cout << "User data changed successfully\n";
	}
	else
		cout << "There is no such user\n";
	system("pause");
	return users;
}


Subscriber* sortByName(Subscriber subscribers[], int countsubscribers)
{
	for (int i = 0; i < countsubscribers - 1; i++)
	{
		string firstname = subscribers[i].lastname + " " + subscribers[i].firstname + " " + subscribers[i].secondname;
		for (int j = i + 1; j < countsubscribers; j++)
		{
			string secondname = subscribers[j].lastname + " " + subscribers[j].firstname + " " + subscribers[j].secondname;
			Subscriber tmp;
			if (strcmp(firstname.c_str(), secondname.c_str()) > 0)
			{
				tmp = subscribers[i];
				subscribers[i] = subscribers[j];
				subscribers[j] = tmp;
			}
		}
	}
	return subscribers;
}


Subscriber* sortByTariff(Subscriber subscribers[], int countsubscribers)
{
	for (int i = 0; i < countsubscribers - 1; i++)
	{
		for (int j = i + 1; j < countsubscribers; j++)
		{
			Subscriber tmp;
			if (strcmp(subscribers[i].tariff.c_str(), subscribers[j].tariff.c_str()) > 0)
			{
				tmp = subscribers[i];
				subscribers[i] = subscribers[j];
				subscribers[j] = tmp;
			}
		}
	}
	return subscribers;
}


Subscriber* sortByYear(Subscriber subscribers[], int countsubscribers)
{
	for (int i = 0; i < countsubscribers - 1; i++)
	{
		for (int j = i + 1; j < countsubscribers; j++)
		{
			Subscriber tmp;
			if (subscribers[i].connectionyear > subscribers[j].connectionyear)
			{
				tmp = subscribers[i];
				subscribers[i] = subscribers[j];
				subscribers[j] = tmp;
			}
		}
	}
	return subscribers;
}


Subscriber* sortById(Subscriber subscribers[], int countsubscribers)
{
	for (int i = 0; i < countsubscribers - 1; i++)
	{
		for (int j = i + 1; j < countsubscribers; j++)
		{
			Subscriber tmp;
			if (subscribers[i].id > subscribers[j].id)
			{
				tmp = subscribers[i];
				subscribers[i] = subscribers[j];
				subscribers[j] = tmp;
			}
		}
	}
	return subscribers;
}


void searchByName(Subscriber subscribers[], int countsubscribers, string name)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		string fullname = subscribers[i].lastname + " " + subscribers[i].firstname + " " + subscribers[i].secondname;
		if (strstr(fullname.c_str(), name.c_str()) > 0)
		{
			cout << "Last name: " << subscribers[i].lastname
				<< "\nFirst name: " << subscribers[i].firstname
				<< "\nSecond name: " << subscribers[i].secondname
				<< "\nPhone number: " << subscribers[i].phonenumber
				<< "\nConnection year: " << subscribers[i].connectionyear
				<< "\nTariff: " << subscribers[i].tariff << endl;
			cout << "----------------------------\n";
		}
	}
}


void searchByYear(Subscriber subscribers[], int countsubscribers, int year)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].connectionyear == year)
		{
			cout << "Last name: " << subscribers[i].lastname
				<< "\nFirst name: " << subscribers[i].firstname
				<< "\nSecond name: " << subscribers[i].secondname
				<< "\nPhone number: " << subscribers[i].phonenumber
				<< "\nConnection year: " << subscribers[i].connectionyear
				<< "\nTariff: " << subscribers[i].tariff << endl;
			cout << "----------------------------\n";
		}
	}
}


void searchByTariff(Subscriber subscribers[], int countsubscribers, string tariff)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].tariff == tariff)
		{
			cout << "Last name: " << subscribers[i].lastname
				<< "\nFirst name: " << subscribers[i].firstname
				<< "\nSecond name: " << subscribers[i].secondname
				<< "\nPhone number: " << subscribers[i].phonenumber
				<< "\nConnection year: " << subscribers[i].connectionyear
				<< "\nTariff: " << subscribers[i].tariff << endl;
			cout << "----------------------------\n";
		}
	}
}


void searchById(Subscriber subscribers[], int countsubscribers, int id)
{
	for (int i = 0; i < countsubscribers; i++)
	{
		if (subscribers[i].id == id)
		{
			cout << "Last name: " << subscribers[i].lastname
				<< "\nFirst name: " << subscribers[i].firstname
				<< "\nSecond name: " << subscribers[i].secondname
				<< "\nPhone number: " << subscribers[i].phonenumber
				<< "\nConnection year: " << subscribers[i].connectionyear
				<< "\nTariff: " << subscribers[i].tariff << endl;
			cout << "----------------------------\n";
		}
	}
}


void showAdminMainMenu(User users[], int countusers, Subscriber subscribers[], int countsubscribers)
{
	int x = -1;
	while (x != 0)
	{
		string lastname, firstname, secondname, phonenumber, tariff, name, login, role, password;
		int connectionyear, id, year, sorttype, searchtype;
		char answer;
		system("cls");
		cout << "Select command:"
			<< "\n1. Show all users;"
			<< "\n2. Add new user;"
			<< "\n3. Change user;"
			<< "\n4. Delete user;"
			<< "\n5. Show all subscribers;"
			<< "\n6. Add new subscriber;"
			<< "\n7. Change subscriber;"
			<< "\n8. Delete subscriber;"
			<< "\n9. Show list of subscribers connected since a certain yaer;"
			<< "\n10. Search;"
			<< "\n11. Sort;"
			<< "\n0. Exit.\n";
		cin >> x;
		switch (x)
		{
		case 1:
			showUsers(users, countusers);
			break;
		case 2:
			cout << "Input login: ";
			cin >> login;
			cout << "Input role: ";
			cin >> role;
			cout << "Input password: ";
			cin >> password;
			if (role != "user" && role != "admin")
			{
				cout << "Invalid role\n";
				system("pause");
			}
			else
			{
				if (addNewUser(login, role, password, users, countusers) == 0)
				{
					users = createUserList(countusers);
					cout << "User successfully added\n";
					system("pause");
				}
			}
			break;
		case 3:
			cout << "Input user id: ";
			cin >> id;
			cout << "You actually want to change this user?(y/n)";
			cin >> answer;
			if (answer == 'y')
				users = changeUser(users, id, countusers);
			break;
		case 4:
			cout << "Input user id: ";
			cin >> id;
			cout << "You actually want to delete this user?(y/n)";
			cin >> answer;
			if (answer == 'y')
			{
				deleteUser(users, countusers, id);
				users = createUserList(countusers);
			}
			break;
		case 5:
			if (countsubscribers == 0)
			{
				cout << "Subscriber list is empty\n";
				system("pause");
			}
			else
				showSubscribers(subscribers, countsubscribers);
			break;
		case 6:
			cout << "Input last name: ";
			cin >> lastname;
			cout << "Input first name: ";
			cin >> firstname;
			cout << "Input second name: ";
			cin >> secondname;
			cout << "Input  phone number: ";
			cin >> phonenumber;
			cout << "Input connection year: ";
			cin >> connectionyear;
			cout << "Input tariff: ";
			cin >> tariff;
			if (addNewSubscriber(lastname, firstname, secondname, phonenumber, connectionyear, tariff, subscribers, countsubscribers) == 0)
			{
				subscribers = createSubscriberList(countsubscribers);
				cout << "Subscriber succesfully added\n";
				system("pause");
			}
			break;
		case 7:
			cout << "Input subscriber id: ";
			cin >> id;
			cout << "You actually want to change this subscriber?(y/n)";
			cin >> answer;
			if (answer == 'y')
				subscribers = changeSubscriber(subscribers, id, countsubscribers);
			break;
		case 8:
			cout << "Input subscriber id: ";
			cin >> id;
			cout << "You actually want to delete this subscriber?(y/n)";
			cin >> answer;
			if (answer == 'y')
			{
				deleteSubscriber(subscribers, countsubscribers, id);
				subscribers = createSubscriberList(countsubscribers);
			}
			break;
		case 9:
			cout << "Input year: ";
			cin >> year;
			showSubscribersSinceYear(subscribers, countsubscribers, year);
			break;
		case 10:
			cout << "Select search type (Case sensitive search):\n"
				<< "1. Subscriber name;\n"
				<< "2. Year;\n"
				<< "3. Tariff;\n"
				<< "4. Id.\n";
			cin >> searchtype;
			switch (searchtype)
			{
			case 1:
				cout << "Input name: ";
				cin >> name;
				searchByName(subscribers, countsubscribers, name);
				system("pause");
				break;
			case 2:
				cout << "Input year: ";
				cin >> year;
				searchByYear(subscribers, countsubscribers, year);
				system("pause");
				break;
			case 3:
				cout << "Input tariff: ";
				cin >> tariff;
				searchByTariff(subscribers, countsubscribers, tariff);
				system("pause");
				break;
			case 4:
				cout << "Input id: ";
				cin >> id;
				searchById(subscribers, countsubscribers, id);
				system("pause");
				break;
			default:
				cout << "Invalid command\n";
				break;
			}
			break;
		case 11:
			cout << "Select sort type:\n"
				<< "1. Subscriber name;\n"
				<< "2. Year;\n"
				<< "3. Tariff;\n"
				<< "4. Id.\n";
			cin >> sorttype;
			switch (sorttype)
			{
			case 1:
				subscribers = sortByName(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 2:
				subscribers = sortByYear(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 3:
				subscribers = sortByTariff(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 4:
				subscribers = sortById(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			default:
				cout << "Invalid command\n";
				break;
			}
			break;
		case 0:
			cout << "Good Bye!\n";
			break;
		}
	}
}


void showUserMainMenu(Subscriber subscribers[], int countsubscribers)
{
	string name, tariff;
	int x = -1;
	int year, searchtype, id, sorttype;
	while (x != 0)
	{
		system("cls");
		cout << "Select command:"
			<< "\n1. Show all subscribers;"
			<< "\n2. Show list of subscribers connected since a certain yaer;"
			<< "\n3. Search;"
			<< "\n4. Sort;"
			<< "\n0. Exit.\n";
		cin >> x;
		switch (x)
		{
		case 1:
			if (countsubscribers == 0)
			{
				cout << "Subscriber list is empty\n";
				system("pause");
			}
			else
				showSubscribers(subscribers, countsubscribers);
			break;
		case 2:
			cout << "Input year: ";
			cin >> year;
			showSubscribersSinceYear(subscribers, countsubscribers, year);
			break;
		case 3:
			cout << "Select search type (Case sensitive search):\n"
				<< "1. Subscriber name;\n"
				<< "2. Year;\n"
				<< "3. Tariff;\n"
				<< "4. Id.\n";
			cin >> searchtype;
			switch (searchtype)
			{
			case 1:
				cout << "Input name: ";
				cin >> name;
				searchByName(subscribers, countsubscribers, name);
				system("pause");
				break;
			case 2:
				cout << "Input year: ";
				cin >> year;
				searchByYear(subscribers, countsubscribers, year);
				system("pause");
				break;
			case 3:
				cout << "Input tariff: ";
				cin >> tariff;
				searchByTariff(subscribers, countsubscribers, tariff);
				system("pause");
				break;
			case 4:
				cout << "Input id: ";
				cin >> id;
				searchById(subscribers, countsubscribers, id);
				system("pause");
				break;
			default:
				cout << "Invalid command\n";
				break;
			}
			break;
		case 4:
			cout << "Select sort type:\n"
				<< "1. Subscriber name;\n"
				<< "2. Year;\n"
				<< "3. Tariff;\n"
				<< "4. Id.\n";
			cin >> sorttype;
			switch (sorttype)
			{
			case 1:
				subscribers = sortByName(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 2:
				subscribers = sortByYear(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 3:
				subscribers = sortByTariff(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			case 4:
				subscribers = sortById(subscribers, countsubscribers);
				showSubscribers(subscribers, countsubscribers);
				break;
			default:
				cout << "Invalid command\n";
				break;
			}
			break;
		case 0:
			cout << "Good Bye!\n";
		}
	}
}


int main()
{
	ifstream file("users.txt");
	string str;
	int countusers = 0, countsubscribers = 0;;
	while (getline(file, str))
		countusers++;
	file.close();
	User* users;
	users = createUserList(countusers);
	file.open("subscribers.txt");
	while (getline(file, str))
		countsubscribers++;
	file.close();
	Subscriber* subscribers;
	subscribers = createSubscriberList(countsubscribers);
	string login, password;
	cout << "Input login: ";
	cin >> login;
	cout << "Input password: ";
	cin >> password;
	if (logIn(login, password, users, countusers))
	{
		cout << "Welcome, " << login;
		if (checkRole(login, users, countusers) == "user")
			showUserMainMenu(subscribers, countsubscribers);
		else
			showAdminMainMenu(users, countusers, subscribers, countsubscribers);
	}
	else
	{
		cout << "Invalid login or password.";
		return -1;
	}
	delete[] users;
	delete[] subscribers;
	system("pause");
	return 0;
}