#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "IP_PACKET.h"
#include "PRIORITY_IP_PACKET.h"
#include "IP_STATISTIC.h"
#include <typeinfo>


void PrintLineDesign(){
    std::cout<<"-----------------------------------------------------------------------------------------------"<<std::endl;
}


int StringTimeToInt(const std::string& StringTime){
    int h, m, s;
    char sep1, sep2;

    //beleteszi a stringet egy streambe amibol mar ki lehet olvasni
    std::istringstream string_stream(StringTime);

    string_stream>>h>>sep1>>m>>sep2>>s;

    return h*3600 + m*60 + s;
}

void WriteLogToFile(int& option_number, IP_STATISTIC& statistic){

    std::ofstream File("AnalyzerLog.txt",std::ios::app);

    if(File.is_open()){
        if(option_number == 1){
            File<<"Az atlagos savszelesseg az adott forras-cim parra: "<<statistic.getAvarageBanwidth_SENDER_RECIVER()<<" Mbps\n";
            File.close();
        }
        if(option_number == 2){
            File<<"Az adott prioritasu csomagok atlagos erkezesi idokoze:"<<statistic.getAvarageArival_PRIORITY()<< " masodperc\n";
            File.close();
        }
        if(option_number == 3){
            File<<"Az osszes adatbol adodo savszelesseg: "<<statistic.getBandwidth_ALL()<<" Mbps\n";
            File.close();
        }
        if(option_number == 4){
            File<<"Az osszes adat "<<statistic.getRatio_PRIO_NON_PRIO()<<"% szazaleka a prioritasos csomagok adata\n";
            File.close();
        }
        if(option_number == 5){
            
            File<<"Az atlagos savszelesseg az adott forras-cim parra: "<<statistic.getAvarageBanwidth_SENDER_RECIVER()<<" Mbps\n";
            File<<"Az adott prioritasu csomagok atlagos erkezesi idokoze:"<<statistic.getAvarageArival_PRIORITY()<< " masodperc\n";
            File<<"Az osszes adatbol adodo savszelesseg: "<<statistic.getBandwidth_ALL()<<" Mbps\n";
            File<<"Az osszes adat "<<statistic.getRatio_PRIO_NON_PRIO()<<"% szazaleka a prioritasos csomagok adata\n";
            File.close();
        }
    }
    else{
        std::cout<<"Opening of File failed!";
    }


}







int ReadIn(std::vector<IP_PACKET*>& Packets, std::string Filename){
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
        std::cout<<"hiba a file megnyitasakor"<<std::endl;
        return 0;
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
    return 1;
};




