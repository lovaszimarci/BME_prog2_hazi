#include "PRIORITY_IP_PACKET.h"
#include <string>
#include <iostream>

PRIORITY_IP_PACKET::PRIORITY_IP_PACKET(std::string sender_ip, std::string receiver_ip,
    int time_of_receiving, int time_of_sending, int p_size, int priority_rating): IP_PACKET(sender_ip,receiver_ip,
    time_of_receiving, time_of_sending, p_size), PRIORITY_RATING(priority_rating){}

int PRIORITY_IP_PACKET::getPriorityRating()
{
    return this->PRIORITY_RATING;
}



void PRIORITY_IP_PACKET::PrintInfo(){
    std::cout<< this->getSenderIp()<<" "<< this->getReceiverIp() <<" "<< this->getTimeOfReceiving() <<" "<<this->getTimeOfSending()<<" "<< this->getPsize()<<" "<< this->getPriorityRating() << std::endl;
}