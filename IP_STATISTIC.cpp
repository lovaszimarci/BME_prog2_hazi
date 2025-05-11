#include "IP_STATISTIC.h"
#include "IP_PACKET.h"
#include "PRIORITY_IP_PACKET.h"
#include <typeinfo>




IP_STATISTIC::IP_STATISTIC(std::vector<IP_PACKET *>& data): DATA(data)
{
}

float IP_STATISTIC::getAvarageBanwidth_SENDER_RECIVER()
{
    return this->AvarageBanwidth_SENDER_RECIVER;
}

float IP_STATISTIC::getAvarageArival_PRIORITY()
{
    return this->AvarageArival_PRIORITY;
}

float IP_STATISTIC::getAvarageBandwidth_ALL()
{
    return AvarageBandwidth_ALL;
}

float IP_STATISTIC::getRatio_PRIO_NON_PRIO()
{
    return this->Ratio_PRIO_NON_PRIO;
}


void IP_STATISTIC::AVARAGE_BANDWITH_SENDER_RECIVER(std::string senderip, std::string reciverip){
    float bandwith_sum = 0.0;
    float number_of_pairs = 0.0;
    for(IP_PACKET* packet : DATA){
        // ip cim parok ellenorzese
        if(packet->getSenderIp() == senderip && packet->getReceiverIp() == reciverip){
            //az adott packet savszelessege szamitasa
            bandwith_sum = bandwith_sum + ((float)packet->getPsize()/(float)packet->GetSecondsInRouter());
            number_of_pairs = number_of_pairs+1;

        }
    }
    // atlag kiszamitasa
    this->AvarageBanwidth_SENDER_RECIVER = bandwith_sum / number_of_pairs ;
}

void IP_STATISTIC::AVARAGE_ARIVAL_PRIORITY(int priority_number)
{
    std::vector<PRIORITY_IP_PACKET*> p_packets;
    
    // az adott prioritasu elemek athelyezese az uj vektorba
    for(IP_PACKET* item : DATA){
        if(typeid(*item) == typeid(PRIORITY_IP_PACKET)){
            PRIORITY_IP_PACKET* p_item = dynamic_cast<PRIORITY_IP_PACKET*>(item);
            if(!p_item){
                std::cout<<"casting failed"<<std::endl;
            }
            if( p_item && p_item->getPriorityRating() == priority_number){
                p_packets.push_back(p_item);
            }
        
        }
    }
    
    int arrival_times[p_packets.size()];


    // az erkezesi idokozok meghatarozasa
    for(int i = 0; i < p_packets.size()-1; i++){
        arrival_times[i] = p_packets[i+1]->getTimeOfReceiving() - p_packets[i]->getTimeOfReceiving();
    }
    // az atlag meghatarozasa 
    int sum = 0;
    for(int i = 0; i < p_packets.size()-1; i++){
        sum = sum + arrival_times[i];
    }
    this->AvarageArival_PRIORITY = (float)sum/ ((float)p_packets.size()-1);

}

void IP_STATISTIC::AVARAGE_BANDWITH_ALL()
{
    float bandwith_sum = 0.0;
    for(IP_PACKET* packet : DATA){
            //az adott packet savszelessege szamitasa
            bandwith_sum = bandwith_sum + ((float)packet->getPsize()/(float)packet->GetSecondsInRouter());
    }
    // atlag kiszamitasa
    this->AvarageBandwidth_ALL = bandwith_sum / (float)DATA.size() ;
    
}

void IP_STATISTIC::RATIO_PRIO_NON_PRIO()
{
    int sum_of_all_data = 0;
    int sum_of_priority_data = 0;
    for(IP_PACKET* item : DATA){
        
        //Priority ellenorzese
        if(typeid(*item) == typeid(PRIORITY_IP_PACKET)){
            sum_of_all_data = sum_of_all_data + item->getPsize();
            sum_of_priority_data = sum_of_priority_data + item->getPsize();
        }
        else{
            sum_of_all_data = sum_of_all_data + item->getPsize();
        }
    }

    this->Ratio_PRIO_NON_PRIO = 100.00*((float)sum_of_priority_data/(float)sum_of_all_data);
}
