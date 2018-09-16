/**************************************
 ** File:    proj1.cpp
 ** Project: CMSC 202 Project 1 - True Grits Snacks, Fall 2017
 ** Author:  Innocent Kironji
 ** Date:    09/28/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file simulates a vending machine. It allows the user to
 ** make purchases and view recipts of the last purchase they made
 ***************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_SNACKS = 10;
const int ARRAY_SIZE = 2;
const int RECEIPT_SIZE = 3;


//Name: printMainMenu
//PreCondition:  The user wants to begin a new action. The user only enters
//                a number value (integer).
//PostCondition: Returns a choice that determines user's next action
int printMainMenu();


//Name: printReceipt
//PreCondition:  There exists two text files. One with payment information
//                on a previous order and with order information from that
//                same order (i.e. items purchased and quantities)
//PostCondition: A well organized reciept is printed for the user to review
void printReceipt();


//Name: loadTable
//PreCondition:  There exists a text file with names and prices of items 
//                for order
//PostCondition: Snack Bar information is loaded into a multi-dimensional 
//                 array
void loadTable(string machineItems[][ARRAY_SIZE], int num_snacks);


//Name: printTable
//PreCondition:  There is an array that has properly loaded
//                the contents of the snack bar
//PostCondition: An organized table of all items in
//                the snack bar will be printed to user
void printTable(string machineItems[][ARRAY_SIZE], int numSnacks);


//Name: writeReceipt
//PreCondition:  The user has placed an order
//PostCondition: The users order is output and also stored in a seperate 
//                text file
void writeReceipt(string order[][RECEIPT_SIZE], int orderSize, 
		 double subtotal, double tax, double total);


//Name: manageOrder
//PreCondition:  The user has chosen to purchase items from the snack bar 
//                and there is a properly loaded snack bar. The user only 
//                enters numbers (integers) for their choices for quantity
//                and item number
//PostCondition: Calculates the subtotal(s), tax and grand total for the
//                user's order
void manageOrder(string machineItems[][ARRAY_SIZE], int num_snacks);


//Name: toString
//PreCondition:  There is a single integer the user wishes to convert
//                to a string
//PostCondition: The entered integer is returned as a string                                                               
string toString (int toBeConverted);


//Name: toDouble
//PreCondition:  There is a string the user wishes to convert and that
//                string represents a real number (i.e. "2.34").
//                The string cannot contain anything other than numbers
//                and one decimal point
//PostCondition  The string will be output as a double
double toDouble (string toBeConverted);


int main(){

  string snackBar[NUM_SNACKS][ARRAY_SIZE] = { {"",""}, {"",""}, {"",""}, 
					      {"",""}, {"",""}, {"",""}, 
					      {"",""}, {"",""}, {"",""}, 
					      {"",""} };
  int choice = 0;

  //The main menu will be repeated after every action is 
  // completed until the user chooses to exit
  do{

    choice = printMainMenu();

    //Manages which action the user wishes to do
    switch (choice){

      //User wishes to make a new order
    case 1:
      loadTable(snackBar, NUM_SNACKS);
      manageOrder(snackBar, NUM_SNACKS);
      break;

      //User chooses to view recipt
    case 2:
      printReceipt();
      break;

      //User chooses to exit
    default:
      cout << "Thank you for using True Grits Snack Bar \n" << endl;
    }

  }while (choice != 3);

  return 0;

}


//printMainMenu
//Determines the next action the user will take
int printMainMenu(){

  int choice = 0;
  cout << endl << "Welcome to the True Grit Snack Bar." << endl;

  //Checks and reprompts the user if they did not make a valid response
  do{

    cout << "What would you like to do?:\n" 
	 << "1. New Order\n" << "2. View Recipt(s)\n" << "3. Exit\n";
    cin >> choice;
    cout << endl;

  }while(choice < 1 || choice > 3); 

  return choice;
}


//printReceipt
//Given that there exists a text file with information from a
// previously made order, prints receipt of that order
void printReceipt(){

  string qnty = "";
  string itemName = "";
  string price = "";
  string subtotal = "";
  string tax = "";
  string total = "";
  ifstream receiptStream ("receipt.txt");
  ifstream payStream ("payment.txt");
  cout << fixed;

  if (receiptStream.is_open() && payStream.is_open()) {

    //Prints Header
    cout << "Your Order:" << endl;
    cout << right << "Qnty" << setw(20) << "Item" 
	 << setw(14) << "Price" << endl;

    //Prints a table of the items from the receipt
    while(getline(receiptStream, qnty, ',') && 
	  getline(receiptStream, itemName, ',') && 
	  getline(receiptStream, price, ',')) {

      cout.precision(2);

      //I had a lot of trouble getting the table to print to the right
      //However, I was able to get the spacing to work for the most part
      cout << right << qnty << setw(23) << itemName 
	   << setw(10) << "$" << setprecision(2) 
	   << toDouble( price.substr(1) ) << endl;
    }

    //Prepares payment info for printing
    getline(payStream, subtotal, '|');
    getline(payStream, tax, '|');
    getline(payStream, total, '|');

    //Prints payment information portion of reciept
    cout << endl;
    cout << "Subtotal: $" << setprecision(2) << toDouble(subtotal) << endl;
    cout << "Tax: $" << setprecision(2) << toDouble(tax) << endl;
    cout << "Total: $" << setprecision(2) << toDouble(total) << endl;
    cout << "Receipt Written" << endl;

  }else
    cout << "The files were unable to open" << endl;

}


//loadTable
//Given a text file with snack bar items, this information
// is loaded into arrary
void loadTable(string machineItems[][ARRAY_SIZE], int num_snacks){

  string snack = "";
  string price = "";
  ifstream snackStream ("proj1_items.txt");

  if (snackStream.is_open()){

    //Counter to hold position for first dimension in array
    int i = 0;

    //Saves each snack and price into a 2D Array 
    while (getline(snackStream, snack, ',')) {

      getline(snackStream, price);
      machineItems[i][0] = snack;
      machineItems[i][1] = "$" + price;
      i++;
    }

    snackStream.close();

  }else
    cout << "File is unable to open" << endl;

  return;
}


//printTable
//Given there is an array of the contents of the snackbar those items 
// will be printed to the user in an organized table
void printTable(string machineItems[][ARRAY_SIZE], int numSnacks){

  cout << fixed;
  cout << right << setw(6) << "Number" << setw(24) << "Item" 
       << setw(16) << " Price" << endl;

  //Prints the snack's item number
  for (int i = 0; i < numSnacks; i++) {

    int itemNum = i + 1;
    cout << right << setw(6) << itemNum;

    //prints the snack's name
    for (int j = 0; j < ARRAY_SIZE; j++) {

      if (j == 0)
	cout << right << setw(24) << machineItems[i][j];

      //prints price
      else
	cout << right << setw(12) << "$" << setprecision(2) 
	     << toDouble( machineItems[i][j].substr(1) );
      
    }

    //For when one snack's full information is printed
    cout << endl;

  }

  return;
}


//writeReceipt
//Given user has completed an order, store that order as a txt file
void writeReceipt(string order[][RECEIPT_SIZE], int orderSize, 
		 double subtotal, double tax, double total){

  string itemInfo = "";
  ofstream receiptStream ("receipt.txt");
  ofstream payStream ("payment.txt");

  if (receiptStream.is_open() && payStream.is_open()) {

    //Consolidates all item information into singular string
    for (int i = 0; i < orderSize; i++) {
      for (int j = 0; j < RECEIPT_SIZE; j++) {

	itemInfo += order[i][j] + ",";
      }

      //New line for the next item in the order
      itemInfo += "\n";
    }

    //Saves item information into one file and payment info into another
    receiptStream << itemInfo;
    payStream << "" << subtotal << "|" << tax << "|" << total << "| ";

    //Close and print files
    receiptStream.close();
    payStream.close();
    cout << endl;
    printReceipt();

  }else
    cout << "The files were unable to open" << endl;

  return;
}


//manageOrder
//Given user has chosen to make an order and there is a properly loaded 
// snack bar to buy from, calculate and print the price of the order
void manageOrder(string machineItems[][ARRAY_SIZE], int numSnacks) {

  const int MAX_NUM_ITEMS = 3;
  const int MAX_POS = 2;
  const double MD_STATE_TAX = 0.06;
  string userOrder[][RECEIPT_SIZE] = { {"", "", ""}, {"", "", ""}, 
				       {"", "", ""} };

  //To keep track of what is being ordered
  int numItems = 0;
  double subtotal = 0.0;
  bool continueOrder = true;

  //Prompts user to make an order until they reach the maximum number 
  // of orders (same as the array size) or they choose to stop earlier
  while (continueOrder && (numItems < MAX_NUM_ITEMS)) {

    int itemNum = 0;
    int quantity = 0;
    char addMore = 'n';

    printTable(machineItems, numSnacks);

    //Checks if user enters an item within the snackbar
    do {
      cout << "What would you like to buy?" <<
	"(Enter the number associated with the snack) ";
      cin >> itemNum;

    }while (itemNum < 1 || itemNum > 10);

    //Store name of ordered item
    int item = itemNum - 1;
    string itemName = machineItems[item][0];
    userOrder[numItems][1] = itemName;

    //Store price
    string priceString = machineItems[item][1];
    double price = toDouble( priceString.substr(1) );
    userOrder[numItems][2] = priceString;

    //Stores user's wanted quantity, adds up price and verifies user 
    //entered a positive integer
    do {
      cout << "How many would you like to buy? ";
      cin >> quantity;

    }while (quantity < 1);
    subtotal += price * quantity;
    userOrder[numItems][0] = toString(quantity); 

    //Only prompts user if they have not reached max number of items
    if (numItems < MAX_POS){
    
      
      bool invalidAns = true;
      
      //Repromts user until correct input is entered
      do {
	cout << "Do you want to add more items? (y/n) ";
	cin >> addMore;

	//Makes sure user entered proper answer
	if (addMore == 'y')
	  invalidAns = false;
	else if (addMore == 'n')
	  invalidAns = false;
	else
	  invalidAns = true;

      }while (invalidAns);

    }else
      addMore = 'n';

    //Stops if the user chooses to no longer make purchases
    if (addMore == 'y'){
      numItems++;
    }else
      continueOrder = false;

  }

  //Calculates information for payment and creates recipt
  double tax = subtotal * MD_STATE_TAX;
  double total = subtotal + tax;
  writeReceipt(userOrder, numItems + 1, subtotal, tax, total);

  return;
}


//toString
//Given there is a single integer the user wishes to convert to a
// string, the integer is returned as a string
string toString (int toBeConverted) {

  string convertedInt = "";

  //Records int wishing to be converted into a text file
  ofstream convertStream ("conversion.txt");
  if (convertStream.is_open()) {

    convertStream << "" << toBeConverted << endl;
    convertStream.close();
  }else
    cout << "Unable to open file" << endl;

  //Outputs the string from the text file into a string variable
  ifstream stringStream ("conversion.txt");
  if (stringStream.is_open()) {

    stringStream >> convertedInt;
    stringStream.close();
  }else
    cout << "Unable to open file" << endl;

  return convertedInt;

}


//toDouble 
//Given there is a string representing a real number) the user 
//wishes to convert to a double, the string is returned as 
//a double                                                                                                         
double toDouble (string toBeConverted) {

  double convertedString = 0.0;

  //Records string wishing to be converted into a text file
  ofstream convertStream ("conversion.txt");
  if (convertStream.is_open()) {

    convertStream << "" << toBeConverted << endl;
    convertStream.close();
  }else
    cout << "Unable to open file" << endl;

  //Outputs from the text file into a double variable                                                                                       
  ifstream doubleStream ("conversion.txt");
  if (doubleStream.is_open()) {

    doubleStream >> convertedString;
    doubleStream.close();
  }else
    cout << "Unable to open file" << endl;

  return convertedString;

}
