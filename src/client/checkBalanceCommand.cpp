#include "checkBalanceCommand.hpp"

void CheckBalance::execute() {
    double balance = _mgr.getBalance();
    cout << "--- Balance is: --- " << balance << endl;
}