#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib> 

using namespace std;

#define model_num 7
#define max_parts 100
#define max_service 100

int current_mg_car;
double cost_p = 0;
double cost_s = 0;

void initializeAdmins();
void initializeUsers();
void signupUser();
void login(string username, string password);
void userLogin(string username, string password);
void AdminMenu();
void UserMenu();
void logout();
void mainmenu();
void clearScreen();

const int nAdmins = 10;
const int nUsers = 100;

struct admin
{
	string username;
	string password;
};

struct user
{
	string username;
	string password;
};

admin adminsdata[nAdmins];
user usersdata[nUsers];
int nextUserIndex = 2;
bool isAdminLoggedIn = false;
string loggedInAdminUsername = "";
bool isUserLoggedIn = false;
string loggedInUserUsername = "";
bool shouldShowMainMenu = true;
void clearScreen()
{
	system("cls");

}
void initializeAdmins()
{
	adminsdata[0].username = "nourmahmoud";
	adminsdata[0].password = "1234";
	adminsdata[1].username = "raghadmohamed";
	adminsdata[1].password = "1234";
	adminsdata[2].username = "waadmohamed";
	adminsdata[2].password = "1234";
	adminsdata[3].username = "salmathabet";
	adminsdata[3].password = "1234";
	adminsdata[4].username = "alifarid";
	adminsdata[4].password = "1234";
	adminsdata[5].username = "ahmedyasser";
	adminsdata[5].password = "1234";
	adminsdata[6].username = "youssefyasser";
	adminsdata[6].password = "1234";
	adminsdata[7].username = "mohamedali";
	adminsdata[7].password = "1234";

}

void initializeUsers()
{
	usersdata[0].username = "mohamedali";
	usersdata[0].password = "1234";
}

void signupUser()
{
	if (nextUserIndex >= nUsers)
	{
		cout << "User capacity reached. Cannot add more users." << endl;
		return;
	}
	string newUsername, newPassword;
	cout << "Enter new username: ";
	cin >> newUsername;
	cout << "Enter new password: ";
	cin >> newPassword;


	for (int i = 0; i < nextUserIndex; i++)
	{
		if (usersdata[i].username == newUsername)
		{
			cout << "Username already exists. Please choose a different one." << endl;
			return;
		}
	}

	usersdata[nextUserIndex].username = newUsername;
	usersdata[nextUserIndex].password = newPassword;
	nextUserIndex++;
	cout << "User signup successful." << endl;
}

void login(string username, string password)
{
	initializeAdmins();

	for (int i = 0; i < nAdmins; i++)
	{
		if (adminsdata[i].username == username && adminsdata[i].password == password)
		{
			isAdminLoggedIn = true;
			loggedInAdminUsername = username;
			cout << "Login successful. Accessing Admin Menu." << endl;
			clearScreen();
			AdminMenu();
			return;
		}
	}
	cout << "Invalid admin username or password." << endl;
}

