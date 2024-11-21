#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include<ctime>
#include <stdexcept>
using namespace std;

class Login {
private:
    string username;
    string password;
    int attempt;

    void logToFile(const string& message) {
        ofstream logFile;
        logFile.open("login_attempts.log", ios::app);
        if (!logFile) {
            throw runtime_error("Unable to open log file!");
        }
        logFile << message << endl;
        logFile.close();
    }

public:
    Login() {
        username = "";
        password = "";
        attempt = 0;
    }

    bool loginprompt() {
        try {
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (username == "admin" && password == "admin@123") {
                cout << "Login successful!!" << endl;
                logToFile("Login successful for user: " + username);
                return true;
            } else {
                attempt++;
                logToFile("Failed login attempt for user: " + username);

                if (attempt >= 3) {
                    logToFile("System locked due to multiple failed attempts.");
                    cout << endl << "Maximum login attempts reached. System locked." << endl;
                    return false;
                } else {
                    throw invalid_argument("Invalid username or password!");
                }
            }
        } catch (const invalid_argument& e) {
            cout << endl << e.what() << endl;
            cout << "********* Try again *********" << endl << endl;
            return loginprompt(); // Recursive call
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
            return false; // Terminate further attempts if file error occurs
        }
    }
};

class Registration {
private:
    string name;
    double phone;
    string email;
    string city;
    int fee;

    bool isValidPhoneNumber(double phone) {
        string phoneStr = to_string(static_cast<long long>(phone));
        regex pattern("^[0-9]{10}$");
        return regex_match(phoneStr, pattern);
    }

    void logToFile(const string& message) {
        ofstream logFile;
        logFile.open("registration_log.txt", ios::app); // Append mode
        if (!logFile) {
            throw runtime_error("Unable to open log file!");
        }
        logFile << message << endl;
        logFile.close();
    }

public:
    Registration() {
        name = "";
        phone = 0;
        email = "";
        city = "";
        fee = 0;
    }

