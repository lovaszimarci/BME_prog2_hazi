#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "IP_PACKET.h"
#include "PRIORITY_IP_PACKET.h"
#include "IP_STATISTIC.h"
#include <typeinfo>


int StringTimeToInt(const std::string& StringTime){
    int h, m, s;
    char sep1, sep2;

    //beleteszi a stringet egy streambe amibol mar ki lehet olvasni
    std::istringstream string_stream(StringTime);

    string_stream>>h>>sep1>>m>>sep2>>s;

    return h*3600 + m*60 + s;
}

void ReadIn(std::vector<IP_PACKET*>& Packets, std::string Filename){
    // buffer az adatsornak
    std::string buffer_data_line;
    //buffer az egyes adatoknak a sorban (a stream miatt kell)
    std::string buffer_data_element;

    // buffer az adatsor elemek eltaralasahoz (indexelheto)
    std::string data_for_packet[6];

    // file megnyitasa
    std::ifstream File(Filename);
    //file error handling
    if(!File){
        std::cout<<"hiba a file megnyitasakor";
    }
    //while loop ami soronkent megy vegig a fajlon
    while(std::getline(File, buffer_data_line)){
        //counter a data_for_packet indexelesehez
        int counter = 0;
        //adatsor streamme alakitja a szavak kiolvasasahoz
        std::istringstream stream_line(buffer_data_line);

        while(stream_line>>buffer_data_element){
            data_for_packet[counter] = buffer_data_element;
            counter = counter + 1;
            //debug
            //std::cout<<data_for_packet[counter];
        }
        //counter reset a kovetkezo sorhoz
        counter = 0;

        //eldonti hogy az adott csomag priority vagy nem
        if(data_for_packet[5] != "0"){
            
            // priority packet tagvaltozo inicializalasa
            Packets.push_back(new PRIORITY_IP_PACKET(data_for_packet[0],data_for_packet[1],
            StringTimeToInt(data_for_packet[2]),StringTimeToInt(data_for_packet[3]),std::stoi(data_for_packet[4]),
            std::stoi(data_for_packet[5])));
        }
        else{
            
            //IP packet tagvaltozo incicializalasa
            Packets.push_back(new IP_PACKET(data_for_packet[0],data_for_packet[1],
            StringTimeToInt(data_for_packet[2]),StringTimeToInt(data_for_packet[3]),
            std::stoi(data_for_packet[4])));

        }
    }
    File.close();
};




int main(){
    
    std::vector<IP_PACKET*> packpack;


    ReadIn(packpack,"test2function.txt");

    IP_STATISTIC stat1(packpack);

    /*
    stat1.AVARAGE_BANDWITH_SENDER_RECIVER("102.45.187.23","87.162.34.10");
    std::cout<<stat1.getAvarageBanwidth_SENDER_RECIVER()<<std::endl;
    */
    stat1.AVARAGE_ARIVAL_PRIORITY(2);
    std::cout<< stat1.getAvarageArival_PRIORITY();

/*
    for(IP_PACKET* item : packpack){
        if(typeid(*item) == typeid(IP_PACKET)){
            std::cout<< "ez sima packet" <<std::endl;
            (*item).PrintInfo();
        }
        else{
            std::cout<< "ez prio packet"<<std::endl;
            PRIORITY_IP_PACKET* p_item = dynamic_cast<PRIORITY_IP_PACKET*>(item);
            (*p_item).PrintInfo();
            std::cout<<(*p_item).getPriorityRating()<<std::endl;
        }
    }
*/


    return 0;





}