void userLogin(string username, string password)
{
	initializeUsers();

	for (int i = 0; i < nextUserIndex; i++)
	{
		if (usersdata[i].username == username && usersdata[i].password == password)
		{
			isUserLoggedIn = true;
			loggedInUserUsername = username;
			cout << "Login successful. Accessing User Menu." << endl;
			clearScreen();
			UserMenu();
			return;
		}
	}
	cout << "Invalid user username or password." << endl;
}
struct part
{
	string name[max_parts];
	int price[max_parts];
	int kilos[max_parts];
	int part_num[max_parts];
	int part_count = 0;
};
struct service
{
	string name[max_service];
	int price[max_service];
	int kilos[max_service];
	int service_count = 0;
}sforservice;
struct cars
{
	string model;
	part parts;
	service services;
	int year;
	int meliage;
	int months;
}mg[model_num];
struct TAX
{
	double tax_admin;
	double tax_parts;
	double tax_service;
}tax;
struct partCounter
{
	string name[max_parts];
	int numParts[max_parts];
}Counter_p;
struct seviceCounter
{
	int num_service;
}Counter_s;
void partscount()
{
	ifstream count;
	count.open("partcounter.txt");
	for (int i = 0;i < 6;i++)
	{
		count >> Counter_p.name[i] >> Counter_p.numParts[i];
	}
}
void savePartsCount()
{
	ofstream out("partcounter.txt");
	if (!out.is_open()) {
		cout << "Error opening file!!!" << endl;
		return;
	}

	for (int i = 0; i < 6; ++i) {
		out << Counter_p.name[i] << " " << Counter_p.numParts[i] << endl;
	}
	out.close();
}
void serviceCounts()
{
	ifstream servicetocount;
	servicetocount.open("sevicecounter.txt");
	servicetocount >> Counter_s.num_service;
}
void saveServiceCount()
{
	ofstream out("sevicecounter.txt");
	if (!out.is_open())
	{
		cout << "error opening file!!!! ";
		return;
	}
	out << Counter_s.num_service;
	out.close();
}
void load_model()
{
	ifstream model;
	model.open("model.txt");
	for (int i = 0;i < model_num;i++)
	{
		model >> mg[i].model;
	}
}
void addParts()
{
	cout << "\n==============================" << endl;
	cout << "      Choose Car Model" << endl;
	cout << "==============================" << endl;
	cout << "1. MG5" << endl;
	cout << "2. MG6" << endl;
	cout << "3. MG ZS" << endl;
	cout << "4. MG7" << endl;
	cout << "5. MG RX Plus" << endl;
	cout << "6. MG HS" << endl;
	cout << "------------------------------" << endl;
	cout << "Enter model number : " << endl;

	int num;
	cin >> num;

	if (num < 1 || num > 6)
	{
		cout << "\n[!] Invalid selection. Please try again.\n" << endl;
		return;
	}

	int modelIndex = num - 1;
	ifstream inFile(mg[modelIndex].model + ".txt");
	ifstream onFile("partcounter.txt");
	if (inFile.is_open()) {
		mg[modelIndex].parts.part_count = 0;
		while (mg[modelIndex].parts.part_count < max_parts &&
			inFile >> mg[modelIndex].parts.name[mg[modelIndex].parts.part_count]
			>> mg[modelIndex].parts.price[mg[modelIndex].parts.part_count]
			>> mg[modelIndex].parts.kilos[mg[modelIndex].parts.part_count]
			>> mg[modelIndex].parts.part_num[mg[modelIndex].parts.part_count]) {
			mg[modelIndex].parts.part_count++;
			Counter_p.numParts[modelIndex] = mg[modelIndex].parts.part_count;
		}
		savePartsCount();
		inFile.close();
	}
	if (mg[modelIndex].parts.part_count >= max_parts)
	{
		cout << "Maximum parts limit reached for this model!" << endl;
		return;
	}

	cout << "How many parts do you want to add? ";
	int addCount;
	cin >> addCount;

	if (addCount <= 0 || addCount > (max_parts - mg[modelIndex].parts.part_count))
	{
		cout << "Invalid number of parts to add." << endl;
		return;
	}
	for (int i = 0; i < addCount; i++)
	{
		cout << "Enter details for part #" << mg[modelIndex].parts.part_count + 1 << ":" << endl;

		cout << "Name: ";
		cin >> mg[modelIndex].parts.name[mg[modelIndex].parts.part_count];

		cout << "Price: ";
		cin >> mg[modelIndex].parts.price[mg[modelIndex].parts.part_count];

		cout << "Kilos: ";
		cin >> mg[modelIndex].parts.kilos[mg[modelIndex].parts.part_count];

		mg[modelIndex].parts.part_count++;
	}
	ofstream outFile(mg[modelIndex].model + ".txt");
	if (!outFile.is_open()) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < mg[modelIndex].parts.part_count; i++)
	{
		outFile << mg[modelIndex].parts.name[i] << " "
			<< mg[modelIndex].parts.price[i] << " "
			<< mg[modelIndex].parts.kilos[i] << " "
			<< mg[modelIndex].parts.part_num[i] << endl;
	}
	outFile.close();
	Counter_p.numParts[modelIndex] = mg[modelIndex].parts.part_count;
	savePartsCount();
	cout << "Successfully added " << addCount << " parts. Total parts now: "
		<< mg[modelIndex].parts.part_count << endl;
}
void costofparts()
{
	ifstream countrr;
	countrr.open("partcounter.txt");
	if (mg[0].model == "mg5")
	{
		ifstream mg5_parts;
		mg5_parts.open("mg5.txt");
		for (int i = 0;i < Counter_p.numParts[0];i++)
		{
			mg5_parts >> mg[0].parts.name[i] >> mg[0].parts.price[i] >> mg[0].parts.kilos[i] >> mg[0].parts.part_num[i];
			mg[0].parts.part_count++;
		}
	}
	if (mg[1].model == "mg6")
	{
		ifstream mg6_parts;
		mg6_parts.open("mg6.txt");
		for (int i = 0;i < Counter_p.numParts[1];i++)
		{
			mg6_parts >> mg[1].parts.name[i] >> mg[1].parts.price[i] >> mg[1].parts.kilos[i] >> mg[1].parts.part_num[i];
			mg[1].parts.part_count++;
		}
	}
	if (mg[2].model == "mgzs")
	{
		ifstream mgzs_parts;
		mgzs_parts.open("mgzs.txt");
		for (int i = 0;i < Counter_p.numParts[2];i++)
		{
			mgzs_parts >> mg[2].parts.name[i] >> mg[2].parts.price[i] >> mg[2].parts.kilos[i] >> mg[2].parts.part_num[i];
			mg[2].parts.part_count++;

		}
	}
	if (mg[3].model == "mg7")
	{
		ifstream mg7_parts;
		mg7_parts.open("mg7.txt");
		for (int i = 0;i < Counter_p.numParts[3];i++)
		{
			mg7_parts >> mg[3].parts.name[i] >> mg[3].parts.price[i] >> mg[3].parts.kilos[i] >> mg[3].parts.part_num[i];
			mg[3].parts.part_count++;
		}
	}
	if (mg[4].model == "mgrxplus")
	{
		ifstream mgrxplus_parts;
		mgrxplus_parts.open("mgrxplus.txt");
		for (int i = 0;i < Counter_p.numParts[4];i++)
		{
			mgrxplus_parts >> mg[4].parts.name[i] >> mg[4].parts.price[i] >> mg[4].parts.kilos[i] >> mg[4].parts.part_num[i];
			mg[4].parts.part_count++;
		}
	}
	if (mg[5].model == "mghs")
	{
		ifstream mghs_parts;
		mghs_parts.open("mghs.txt");
		for (int i = 0;i < Counter_p.numParts[5];i++)
		{
			mghs_parts >> mg[5].parts.name[i] >> mg[5].parts.price[i] >> mg[5].parts.kilos[i] >> mg[5].parts.part_num[i];
			mg[5].parts.part_count++;
		}
	}

}
void cost_service()
{
	ifstream mg_services;
	mg_services.open("services.txt");
	for (int i = 0;i < Counter_s.num_service;i++)
	{
		mg_services >> sforservice.name[i] >> sforservice.price[i] >> sforservice.kilos[i];
		sforservice.service_count++;
	}
}
void searchservice()
{
	ifstream files("services.txt");

	while (sforservice.service_count < max_service &&
		files >> sforservice.name[sforservice.service_count]
		>> sforservice.price[sforservice.service_count]
		>> sforservice.kilos[sforservice.service_count]) {
		sforservice.service_count++;
	}
	files.close();

	cout << "\n==============================" << endl;
	cout << "       Search for Service" << endl;
	cout << "==============================" << endl;
	cout << "Enter service name: ";

	string search;
	cin >> search;
	bool found = false;
	for (int i = 0;i < sforservice.service_count;i++)
	{
		if (sforservice.name[i] == search)
		{
			cout << "\nService Found:" << endl;
			cout << "------------------------------" << endl;
			cout << "Name  : " << sforservice.name[i] << endl;
			cout << "Price : " << sforservice.price[i] << endl;
			cout << "KMs   : " << sforservice.kilos[i] << endl;
			cout << "------------------------------" << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "\n[!] Service not found!" << endl;
	}
}
void viewparts()
{

	cout << "\n==============================" << endl;
	cout << "         View Parts" << endl;
	cout << "==============================" << endl;
	cout << "1. MG5" << endl;
	cout << "2. MG6" << endl;
	cout << "3. MG ZS" << endl;
	cout << "4. MG7" << endl;
	cout << "5. MG RX Plus" << endl;
	cout << "6. MG HS" << endl;
	cout << "------------------------------" << endl;
	cout << "Choose a model number : " << endl;

	int num;
	cin >> num;
	if (num >= 1 && num <= 6)
	{
		int modelindex = num - 1;
		ifstream file(mg[modelindex].model + ".txt");
		mg[modelindex].parts.part_count = 0;

		cout << "\nParts for model: " << mg[modelindex].model << endl;
		cout << "---------------------------------------------" << endl;
		cout << "No.  | Name         | Price   | KMs   | Part#" << endl;
		cout << "---------------------------------------------" << endl;

		while (mg[modelindex].parts.part_count < max_parts && file >> mg[modelindex].parts.name[mg[modelindex].parts.part_count]
			>> mg[modelindex].parts.price[mg[modelindex].parts.part_count]
			>> mg[modelindex].parts.kilos[mg[modelindex].parts.part_count]
			>> mg[modelindex].parts.part_num[mg[modelindex].parts.part_count])
		{

			cout << mg[modelindex].parts.part_count + 1 << ". "
				<< mg[modelindex].parts.name[mg[modelindex].parts.part_count] << "   "
				<< mg[modelindex].parts.price[mg[modelindex].parts.part_count] << "   "
				<< mg[modelindex].parts.kilos[mg[modelindex].parts.part_count] << endl;

			mg[modelindex].parts.part_count++;

		}
		if (mg[modelindex].parts.part_count == 0)
		{
			cout << "[!] No parts found for this model." << endl;
		}
		cout << "---------------------------------------------" << endl;

		file.close();
	}
	else
	{
		cout << "\n[!] Invalid model number selected!" << endl;
	}
}
void updateParts()
{
	cout << "\n==============================" << endl;
	cout << "        Update Parts" << endl;
	cout << "==============================" << endl;
	cout << "1. MG5\n2. MG6\n3. MG ZS\n4. MG7\n5. MG RX Plus\n6. MG HS\n";
	cout << "Choose a model number (1-6): ";

	int modelChoice;
	cin >> modelChoice;
	if (modelChoice < 1 || modelChoice > 6) {
		cout << "\n[!] Invalid selection!\n";
		return;
	}

	int modelIndex = modelChoice - 1;
	ifstream inFile(mg[modelIndex].model + ".txt");
	mg[modelIndex].parts.part_count = 0;

	while (mg[modelIndex].parts.part_count < max_parts &&
		inFile >> mg[modelIndex].parts.name[mg[modelIndex].parts.part_count]
		>> mg[modelIndex].parts.price[mg[modelIndex].parts.part_count]
		>> mg[modelIndex].parts.kilos[mg[modelIndex].parts.part_count]
		>> mg[modelIndex].parts.part_num[mg[modelIndex].parts.part_count]) {
		mg[modelIndex].parts.part_count++;
	}
	inFile.close();

	if (mg[modelIndex].parts.part_count == 0) {
		cout << "\n[!] No parts available for this model.\n";
		return;
	}
	cout << "\nCurrent parts for model: " << mg[modelIndex].model << "\n";
	cout << "---------------------------------------------\n";
	for (int i = 0; i < mg[modelIndex].parts.part_count; i++) {
		cout << i + 1 << ". " << mg[modelIndex].parts.name[i] << " (Part #: " << mg[modelIndex].parts.part_num[i] << ")\n"
			<< "   Price : $" << mg[modelIndex].parts.price[i] << "\n"
			<< "   Kilos : " << mg[modelIndex].parts.kilos[i] << " km\n";
		cout << "---------------------------------------------\n";
	}
	cout << "Enter part number to update (1-" << mg[modelIndex].parts.part_count << "): ";
	int partChoice;
	cin >> partChoice;

	if (partChoice < 1 || partChoice > mg[modelIndex].parts.part_count) {
		cout << "\n[!] Invalid part selection!\n";
		return;
	}

	int partIndex = partChoice - 1;
	cout << "\nWhat do you want to update?\n"
		<< "1. Name\n2. Price\n3. Kilos\n"
		<< "Choose an option: ";

	int updateChoice;
	cin >> updateChoice;
	switch (updateChoice) {
	case 1:
		cout << "Enter new name: ";
		cin >> mg[modelIndex].parts.name[partIndex];
		break;
	case 2:
		cout << "Enter new price: ";
		cin >> mg[modelIndex].parts.price[partIndex];
		break;
	case 3:
		cout << "Enter new replacement interval (km): ";
		cin >> mg[modelIndex].parts.kilos[partIndex];
		break;
	default:
		cout << "\n[!] Invalid option!\n";
		return;
	}
	ofstream outFile(mg[modelIndex].model + ".txt");
	for (int i = 0; i < mg[modelIndex].parts.part_count; i++) {
		outFile << mg[modelIndex].parts.name[i] << " "
			<< mg[modelIndex].parts.price[i] << " "
			<< mg[modelIndex].parts.kilos[i] << " "
			<< mg[modelIndex].parts.part_num[i] << "\n";
	}
	outFile.close();

	cout << "\n[✓] Part updated successfully!\n";
}
void viewServices() {
	cout << "\033[2J\033[H";
	ifstream file("services.txt");
	sforservice.service_count = 0;

	cout << "\n==================================" << endl;
	cout << "           Services List          " << endl;
	cout << "==================================" << endl;


	if (file.is_open()) {
		while (sforservice.service_count < max_service &&
			file >> sforservice.name[sforservice.service_count]
			>> sforservice.price[sforservice.service_count]
			>> sforservice.kilos[sforservice.service_count]) {

			int i = sforservice.service_count;
			cout << i + 1 << ". Service Name : " << sforservice.name[i] << endl;
			cout << "   Price       : " << sforservice.price[i] << " LE" << endl;
			cout << "   Due at      : " << sforservice.kilos[i] << " km" << endl;
			cout << "----------------------------------" << endl;
			sforservice.service_count++;
		}
		file.close();

		if (sforservice.service_count == 0) {
			cout << "[!] No services available." << endl;
		}
	}
	else {
		cout << "[!] Error: Could not open services.txt file." << endl;

	}
}
void addServices() {
	cout << "\033[2J\033[H";
	serviceCounts();
	ifstream inFile("services.txt");
	sforservice.service_count = 0;
	if (inFile.is_open()) {
		while (sforservice.service_count < max_service &&
			inFile >> sforservice.name[sforservice.service_count]
			>> sforservice.price[sforservice.service_count]
			>> sforservice.kilos[sforservice.service_count]) {
			sforservice.service_count++;
		}
		inFile.close();
	}

	int num;
	cout << "\n======== ADD SERVICES ========\n";
	cout << "Current services: " << sforservice.service_count << "\n";
	cout << "How many services do you want to add? " << endl;
	cin >> num;

	if (num <= 0 || num > max_service - sforservice.service_count) {
		cout << "❌ Invalid number of services to add.\n";
		return;
	}

	for (int i = 0; i < num; i++) {
		cout << "\nService #" << sforservice.service_count + 1 << ":\n";
		cout << "  Name : ";
		cin >> sforservice.name[sforservice.service_count];
		cout << "  Cost : ";
		cin >> sforservice.price[sforservice.service_count];
		cout << "  Due at (km): ";
		cin >> sforservice.kilos[sforservice.service_count];
		sforservice.service_count++;
	}
	ofstream outFile("services.txt");
	for (int i = 0; i < sforservice.service_count; i++) {
		outFile << sforservice.name[i] << " "
			<< sforservice.price[i] << " "
			<< sforservice.kilos[i] << endl;
	}
	outFile.close();
	Counter_s.num_service = sforservice.service_count;
	saveServiceCount();

	cout << "\n✅ Successfully added " << num << " service(s).\n";
	cout << "📦 Total services now: " << sforservice.service_count << "\n";
}
void updateservice()
{
	cout << "\033[2J\033[H";
	string name;
	double cost;
	string x;
	ifstream inFile("services.txt");
	if (inFile.is_open())
	{
		while (sforservice.service_count < max_service && inFile >> sforservice.name[sforservice.service_count] >> sforservice.price[sforservice.service_count] >> sforservice.kilos[sforservice.service_count]) {
			sforservice.service_count++;
		}
		inFile.close();
	}

	cout << "\n======== UPDATE SERVICE ========\n";
	cout << "Enter service name to update: ";
	cin >> name;
	for (int i = 0; i < sforservice.service_count; i++) {
		if (sforservice.name[i] == name)
		{
			cout << "What would you like to update (name/cost)? ";
			cin >> x;
			if (x == "name" || x == "Name" || x == "NAME") {
				cout << endl << "Enter new name" << endl;
				cin >> sforservice.name[i];
			}
			else if (x == "cost" || x == "Cost" || x == "COST") {
				cout << endl << "Enter new cost" << endl;
				cin >> sforservice.price[i];
			}
			else {
				cout << "❌ Invalid option.\n";
				return;
			}
			ofstream outFile("services.txt");
			for (int j = 0; j < sforservice.service_count; j++) {
				outFile << sforservice.name[j] << " " << sforservice.price[j] << " " << sforservice.kilos[j] << endl;
			}
			outFile.close();

			cout << "✅ Service updated successfully.\n";
			return;
		}
	}
	cout << "❌ Service not found.\n";
}
void searchparts()
{
	cout << "------------------------" << endl;
	cout << "1. MG5" << endl;
	cout << "2. MG6" << endl;
	cout << "3. MGZS" << endl;
	cout << "4. MG7" << endl;
	cout << "5. MGRXPlus" << endl;
	cout << "6. MGHS" << endl;
	cout << "------------------------" << endl;
	cout << "Choose a number: ";
	int num;
	cin >> num;
	if (num < 1 || num > 6) {
		cout << "Invalid choice! Please choose a number between 1 and 6." << endl;
		return;
	}
	cout << "Enter part name to search: ";
	string searchingpart;
	cin >> searchingpart;
	bool found = false;
	if (num == 1)
	{
		ifstream files("mg5.txt");
		if (files.is_open()) {
			while (mg[0].parts.part_count < max_parts &&
				files >> mg[0].parts.name[mg[0].parts.part_count]
				>> mg[0].parts.price[mg[0].parts.part_count]
				>> mg[0].parts.kilos[mg[0].parts.part_count]
				>> mg[0].parts.part_num[mg[0].parts.part_count]) {
				mg[0].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[0].parts.part_count;i++)
		{
			ifstream inFile("mg5.txt");
			{
				if (mg[0].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[0].parts.name[i] << endl;
					cout << "Price : " << mg[0].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}
	if (num == 2)
	{
		ifstream files("mg6.txt");
		if (files.is_open()) {
			while (mg[1].parts.part_count < max_parts &&
				files >> mg[1].parts.name[mg[1].parts.part_count]
				>> mg[1].parts.price[mg[1].parts.part_count]
				>> mg[1].parts.kilos[mg[1].parts.part_count]
				>> mg[1].parts.part_num[mg[1].parts.part_count]) {
				mg[1].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[1].parts.part_count;i++)
		{
			ifstream inFile("mg6.txt");
			{
				if (mg[1].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[1].parts.name[i] << endl;
					cout << "Price : " << mg[1].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}
	if (num == 3)
	{
		ifstream files("mgzs.txt");
		if (files.is_open()) {
			while (mg[2].parts.part_count < max_parts &&
				files >> mg[2].parts.name[mg[2].parts.part_count]
				>> mg[2].parts.price[mg[2].parts.part_count]
				>> mg[2].parts.kilos[mg[2].parts.part_count]
				>> mg[2].parts.part_num[mg[2].parts.part_count]) {
				mg[2].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[2].parts.part_count;i++)
		{
			ifstream inFile("mgzs.txt");
			{
				if (mg[2].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[2].parts.name[i] << endl;
					cout << "Price : " << mg[2].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}
	if (num == 4)
	{
		ifstream files("mg7.txt");
		if (files.is_open()) {
			while (mg[3].parts.part_count < max_parts &&
				files >> mg[3].parts.name[mg[3].parts.part_count]
				>> mg[3].parts.price[mg[3].parts.part_count]
				>> mg[3].parts.kilos[mg[3].parts.part_count]
				>> mg[3].parts.part_num[mg[3].parts.part_count]) {
				mg[3].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[3].parts.part_count;i++)
		{
			ifstream inFile("mg7.txt");
			{
				if (mg[3].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[3].parts.name[i] << endl;
					cout << "Price : " << mg[3].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}
	if (num == 5)
	{
		ifstream files("mgrxplus.txt");
		if (files.is_open()) {
			while (mg[4].parts.part_count < max_parts &&
				files >> mg[4].parts.name[mg[4].parts.part_count]
				>> mg[4].parts.price[mg[4].parts.part_count]
				>> mg[4].parts.kilos[mg[4].parts.part_count]
				>> mg[4].parts.part_num[mg[4].parts.part_count]) {
				mg[4].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[4].parts.part_count;i++)
		{
			ifstream inFile("mgrxplus.txt");
			{
				if (mg[4].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[4].parts.name[i] << endl;
					cout << "Price : " << mg[4].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}
	if (num == 6)
	{
		ifstream files("mghs.txt");
		if (files.is_open()) {
			while (mg[5].parts.part_count < max_parts &&
				files >> mg[5].parts.name[mg[5].parts.part_count]
				>> mg[5].parts.price[mg[5].parts.part_count]
				>> mg[5].parts.kilos[mg[5].parts.part_count]
				>> mg[5].parts.part_num[mg[5].parts.part_count]) {
				mg[5].parts.part_count++;
			}
		}
		for (int i = 0;i < mg[5].parts.part_count;i++)
		{
			ifstream inFile("mghs.txt");
			{
				if (mg[5].parts.name[i] == searchingpart)
				{
					cout << "\nPart Found:" << endl;
					cout << "------------------------------" << endl;
					cout << "Name  : " << mg[5].parts.name[i] << endl;
					cout << "Price : " << mg[5].parts.price[i] << endl;
					cout << "------------------------------" << endl;
					found = true;
					break;
				}
			}
		}
		if (!found)
		{
			cout << "Part not found!! ";
		}
	}

}
bool user_car_mg()
{
	string car;
	int year;
	int distance;
	int month;
	cout << "                 " << "*============* MG Motor Vehicle *=============*" << endl;
	cout << "Please Enter your car model :";
	cin >> car;
	cout << "------------------------------------" << endl;
	cout << "Please enter year :";
	while (1)
	{
		cin >> year;
		cin.ignore();
		if (year <= 2016 || year >= 2026)
		{
			cout << "There is No Car with this year!!" << endl;
			cout << "---------------------------------" << endl;
			cout << "Please Enter another year : ";
			continue;

		}
		if (year >= 2017 && year <= 2025)
			break;
	}
	cout << "-------------------------" << endl;
	cout << "Please enter mileage : ";
	cin >> distance;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input! Try again.\n";
	}
	cout << "-----------------------------" << endl;
	cout << "In how many month(s) : ";
	while (1)
	{

		cin >> month;
		cin.ignore();
		if (month >= 6 && month <= 36)
			break;
		if (month <= 5)
		{
			cout << "tooo....looooww :( " << endl;
			cout << "-------------------------------" << endl;
			cout << "Please enter another month(s) : ";
			continue;
		}
		if (month >= 37)
		{
			cout << "tooo....highhh :( " << endl;
			cout << "-------------------------------" << endl;
			cout << "Please enter another month(s) : ";
			continue;
		}


	}
	int check = 0;
	for (int i = 0; i < 6; i++)
	{
		if (car == mg[i].model)
		{
			current_mg_car = i;
			check = 1;
			break;
		}

	}
	if (check == 1)
	{
		cout << "car found\n";
		system("pause");

		mg[current_mg_car].year = year;
		mg[current_mg_car].meliage = distance;
		mg[current_mg_car].months = month;
		return true;
	}
	else
	{
		cout << "your model is not supported\n";
		system("pause");
		return false;
	}
}
void admin_input() // DONE WITH FILES
{
	ofstream taxes; //create file
	taxes.open("tax.txt");//open file 

	cout << "Enter Tax:" << endl;
	while (1)
	{
		cin >> tax.tax_admin;
		tax.tax_admin /= 100;
		if (tax.tax_admin >= 0)
			cout << "Tax is: " << tax.tax_admin * 100 << "%" << endl;
		if (tax.tax_admin < 0)
		{
			cout << "Invalid tax!!" << endl;
			cout << "Enter new tax: " << endl;
		}
		else
			break;
	}
	taxes << tax.tax_admin;
}
double service_tax(double elreturn_bta3_maintenance)
{
	ifstream taxes; //create file
	taxes.open("tax.txt");//open file 
	taxes >> tax.tax_admin;
	tax.tax_service = tax.tax_admin * elreturn_bta3_maintenance;
	return tax.tax_service;
}
double part_tax(double elreturn_bta3_maintenance)
{
	ifstream taxes; //create file
	taxes.open("tax.txt");//open file 
	taxes >> tax.tax_admin;
	tax.tax_parts = tax.tax_admin * elreturn_bta3_maintenance;
	return tax.tax_parts;
}
void output_tax() // total tax included
{
	cout << "Total Tax is: " << tax.tax_parts + tax.tax_service << " LE" << endl;
}
void change_tax() // aaml file?? 
{
	ofstream taxes; //create file
	taxes.open("tax.txt");
	cout << "Enter new tax: " << endl;
	while (1)
	{
		cin >> tax.tax_admin;
		tax.tax_admin /= 100;
		if (tax.tax_admin >= 0)
		{
			cout << "Tax changed successfully" << endl;
			cout << "New tax is: " << tax.tax_admin * 100 << "%" << endl;
			break;

		}
		if (tax.tax_admin < 0)
		{
			cout << "Invalid tax!! " << endl;
			cout << "Enter new tax: " << endl;
		}
	}
	taxes << tax.tax_admin;
}
double discount_coupon(double& sum) // Discount with coupon  w lazm nsheelo mn el sum fel akherrr
//coupon =5505 aashan 3eed melady :)
{
	string answer;
	int coupon; // aamlo int wala string?? aashan lw dkhlt el coupon string byaaml infinte loop
	cout << "Do you have coupon? " << endl;
	cin >> answer;
	if (answer == "Yes" || answer == "yes")
	{
		while (1)
		{
			cout << "Enter coupon: ";
			cin >> coupon;
			if (coupon == 5505)
			{
				cout << "You have 15% off now!! " << endl;
				cout << "Congrats " << sum * 15 / 100 << " LE was deducted from your bill" << endl;
				cout << "Pay " << sum - sum * 15 / 100 << " LE" << endl;
				sum = sum - sum * 15 / 100;
				break;

			}
			if (coupon != 5505)
			{
				cout << "Invalid coupon! " << endl;
				cout << "Do you have another coupon? " << endl;
				cin >> answer;
				if (answer == "no" || answer == "No" || answer == "NO")
				{
					cout << "Pay " << sum << " LE" << endl;
					break;
				}
				if (answer == "yes" || answer == "Yes" || answer == "YES")
					continue;
			}
		}
	}
	if (answer == "no" || answer == "No" || answer == "NO")
		return sum;
}
double discount(double& sum) // discount when sum>=3000
{
	//if sum>=3000 10% off      
	if (sum >= 6000)
	{
		cout << "You have discount 10%!!" << endl;
		cout << "Congrats " << sum * 10 / 100 << " LE was deducted from your bill" << endl;
		cout << "Pay " << sum - sum * 10 / 100 << " LE" << endl;
		sum = sum - sum * 10 / 100;
	}
	else
	{
		cout << "You have no discount" << endl;
	}
	return sum;
}
void payment_method(double total)
{
	string payment, card_no;
	int cvv;
	cout << "Payment method: " << endl;
	cout << "1.Cash " << endl;
	cout << "2.Debit/Credit card" << endl;
	cout << "Enter payment method: ";
	while (1)
	{
		cin >> payment;
		if (payment == "1")
		{
			cout << "Pay : " << total << " LE " << endl;
			break;
		}
		if (payment == "2")
		{
			cout << "Enter card number: " << endl;
			cin >> card_no;
			cout << "Enter cvv: " << endl;
			cin >> cvv;
			cout << "Successuful payment!" << endl;
			cout << total << " LE deducted from your balance" << endl;
			break;
		}
		if (payment != "1" || payment != "2")
		{
			cout << "choose from 1 & 2 :(" << endl;
			cout << "1.Cash " << endl;
			cout << "2.Debit/Credit card" << endl;
			cout << "Enter payment method: ";
		}

	}
	cout << "Thank you:) " << endl;
}
void rating()
{
	string answer;
	int rate;

	cout << "Do you want to rate ??" << endl;
	while (1)
	{
		cin >> answer;

		if (answer == "No" || answer == "no")
			break;
		if (answer == "Yes" || answer == "yes")
		{
			cout << "1.Very bad" << endl;
			cout << "2.Bad" << endl;
			cout << "3.Good" << endl;
			cout << "4.Very Good" << endl;
			cout << "5.Excellent" << endl;
			cout << "Chooce your rate :";
			while (1)
			{
				cin >> rate;

				if (rate == 1 || rate == 2)
				{
					cout << "Why didn't you enjoy our system!?" << endl;
					cin >> answer;
					cout << "Thank You !!" << endl;
					break;
				}
				if (rate == 3 || rate == 4 || rate == 5)
				{
					cout << "Thank You !! ;)" << endl;
					break;
				}
				else
					cout << "Rate from 1 to 5: ";
			}
			break;
		}
		else
			cout << "yes or no" << endl;
	}
}
double total;
void calc() {
	int mileage = mg[current_mg_car].meliage;

	cost_p = 0;
	cost_s = 0;

	if (mileage >= 0 && mileage < 10000) {
		cout << "No need for changing parts or services.\n";
	}
	else if (mileage >= 10000 && mileage < 15000) {
		cout << "Mileage Range: 10,000 - 14,999 km\n";
		for (int i = 0; i < Counter_p.numParts[current_mg_car]; i++) {
			if (mg[current_mg_car].parts.kilos[i] == 10000) {
				cout << "  Part: " << mg[current_mg_car].parts.name[i] << " | Price: " << mg[current_mg_car].parts.price[i] << endl;
				cost_p += mg[current_mg_car].parts.price[i];
			}
		}

		cout << "Services: \n";
		for (int i = 0; i < Counter_s.num_service; i++) {
			if (sforservice.kilos[i] == 10000) {
				cout << "  Service: " << sforservice.name[i] << " | Price: " << sforservice.price[i] << endl;
				cost_s += sforservice.price[i];
			}
		}
	}
	else if (mileage >= 15000 && mileage < 20000) {
		cout << "Mileage Range: 15,000 - 19,999 km\n";
		for (int i = 0; i < Counter_p.numParts[current_mg_car]; i++) {
			if (mg[current_mg_car].parts.kilos[i] == 10000 || mg[current_mg_car].parts.kilos[i] == 20000) {
				cout << "  Part: " << mg[current_mg_car].parts.name[i] << " | Price: " << mg[current_mg_car].parts.price[i] << endl;
				cost_p += mg[current_mg_car].parts.price[i];
			}
		}

		cout << "Services: \n";
		for (int i = 0; i < Counter_s.num_service; i++) {
			if (sforservice.kilos[i] == 10000 || sforservice.kilos[i] == 20000) {
				cout << "  Service: " << sforservice.name[i] << " | Price: " << sforservice.price[i] << endl;
				cost_s += sforservice.price[i];
			}
		}
	}
	else if (mileage >= 20000 && mileage < 30000) {
		cout << "Mileage Range: 20,000 - 29,999 km\n";
		for (int i = 0; i < Counter_p.numParts[current_mg_car]; i++) {
			if (mg[current_mg_car].parts.kilos[i] == 10000 || mg[current_mg_car].parts.kilos[i] == 20000 || mg[current_mg_car].parts.kilos[i] == 30000) {
				cout << "  Part: " << mg[current_mg_car].parts.name[i] << " | Price: " << mg[current_mg_car].parts.price[i] << endl;
				cost_p += mg[current_mg_car].parts.price[i];
			}
		}

		cout << "Services: \n";
		for (int i = 0; i < Counter_s.num_service; i++) {
			if (sforservice.kilos[i] == 10000 || sforservice.kilos[i] == 20000) {
				cout << "  Service: " << sforservice.name[i] << " | Price: " << sforservice.price[i] << endl;
				cost_s += sforservice.price[i];
			}
		}
	}
	else if (mileage >= 30000 && mileage < 40000) {
		cout << "Mileage Range: 30,000 - 39,999 km\n";
		for (int i = 0; i < Counter_p.numParts[current_mg_car]; i++) {
			if (mg[current_mg_car].parts.kilos[i] == 10000 || mg[current_mg_car].parts.kilos[i] == 20000 || mg[current_mg_car].parts.kilos[i] == 30000 || mg[current_mg_car].parts.kilos[i] == 40000) {
				cout << "  Part: " << mg[current_mg_car].parts.name[i] << " | Price: " << mg[current_mg_car].parts.price[i] << endl;
				cost_p += mg[current_mg_car].parts.price[i];
			}
		}

		cout << "Services: \n";
		for (int i = 0; i < Counter_s.num_service; i++) {
			if (sforservice.kilos[i] == 10000 || sforservice.kilos[i] == 20000) {
				cout << "  Service: " << sforservice.name[i] << " | Price: " << sforservice.price[i] << endl;
				cost_s += sforservice.price[i];
			}
		}
	}
	else if (mileage >= 40000) {
		cout << "Mileage Range: 40,000+ km\n";
		for (int i = 0; i < Counter_p.numParts[current_mg_car]; i++) {
			cout << "  Part: " << mg[current_mg_car].parts.name[i] << " | Price: " << mg[current_mg_car].parts.price[i] << endl;
			cost_p += mg[current_mg_car].parts.price[i];
		}

		cout << "Services: \n";
		for (int i = 0; i < Counter_s.num_service; i++) {
			if (sforservice.kilos[i] == 10000 || sforservice.kilos[i] == 20000 || sforservice.kilos[i] == 30000) {
				cout << "  Service: " << sforservice.name[i] << " | Price: " << sforservice.price[i] << endl;
				cost_s += sforservice.price[i];
			}
		}
	}
	part_tax(cost_p);
	service_tax(cost_s);
	cout << "------------------------------------\n";
	cout << "Total Estimated Cost: $" << (cost_p + cost_s + tax.tax_parts + tax.tax_service) << endl;
	cout << "------------------------------------\n";
	total = cost_p + cost_s + tax.tax_parts + tax.tax_service;
	discount(total);
	discount_coupon(total);

}
void detailed_cost()
{
	cout << "Total bill was: " << cost_s + cost_p + tax.tax_parts + tax.tax_service << " LE " << endl;
	cout << "Now total bill is: " << total << " LE divided to " << endl;
	cout << "Cost of parts: " << cost_p << " LE " << endl;
	cout << "Cost of services: " << cost_s << " LE " << endl;
	service_tax(cost_s);
	part_tax(cost_p);
	cout << "Taxes of services: " << tax.tax_service << " LE " << endl;
	cout << "Taxes of parts: " << tax.tax_parts << endl;
}

void mainmenu()
{
	string username, password;
	char visitor;
	cout << "        Welcome to our Motor Vehicle Service Cost Estimation!" << endl;
	cout << "       ******* ******* ******* ******* ******* ******* ******** " << endl;

	while (shouldShowMainMenu)
	{
		cout << "\nPress" << endl;
		cout << "U to Login as a User" << endl;
		cout << "S to Signup as a User" << endl;
		cout << "A to Login as an Admin" << endl;
		cout << "E to Exit" << endl;

		cin >> visitor;

		if (visitor == 'a' || visitor == 'A')
		{
			clearScreen();
			cout << "Enter Admin Username: ";
			cin >> username;
			cout << "Enter Admin Password: ";
			cin >> password;
			login(username, password);
		}
		else if (visitor == 'u' || visitor == 'U')
		{
			clearScreen();
			cout << "Enter User Username: ";
			cin >> username;
			cout << "Enter User Password: ";
			cin >> password;
			userLogin(username, password);
		}
		else if (visitor == 's' || visitor == 'S')
		{
			clearScreen();
			signupUser();
		}
		else if (visitor == 'e' || visitor == 'E')
		{
			cout << "Exiting the application. Goodbye!" << endl;//rate hena
			rating();

			shouldShowMainMenu = false;
		}
		else
		{
			cout << "Invalid input, Please try again." << endl;
		}
	}
}
void AdminMenu()
{
	char choice;
	do
	{
		cout << "\n--- Admin Menu ---" << endl;
		cout << "Logged in as: " << loggedInAdminUsername << endl;
		cout << "1. Add/Update Parts" << endl;
		cout << "2. Add/Update Services" << endl;
		cout << "3. Set/Update Tax Rates" << endl;
		cout << "4. Search System" << endl;
		cout << "5. Logout" << endl;

		cout << "Enter your choice: ";
		cin >> choice;
		clearScreen();
		switch (choice)
		{
		case '1':
			cout << "1. Add Parts\n2. Update Parts";
			int num1;
			cin >> num1;
			for (int i = 0;i < 100;i++)
			{
				if (num1 == 1)
				{
					load_model();
					partscount();
					costofparts();
					addParts();
					break;
				}

				else if (num1 == 2)
				{
					load_model();
					partscount();
					costofparts();
					updateParts();
					break;
				}
				else
				{
					cout << "wrong number.\nenter another number: ";
					cin >> num1;
				}
			}
			break;
		case'2':
			cout << "1. Add Services\n2. Update Services";
			int num2;
			cin >> num2;
			for (int i = 0;i < 100;i++)
			{
				if (num2 == 1)
				{
					load_model();
					addServices();
					serviceCounts();
					cost_service();

					break;
				}

				else if (num2 == 2)
				{
					load_model();
					updateservice();
					serviceCounts();
					cost_service();
					break;
				}
				else
				{
					cout << "wrong number.\nenter another number: " << endl;
					cin >> num2;
				}
			}
			break;
		case '3':
			cout << "1. set tax\n2. Update tax\n";
			int num3;
			cin >> num3;
			if (num3 == 1)
			{
				admin_input();
			}
			else if (num3 == 2)
			{
				change_tax();
			}
			else
			{
				cout << "invalid number!!!" << endl;
			}

			break;
		case '4':
			cout << "1. Search Parts\n2. Search Services";
			int num4;
			cin >> num4;
			if (num4 == 1)
			{
				searchparts();
			}
			else if (num4 == 2)
			{
				searchservice();
			}
			else
			{
				cout << "wrong input";
			}
		case '5':
			logout();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 6 && isAdminLoggedIn);
}

void UserMenu()
{
	cout << "\n--- User Menu ---" << endl;
	cout << "Logged in as: " << loggedInUserUsername << endl;
	//user functions
	int choice;
	do
	{
		cout << "\n--- User Menu ---" << endl;
		cout << "1. Show Parts" << endl;
		cout << "2. Show Services" << endl;
		cout << "3. Manage Maintenance Schedules" << endl;
		cout << "4. Detailed Cost Estimation" << endl;
		cout << "5. paying method" << endl;
		cout << "6. Logout" << endl;

		cout << "Enter your choice: ";
		cin >> choice;
		cout << "\033[2J\033[H"; //clear screen
		switch (choice)
		{


		case 1:

			load_model();
			partscount();
			costofparts();
			viewparts();
			break;
		case 2:

			load_model();
			viewServices();
			serviceCounts();
			cost_service();

			break;

		case 3:
			load_model();
			partscount();
			serviceCounts();
			cost_service();
			costofparts();
			if (!user_car_mg())
			{
				break;
			}
			calc();
			break;
		case 4:
			detailed_cost();
			break;
		case 5:
			payment_method(total);
			break;
		case 6:
			logout();

			break;
		default:
			cout << "Invalid Number, Please Try Again" << endl;
		}
	} while (choice != 6);
	shouldShowMainMenu = true;


}


void logout()
{
	if (isAdminLoggedIn)
	{
		isAdminLoggedIn = false;
		loggedInAdminUsername = "";
		cout << "Admin logged out successfully. Returning to the main menu." << endl;
	}
	else if (isUserLoggedIn)
	{
		isUserLoggedIn = false;
		loggedInUserUsername = "";
		cout << "User logged out successfully. Returning to the main menu." << endl;
	}
	shouldShowMainMenu = true;
	mainmenu();
}
int main()
{
	initializeAdmins();
	initializeUsers();
	load_model();
	mainmenu();
}