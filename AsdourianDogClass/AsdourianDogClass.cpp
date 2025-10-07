//-----------------------------------------------------------------------------
// Aram Asdourian   CMPSC330   2/24/2025
//
// creates the dog class as described in assignments
// the class lets the user manage a dog kennel
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

//constant vector of valid dog breeds
const vector<string> dogBreeds = { "Husky", "Dachshund", "Corgi", "Poodle"};

//constant vector of the age charts
//the numbers location in the vector is the age in dog years and the numbers value is in human years
//example humanYearsChartSmall[5] == 36, so 5 years in dog years is 36 in human years
const vector<int> humanYearsChartSmall = {0, 15, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80};
const vector<int> humanYearsChartMedium = {0, 15, 24, 28, 32, 36, 42, 47, 51, 56, 60, 65, 69, 74, 78, 83, 87};
const vector<int> humanYearsChartLarge = {0, 15, 24, 28, 32, 36, 45, 50, 55, 61, 66, 72, 77, 82, 88, 93, 120};
//-----------------------------------------------------------------------------
// Class name: dog
// 
// created by: Aram Asdourian 2/24/2025
// 
// description:
// allows the user to manage a dog kennel and assign and view values to dogs such as:
// name, weight, gender, breed, birthday, health, shot status, months in kennel, and age in dog as well as human years
// 
// functions:
// 
// setName / getName
//     lets the user give the dog a name and view the name
// 
// setWeight / getWeight
//		lets the user give the dog a weight and view the weight
// 
// setGender / getGender
//		lets the user give the dog a gender and view the gender
// 
// setBreed / getBreed
//		lets the user give the dog a breed and view the breed, also checks if the breed is valid for the kennel
// 
// setBirthDate / getBirthDate
//		lets the user give the dog a BirthDay and view the birthday, also checks if the numbers entered are valid dates
// 
// setHealthRating / getHealthRating
//		lets the user assign the dogs health a rating and view the rating, checks if the rating is within the valid 1-5 range
// 
// setHasShots / getHasShots
//		lets the user say whether the dog has had their shots or not and view if they had
// 
// setMonthsInKennel / getMonthsInKennel
//		lets the user give and view how many months the dog has been in the kennel
// 
// inHumanYears
//		gives the user the dogs age in dog and human years, checks if the dog was given a birthday and weight first
//		the human years are found by referencing 3 constant charts, the weight is used to decide which chart is appropriate for the dogs size
//		
//-----------------------------------------------------------------------------
class dog
{
private:
	//initializes all the variables
	string name;
	string gender;
	string breed;
	int weight;
	string birthDate;
	int health;
	bool hasShots;
	int monthsInKennel;

public:
//got help with constructors from here: https://www.geeksforgeeks.org/constructors-c/
	dog()
	{
		name = "";
		gender = "";
		breed = "";
		weight = 0;
		birthDate = "";
		health = 0;
		hasShots = false;
		monthsInKennel = -1;
	}

//-----------------------------------------------------------------------------

	string setName()
	{
		//asks for the name and writes it to the variable
		cout << "\nEnter the name of dog: "; cin >> name;
		return "The name of the dog is now '" + name + "'.\n\n";
	}

//-----------------------------------------------------------------------------	

	string getName()
	{
		//returns the name, gives an error if no name was made
		string getNameOutput;
		if (name == "")
		{
			getNameOutput = "\nThe dogs name is unknown.\n\n";
		}
		else
		{
			getNameOutput = "\nThe name of the dog is '" + name + "'.\n\n";
		}
		return getNameOutput;
	}

//-----------------------------------------------------------------------------

	string setWeight()
	{
		cout << "\nEnter the weight of dog in pounds: "; cin >> weight;
		//checks for invalid inputs and prompts again
		while (weight <= 0 or weight > 350)
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid weight, Enter the weight of dog: "; cin >> weight;
		} 

		return "\nThe weight of the dog is now " + to_string(weight) + "lbs.\n\n";
	}

//-----------------------------------------------------------------------------

	string getWeight()
	{
		//returns the weight or an error if there is none
		string getWeightOutput;
		if (weight == 0)
		{
			getWeightOutput = "\nThe weight of the dog is unknown.\n\n";
		}
		else 
		{
			getWeightOutput = "\nThe weight of the dog is " + to_string(weight) + "lbs.\n\n";
		}
		return getWeightOutput;
	}

