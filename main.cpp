//hamna b mustafa
//hbm170002
#include <iostream>

#include <fstream>

#include <algorithm>

#include <string>

#include <iomanip>

#include <ctype.h>

#include <cmath>

using namespace std;
const string filename = "sampletheater.txt"; //file to edit for ticket reservations

int checkIfReserve(string input) { //checks to see if the user's input is valid and if the user want's to reserve
    if (input == "reserve seats" || input == "reserve" || input == "reserve seat" || input == "1")
        return 1;
    else
        return 0;
}

int seatingChart(string filename) { //displays the seating chart.
    fstream file;
    file.open(filename, ios::out | ios:: in );
    int rowNum = 0;
// We open the file and iterate over the length of the row and use the ascii characters of the alphabet to store all of the alphabets uptill the length of the row in 'columnAlphabet'
    if (file.is_open()) {
        string line;
        string columnAlphabet = "  ";
        getline(file, line);
        int length;
        length = int(line.length());
        int alphabetascii = int('A');
        for (int i = 0; i < length; i++) {
            columnAlphabet += char(alphabetascii);
            alphabetascii++;
        }
        columnAlphabet += "\n";
        cout << columnAlphabet;
        file.seekg(0); //go to the beginning of the file.
        while (!(file.eof())) {
         // iterate over each row and check to see if any of the seats are already reserved, i.e. 'A','C','S'.
         //If a seat is reserved, we output a '#', otherwise we output a '.'

            getline(file, line);
            for (int i = 0; i < length; i++) {
                if (line[i] == 'A' || line[i] == 'C' || line[i] == 'S')
                    line[i] = '#';
            }
            rowNum += 1;
            cout << rowNum << " " << line << endl;
        }

        file.close();
    }
    return rowNum; //we return the rowNum that the user has selected to be used in later functions.
}

string validateInput(string str, char rowColSeatBest, int rowNum, string filename) {
    //the variable rowColSeatBest tells us which input we are validating.
   //If it is 'C', we are validating the column(i.e. the starting seat).
   //If it is 'B', we are validating the input entered when the user if asked if they want to reserve the best available seats.
   // If it is 'R', we are validating the input entered when asking the user for their desired row.
   // If it is 'S', we are validating the input entered when asking the user for the number of adult, child and senior tickets.
    int valid;
    do {
        valid = 1; // setting 'valid' to one so that if an input is invalid, we can set it to 0. If 'valid' is 0, loop will keep running until valid input is entered and 'valid' changes to 1.
        if (rowColSeatBest == 'C') {
            if (str.length() == 1) { //statement checks to see if the length of the string is one because the starting seat can only be one alphabet.
                fstream file;
                file.open(filename, ios:: in );
                if (file.is_open()) {
                    string line;
                    getline(file, line);
                    char chr = char(toupper(char(str[0])));
                    if (isalpha(chr)){// statement checks to make the sure the character is an alphabet.
                    if (!(chr < (char(int('A') + line.length())))) // statement checks to make sure that the alphabet entered one of the alphabets from the column.
                     // for example, if the user enters 'Z' but the column only goes up till 'T', the variable valid will be set to 0 and user will be asked to enter valid input.
                        valid = 0;}
                     else
                        valid = 0;
                }
                file.close();
            } else
                valid = 0;
        
        } else if (rowColSeatBest == 'B'){
            if (str.length()==1){
                if(!(char(toupper(char(str[0])))=='Y' || char(toupper(char(str[0])))=='N'))// statement makes sure the input is either a 'Y' or an 'N' as required.
                    valid = 0;
            }
            else
                valid=0;
        }
         else { // since both the row and the number of seats (adult, child and senior) need to be integers, this else statement checks to make sure that they are.

            for (int i = 0; i < str.length(); i++) { // this for loop iterates over the string to make sure that each character in the string is an integer.
                if (!(isdigit(char(str[i])))) {
                    valid = 0; // if a character is encountered which is not an integer, 'valid' is set to 0 and we break out of the loop.
                    break;
                }
            }
            if (rowColSeatBest == 'R' && valid) { // this statement checks to see that the input was valid and lesser than or equal to the number of rows available.
               // for example, if the user enters '73' but the there are only '10' rows in the auditorium, they will be asked to enter valid input.
                int strToInt = stoi(str);
                if (!(strToInt <= rowNum))
                    valid = 0;
            }
        }
        if (valid == 0) { //statement carried out when input is invalid.
            cout << "Please enter valid input" << endl;
            cin >> str; // keeps inputing until a valid input is encountered.
        }
    }
    while (valid == 0); //keeps running until a valid input is encountered.
    return str; //returns the valid input.
}
int checkAvailability(int rowNumber, char seatLetter, int tickets, string filename) {
    fstream file;
    string line;
    file.open(filename, ios::out | ios:: in );
    if (file.is_open()) {
        for (int i = 1; i <= rowNumber; i++) { //this loop runs until the row that the user wants is reached. That row is stored in the variable 'line'.
            getline(file, line);
        }
        int column = int(seatLetter) - int('A'); //this stores the index of the starting seat in the line in the variable 'column'
        for (int i = column; i < column + tickets; i++) { //this loop checks to see if the seats that the user wanted are available, i.e if they are a '.' in the file.
            if (!(line[i] == '.')) // if even one of the seats is not available, the function returns 0.
                return 0;
        }
    }
    file.close();
    return 1; // the function returns 1 if the chosen seats are available.
}

