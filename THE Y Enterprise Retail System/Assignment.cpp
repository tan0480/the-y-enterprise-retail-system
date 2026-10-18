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

// Function to ask customer about membership and assign discount
int membership() {
    string member;
    int membershipType = 0;

    // Ask if customer is a member
    cout << "Are you a member of THE Y Enterprise? (y for Yes, n for No) : ";
    cin >> member;

    // Validate input (must be y or n)
    while (member.length() != 1 ||
        (tolower(member[0]) != 'y' && tolower(member[0]) != 'n')) {
        cout << "Invalid choice, please retry!!" << endl;
        cout << "Are you a member of THE Y Enterprise? (y for Yes, n for No) : ";
        cin >> member;
    }

    // If customer is a member, ask membership tier
    if (tolower(member[0]) == 'y') {
        cout << "Customer membership Tier List" << endl
            << "1. Bronze" << endl
            << "2. Silver" << endl
            << "3. Gold" << endl;

        cout << "What is your membership type? (1-3) : ";
        cin >> membershipType;

        // Validate membership input
        while (true) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Alphabet is not allowed !!" << endl;
            }
            else if (membershipType < 1 || membershipType > 3) {
                cout << "The integer is out of the range between 1-3 !!" << endl;
            }
            else {
                break;
            }

            cout << "Please enter your membership type (1-3) : ";
            cin >> membershipType;
        }

        // Display discount info
        if (membershipType == 1) {
            cout << "Congratulations you have a 5% discount !!!" << endl << endl;
        }
        else if (membershipType == 2) {
            cout << "Congratulations you have a 10% discount !!!" << endl << endl;
        }
        else if (membershipType == 3) {
            cout << "Congratulations you have a 15% discount !!!" << endl << endl;
        }
    }

    return membershipType; // 0 = no membership
}

// Function to calculate totals and print invoice preview (before payment)
InvoiceSummary invoice(int membershipType) {
    InvoiceSummary summary{};
    summary.invoiceNumber = invoiceNo++;

    string phone = "No. Telephone: 03-11199999";
    string shopName = " THE Y Enterprise";
    double total = 0;
    int totalQuantity = 0, width = 60;
    int pad = (width - phone.length()) / 2;
    int pad2 = (width - shopName.length()) / 2;

    // Get date and time
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    char dateStr[30];
    strftime(dateStr, sizeof(dateStr), "%d-%m-%Y %H:%M:%S", &ltm);

    // Print invoice header
    cout << "Invoice: " << endl;
    cout << string(pad2, ' ') << shopName << endl;
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << setfill(' ');
    cout << string(pad, ' ') << phone << endl;
    cout << left << setw(35) << ("Invoice No: " + to_string(invoiceNo))
        << right << "Date: " << dateStr << endl << endl;

    // Print table headers
    cout << left << setw(5) << "No."
        << setw(20) << "Product"
        << setw(15) << "Price(RM)"
        << setw(10) << "Qty"
        << setw(10) << "Total(RM)" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << setfill(' ');

    // List items
    int i = 1;
    for (auto& item : cart) {
        double itemTotal = item.price * item.quantity;
        total += itemTotal;
        totalQuantity += item.quantity;

        cout << left << setw(5) << i++
            << setw(20) << item.product
            << setw(15) << fixed << setprecision(2) << item.price
            << setw(10) << item.quantity
            << setw(10) << fixed << setprecision(2) << itemTotal << endl;
    }

    // Print subtotal
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << setfill(' ');
    cout << right << setw(45) << "Subtotal (RM) " << ":"
        << setw(10) << fixed << setprecision(2) << total << endl;

    // Calculate service charge, tax, and discount
    double serviceCharge = total * 0.06;
    double tax = total * 0.10;
    double discount = 0.0;

    if (membershipType == 1) discount = total * discount1;
    else if (membershipType == 2) discount = total * discount2;
    else if (membershipType == 3) discount = total * discount3;

    double finalAmount = total + serviceCharge + tax - discount;

    // Print charges and totals
    cout << right << setw(45) << "Service Charge (6%) " << ":"
        << setw(10) << fixed << setprecision(2) << serviceCharge << endl;
    cout << right << setw(45) << "Tax (10%) " << ":"
        << setw(10) << fixed << setprecision(2) << tax << endl;
    cout << right << setw(45) << "Membership Discount " << ":"
        << setw(10) << fixed << setprecision(2) << -discount << endl;

    cout << endl;
    cout << setfill('-') << setw(60) << "-" << endl;
    cout << setfill(' ');
    cout << right << setw(45) << "Total items bought " << ":"
        << setw(10) << totalQuantity << endl;
    cout << right << setw(45) << "Total Payable (RM) " << ":"
        << setw(10) << fixed << setprecision(2) << finalAmount << endl;
    cout << setfill('-') << setw(60) << "-" << endl;

    // Store values in summary
    summary.total = total;
    summary.serviceCharge = serviceCharge;
    summary.tax = tax;
    summary.discount = discount;
    summary.finalAmount = finalAmount;
    summary.totalQuantity = totalQuantity;

    return summary;
}

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

