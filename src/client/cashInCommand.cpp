#include "cashInCommand.hpp"

void CashIn::execute() {
    cout << "Insert amount: ";
    int amount;
    cin >> amount;
    bool res = _mgr.cashIn(amount);
    if (res)
        cout << "--- Your amount is successfully set ---" << endl;
    else
        cout << "--- Failed transaction ---" << endl;
}