    void details() {
        try {
            cout << "Enter your name: ";
            cin >> name;

            cout << "Enter your phone number (10 digits): ";
            cin >> phone;

            while (!isValidPhoneNumber(phone)) {
                logToFile("Invalid phone number entered: " + to_string(phone));
                cout << "Invalid phone number! Please enter a 10-digit number: ";
                cin >> phone;
            }

            cout << "Enter your email address: ";
            cin >> email;

            if (email.find('@') == string::npos || email.find('.') == string::npos) {
                logToFile("Invalid email address entered: " + email);
                throw invalid_argument("Invalid email address! Please enter a valid email.");
            }

            cout << "Enter your city: ";
            cin >> city;

            logToFile("Details entered successfully for: " + name);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error: " + string(e.what()));
            details(); // Restart the input process
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void registrationfee() {
        try {
            cout << "To complete your registration you have to pay Rs.2000" << endl;
            cout << "Enter the amount you want to pay: ";
            cin >> fee;

            while (fee != 2000) {
                logToFile("Incorrect registration fee entered: " + to_string(fee));
                cout << "Error: Minimum registration fee is Rs. 2000." << endl;
                cout << "Do the payment again!!" << endl;
                cin >> fee;
            }

            logToFile("Registration fee paid successfully for: " + name);
            cout << "Registration Successful!!" << endl;
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    int getregistrationfee() {
        return fee;
    }
};

class Admission {
protected:
    string EnrollmentNo;
    string fullName;
    string dateOfBirth;
    long long phoneNumber;
    string email;
    string address;
    string School_roll_no;
    double SchoolMarks;
    long long governmentID;
    double totalfees;
    string course;

    void logToFile(const string& message) {
        ofstream logFile;
        logFile.open("admission_log.txt", ios::app); // Append mode
        if (!logFile) {
            throw runtime_error("Unable to open log file!");
        }
        logFile << message << endl;
        logFile.close();
    }

public:
    Admission() {
        EnrollmentNo = "";
        fullName = "";
        dateOfBirth = "";
        phoneNumber = 0;
        email = "";
        address = "";
        School_roll_no = "";
        SchoolMarks = 0;
        governmentID = 0;
        totalfees = 0;
        course = "";
    }

    void personalinfo() {
        try {
            cout << "Enter your enrollment number: ";
            cin >> EnrollmentNo;

            cout << "Enter your full name: ";
            cin.ignore();
            getline(cin, fullName);

            cout << "Enter your date of birth (dd-mm-yyyy): ";
            cin >> dateOfBirth;

            cout << "Enter your phone number (10 digits): ";
            cin >> phoneNumber;
            if (to_string(phoneNumber).length() != 10) {
                throw invalid_argument("Invalid phone number! Must be 10 digits.");
            }

            cout << "Enter your email address: ";
            cin >> email;
            if (email.find('@') == string::npos || email.find('.') == string::npos) {
                throw invalid_argument("Invalid email address! Please enter a valid email.");
            }

            cout << "Enter your address: ";
            cin.ignore();
            getline(cin, address);

            cout << "Enter your Aadhar Number (12 digits): ";
            cin >> governmentID;
            if (to_string(governmentID).length() != 12) {
                throw invalid_argument("Invalid Aadhar number! Must be 12 digits.");
            }

            logToFile("Personal info entered successfully for: " + EnrollmentNo);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error in personal info: " + string(e.what()));
            personalinfo(); // Restart input process
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void educationalinfo() {
        try {
            cout << "Enter your Sr. Secondary School Roll Number: ";
            cin >> School_roll_no;

            cout << "Enter your Sr. Secondary School Marks (out of 100): ";
            cin >> SchoolMarks;
            if (SchoolMarks < 0 || SchoolMarks > 100) {
                throw out_of_range("Invalid marks! Must be between 0 and 100.");
            }

            logToFile("Educational info entered successfully for: " + EnrollmentNo);
        } catch (const out_of_range& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error in educational info: " + string(e.what()));
            educationalinfo(); // Restart input process
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void courses() {
        try {
            int choice;
            cout << "Choose your Programme:" << endl;
            cout << "1. Computer Science Engineering (Rs.60000/sem)" << endl;
            cout << "2. Information Technology Engineering (Rs.50000/sem)" << endl;
            cout << "3. Electronics Engineering (Rs.45000/sem)" << endl;
            cout << "4. Mechanical Engineering (Rs.40000/sem)" << endl;
            cout << "5. Chemical Engineering (Rs.35000/sem)" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    course = "Computer Science";
                    totalfees = 480000;
                    break;
                case 2:
                    course = "Information Technology";
                    totalfees = 400000;
                    break;
                case 3:
                    course = "Electronics Engineering";
                    totalfees = 360000;
                    break;
                case 4:
                    course = "Mechanical Engineering";
                    totalfees = 320000;
                    break;
                case 5:
                    course = "Chemical Engineering";
                    totalfees = 280000;
                    break;
                default:
                    throw invalid_argument("Invalid course selection.");
            }

            logToFile("Course selected successfully for: " + EnrollmentNo + ", Course: " + course);
            cout << "Your admission is successfully completed!!" << endl;
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error in course selection: " + string(e.what()));
            courses(); // Restart course selection
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void display() {
        try {
            cout << "Your details are as follows:" << endl << endl;
            cout << "Enrollment Number: " << EnrollmentNo << endl;
            cout << "Full Name: " << fullName << endl;
            cout << "Date of Birth: " << dateOfBirth << endl;
            cout << "Phone Number: " << phoneNumber << endl;
            cout << "Email Address: " << email << endl;
            cout << "Address: " << address << endl;
            cout << "Aadhar Number: " << governmentID << endl;
            cout << "Sr. Secondary School Roll Number: " << School_roll_no << endl;
            cout << "Sr. Secondary School Marks: " << SchoolMarks << endl;
            cout << "Course: " << course << endl;
            cout << "Total Fees: " << totalfees << endl;

            logToFile("Details displayed successfully for: " + EnrollmentNo);
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    string getenrollmentNumber() {
        return EnrollmentNo;
    }
};


class Payment_semester : private Admission {
private:
    double amountPaid;
    double totalAmountDue;
    int paymentOption;

    void logToFile(const string& message) {
        ofstream logFile("payment_log.txt", ios::app); // Append mode
        if (!logFile) {
            throw runtime_error("Unable to open log file!");
        }
        logFile << message << endl;
        logFile.close();
    }

public:
    Payment_semester() {
        amountPaid = 0;
        totalAmountDue = 0;
        paymentOption = 0;
    }

    void choosePaymentOption() {
        try {
            cout << "Choose Payment Option:\n";
            cout << "1. Yearly (10% discount)\n";
            cout << "2. Semester-wise\n";
            cout << "3. Quarterly (5% extra charge)\n";
            cout << "Enter your choice: ";
            cin >> paymentOption;

            if (paymentOption < 1 || paymentOption > 3) {
                throw invalid_argument("Invalid payment option. Please choose a valid option.");
            }

            switch (paymentOption) {
                case 1:
                    totalAmountDue = totalfees * 0.9; // 10% discount
                    logToFile("Payment option selected: Yearly (10% discount applied)");
                    break;
                case 2:
                    totalAmountDue = totalfees; // No discount
                    logToFile("Payment option selected: Semester-wise");
                    break;
                case 3:
                    totalAmountDue = totalfees * 1.05; // 5% extra charge
                    logToFile("Payment option selected: Quarterly (5% extra charge applied)");
                    break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error in payment option: " + string(e.what()));
            choosePaymentOption(); // Retry input
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    bool isLatePayment() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int dueDay = 15; // Assuming 15th of the month as the due date
        return (ltm->tm_mday > dueDay);
    }

    void applyFine() {
        try {
            if (isLatePayment()) {
                totalAmountDue += 500; // Late payment fine
                cout << "A fine of Rs.500 has been added for late payment.\n";
                logToFile("Late payment fine of Rs.500 added.");
            }
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void makePayment() {
        try {
            applyFine(); // Check for late payment and apply fine
            cout << "Total amount due: Rs." << totalAmountDue << endl;
            cout << "Enter the amount to pay: ";
            cin >> amountPaid;

            if (amountPaid < totalAmountDue) {
                throw logic_error("Insufficient payment. Payment failed.");
            }

            cout << "Payment successful! Thank you.\n";
            logToFile("Payment successful. Amount paid: Rs." + to_string(amountPaid));
        } catch (const logic_error& e) {
            cerr << "Error: " << e.what() << endl;
            logToFile("Error in payment: " + string(e.what()));
            cout << "You still owe Rs." << totalAmountDue - amountPaid << endl;
            cout << "Please pay the remaining amount to complete the payment.\n";
            makePayment(); // Retry payment
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }

    void displayPaymentDetails() {
        try {
            cout << "Payment Option: ";
            switch (paymentOption) {
                case 1:
                    cout << "Yearly (10% discount applied)\n";
                    break;
                case 2:
                    cout << "Semester-wise\n";
                    break;
                case 3:
                    cout << "Quarterly (5% extra charge applied)\n";
                    break;
                default:
                    cout << "Not selected\n";
            }
            cout << "Total Fees Due (after fines/discounts): Rs." << totalAmountDue << endl;
            cout << "Amount Paid: Rs." << amountPaid << endl;

            logToFile("Displayed payment details for Enrollment: " + EnrollmentNo);
        } catch (const runtime_error& e) {
            cerr << "File Error: " << e.what() << endl;
        }
    }
};

class Student {
public:
    Registration registration;
    Admission admission;
    Payment_semester payment;
    bool registered = false;
    bool admitted = false;
    bool paymentDone = false;
};

int main() {
    Login login;
    vector<Student> students;
    bool loggedIn = false;
    int choice;

    cout << "====== Welcome to the College Management System ======\n";

    while (true) {
        cout << "\nPlease select an option:\n";
        cout << "1. Login\n";
        cout << "2. Registration\n";
        cout << "3. Admission\n";
        cout << "4. Payment\n";
        cout << "5. View Admission Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        // Input validation for menu choice
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    if (!loggedIn) {
                        cout << "\n--- Login ---\n";
                        loggedIn = login.loginprompt();
                        if (!loggedIn) {
                            cout << "System locked due to multiple failed login attempts.\n";
                            return 0;
                        }
                    } else {
                        cout << "You are already logged in.\n";
                    }
                    break;

                case 2:
                    if (loggedIn) {
                        cout << "\n--- Registration ---\n";
                        Student newStudent;
                        newStudent.registration.details();
                        newStudent.registration.registrationfee();
                        newStudent.registered = true;
                        students.push_back(newStudent);
                        cout << "Registration successful!\n";
                    } else {
                        cout << "Please log in first.\n";
                    }
                    break;

                case 3:
                    if (loggedIn) {
                        if (students.empty()) {
                            cout << "No registered students found. Please register a student first.\n";
                            break;
                        }
                        cout << "\n--- Admission Details ---\n";
                        for (size_t i = 0; i < students.size(); ++i) {
                            if (students[i].registered) {
                                cout << i + 1 << ". Registered Student\n"; // Placeholder for student info
                            }
                        }
                        cout << "Select a student to admit (by number): ";
                        int studentIndex;
                        if (!(cin >> studentIndex) || studentIndex <= 0 || studentIndex > students.size()) {
                            cout << "Invalid selection. Please try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }

                        if (students[studentIndex - 1].registered) {
                            students[studentIndex - 1].admission.personalinfo();
                            students[studentIndex - 1].admission.educationalinfo();
                            students[studentIndex - 1].admission.courses();
                            students[studentIndex - 1].admitted = true;
                            cout << "Admission completed for student.\n";
                        } else {
                            cout << "Selected student is not registered yet.\n";
                        }
                    } else {
                        cout << "Please log in first.\n";
                    }
                    break;

                case 4:
                    if (loggedIn) {
                        if (students.empty()) {
                            cout << "No admitted students found. Please complete an admission first.\n";
                            break;
                        }
                        cout << "\n--- Payment Options ---\n";
                        for (size_t i = 0; i < students.size(); ++i) {
                            if (students[i].admitted) {
                                cout << i + 1 << ". " << students[i].admission.getenrollmentNumber() << endl;
                            }
                        }
                        cout << "Select a student for payment (by number): ";
                        int paymentIndex;
                        if (!(cin >> paymentIndex) || paymentIndex <= 0 || paymentIndex > students.size()) {
                            cout << "Invalid selection. Please try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }

                        if (students[paymentIndex - 1].admitted) {
                            students[paymentIndex - 1].payment.choosePaymentOption();
                            students[paymentIndex - 1].payment.makePayment();
                            students[paymentIndex - 1].paymentDone = true;
                            cout << "Payment completed for student.\n";
                        } else {
                            cout << "Selected student is not admitted yet.\n";
                        }
                    } else {
                        cout << "Please log in first.\n";
                    }
                    break;

                case 5:
                    if (!students.empty()) {
                        cout << "\n--- View Admission Details ---\n";
                        for (size_t i = 0; i < students.size(); ++i) {
                            if (students[i].admitted) {
                                cout << i + 1 << ". " << students[i].admission.getenrollmentNumber() << endl;
                            }
                        }
                        cout << "Select a student to view details (by number): ";
                        int viewIndex;
                        if (!(cin >> viewIndex) || viewIndex <= 0 || viewIndex > students.size()) {
                            cout << "Invalid selection. Please try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }

                        if (students[viewIndex - 1].admitted) {
                            students[viewIndex - 1].admission.display();
                            cout << "\n--- Payment Summary ---\n";
                            students[viewIndex - 1].payment.displayPaymentDetails();
                        } else {
                            cout << "Selected student is not admitted yet.\n";
                        }
                    } else {
                        cout << "No admissions found.\n";
                    }
                    break;

                case 6:
                    cout << "Exiting the system. Thank you!\n";
                    return 0;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}