// Function to generate daily sales report (staff option)
void report() {
    if (allInvoices.empty()) {
        cout << "No transactions recorded yet." << endl;
        return;
    }

    int totalCustomers = allInvoices.size();
    double totalSales = 0, totalDiscount = 0;
    int totalItems = 0, totalRatings = 0;
    map<int, int> categorySales;

    // Summarize data from invoices
    for (auto& inv : allInvoices) {
        totalSales += inv.finalAmount;
        totalDiscount += inv.discount;
        totalItems += inv.totalQuantity;
        totalRatings += inv.rating;

        for (auto& it : inv.items) {
            categorySales[it.category] += it.quantity;
        }
    }

    // Find top and least selling categories
    int topCategory = -1;
    int leastCategory = -1;
    int maxSold = -1;
    int minSold = INT_MAX;

    if (categorySales.empty()) {
        cout << "No items sold today." << endl;
    }
    else {
        for (auto& c : categorySales) {
            if (c.second > maxSold) {
                maxSold = c.second;
                topCategory = c.first;
            }
            if (c.second < minSold) {
                minSold = c.second;
                leastCategory = c.first;
            }
        }
    }

    double avgSpending = totalSales / totalCustomers;
    double avgRating = static_cast<double>(totalRatings) / totalCustomers;

    // Get current date/time
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    char dateStr[30];
    strftime(dateStr, sizeof(dateStr), "%d-%m-%Y %H:%M:%S", &ltm);

    // Print report
    string report = "Daily Sales Report";
    int width = 60;
    int pad = (width - report.length()) / 2;
    int pad2 = (width - strlen(dateStr)) / 2;

    cout << string(pad, ' ') << report << endl;
    cout << string(pad2, ' ') << dateStr << endl;
    cout << setw(width) << setfill('=') << "=" << endl;
    cout << setfill(' ');

    cout << "Total Customer                 : " << totalCustomers << endl;
    cout << "Overall Sales (RM)             : " << fixed << setprecision(2) << totalSales << endl;
    cout << "Total Item Sold                : " << totalItems << endl;

    for (auto& c : categorySales) {
        cout << "  Category " << c.first << ": " << c.second << " items" << endl;
    }

    cout << "Top Selling Category           : Category " << topCategory << " (" << maxSold << " items)" << endl;
    cout << "Least Selling Category         : Category " << leastCategory << " (" << minSold << " items)" << endl;
    cout << "Average Spending per Customer  : RM " << avgSpending << endl;
    cout << "Discount Used (RM)             : " << totalDiscount << endl;
    cout << "Average Rating                 : " << fixed << setprecision(1) << avgRating << "/5" << endl;
    cout << setw(60) << setfill('=') << "=" << endl;
    cout << setfill(' ');

    loopAgain();
}

