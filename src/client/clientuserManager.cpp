#include "clientuserManager.hpp"

ClientUserManagerImpl::ClientUserManagerImpl()
    :m_socket(nullptr)
{}

ClientUserManagerImpl::~ClientUserManagerImpl()
{
    m_socket->close();
}

ClientUserManagerImpl& ClientUserManagerImpl::getClientUserManager() {
    static ClientUserManagerImpl mgr;
    return mgr;
}

int ClientUserManagerImpl::connectSocket(std::unique_ptr<iClientSocket> socket)
{
    m_socket = std::move(socket);
    return m_socket->connect();
}

void ClientUserManagerImpl::setCardNumber(std::string& card_number) {
    do
    {
        cout << "Enter card number: " << endl;
        cin >> card_number;
        if (card_number.size() != 12)
        {
            cout << "--- Invalid card input, must be 12 symbols ---" << endl;
            continue;
        }
        break;
    }
    while(true);
}

void ClientUserManagerImpl::setPin(std::string& pin) {
    do
    {
        cout << "Enter pin: " << endl;
        cin >> pin;

        if (pin.size() != 4) {
            cout << "--- Invalid pin input, must be 4 symbols ---" << endl;
            continue;
        }
        break;

    } while(true);
}


void ClientUserManagerImpl::setCredentials()
{
    std::string card_number;
    std::string pin;

    setCardNumber(card_number);
    setPin(pin);

    m_card_number = card_number;
    m_pin = pin;
}


bool ClientUserManagerImpl::processRegistration()
{
    std::string mes = PROCESS_REGISTRATION;
    mes += m_card_number;
    mes += m_pin;
    int res = m_socket->sendMessage(mes);

    assert(res > 0);

    res = m_socket->receiveMessage(mes);
    assert(res > 0);

    return (mes == "1") ? true : false;
}

bool ClientUserManagerImpl::processCard()
{
    std::string mes = PROCESS_CARD;
    mes += m_card_number;
    mes += m_pin;
    int response = m_socket->sendMessage(mes);
    assert(response > 0);
    
    response = m_socket->receiveMessage(mes);
    assert(response > 0);

    return mes == OK ? true : false;
}

bool ClientUserManagerImpl::cashIn(int amount)
{
    std::string mes = PROCESS_CASHIN;
    mes += m_card_number;
    mes += m_pin;
    mes += to_string(amount);
    int response = m_socket->sendMessage(mes);
    assert(response > 0);

    response = m_socket->receiveMessage(mes);
    assert(response > 0);

    return mes == OK ? true : false;
}

bool ClientUserManagerImpl::cashOut(int amount)
{
    std::string mes = PROCESS_CASHOUT;
    mes += m_card_number;
    mes += m_pin;
    mes += to_string(amount);
    int response = m_socket->sendMessage(mes);
    assert(response > 0);

    response = m_socket->receiveMessage(mes);
    assert(response > 0);

    return mes == OK ? true : false;
}

double ClientUserManagerImpl::getBalance()
{
    std::string mes = GET_BAL;
    mes += m_card_number;
    mes += m_pin;
    int response = m_socket->sendMessage(mes);

    if(response < 0)
    {
        assert(false);
    }
    response = m_socket->receiveMessage(mes);
    if(response < 0)
    {
        assert(false);
    }
    return atoi(mes.c_str());
}
