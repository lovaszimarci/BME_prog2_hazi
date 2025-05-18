#pragma once
#include <vector>
#include <iostream>
#include "IP_PACKET.h"
#include "PRIORITY_IP_PACKET.h"
#include <string>
class IP_STATISTIC{
    private:
        std::vector<IP_PACKET*> DATA;
        float AvarageBanwidth_SENDER_RECIVER;
        float AvarageArival_PRIORITY;
        float Bandwidth_ALL;
        float Ratio_PRIO_NON_PRIO;

    public:
        //konstruktor
        IP_STATISTIC(std::vector<IP_PACKET*>& data);
        // getterek
        float getAvarageBanwidth_SENDER_RECIVER();
        float getAvarageArival_PRIORITY();
        float getBandwidth_ALL();
        float getRatio_PRIO_NON_PRIO();
        //setterek nem kellenek mert nem lesz az osztalyon kivul allitva az ertek

        //statisztikai fuggvenyek

        void AVARAGE_BANDWITH_SENDER_RECIVER(std::string senderip, std::string reciverip);
        void AVARAGE_ARIVAL_PRIORITY(int priority_number);
        void BANDWITH_ALL();
        void RATIO_PRIO_NON_PRIO();





};