int bestAvailable(int rowNumber, int totalTickets, string filename) { //provided that the seats the user wanted weren't available, this function finds the best available seats in that particular row.
    fstream file;
    string line;
    file.open(filename, ios::out | ios:: in );
    char startingSeat = '0';
    if (file.is_open()) {
        for (int i = 1; i <= rowNumber; i++) { //this loop gets stores the required row in the variable 'line'
            getline(file, line);
        }
        // line 149 to line 161 finds the seats whose midpoint is closest to the midpoint of the row.
        int length = int(line.length());
        float shortestDist = 30.0; //setting the shortest distance to 30 because the maximum length of the row is 26 is there are only 26 alphabets. No distance can be greater than 30.
        float midpoint = float(length - 1) / 2; // midpoint of the row.
        //cout << "length: "<<length;
        //cout << "midpoint: "<< midpoint<<endl;
        for (int i = 0; i <= length - totalTickets; i++) { //loop iterates over the row up until the length of the line minus the total tickets. This is because it is useless to iterate after that because there won't be enough seats after that.
            char available = 'Y';
            for (int j = 0; j < totalTickets; j++) {//iterates over a starting seat to the total number of seats required.
                if (!(line[i + j] == '.')) { //checks to see if the seats are available. If they are not, breaks out of loop and changes 'available' to 0.
                    available = 'N';
                    break;
                }
            }

            if (available == 'Y') {
                //cout << "i :" << i << endl;
                //cout << "midpoint" << midpoint<<endl;
                float dist = midpoint - float(i) - ((float(totalTickets) - 1) / 2); //calculates the distance between the midpoint of the seats and the midpoint of the row.
                // cout << "Distance: " << dist << endl;
                // cout << "Column: " << char(int('A')+i)<< endl;
                //  cout << "abs: " <<abs(dist) << endl;
                if (abs(dist) < abs(shortestDist)) { //if the distance is lesser than the distance already stored, 'shortestDist' is updated to the new distance and the corresponding seat is stored in 'startingSeat'

                    shortestDist = dist;
                    //cout << "shortest dist"<< shortestDist<<endl;
                    startingSeat = char(int('A') + i);
                }
                // cout << "starting seat " << startingSeat<<endl;
            }
        }
        if (shortestDist == 30) {
            cout << "Sorry, those seats are not available and there are no available seats in that row." << endl; //if there are no best available seats in that row, this sentence is displayed.
            return 0;
        } else {
            cout << "Best available is: " << rowNumber << startingSeat << "-" << rowNumber << char(int(startingSeat) + totalTickets - 1) << endl; //displays the best available seats.
        }

        //for (int i=1; i< length-rowNumber+1;i++)
    }
    file.close();
    return int(startingSeat);
}
int reserveSeats(int rowNumber, char seatLetter, int adultTickets, int childTickets, int seniorTickets, string filename) {
    fstream file;
    string line;
    file.open(filename, ios::out | ios:: in );
    if (file.is_open()) {
        for (int i = 1; i < rowNumber; i++) { //loop sets the index to the start of the required row in the file
            getline(file, line);
        }
        int column = int(seatLetter) - int('A'); //finds the index of starting seat in that row
        int currentIndex = int(file.tellg()); //finds the current index of the file
        file.seekp(currentIndex + column); //sets the index of the file to where the starting seat is located
        for (int i = 0; i < adultTickets; i++) //loops over the number of adult seats and changes them from '.' to 'A' (reserving them)
            file << 'A';
        for (int i = 0; i < childTickets; i++) //loops over the number of children seats and changes them from '.' to 'C' (reserving them)
            file << 'C';
        for (int i = 0; i < seniorTickets; i++)  //loops over the number of senior seats and changes them from '.' to 'S' (reserving them)
            file << 'S';
        cout << "Your seats have been reserved!" << endl;
        file.close();
    }
    return 0;
}