//-----------------------------------------------------------------------------

	string setGender()
	{
		//prompts user to type m or f for the dogs gender
		string genderInput;
		cout << "\nType 'M' if dog is male or 'F' if dog is female: "; cin >> genderInput;
		//checks for both upper and lowercase inputs
		while (genderInput != "m" and genderInput != "M" and genderInput != "f" and genderInput != "F")
		{
			cout << "\ninvalid input, type 'M' if dog is male or 'F' if dog is female: "; cin >> genderInput;
		}
		if (genderInput == "m" or genderInput == "M")
		{
			cout << "test";
			//i decided to make it a string instead of a bool because i think it looks nicer and works better with getGender()
			gender = "Male";
		}
		if (genderInput == "f" or genderInput == "F")
		{
			gender = "Female";
		}
		return "\nThe dogs gender is now " + gender + ".\n\n";
	}

//-----------------------------------------------------------------------------

	string getGender()
	{
		//returns the gender or an error if there is none
		string getGenderOutput;
		if (gender == "")
		{
			getGenderOutput = "\nThe dogs gender is unknown.\n\n";
		}
		else
		{
			getGenderOutput = "\nThe dogs gender is " + gender + ".\n\n";
		}
		return getGenderOutput;
	}

//-----------------------------------------------------------------------------

	string setBreed()
	{
		cout << "\nEnter the dog breed (Valid breeds are ";
		//iterates over the list of dog breeds to print them out
		//i could have just manually wrote them in the cout but then it wouldnt change if i wanted to change the list
		for (int i = 0; i < dogBreeds.size()-1; i++)
		{
			cout << dogBreeds[i] + ", ";
		}
		cout << "and " + dogBreeds.back() + "): ";
		
		cin >> breed;
		//converts the user input to lower case and then capitalizes the first letter just in case the user used improper capitalization
		// got help with converting to lowercase from here: https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
		transform(breed.begin(), breed.end(), breed.begin(), tolower);
		//got help with capitalizing first letter here: https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
		breed[0] = toupper(breed[0]);

		//goes through the entire prompt again if the input is invalid
		while (breed != "Husky" and breed != "Dachshund" and breed != "Corgi" and breed != "Poodle")
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid input, enter the dog breed (Valid breeds are ";
			for (int i = 0; i < dogBreeds.size() - 1; i++)
			{
				cout << dogBreeds[i] + ", ";
			}
			cout << "and " + dogBreeds.back() + "): "; cin >> breed;
			transform(breed.begin(), breed.end(), breed.begin(), tolower);
			breed[0] = toupper(breed[0]);
		}
		return "\nThe dogs breed is now "+ breed + ".\n\n";
	}

//-----------------------------------------------------------------------------
	
	string getBreed()
	{
		//returns the breed or an error if there is none
		string getBreedOutput;
		if (breed == "")
		{
			getBreedOutput = "\nThe dogs breed is unknown.\n\n";
		}
		else
		{
			getBreedOutput = "\nThe dogs breed is " + breed +".\n\n";
		}
		return getBreedOutput;
	}

//-----------------------------------------------------------------------------
		
	string setBirthDate()
	{
		//clears the birthDate variable and initializes the months, days, and year variables
		birthDate = "";
		int months;
		int days;
		int years;

		//asks for the month and checks if its a valid month
		cout << "\nEnter the month of the dogs Birhtday(xx): "; cin >> months;
		while (months < 1 or months > 12)
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid input, enter the month of the dogs Birhtday(xx): "; cin >> months;
		}
		//if the month is less than 10 a 0 has to be appended before the number, otherwise the entire number is appended
		if (months < 10)
		{
			birthDate += "0" + to_string(months) + "/";
		}
		else
		{
			birthDate += to_string(months) + "/";
		}
		
		//does the same for days
		cout << "\nEnter the day of the dogs Birhtday(xx): "; cin >> days;
		while (days < 1 or days > 31)
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid input, enter the day of the dogs Birhtday(xx): "; cin >> days;
		}
		//if the day is less than 10 a 0 has to be appended before the number, otherwise the entire number is appended
		if (months < 10)
		{
			birthDate += "0" + to_string(days) + "/";
		}
		else
		{
			birthDate += to_string(days) + "/";
		}

		//does the same for years
		cout << "\nEnter the year of the dogs Birhtday(xxxx): "; cin >> years;
		//the dog years to human years chart i found only goes up to 16 years old
		//so the class only accepts birthdays up to 16 years ago(2009)
		while (years < 2009 or years > 2025)
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid input, enter the year of the dogs Birhtday(xxxx): "; cin >> years;
		}
		birthDate += to_string(years);
		return "\nThe dogs birthday is " + birthDate +".\n\n";
	}

