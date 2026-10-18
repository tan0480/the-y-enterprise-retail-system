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

// Function to allow user to choose a product category
int chooseCategory() {
    int category;
    cout << "Category: " << endl
        << "1. Clothes   /     \\" << endl
        << "            / |   | \\" << endl
        << "               --- " << endl
        << "2. Electronics Gadget   *********" << endl
        << "                        *       *" << endl
        << "                        *       *" << endl
        << "                        *       *" << endl
        << "                        *       *" << endl
        << "                        *   0   *" << endl
        << "                        *********" << endl
        << "3. Furniture   * " << endl
        << "               * " << endl
        << "               * " << endl
        << "               ****** " << endl
        << "               *    * " << endl
        << "               *    * " << endl
        << "4. Food and Beverages   ( (" << endl
        << "                         ) )" << endl
        << "                      ........" << endl
        << "                      |      |]" << endl
        << "                      \\      /" << endl
        << "                       `----'" << endl;

    cout << "Choose a category that you want to order (1-4): ";
    cin >> category;

    // Validate category choice
    while (true) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Alphabet is not allowed !!" << endl;
        }
        else if (category < 1 || category > 4) {
            cout << "The integer is out of the range between 1-4 !!" << endl;
        }
        else {
            break;
        }

        cout << "Please choose a category that you want to order (1-4): ";
        cin >> category;
    }

    return category;
}

// Function to select item type within a chosen category
void chooseType(int category) {
    string type, add_on;
    int quantity = 0;

    // Display product list based on category
    if (category == 1) {
        cout << left << setw(20) << "Type"
            << setw(20) << "Product"
            << setw(20) << "Price(RM)" << endl;
        cout << left << setw(20) << "AAA"
            << setw(20) << "T-Shirt"
            << setw(20) << "49.00" << endl;
        cout << left << setw(20) << "BBB"
            << setw(20) << "Jeans"
            << setw(20) << "89.00" << endl;
        cout << left << setw(20) << "CCC"
            << setw(20) << "Dress"
            << setw(20) << "129.00" << endl << endl;
    }
    else if (category == 2) {
        cout << left << setw(20) << "Type"
            << setw(20) << "Product"
            << setw(20) << "Price(RM)" << endl;
        cout << left << setw(20) << "AAA"
            << setw(20) << "Laptop"
            << setw(20) << "4999.00" << endl;
        cout << left << setw(20) << "BBB"
            << setw(20) << "Game Console"
            << setw(20) << "2999.00" << endl;
        cout << left << setw(20) << "CCC"
            << setw(20) << "Smartphone"
            << setw(20) << "3999.00" << endl << endl;
    }
    else if (category == 3) {
        cout << left << setw(20) << "Type"
            << setw(20) << "Product"
            << setw(20) << "Price(RM)" << endl;
        cout << left << setw(20) << "AAA"
            << setw(20) << "Sofa"
            << setw(20) << "1999.00" << endl;
        cout << left << setw(20) << "BBB"
            << setw(20) << "Dining Table"
            << setw(20) << "1299.00" << endl;
        cout << left << setw(20) << "CCC"
            << setw(20) << "Ergonomic Chair"
            << setw(20) << "899.00" << endl << endl;
    }
    else if (category == 4) {
        cout << left << setw(20) << "Type"
            << setw(20) << "Product"
            << setw(20) << "Price(RM)" << endl;
        cout << left << setw(20) << "AAA"
            << setw(20) << "Nama Chocolate"
            << setw(20) << "99.00" << endl;
        cout << left << setw(20) << "BBB"
            << setw(20) << "Tea"
            << setw(20) << "149.00" << endl;
        cout << left << setw(20) << "CCC"
            << setw(20) << "Coffee"
            << setw(20) << "49.00" << endl << endl;
    }

    // Ask user to select product type
    cout << setw(20) << "Enter type" << " : ";
    cin >> type;
    for (auto& c : type) c = toupper(c);

    // Validate type input
    while (type.length() != 3 || !(type == "AAA" || type == "BBB" || type == "CCC")) {
        cout << "Invalid type, please retry!!" << endl;
        cout << setw(20) << "Enter type" << " : ";
        cin >> type;
        for (auto& c : type) c = toupper(c);
    }

    // Ask quantity
    cout << setw(20) << "Enter Quantity" << " : ";
    cin >> quantity;
    while (true) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Alphabet is not allowed !!" << endl;
        }
        else if (quantity < 1) {
            cout << "The integer is out of the range !!" << endl;
        }
        else {
            break;
        }
        cout << setw(20) << "Enter Quantity" << " : ";
        cin >> quantity;
    }

    // Add selected item to cart
    if (category == 1) {
        if (type == "AAA") cart.push_back({ 1, "T-Shirt", 49.00, quantity });
        else if (type == "BBB") cart.push_back({ 1, "Jeans", 89.00, quantity });
        else if (type == "CCC") cart.push_back({ 1, "Dress", 129.00, quantity });
    }
    else if (category == 2) {
        if (type == "AAA") cart.push_back({ 2, "Laptop", 4999.00, quantity });
        else if (type == "BBB") cart.push_back({ 2, "Game Console", 2999.00, quantity });
        else if (type == "CCC") cart.push_back({ 2, "Smartphone", 3999.00, quantity });
    }
    else if (category == 3) {
        if (type == "AAA") cart.push_back({ 3, "Sofa", 1999.00, quantity });
        else if (type == "BBB") cart.push_back({ 3, "Dining Table", 1299.00, quantity });
        else if (type == "CCC") cart.push_back({ 3, "Ergonomic Chair", 899.00, quantity });
    }
    else if (category == 4) {
        if (type == "AAA") cart.push_back({ 4, "Nama Chocolate", 99.00, quantity });
        else if (type == "BBB") cart.push_back({ 4, "Tea", 149.00, quantity });
        else if (type == "CCC") cart.push_back({ 4, "Coffee", 49.00, quantity });
    }

    // Ask if user wants to add more items
    cout << "Would you like to add anything else? (y for Yes, n for No): ";
    cin >> add_on;

    while (add_on.length() != 1 || (tolower(add_on[0]) != 'y' && tolower(add_on[0]) != 'n')) {
        cout << "Invalid choice, please retry!!" << endl;
        cout << "Would you like to add anything else? (y for Yes, n for No): ";
        cin >> add_on;
    }

    // Recursive selection
    if (tolower(add_on[0]) == 'y') {
        string selection;
        cout << "Do you want to order another type or category? (t for type, c for category): ";
        cin >> selection;

        while (selection.length() != 1 || (tolower(selection[0]) != 't' && tolower(selection[0]) != 'c')) {
            cout << "Invalid choice, please retry!!" << endl;
            cout << "Do you want to order another type or category? (t for type, c for category): ";
            cin >> selection;
        }

        if (tolower(selection[0]) == 't') {
            chooseType(category);
        }
        else if (tolower(selection[0]) == 'c') {
            int newCategory = chooseCategory();
            chooseType(newCategory);
        }
    }
}

