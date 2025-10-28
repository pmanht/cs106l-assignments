#include "class.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <iomanip>

//list initilization constructor
static std::vector<std::string> ConnectedDst = {"192.168.30.22",
                                                "172.16.52.2",
                                                "192.168.40.127"};

NetworkPacket::NetworkPacket(std::string src, std::string dst, std::string payload):
src(src), dst(dst), payload(payload) {}

//default constructor
NetworkPacket::NetworkPacket():
src(""), dst(""), payload("") {}

NetworkPacket::~NetworkPacket() {}

bool NetworkPacket::CheckConnection() {
    std::string ip;
    bool ret = false;

    if (dst == "") return false;
    for (auto it = ConnectedDst.begin(); it != ConnectedDst.end(); ++it) {
        ip = *it;
        if (dst.compare(ip) == 0) {
            ret = true;
            break;
        }
    }
    return ret;
}

bool NetworkPacket::SendToDst() {
    std::cout << "Sending packet from " << src <<
        " to " << dst << std::endl;
    return true;
}

void NetworkPacket::PrintInfo() const {
    std::cout << "Source IP: " << src <<  std::endl;
    std::cout << "Destination IP: " << dst <<  std::endl;
    std::cout << "Payload: " << payload << std::endl;
}

bool NetworkPacket::Execute() {
    return CheckConnection() && SendToDst();
}

std::string NetworkPacket::getSrc() const {
    return this->src;
}

std::string NetworkPacket::getDst() const {
    return this->dst;
}

std::string NetworkPacket::getPayload() const {
    return this->payload;
}

void NetworkPacket::setSrc(std::string newSrc) {
    this->src = newSrc;
}

void NetworkPacket::setDst(std::string newDst) {
    this->dst = newDst;
}

void NetworkPacket::setPayload(std::string payload) {
    this->payload = payload;
}