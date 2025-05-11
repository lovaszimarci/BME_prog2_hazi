#include "IP_PACKET.h"
#include <string>
#include <iostream>

IP_PACKET::IP_PACKET(std::string sender_ip, std::string receiver_ip, int time_of_receiving,int time_of_sending, int p_size):
SENDER_IP(sender_ip), RECIVER_IP(receiver_ip),TIME_OF_RECEIVING(time_of_receiving), TIME_OF_SENDING(time_of_sending), P_SIZE(p_size)
{
}

// getterek
std::string IP_PACKET::getSenderIp()
{
    return this->SENDER_IP;
}

std::string IP_PACKET::getReceiverIp()
{
    return this->RECIVER_IP;
}

int IP_PACKET::getTimeOfReceiving()
{
    return this->TIME_OF_RECEIVING;
}

int IP_PACKET::getTimeOfSending()
{
    return this->TIME_OF_SENDING ;
}

int IP_PACKET::getPsize()
{
    return this->P_SIZE;
}

void IP_PACKET::PrintInfo()
{
    std::cout<< this->SENDER_IP<<" "<< this->RECIVER_IP<<" "<<this->TIME_OF_SENDING<<" "<<this->TIME_OF_SENDING<<" "<< this->P_SIZE << std::endl;
}


int IP_PACKET::GetSecondsInRouter(){
    return this->getTimeOfSending() - this->getTimeOfReceiving();
}