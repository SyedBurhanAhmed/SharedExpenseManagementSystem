#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

// function to add members
void addMembers(vector<vector<float>>& members, vector<string>& memberNames) {
    int numMembers;
    cout << "Enter the number of members: ";
    cin >> numMembers;
    //resize the 2d vector according to number of members
    members.resize(numMembers, vector<float>(numMembers, 0));
    memberNames.resize(numMembers);
    //for loop to input member names
    for(int i = 0; i < numMembers; i++) {
        cout << "Enter the name of member " << i+1 << ": ";
        cin >> memberNames[i];
    }
}

// function to show members
void showMembers(vector<string>& memberNames)
{
    cout<<"\nThe members are:\n";
    //for loop to display member names
    for(int i = 0; i < memberNames.size(); i++)
    {
        cout<<i+1<<"."<<memberNames[i]<<endl;
    }
    cout<<endl;
}

// function to add expenses
void addExpense(vector<vector<float>>& members, vector<string>& memberNames) {
    //taking input for expense
    float expense;
    cout << "Enter the amount of expense: ";
    cin >> expense;
    //taking input of payer name
    string payerName;
    cout << "Enter the name of the payer: ";
    cin >> payerName;
    int numMembers = members.size();
    int payerIndex = -1;
    // get the index of the payer
    for(int i = 0; i < numMembers; i++) {
        if(memberNames[i] == payerName) {
            payerIndex = i;
            break;
        }
    }
    if(payerIndex == -1) {
        cout << "Invalid payer name." << endl;
        return;
    }
    //calculate the per person expense
    float perPersonExpense = expense / (numMembers);
    for(int i = 0; i < numMembers; i++) {
        if(i == payerIndex) {
            continue;
        }
        members[i][payerIndex] += perPersonExpense;
        members[payerIndex][i] -= perPersonExpense;
    }
}

// function to calculate net balance and save expense history
void saveExpenseHistory(vector<vector<float>>& members, vector<string>& memberNames) {
    //creating a file
    ofstream outfile("expense_history.txt");
    int numMembers = members.size();
    //getting data in file
    outfile << "Members\t";
    for(int i = 0; i < numMembers; i++) {
        outfile << memberNames[i] << "\t";
    }
    outfile << endl;
    //writing the balance in the file
    for(int i = 0; i < numMembers; i++) {
        outfile << memberNames[i] << "\t";
        for(int j = 0; j < numMembers; j++) {
            outfile << members[i][j] << "\t";
        }
        outfile << endl;
    }
    //closing file
    outfile.close();
    cout << "\nExpense history saved in expense_history.txt file.\n\n";
}

//function to display expense history
void showExpenseHistory() {
     //reading expenses from file
     ifstream file("expense_history.txt");
     //checking if file is opened successfully
    if (file.is_open()) {
        cout << "Expense History:" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        //closing the file
        file.close();
    }
    else {
        //file not found
        cout << "Unable to open expense history file." << endl;
    }
}

// main function
int main() {
    cout<<"\t\t\t\t Shared Expenses Management System (SEMS)\n ";

    //2d vector to store values against members
    vector<vector<float>> members;

    // vector to store name of members
    vector<string> memberNames;
    int choice;

    //do while loop
    do {
    cout <<"Choose an option from the following\n";
    cout << "1. Add members.\n";
    cout << "2. Show members.\n";
    cout << "3. Add expense.\n";
    cout << "4. Calculate net balance and Save Expense History.\n";
    cout << "5. Show Expense History.\n";
    cout << "6. Exit.\n";
    cout<<"Enter the option:";

    int choice;
    cin >> choice;
    //switch statement to choose the functionality
    switch(choice) {
        case 1:
            addMembers(members, memberNames);
            break;
        case 2:
            showMembers(memberNames);
            break;
        case 3:
            addExpense(members, memberNames);
            break;
        case 4:
            saveExpenseHistory(members, memberNames);
            break;
        case 5:
            showExpenseHistory();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (true);
}
