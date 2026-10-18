#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cctype>
#include <vector>
#include <cstring>
#include <map>

#define discount1 0.05  // Bronze membership discount = 5%
#define discount2 0.10  // Silver membership discount = 10%
#define discount3 0.15  // Gold membership discount = 15%
using namespace std;

// Structure to represent an item in the cart
struct cartItem {
    int category;       // Item category (1 = Clothes, 2 = Electronics, etc.)
    string product;     // Product name
    double price;       // Unit price
    int quantity;       // Quantity purchased
};

// Structure to store details of a completed invoice
struct InvoiceSummary {
    int invoiceNumber;        // Unique invoice ID
    double total;             // Subtotal before extra charges/discounts
    double finalAmount;       // Final amount payable
    int totalQuantity;        // Total number of items bought
    double serviceCharge;     // 6% service charge
    double tax;               // 10% tax
    double discount;          // Discount based on membership
    double rating;            // Customer rating for service (1-5)
    vector<cartItem> items;   // List of purchased items
};

// Global counters
static int invoiceNo = 0;  // Tracks invoice number
static int cusNum = 1;     // Tracks customer number

// Global vectors
vector<cartItem> cart;              // Holds current cart items
vector<InvoiceSummary> allInvoices; // Stores all invoices (used for reporting)

// Function declarations
void mainMenu();
void exitProgram();
void logo();

int chooseCategory();
void chooseType(int category);


void receipt(int membershipType, const InvoiceSummary& summary);
InvoiceSummary invoice(int membershipType);

int membership();
void loopAgain();
void report();

