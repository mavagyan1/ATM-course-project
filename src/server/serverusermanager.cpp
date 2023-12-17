
#include "serverusermanager.hpp"
#include <vector>
#include <cassert>

using namespace std;

namespace {

    const string DB_NAME = "atm.db";
    const string TABLE_NAME = "user";
    const string COL_CARD_NUMBER = "card_number";
    const string COL_PIN = "pin";
    const string COL_BALANCE = "balance";

    const std::string OK = "1";
    const std::string NOT_OK = "2";

    template<class ...Args>
    std::string makeSql(Args ...args)
    {
        std::string query = "";
        std::vector<std::string> vec = {args...};
        for(auto item : vec)
        {
            query += item;
            query += " ";
        }
        query += ';';
        return query;
    }

}


ServerUserManagerImpl& ServerUserManagerImpl::getServerUserManager() {
    static ServerUserManagerImpl mgr;
    return mgr;
}

ServerUserManagerImpl::ServerUserManagerImpl() 
    : m_db{SqlDBImpl::getSqlDB()} 
    ,m_socket{nullptr} { }

void ServerUserManagerImpl::startServer()
{
    while(true)
    {
        processMessage();
    }
}

bool ServerUserManagerImpl::connectDb()
{
    m_db.connect(DB_NAME);
    auto res = m_db.runSql(
            makeSql("create table if not exists", TABLE_NAME, "(", COL_CARD_NUMBER, "TEXT,", COL_PIN, "TEXT,",
                    COL_BALANCE, "TEXT);"));
    return (res.second == 0) ? true : false;
}

bool ServerUserManagerImpl::connectSocket(std::unique_ptr <iServerSocket> socket)
{
    m_socket = std::move(socket);

    if (m_socket->bind() < 0) {
        return false;
    }

    m_socket->listen();

    if (m_socket->accept() < 0) {
        return false;
    }

    return true;
}

void ServerUserManagerImpl::processMessage()
{
    int received = m_socket->receiveMessage(m_received_message);

    if (received > 0)
    {
        m_card_number = m_received_message.substr(1, 12);
        m_pin = m_received_message.substr(13, 4);

        auto process_type = m_received_message[0];

        if (process_type == '1') // registration
        {
            cardRegistration();
        }
        else if (process_type == '2') // process card 
        {
            validate() ?  m_socket->sendMessage(OK) : m_socket->sendMessage(NOT_OK);
        }

        else if(process_type == '3') // get balance
        {
            if (validate())
            {
                string balance = getBalance();
                int response = m_socket ->sendMessage(balance);
                assert(response > 0);
            }
        }
        else if(process_type == '4') // cash in
        {
            if (validate())
            {
                std::string amount = m_received_message.substr(17);
                cashIn(amount);
                m_socket->sendMessage(OK);
            }
        }
        else if (process_type == '5') // cash out
        {
            if (validate())
            {
                std::string amount = m_received_message.substr((17));
                cashOut(amount) ? m_socket->sendMessage(OK) : m_socket->sendMessage(NOT_OK);

            }
        }
    }
}

void ServerUserManagerImpl::cardRegistration()
{
    auto res = m_db.runSql(makeSql("select", COL_CARD_NUMBER, "from", TABLE_NAME,
                                    "where", COL_CARD_NUMBER, "=", m_card_number));

    if (res.first.empty()) {
        auto user_reg = m_db.runSql(
                makeSql("insert", "into", TABLE_NAME, "(", COL_CARD_NUMBER, ",", COL_PIN, ",", COL_BALANCE, ")",
                        "values", "(", m_card_number, ",", m_pin, ",", "0", ")"));
        assert(user_reg.second == 0);
        if (m_socket->sendMessage("1") < 0)
        {
            assert(false);
        }
    }
    else
    {
        if (m_socket->sendMessage("2") < 0)
        {
            assert(false);
        }
    }
}

bool ServerUserManagerImpl::validate()
{
    auto res = m_db.runSql(makeSql("select", "*","from", TABLE_NAME,
                                    "where", COL_CARD_NUMBER , "=", m_card_number,"and", COL_PIN, "=" , m_pin));
    assert(res.second == 0);

    if(!res.first.empty())
        return true;

    return false;

}

string ServerUserManagerImpl::getBalance()
{
    auto res = m_db.runSql(makeSql("select", COL_BALANCE,"from", TABLE_NAME,
                                    "where", COL_CARD_NUMBER , "=", m_card_number,"and", COL_PIN, "=" , m_pin));

    assert(res.second == 0);

    assert(!res.first[0].empty());

    std::string balance = res.first[0][0];
    return balance;
}

void ServerUserManagerImpl::cashIn(const string& amount)
{
    const string balance = getBalance();
    int result = stoi(amount) + stoi(balance);
    auto res = m_db.runSql(makeSql("update", TABLE_NAME, "set", COL_BALANCE, "=", to_string(result),
                                    "where", COL_CARD_NUMBER, "=", m_card_number, "and", COL_PIN, "=", m_pin));
    assert(res.second == 0);
}

bool ServerUserManagerImpl::cashOut(std::string& amount)
{
    const string balance = getBalance();
    int result = stoi(balance) - stoi(amount);
    if(result >= 0)
    {
        auto res = m_db.runSql(makeSql("update", TABLE_NAME, "set", COL_BALANCE, "=", to_string(result),
                                        "where", COL_CARD_NUMBER, "=", m_card_number, "and", COL_PIN, "=", m_pin));
        assert(res.second == 0);
        return true;
    }
    else
    {
        return false;
    }
}
