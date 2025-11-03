#include <iostream>
using namespace std;

class ATM {
private:
    int pin;
    double userBalance;

    // Denominations and their counts stored in arrays
    static int denominations[4];// = {2000, 500, 200, 100};
    static int noteCount[4]; //= {10, 20, 30, 50}; 

public:
    ATM(int p, double balance) {
        pin = p;
        userBalance = balance;
    }

    void start() {
        welcomeScreen();  // This function created for start the ATM process
    }

private:
    void welcomeScreen() {  // Welcome screen display
        cout << "----------------------------------\n";
        cout << "        WELCOME TO THE ATM        \n";
        cout << "----------------------------------\n";
        selectLanguage(); // This function is created for language selection
    }

    void selectLanguage() {
        int choice;
        cout << "SELECT LANGUAGE:\n1. ENGLISH\n2. HINDI\nEnter your choice: ";
        cin >> choice;

        if (choice == 1)
            cout << "\nLanguage Selected: ENGLISH\n";
        else if (choice == 2)
            cout << "\nLanguage Selected: HINDI\n";
        else
            cout << "\nInvalid option. Defaulting to ENGLISH.\n";

        selectApplication();  // This function is created for application selection like DOMESTIC or INTERNATIONAL
    }

    void selectApplication() {
        int choice;
        cout << "\nPLEASE SELECT APPLICATION ID:\n1. DOMESTIC\n2. INTERNATIONAL\nEnter your choice: ";
        cin >> choice;

        if (choice == 1)
            cout << "\nApplication Selected: DOMESTIC\n";
        else if (choice == 2)
            cout << "\nApplication Selected: INTERNATIONAL\n";
        else
            cout << "\nInvalid option. Defaulting to DOMESTIC.\n";

        authenticateUser();  // This is created for user authentication using PIN 
    }

    void authenticateUser() {
        int enteredPin;
        cout << "\nENTER YOUR PIN: ";
        cin >> enteredPin;

        if (enteredPin == pin) {  // if entered pin is correct then proceed to user menu
            cout << "\nPIN Verified Successfully!\n";
            userMenu();
        } else {
            cout << "\nInvalid PIN! Access Denied.\n";
        }
    }

    void userMenu() { //user entered pin is matched to PIN then this user menu will be displayed
        int choice;
        bool active = true;

        while (active) {
            cout << "\n----------------------------------\n";
            cout << "         USER MENU                \n";
            cout << "----------------------------------\n";
            cout << "1. WITHDRAW\n";
            cout << "2. DEPOSIT\n";
            cout << "3. BANK BALANCE\n";
            cout << "4. AVAILABLE BALANCE IN ATM\n";
            cout << "5. EXIT\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {    // this switch function is created for user to choose an option from user menu
                case 1: withdrawCash(); break;
                case 2: depositCash(); break;
                case 3: checkBalance(); break;
                case 4: totalATMBalance(); break;
                case 5:
                    cout << "\nTHANK YOU VISIT AGAIN!\n";
                    active = false;
                    break;
                default:
                    cout << "\nInvalid Option! Please try again.\n";
            }
        }
    }

    void withdrawCash() {   // this function is created for cash withdrawal
        double amount;
        cout << "\nPLEASE ENTER AMOUNT: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid amount.\n";
            return;
        }

        double atmTotal = totalATMBalance();  

        if (amount > userBalance) {
            cout << "\nINSUFFICIENT BALANCE IN ACCOUNT!\n";
        } 
        else if (amount > atmTotal) {
            cout << "\nAMOUNT IS NOT SUFFICIENT IN ATM\n";
        } 
        else if (((int)amount) % 100 != 0) {
            cout << "\nPlease enter amount in multiples of 100.\n";
        }
        else {
            if (dispenseCash(amount)) {
                userBalance -= amount;
                cout << "\nPLEASE COLLECT YOUR CASH\n";
            } else {
                cout << "\nUnable to dispense requested amount with available denominations.\n";
            }
        }
    }

    void depositCash() {  // this function is created for cash diposit
        double amount;
        cout << "\nPLEASE ENTER YOUR CASH: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid deposit amount.\n";
            return;
        }

        userBalance += amount;

        // ---------- TO UPDATE ATM BALANCE AUTOMATICALLY ----------
        // Distribute deposited cash into denominations (simple logic)
        double remaining = amount;
        for (int i = 0; i < 4; i++) {
            int notesAdded = (int)(remaining / denominations[i]);
            if (notesAdded > 0) {
                noteCount[i] += notesAdded;
                remaining -= notesAdded * denominations[i];
            }
        }

        cout << "\nMONEY DEPOSIT SUCCESSFULLY COMPLETED\n";
    }

    void checkBalance() {  // this functuon is created for checking bank balance after diposit or after withdrawal or intially
        cout << "\nYOUR BANK BALANCE IS: ₹" << userBalance << endl;
    }

    bool dispenseCash(double amount) { // this function is created for dispensing cash from ATM
        int tempNotes[4];
        for (int i = 0; i < 4; i++)
            tempNotes[i] = noteCount[i];

        int dispensedNotes[4] = {0, 0, 0, 0};

        for (int i = 0; i < 4; i++) {
            int denom = denominations[i];
            int notesNeeded = (int)(amount / denom);

            if (notesNeeded > 0) {
                if (notesNeeded <= tempNotes[i]) {
                    dispensedNotes[i] = notesNeeded;
                    amount -= notesNeeded * denom;
                    tempNotes[i] -= notesNeeded;
                } else {
                    dispensedNotes[i] = tempNotes[i];
                    amount -= tempNotes[i] * denom;
                    tempNotes[i] = 0;
                }
            }
        }

        if (amount == 0) {
            for (int i = 0; i < 4; i++)
                noteCount[i] = tempNotes[i];

            cout << "\nDispensed Denominations:\n";
            for (int i = 0; i < 4; i++) {
                if (dispensedNotes[i] > 0)
                    cout << "₹" << denominations[i] << " x " << dispensedNotes[i] << endl;
            }
            return true;
        }
        return false;
    }

    double totalATMBalance() {  // this function is created to calculate total ATM balance
        double total = 0;
        for (int i = 0; i < 4; i++) {
            total += denominations[i] * noteCount[i];
        }
        cout << "\nTOTAL AVAILABLE BALANCE IN ATM: ₹" << total << endl;
        for(int i=0; i<4; i++) {
            cout << "₹" << denominations[i] << "X" << noteCount[i] << endl;
        }
    }

};

int ATM::denominations[4] = {2000, 500, 200, 100};
int ATM::noteCount[4] = {10, 20, 30, 50};

int main() {
    ATM atm(1234, 10000); // PIN = 1234, Balance = ₹10,000
    ATM atm1(3622, 5000); // PIN = 3622, Balance = ₹5,000
    atm.start();
    atm1.start();
    return 0;
}