int generateReport(string filename) { // this loop iterates over the entire file
    fstream file;
    file.open(filename);
    int index = 0;
    int totalSeats = 0;
    int totalTickets = 0;
    int adultTickets = 0;
    int childTickets = 0;
    int seniorTickets = 0;
    float totalSales = 0.0;
    if (file.is_open()) {
        while (!(file.eof())) {
            char ch;
            file.get(ch); //gets each character in the file
            //cout << ch;
            if (ch == '.' || ch == 'A' || ch == 'C' || ch == 'S') { //checks if the character is either reserved or available.
                totalSeats += 1; //adds the seat to the total seat.
                if (!(ch == '.')) //if the character is reserved (i.e. not '.'), the number of total tickets is incremented.
                    totalTickets += 1;
                if (ch == 'A') //if the character is reserved as an adult ticket (i.e. 'A'), the number of adult tickets is incremented.
                    adultTickets += 1;
                if (ch == 'C') //if the character is reserved as a child ticket (i.e. 'C'), the number of child tickets is incremented.
                    childTickets += 1;
                if (ch == 'S') //if the character is reserved as a senior ticket (i.e. 'S'), the number of senior tickets is incremented.
                    seniorTickets += 1;
            }
            index += 1;
            file.seekp(index);
        }
        //cost of an adult ticket = $10
        //cost of a child ticket = $5
        //cost of a senior ticket = $7.5
        //totalSales is calculated by multiplying the cost with the corresponding ticket category and adding them.
        totalSales = (10 * adultTickets) + (5 * childTickets) + (7.50 * seniorTickets);
        //the report is displayed.
        cout << "Report:" << endl;
        cout << "Total Seats     " << totalSeats << endl;
        cout << "Total Tickets   " << totalTickets << endl;
        cout << "Adult Tickets   " << adultTickets << endl;
        cout << "Child Tickets   " << childTickets << endl;
        cout << "Senior Tickets  " << seniorTickets << endl;
        cout << "Total Sales     $";
        printf("%.2f", totalSales);
    }
    file.close();
    return 0;
}

int main() {
   string input;
    do {
        cout << "1. Reserve Seats" << endl << "2. Exit" << endl; //displays menu
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower); // converts input to lowercase
        int rowNum;
        string row;
        int rowN;
        string startingSeatString;
        char startingSeat;
        string adultString;
        int adult;
        string childString;
        int child;
        string seniorString;
        int senior;

        if (checkIfReserve(input)) { // function 'checkIfReserve' checks is the user has chosen the reserve option with valid input.
            rowNum = seatingChart(filename); //'seatingChart' is invoked which returns the number of rows in the seating chart.
            cout << "Please enter the row that you have chosen:" << endl;
            cin >> row;
            // all the inputs are going to be validated through the function "validateInput". Since they are stored in string variables, once they have been validated, they are converted to the required type.
            //the required type for the row input, adult tickets, child tickets and senior tickets is integer. The required type for the starting seat is a character.
            row = validateInput(row, 'R', rowNum, filename);
            rowN = stoi(row);
            cout << "Please enter the starting seat that you have chosen:" << endl;
            cin >> startingSeatString;
            startingSeatString = validateInput(startingSeatString, 'C', rowNum, filename);
            startingSeat = char(toupper(char(startingSeatString[0])));
            cout << "Please enter the number of adult tickets:" << endl;
            cin >> adultString;
            adultString = validateInput(adultString, 'S', rowNum, filename);
            adult = stoi(adultString);
            cout << "Please enter the number of child tickets:" << endl;
            cin >> childString;
            childString = validateInput(childString, 'S', rowNum, filename);
            child = stoi(childString);
            cout << "Please enter the number of senior tickets:" << endl;
            cin >> seniorString;
            seniorString = validateInput(seniorString, 'S', rowNum, filename);
            senior = stoi(seniorString);
            if (checkAvailability(rowN, startingSeat, adult + child + senior, filename)) { //function 'checkAvailability' checks to see if the seats the user wants are available.
                reserveSeats(rowN, startingSeat, adult, child, senior, filename); //if they are available, 'reserveSeats' is called which reserves those seats in the file.
            } else { //if the seats are not available, 'bestAvailable' is called which searched for best seats closest to the middle of the row.
                int startingSeat;
                startingSeat = bestAvailable(rowN, adult + child + senior, filename); //this function returns the starting seat for the best seats available and this is stored in the variable startingSeat
                if (startingSeat) {
                    cout << "Would you like to reserve these seats instead? Enter Y for yes and N for no:" << endl; //Asks the user if they want to select the best available seats.
                    string reserveBestString;
                    char reserveBest;
                    cin >> reserveBestString;
                    reserveBestString = validateInput(reserveBestString,'B',rowNum, filename); //validates input.
                    reserveBest = char(toupper(char(reserveBestString[0])));
                    if (reserveBest == 'Y') //if user enters 'Y', the best available seats are reserved.
                        reserveSeats(rowN, char(startingSeat), adult, child, senior, filename);
                }
            }

        } else if (!(input == "exit" || input == "2")) //checks to see if user entered invalid input.
            cout << "Please enter valid input:" << endl;
    }
    while (!(input == "exit" || input == "2")); // loop keeps running until the user decides to exit.
    generateReport(filename); //displays report.
}
