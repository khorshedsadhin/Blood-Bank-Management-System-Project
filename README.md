# Blood-Bank-Management-System-Project
This C++ program implements a simple Blood Bank Management System. It allows users to perform various operations such as adding a donor, displaying donors, searching donors by blood type, updating donor information, and deleting donors. Donor information includes name, gender, blood type, contact number, Gmail address, last donation date, and eligibility status.

Classes:

'Date': Represents a date with day, month, and year components.
'Donor': Represents a blood donor with attributes like name, gender, blood type, contact number, Gmail address, last donation date, and status.

Constant:

'currDate': Represents the current date and is used for calculating the eligibility status of donors.

Functions:

'countLeapYears': Calculates the number of leap years in a given date.
'getDifference': Calculates the difference in days between two dates.
'Feature functions': addDonor, displayDonors, searchDonorsByBloodType, updateDonor, and deleteDonor provide functionalities to manage donor information.
'File functions': saveDonorsToFile and readDonorsFromFile save and load donor information from a file, respectively.

Usage:

Run the program.
Choose from the main menu options to manage donor information.
Donor information is stored in a file named "donors.txt".
The program automatically saves changes to the file after adding, updating, or deleting donors.

Note:

The program utilizes the 'conio.h' library for platform-specific functions, so it may need adjustments based on the compiler and platform.
Users are encouraged to customize and enhance the program based on specific requirements.
Always update the 'currDate' constant to reflect the current date for accurate eligibility calculations.
