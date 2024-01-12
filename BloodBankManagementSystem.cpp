#include<bits/stdc++.h>
#include<conio.h>
using namespace std;


//Classes
class Date
{
public:
    int day, month, year;
    char c,e;

    Date() {}
    Date(int d, char x, int m, char z, int y)
    {
        day = d;
        c = x;
        month = m;
        e = z;
        year = y;
    }
    void inputDate()
    {
        cin>>day>>c>>month>>e>>year;
    }
};

class Donor
{
public:
    string name;
    string gender;
    string bloodType;
    string contactNumber;
    string gmailAddress;
    Date lastDonationDate;
    string status;

    Donor() : status("Not Eligible") {} // Initialize status to "Not Eligible" by default

};



//constant things
const Date currDate(6,'-',12,'-',2023);  //current date (need to update)
const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
      };



//function list
int countLeapYears(Date d);
int getDifference(Date dt1,Date dt2);

void addDonor(vector<Donor>& donors, const string& filename);
void displayDonors(const vector<Donor>& donors);
void searchDonorsByBloodType(const vector<Donor>& donors, const string& bloodType);
void updateDonor(vector<Donor>& donors, const string& filename);
void deleteDonor(vector<Donor>& donors, const string& filename);

void saveDonorsToFile(const vector<Donor>& donors, const string& filename);
void readDonorsFromFile(vector<Donor>& donors, const string& filename);



//Date related functions
int countLeapYears(Date d)
{
    int years = d.year;

    /* Check if the current year needs to be
       considered for the count of leap years
       or not */
    if (d.month <= 2)
        years--;

    /* An year is a leap year if it
       is a multiple of 4,
       multiple of 400 and not a
       multiple of 100. */
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1,Date dt2)
{
    /* COUNT TOTAL NUMBER OF DAYS
       BEFORE FIRST DATE 'dt1' */

    // initialize count using years and day
    long int n1 = dt1.year * 365 + dt1.day;

    // Add days for months in given date
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];

    /* Since every leap year is of 366 days,
       Add a day for every leap year */
    n1 += countLeapYears(dt1);

    /* SIMILARLY, COUNT TOTAL NUMBER OF
       DAYS BEFORE 'dt2' */

    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    // return difference between two counts
    return (n2 - n1);
}



//feature functions
void addDonor(vector<Donor>& donors, const string& filename)
{
    Donor newDonor;
    cout <<endl<< "\t\t      >> Donor Information :" << endl;
    cout << "\t\t     ------------------------" << endl;
    cout << "\n\n\t\t -> Enter Donor Name: ";
    cin.ignore();
    getline(cin, newDonor.name);
    cout << "\n\t\t -> Enter Gender (M/F): ";
    getline(cin, newDonor.gender);
    cout <<endl<< "\t\t -> Enter Blood Type (A/B/AB/O +/-): ";
    cin >> newDonor.bloodType;
    cin.ignore();

    // Validate contact number
    do {
        cout << "\n\t\t -> Enter Contact Number: ";
        getline(cin, newDonor.contactNumber);
        if (newDonor.contactNumber.length() != 11) {
            cout <<endl<< "\n\t\t [Error: Invalid contact number. Please enter exactly 11 digits.]\n"<<endl;
        }
    } while (newDonor.contactNumber.length() != 11);

    // Validate Gmail address
    do {
        cout << "\n\t\t -> Enter Gmail address: ";
        getline(cin, newDonor.gmailAddress);
        if (newDonor.gmailAddress.length() <= 10 ||
            newDonor.gmailAddress.substr(newDonor.gmailAddress.length() - 10) != "@gmail.com") {
            cout <<endl<< "\n\t\t [Error: Invalid Gmail address. Please enter a valid address ending with @gmail.com.]\n"
            <<endl;
        }
    } while (newDonor.gmailAddress.length() <= 10 ||
             newDonor.gmailAddress.substr(newDonor.gmailAddress.length() - 10) != "@gmail.com");

    cout << "\n\t\t -> Enter last date of donating blood (e.g., 29-2-2023): ";
    newDonor.lastDonationDate.inputDate();

    int daysInBetween = getDifference(newDonor.lastDonationDate, currDate);
    if((newDonor.gender == "F" && daysInBetween >= 120) || (newDonor.gender == "M" && daysInBetween >= 90))
        newDonor.status = "Eligible for Blood Donation.";

    donors.push_back(newDonor);

    cout <<endl<<endl<< "\t\t >> Donor added successfully! <<";
    saveDonorsToFile(donors, filename); // Auto save after adding a donor
    cout << "\n" << endl;
}