//-----------------------------------------------------------------------------
			
	string getBirthDate()
	{
		//returns the birthdate or an error if there is none
		string getBirthDateOutput;
		if (birthDate == "")
		{
			getBirthDateOutput = "\nThe dogs birthday is unknown.\n\n";
		}
		else
		{
			getBirthDateOutput = "\nThe dogs birthday is " + birthDate + ".\n\n";
		}
		return getBirthDateOutput;
	}

//-----------------------------------------------------------------------------
		
	string setHealthRating()
	{
		cout << "\nEnter the dogs health rating on a scale of 1-5: "; cin >> health;
		while (health > 5 or health < 1)
		{
			cin.clear(); cin.ignore();
			cout << "\nInvalid input, enter the dogs health rating on a scale of 1-5: "; cin >> health;
		}
		return "\nThe dogs health rating is now " + to_string(health) +".\n\n";
	}

//-----------------------------------------------------------------------------
			
	string getHealthRating()
	{
		//returns the health or an error if there is none
		string getHealthOutput;
		if (health == 0)
		{
			getHealthOutput = "\nThe dogs health is unknown.\n\n";
		}
		else
		{
			getHealthOutput = "\nThe dogs health rating is " + to_string(health) +".\n\n";
		}
		return getHealthOutput;
	}

//-----------------------------------------------------------------------------
		
	string setHasShots()
	{
		string hasShotsInput;
		string hasShotsOutput;
		cout << "\nDoes the dog have their shots? (Y/N): "; cin >> hasShotsInput;
		while (hasShotsInput != "y" and hasShotsInput != "Y" and hasShotsInput != "n" and hasShotsInput != "N")
		{
			cout << "\ninvalid input, does the dog have their shots? (Y/N): "; cin >> hasShots;
		}
		if (hasShotsInput == "y" or hasShotsInput == "Y")
		{
			hasShots = true;
			hasShotsOutput = "\nThe dog has their shots.\n\n";
		}
		if (hasShotsInput == "n" or hasShotsInput ==  "N")
		{
			hasShots = false;
			hasShotsOutput = "\nThe dog does not have their shots.\n\n";
		}
		return hasShotsOutput;
	}

//-----------------------------------------------------------------------------

	string getHasShots()
	{
		//returns the shot status or an error if there is none
		string hasShotsOutput;
		if (hasShots == true)
		{
			hasShotsOutput = "\nThe dog has their shots.\n\n";
		}
		if (hasShots == false)
		{
			hasShotsOutput = "\nThe dog does not have their shots.\n\n";
		}
		if (hasShots == 0)
		{
			hasShotsOutput = "\nIt is unknown whether the dog has shots or not.\n\n";
		}

		return hasShotsOutput;
	}

//-----------------------------------------------------------------------------

	string setMonthsInKennel()
	{
		//prompts the user to give the months until a number above 0 is given
		cout << "\nHow many months has the dog been in the kennel?: "; cin >> monthsInKennel;
		while (monthsInKennel < 0)
		{
			cout << "\ninvalid input, how many months has the dog been in the kennel?: "; cin >> monthsInKennel;
		}

		return "\nThe dog has been in the kennel for " + to_string(monthsInKennel) +" month(s).\n\n";
	}

//-----------------------------------------------------------------------------

	string getMonthsInKennel()
	{
		//returns the months in kennel or an error if there is none
		string getMonthsInKennelOutput;
		if (monthsInKennel < 0)
		{
			getMonthsInKennelOutput = "\nIt is unknown how long the dog has been in the kennel.\n\n";
		}
		else
		{
			getMonthsInKennelOutput = "\nThe dog has been in the kennel for " + to_string(monthsInKennel) +" month(s).\n\n";
		}
		return getMonthsInKennelOutput;
	}

