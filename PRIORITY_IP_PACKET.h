#pragma once
#include "IP_PACKET.h"

class PRIORITY_IP_PACKET: public IP_PACKET {
    private:
        int PRIORITY_RATING;
    public:
        PRIORITY_IP_PACKET(std::string sender_ip, std::string receiver_ip, int time_of_receiving,int time_of_sending, int p_size, int priority_rating);


        int getPriorityRating();

        //log
        void PrintInfo();
};
