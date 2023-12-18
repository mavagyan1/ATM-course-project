#include "clientApplication.hpp"
#include "iclientsocket.hpp"
#include "clientsocket.hpp"
#include <iostream>
#include <memory>
#include <limits>
#include "commandRegistry.hpp"

ClientApplication::ClientApplication()
    :_mgr{ClientUserManagerImpl::getClientUserManager()}
    ,_reg{CommandRegistry::getCommandRegistry()}
{ }

void ClientApplication::printOptions() {
    std::cout << endl;
    std::cout << "Check balance, press 1" << endl;
    std::cout << "Cash in, press 2" << endl;
    std::cout << "Cash out, press 3" << endl;
    std::cout << "Exit, press 4" << endl;
    std::cout << endl;
}

void ClientApplication::printMenu() {
    std::cout << "New card registration, press 1" << std::endl;
    std::cout << "Enter card number, press 2" << std::endl;
    std::cout << "Exit, press 3" << std::endl;
}


int ClientApplication::runApp() {
    std::unique_ptr<iClientSocket> s = std::make_unique<CLIENT_SOCKET::ClientSocketImpl>();
    if(_mgr.connectSocket( std::move(s) ) == -1) {
        std::cerr << "Internal server error" << std::endl;
        return -1;
    }
    runATM();
    return 0;
}

int ClientApplication::getInput() const {
    int input;
    while (true) {
        std::cout << "Enter a number: ";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return input;
}

void ClientApplication::processInput() {
    try {
        printOptions();
        int choice = getInput();
        auto cmd = _reg.findCommand(choice);
        cmd->execute();
    }
        catch(std::exception& exp) {
            std::cout << exp.what() << std::endl;
    }
}

void ClientApplication::runATM() {
    do
    {
        printMenu();
        int choice = getInput();
        if(choice == 1 || choice == 2 )
            _mgr.setCredentials();
        
        switch (choice) {   
        case 1 :
            if(_mgr.processRegistration())
                std::cout << "--- Card Registered ---" << std::endl;
            else{
                std::cout <<"--- Card Already exists. Try Another Card Number ---" << std::endl;
                continue;
            }
            break;
        case 2 :
            if (!_mgr.processCard()) {
                std::cout << "--- Invalid card number or pin, try again ---" << endl;
                continue;
            } 
            else {
                do{   
                    processInput();
                }while(_mgr.isActive()); 
            }
            break;
        case 3 :
            isActive = false;
            break;
        default:
            break;
        }

    }while(isActive);

}