int main(){
    // a log file torlese az elozo hasznalat utan
    std::ofstream File("AnalyzerLog.txt",std::ios::trunc);
    if(!File){
        std::cout<<"hiba a log file megnyitasakor!";
    }
    File.close();    

    std::vector<IP_PACKET*> packets;


    std::string Filename;
    std::string ip1;
    std::string ip2;
    int Priority_rating;
    int function_number;
    int priority = 0;
    int option = 0;
    int exit = 0;



    
        std::cout<<"  _____ _____                     _        _                          _                    "<<std::endl;
        std::cout<<" |_   _|  __ \\                   | |      | |       /\\               | |                   "<<std::endl;
        std::cout<<"   | | | |__) |  _ __   __ _  ___| | _____| |_     /  \\   _ __   __ _| |_   _ _______ _ __ "<<std::endl;
        std::cout<<"   | | |  ___/  | '_ \\ / _` |/ __| |/ / _ \\ __|   / /\\ \\ | '_ \\ / _` | | | | |_  / _ \\ '__|"<<std::endl;
        std::cout<<"  _| |_| |      | |_) | (_| | (__|   <  __/ |_   / ____ \\| | | | (_| | | |_| |/ /  __/ |   "<<std::endl;
        std::cout<<" |_____|_|      | .__/ \\__,_|\\___|_|\\_\\___|\\__| /_/    \\_\\_| |_|\\__,_|_|\\__, /___\\___|_|   "<<std::endl;
        std::cout<<"                | |                                                      __/ |             "<<std::endl;
        std::cout<<"                |_|                                                     |___/              "<<std::endl;
        std::cout<<"Adja meg az elemzeshez hasznalt fajl nevet."<<std::endl;
        std::cin>> Filename;
        std::cout<<std::endl;

        // a log file beolvasasa

        while(ReadIn(packets,Filename) != 1){
            std::cout<<"Adjon meg egy helyes fajl nevet:"<<std::endl;
            std::cin>> Filename;
        }
        
        IP_STATISTIC stat1(packets);
        


        while(exit == 0){
            std::cout<<" "<<std::endl;
            std::cout<<"Az elemzas elkezdeshez valasszon az alabbi opciok kozul!(1-6):"<<std::endl;
            std::cout<<"1)Atlagos savszelesseg szamitasa egy adott forras-cel parra"<<std::endl;
            std::cout<<"2)Adott prioritasu csomagok atlagos erkezesi idokozenek szamitasa"<<std::endl;
            std::cout<<"3)Az osszes csomagbol adodo savszelesseg szamitasa"<<std::endl;
            std::cout<<"4)Az atvitt prioritasos csomagok adatmennyisegenek aranya az osszes adathoz kepest"<<std::endl;
            std::cout<<"5) Az osszes funkcio futtatasa"<<std::endl;
            std::cout<<"6) kilepes"<<std::endl;
            std::cout<<"A valasztott opcio szama: ";
            std::cin>> option;
            std::cout<<std::endl;

            while (std::cin.fail() || option < 1 || option > 6) {
            std::cin.clear(); // hibás flag törlése
            std::cout << "Kerem adjon meg egy szamot 1 es 6 kozott: ";
            std::cin >> option;
            }
            
            // opciok
            if(option == 1){
                std::cout<<"Adjon meg egy kereseshez hasznalando forras-cel ip cim part"<<std::endl;
                std::cout<<"A forras ip cim: ";
                std::cin>>ip1;
                while(std::cin.fail()){
                    std::cout<<"Adjon meg egy helyes ip cimet!"<<std::endl;
                    std::cin>>ip1;
                }
                std::cout<<std::endl;
                std::cout<<"A cel ip cim: ";
                std::cin>>ip2;
                while (std::cin.fail())
                {
                    std::cout<<"Adjon meg egy helyes ip cimet!"<<std::endl;
                    std::cin>>ip2;
                }
                
                stat1.AVARAGE_BANDWITH_SENDER_RECIVER(ip1,ip2);
                //error handling
                if(stat1.getAvarageBanwidth_SENDER_RECIVER() == 0.0){
                    PrintLineDesign();
                    std::cout<<"Nem talalhato a megadott forras-cel ip cim!"<<std::endl;
                    PrintLineDesign();
                }
                else{
                    PrintLineDesign();
                    std::cout<<"Az atlagos savszelesseg az adott forras-cel parra: "<<stat1.getAvarageBanwidth_SENDER_RECIVER()<<"Mbps"<<std::endl;
                    PrintLineDesign();
                    WriteLogToFile(option,stat1);
                }
                
            }
            if(option == 2){
                std::cout<<"Adjon meg egy prioritasi erteket(1-3): ";
                std::cin>>priority;
                std::cout<<std::endl;
                while (priority < 1 || priority > 3 || std::cin.fail())
                {
                    std::cout<<"Adjon meg egy helyes erteket!: ";
                    std::cin>>priority;
                    std::cout<<std::endl;
                }
                stat1.AVARAGE_ARIVAL_PRIORITY(priority);

                //error handling
                if(stat1.getAvarageArival_PRIORITY() == 0.0){
                    PrintLineDesign();
                    std::cout<<"Nem talalhato " <<priority<< " prioritasu IP csomag!"<<std::endl;
                    PrintLineDesign();
                }
                else{
                    PrintLineDesign();
                    std::cout<<"Az adott prioritasu csomagok atlagos erkezesi idokoze:"<<stat1.getAvarageArival_PRIORITY()<<" masodperc"<<std::endl;
                    WriteLogToFile(option,stat1);
                    PrintLineDesign();
                }
            
            }
                
            
            if(option == 3){
                stat1.BANDWITH_ALL();
                PrintLineDesign();
                std::cout<<"Az osszes adatbol adodo savszelesseg: "<<stat1.getBandwidth_ALL()<<"Mbps"<<std::endl;
                PrintLineDesign();
                
                WriteLogToFile(option,stat1);


            }
            if(option == 4){
                stat1.RATIO_PRIO_NON_PRIO();
                PrintLineDesign();
                std::cout<<"Az osszes adat "<<stat1.getRatio_PRIO_NON_PRIO()<<"% szazaleka a prioritasos csomagok adata"<<std::endl;
                PrintLineDesign();
                WriteLogToFile(option,stat1);

            }
            if(option == 5){

                // 1. fuggveny
                std::cout<<"Adjon meg egy kereseshez hasznalando forras-cel ip cim part"<<std::endl;
                std::cout<<"A forras ip cim: ";
                std::cin>>ip1;
                while(std::cin.fail()){
                    std::cout<<"Adjon meg egy helyes ip cimet!"<<std::endl;
                    std::cin>>ip1;
                }
                std::cout<<std::endl;
                std::cout<<"A cel ip cim: ";
                std::cin>>ip2;
                while (std::cin.fail())
                {
                    std::cout<<"Adjon meg egy helyes ip cimet!"<<std::endl;
                    std::cin>>ip2;
                }
                
                stat1.AVARAGE_BANDWITH_SENDER_RECIVER(ip1,ip2);

                
                
                
                // 2 fuggveny
                std::cout<<"Adjon meg egy prioritasi erteket(1-3): ";
                std::cin>>priority;
                std::cout<<std::endl;
                while (priority < 1 || priority > 3 || std::cin.fail())
                {
                    std::cout<<"Adjon meg egy helyes erteket!: ";
                    std::cin>>priority;
                    std::cout<<std::endl;
                }

                stat1.AVARAGE_ARIVAL_PRIORITY(priority);

              
                PrintLineDesign();
                //1 es 2 fugveny print 
                //error handling
                if(stat1.getAvarageBanwidth_SENDER_RECIVER() == 0.0){
                    std::cout<<"Nem talalhato a megadott forras-cel ip cim!"<<std::endl;
                }
                else{
                    std::cout<<"Az atlagos savszelesseg az adott forras-cel parra: "<<stat1.getAvarageBanwidth_SENDER_RECIVER()<<"Mbps"<<std::endl;
                    
                }
                //error handling
                if(stat1.getAvarageArival_PRIORITY() == 0.0){
                    std::cout<<"Nem talalhato " <<priority<< " prioritasu IP csomag!"<<std::endl;
                }
                else{
                    std::cout<<"Az adott prioritasu csomagok atlagos erkezesi idokoze:"<<stat1.getAvarageArival_PRIORITY()<<" masodperc"<<std::endl;
                   
                }


                // 3. fuggveny
                stat1.BANDWITH_ALL();
                std::cout<<"Az osszes adatbol adodo savszelesseg: "<<stat1.getBandwidth_ALL()<<"Mbps"<<std::endl;

            
                // 4. fuggveny
                stat1.RATIO_PRIO_NON_PRIO();
                std::cout<<"Az osszes adat "<<stat1.getRatio_PRIO_NON_PRIO()<<"% szazleka a prioritasos csomagok adata"<<std::endl;

                PrintLineDesign();


                WriteLogToFile(option,stat1);
            
            
            }
            if(option == 6){
                exit = 1;
            }
        }
        // memoria felszabaditas
    for(IP_PACKET* item : packets){
        delete item;
    }


}