void displayDonors(const vector<Donor>& donors)
{
    const string filename = "donors.txt";
    if (donors.empty())
    {
        cout << "     >> No donors found. <<" << endl;
    }
    else
    {
        cout <<endl<< "Donors loaded from " << filename << " successfully!" << endl;
        cout <<endl<< "\t  >> List of donors:" << endl;
        cout << "\t ---------------------" << endl;
        for (const auto& donor : donors)
        {
            if(!donor.name.empty() && !donor.bloodType.empty() && !donor.contactNumber.empty())
            {
                cout <<endl<<endl<< "    -> Name: " << donor.name << endl
                     << "    -> Gender: " <<donor.gender<<endl
                     << "    -> Blood Type: " << donor.bloodType << endl
                     << "    -> Contact Number: " << donor.contactNumber << endl
                     << "    -> Gmail Address: " << donor.gmailAddress << endl
                     << "    -> Last Donation Date: " << donor.lastDonationDate.day<<"-"
                     <<donor.lastDonationDate.month<<"-"<<donor.lastDonationDate.year << endl
                     <<"    -> Status: " << donor.status << endl;
            }
        }
    }
    getch();
    system("cls");
}

void searchDonorsByBloodType(const vector<Donor>& donors, const string& bloodType)
{
    bool found = false;
    cout<<endl << "\t  >> Donors with blood type " << bloodType << ":" << endl;
    cout << "\t  ---------------------------" << endl<<endl<<endl;
    for (const auto& donor : donors)
    {
        if (donor.bloodType == bloodType)
        {
            cout << "    -> Name: " << donor.name << endl
                 << "    -> Gender: " <<donor.gender<<endl
                 << "    -> Blood Type: " << donor.bloodType << endl
                 << "    -> Contact Number: " << donor.contactNumber << endl
                 << "    -> Gmail Address: " << donor.gmailAddress << endl
                 << "    -> Last Donation Date: " << donor.lastDonationDate.day<<"-"
                 <<donor.lastDonationDate.month<<"-"<<donor.lastDonationDate.year << endl
                 <<"    -> Status: " << donor.status <<endl<<endl<<endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "     >> No donors found with blood type " << bloodType << "." << endl;
    }
    getch();
    system("cls");
}

void updateDonor(vector<Donor>& donors, const string& filename)
{
    string donorName;
    cout <<endl<<endl<< "\tEnter the name of the donor you want to update: ";
    cin.ignore();
    getline(cin, donorName);

    bool donorFound = false;
    for (Donor& donor : donors)
    {
        if (donor.name == donorName)
        {
            cout << "\tUpdating donor information for " << donorName << ":" << endl<<endl;

            // Validate contact number
            do
            {
                cout << "\t -> Enter new Contact Number: ";
                getline(cin, donor.contactNumber);
                if (donor.contactNumber.length() != 11)
                {
                    cout <<endl<< "\t [Error: Invalid contact number. Please enter exactly 11 digits.]\n"<<endl;
                }
            }
            while (donor.contactNumber.length() != 11);

            // Validate Gmail address
            do
            {
                cout << "\t -> Enter new Gmail address: ";
                getline(cin, donor.gmailAddress);
                if (donor.gmailAddress.length() < 10 ||
                        donor.gmailAddress.substr(donor.gmailAddress.length() - 10) != "@gmail.com")
                {
                    cout <<endl<< "\t [Error: Invalid Gmail address. Please enter a valid address ending with @gmail.com.]\n"
                    <<endl;
                }
            }
            while (donor.gmailAddress.length() < 10 ||
                    donor.gmailAddress.substr(donor.gmailAddress.length() - 10) != "@gmail.com");

            cout << "\t-> Enter new last donation date (e.g., 29-2-2023): ";
            donor.lastDonationDate.inputDate();

            int daysInBetween = getDifference(donor.lastDonationDate, currDate);
            if ((donor.gender == "F" && daysInBetween >= 120) || (donor.gender == "M" && daysInBetween >= 90))
                donor.status = "Eligible for Blood Donation.";
            else
                donor.status = "Not Eligible";

            cout <<endl<< "\tDonor information updated successfully!" << endl;
            saveDonorsToFile(donors, filename); // Save updated donor information
            donorFound = true;
            break; // No need to continue searching
        }
    }

    if (!donorFound)
    {
        cout << "\tNo donor found with the name " << donorName << "." << endl;
        getch();
        system("cls");
    }
}

void deleteDonor(vector<Donor>& donors, const string& filename)
{
    string donorName;
    cout <<endl<<endl<< "\tEnter the name of the donor you want to delete: ";
    cin.ignore();
    getline(cin, donorName);

    bool donorFound = false;
    for (auto it = donors.begin(); it != donors.end();)
    {
        if (it->name == donorName)
        {
            it = donors.erase(it); // Erase the donor from the vector
            donorFound = true;
        }
        else
        {
            ++it;
        }
    }

    if (donorFound)
    {
        cout << "\tDonor " << donorName << " has been deleted from the database." << endl;
        saveDonorsToFile(donors, filename); // Save the updated donor list without the deleted donor
    }
    else
    {
        cout << "\tNo donor found with the name " << donorName << "." << endl;
        getch();
        system("cls");
    }
}



//file related functions
void saveDonorsToFile(const vector<Donor>& donors, const string& filename)
{
    ofstream outputFile(filename);
    if (!outputFile)
    {
        cerr << "Error: Cannot open the file " << filename << " for writing." << endl;
        return;
    }

    for (const auto& donor : donors)
    {
        outputFile << donor.name << "," <<donor.gender<<","<< donor.bloodType << ","
                   << donor.contactNumber << "," << donor.gmailAddress << ","
                   << donor.lastDonationDate.day<<"-"
                   <<donor.lastDonationDate.month<<"-"<<donor.lastDonationDate.year<<","<<donor.status << endl;
    }

    outputFile.close();
    getch();
    system("cls");
}

void readDonorsFromFile(vector<Donor>& donors, const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cerr << "Error: Cannot open the file " << filename << " for reading." << endl;
        return;
    }

    donors.clear();  // Clear the existing list of donors

    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        Donor newDonor;
        getline(ss, newDonor.name, ',');
        getline(ss, newDonor.gender, ',');
        getline(ss, newDonor.bloodType, ',');
        getline(ss, newDonor.contactNumber, ',');
        getline(ss, newDonor.gmailAddress, ',');
        ss >> newDonor.lastDonationDate.day;
        ss.ignore();
        ss >> newDonor.lastDonationDate.month;
        ss.ignore();
        ss >> newDonor.lastDonationDate.year;
        ss.ignore();
        getline(ss,newDonor.status, ',');

        donors.push_back(newDonor);
    }

    inputFile.close();
}



