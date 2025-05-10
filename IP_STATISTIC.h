#pragma once
#include <vector>
#include <iostream>
#include "IP_PACKET.h"
#include "PRIORITY_IP_PACKET.h"

class IP_STATISTIC{
    private:
        std::vector<IP_PACKET*> DATA;
        float AvarageBanwidth_SENDER_RECIVER;
        float AvarageArival_PRIORITY;
        float AvarageBandwidth_ALL;
        float Ratio_PRIO_NON_PRIO;

    public:
        //konstruktor
        IP_STATISTIC(std::vector<IP_PACKET*> data);
        // getterek
        float getAvarageBanwidth_SENDER_RECIVER();
        float getAvarageArival_PRIORITY();
        float getAvarageBandwidth_ALL();
        float getRatio_PRIO_NON_PRIO();
        //setterek nem kellenek mert nem lesz az osztalyon kivul allitva az ertek

        //statisztikai fuggvenyek

        void AVARAGE_BANDWITH_SENDER_RECIVER();
        void AVARAGE_ARIVAL_PRIORITY();
        void AVARAGE_BANDWITH_ALL();
        void RATIO_PRIO_NON_PRIO();





};