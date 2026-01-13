#include "Payment.h"

void Payment::processPayment() {
    string method;
    cout << "\nPayment Method (Easypaisa/JazzCash): ";
    cin >> method;
    string phone, otp;
    cout << "Phone Number: ";
    cin >> phone;
    cout << "OTP: ";
    cin >> otp;
    cout << "Transaction Successful via " << method << "\n";
}