//main function
int main()
{
    vector<Donor> donors;
    const string filename = "donors.txt";
    readDonorsFromFile(donors, filename);  // Load data from the file

    int choice;
    while (true)
    {
        cout <<"\t\t\t\t\t\t\t\t\t\t ============================";
        cout <<"\n\t\t\t\t\t\t\t\t\t\t BLOOD BANK MANAGEMENT SYSTEM" << endl;
        cout<<"\t\t\t\t\t\t\t\t\t\t          MAIN MENU"<<endl;
        //cout<<"\t\t\t\t\t\t\t\t\t\t       By: ByteBreakers"<<endl;
        cout <<"\t\t\t\t\t\t\t\t\t\t ============================";

        cout <<endl<<endl<<endl<< "\n\t\t\t\t\t\t\t  1. Add Donor" << endl;
        cout << "\n\t\t\t\t\t\t\t  2. Display Donors" << endl;
        cout << "\n\t\t\t\t\t\t\t  3. Search Donors by Blood Type" << endl;
        cout << "\n\t\t\t\t\t\t\t  4. Update Donor" << endl;
        cout << "\n\t\t\t\t\t\t\t  5. Delete Donor" << endl;
        cout << "\n\t\t\t\t\t\t\t  6. Exit" << endl;
        cout << "\n\n\t\t\t\t\t\t\t-> Enter your choice: ";
        cin >> choice;
        system("cls");

        if (choice == 1)
        {
            addDonor(donors, filename);
        }
        else if (choice == 2)
        {
            displayDonors(donors);
        }
        else if (choice == 3)
        {
            cout <<endl<<endl<< "     >> Enter blood type to search (A/B/AB/O +/-): ";
            string bloodType;
            cin.ignore();
            getline(cin, bloodType);
            searchDonorsByBloodType(donors, bloodType);
        }
        else if (choice == 4)
        {
            updateDonor(donors, filename);
        }
        else if (choice == 5)
        {
            deleteDonor(donors, filename);
        }
        else if (choice == 6)
        {
            cout <<endl<<endl<< "                                              ------------>> Exiting the program <<------------" << endl;
            return 0;
        }
        else
        {
            cout <<endl<<endl<< "     [Invalid choice. Try again.]" << endl;
        }
    }

    return 0;
}
