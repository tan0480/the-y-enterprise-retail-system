# THE Y Enterprise Retail System

A C++ console application developed for AMCS1013 Problem Solving and Programming. It demonstrates a retail checkout workflow and an in-session sales report.

## Features

- Customer and staff menus with input validation.
- Four product categories: clothes, electronics, furniture, and food and beverages.
- Product selection, quantities, and a shopping cart.
- Bronze, Silver, and Gold membership discounts of 5%, 10%, and 15%.
- Invoice calculation with the assignment's fixed 6% service charge and 10% tax.
- Simulated payment selection, payment amount validation, change, and receipts.
- Customer ratings and sales summaries with category statistics.

## Build and run

The supplied solution targets Windows, Visual Studio 2022, the v143 C++ toolset, and a Windows 10 SDK. Install the Desktop development with C++ workload, open `THE Y Enterprise Retail System.sln`, select an x64 configuration, and build/run the console application.

Alternatively, with MSYS2 UCRT64 GCC on Windows, run from the repository root in PowerShell:

```powershell
g++ -std=c++17 -Wall -Wextra "THE Y Enterprise Retail System/Assignment.cpp" -o retail.exe
.\retail.exe
```

The UCRT64 `bin` directory must be on PATH for the compiler and runtime DLLs. The source uses the Windows `localtime_s` interface; Linux/macOS compatibility is not claimed.

Choose `c` for a customer or `s` for staff. Complete a purchase, answer `y` to continue to the next user, then choose staff and Report to inspect the transactions from that session.

## Coding contributions

| Contributor | Coding contribution |
| --- | --- |
| [Tan Yi Heng](https://github.com/tan0480) | `membership()`, `invoice()`, `report()`: membership discounts, invoice calculations, sales reporting, and date/time integration; shared application integration. |
| [Cheah Yong Shun](https://github.com/ys012007) | `chooseCategory()`, `chooseType()`: category and product selection, quantity validation, and cart entry. |
| [Lam Yi Hen](https://github.com/lamyihen77-beep) | `receipt()`, `loopAgain()`: payment validation, change, receipts, ratings, transaction history, and next-customer flow. |
| [Lim Jun Yi](https://github.com/ljunyi0212) | `logo()`, `exitProgram()`, `mainMenu()`, and entry-point integration: console presentation, menus, and input validation. |

Function ownership follows the assignment report's Programming sections and the team's confirmed contribution mapping. Shared declarations are credited to all four contributors. The import commits record an existing assignment, not its original development timeline. Tan Yi Heng performs the commits and push; authors and co-author trailers credit the actual contributions. Early import commits are partial source snapshots and are not standalone runnable versions.

## Scope and limitations

- Transactions exist only in memory and are lost when the program exits. The daily sales report summarizes the current session, not a persistent date-filtered database.
- Payment methods are simulated; no payment gateway or real transaction processing is included.
- The staff menu is a role selection, not an authenticated login.
- Rates are assignment constants, not current tax or accounting guidance.
- The original source is preserved. GCC reports an existing unused `membershipType` parameter in `receipt()`.

## Verification

On Windows with UCRT64 GCC, the original source compiled with the warning noted above. Isolated scripted checks passed for customer exit, empty reporting, purchases and reports for all four membership cases (none/Bronze/Silver/Gold), and recovery from invalid menu, category, product, quantity, tier, payment, and rating input. These checks do not replace exhaustive testing or a Visual Studio build.

Only source, shared Visual Studio project files, and repository documentation are included. IDE caches, personal settings, binaries, reports, and build output are excluded.
