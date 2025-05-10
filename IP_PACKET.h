#pragma once
#include <string>
#include <stdio.h>


class IP_PACKET
{
private:

    std::string SENDER_IP;
    std::string RECIVER_IP;
    int TIME_OF_RECEIVING;
    int TIME_OF_SENDING;
    int P_SIZE;

public:


    // konstruktor, destruktor
    IP_PACKET(std::string sender_ip, std::string receiver_ip, int time_of_receiving,int time_of_sending, int p_size);

    virtual ~IP_PACKET() = default;
    
// getterek
    std::string getSenderIp();
    std::string getReceiverIp();
    int getTimeOfReceiving();
    int getTimeOfSending();
    int getPsize();

// setterek nincsenek mert nem fog valtozni a program futasa kozben az ertek

// log
    virtual void PrintInfo();

    
};


