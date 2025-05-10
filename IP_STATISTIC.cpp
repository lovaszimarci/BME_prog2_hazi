#include "IP_STATISTIC.h"

IP_STATISTIC::IP_STATISTIC(std::vector<IP_PACKET *> data): DATA(data)
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
