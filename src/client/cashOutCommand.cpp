#include "cashOutCommand.hpp"

void CashOut::execute() {
    cout << "Insert amount: ";
    int amount;
    cin >> amount;
    bool res = _mgr.cashOut(amount);
    if (res)
        cout << "--- Take your cash! ---" << endl;
    else
        cout << "--- Not enough amount ---" << endl;
}