//-----------------------------------------------------------------------------

	string inHumanYears()
	{
		//initializes neccecary variables
		int dogYears;
		int humanYears;
		int currentYear = 2025;
		string inHumanYearsOutput;
		//makes sure that the dog has a birthday and weight so it can do the calculations
		if (birthDate == "" or weight == 0)
		{
			inHumanYearsOutput = "\nThe dogs birthday or weight is unknown.\n\n";
		}
		else
		{
			//first determines dog years by subtracting the year in the birthday with the current year
			dogYears = currentYear - stoi(birthDate.substr(6, 9));
			//determines what the dogs weight is so it can use the correct chart
			if (weight <= 20)
			{
				humanYears = humanYearsChartSmall[dogYears];
			}
			if (weight >= 21 and weight <= 50)
			{
				humanYears = humanYearsChartMedium[dogYears];
			}
			if (weight >= 51)
			{
				humanYears = humanYearsChartLarge[dogYears];
			}
			//creates the output and returns
			inHumanYearsOutput = "\nIn dog years the dog is " + to_string(dogYears) + " year(s) old, in human years that is " + to_string(humanYears) + " year(s) old.\n\n";
		}
		return inHumanYearsOutput;
	}
};



int main()
{
	dog userDog;
	bool programRunning = true;
	while (programRunning)
	{
		int userSelect;
		printf("-----------------------------------------------------------------------------\n");
		printf("Welcome to the kennel, below is your options for activities");
		printf("\n(1)set name         (2) get name");
		printf("\n(3)set weight       (4) get weight");
		printf("\n(5)set gender       (6) get gender");
		printf("\n(7)set breed        (8) get breed");
		printf("\n(9)set birthday     (10) get birthday");
		printf("\n(11)set health      (12) get health");
		printf("\n(13)set shots       (14) get shots");
		printf("\n(15)set kennel time (16) get kennel time");
		printf("\n(17)get human years (0) exit");
		cout << "\nenter your selection: "; cin >> userSelect;
		while (userSelect < 0 or userSelect > 17)
		{
			cin.clear(); cin.ignore();
			printf("\n\nInvalid selection, try again.");
			printf("\n(1)set name         (2) get name");
			printf("\n(3)set weight       (4) get weight");
			printf("\n(5)set gender       (6) get gender");
			printf("\n(7)set breed        (8) get breed");
			printf("\n(9)set birthday     (10) get birthday");
			printf("\n(11)set health      (12) get health");
			printf("\n(13)set shots       (14) get shots");
			printf("\n(15)set kennel time (16) get kennel time");
			printf("\n(17)get human years (0) exit");
			cout << "\nenter your selection: "; cin >> userSelect;
		}
		if (userSelect == 1)
		{
			cout << userDog.setName();
		}

		if (userSelect == 2)
		{
			cout << userDog.getName();
		}

		if (userSelect == 3)
		{
			cout << userDog.setWeight();
		}

		if (userSelect == 4)
		{
			cout << userDog.getWeight();
		}

		if (userSelect == 5)
		{
			cout << userDog.setGender();
		}

		if (userSelect == 6)
		{
			cout << userDog.getGender();
		}

		if (userSelect == 7)
		{
			cout << userDog.setBreed();
		}

		if (userSelect == 8)
		{
			cout << userDog.getBreed();
		}

		if (userSelect == 9)
		{
			cout << userDog.setBirthDate();
		}

		if (userSelect == 10)
		{
			cout << userDog.getBirthDate();
		}

		if (userSelect == 11)
		{
			cout << userDog.setHealthRating();
		}

		if (userSelect == 12)
		{
			cout << userDog.getHealthRating();
		}

		if (userSelect == 13)
		{
			cout << userDog.setHasShots();
		}

		if (userSelect == 14)
		{
			cout << userDog.getHasShots();

		}

		if (userSelect == 15)
		{
			cout << userDog.setMonthsInKennel();
		}

		if (userSelect == 16)
		{
			cout << userDog.getMonthsInKennel();
		}

		if (userSelect == 17)
		{
			cout << userDog.inHumanYears();
		}
		if (userSelect == 0)
		{
			programRunning = false;
		}
	}
}


