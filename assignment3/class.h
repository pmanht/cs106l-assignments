#include <string>
#include <cstdint>

class NetworkPacket {   
private:
    std::string src;
    std::string dst;
    std::string payload;
    bool        CheckConnection();
    bool        SendToDst();
public:
    //list initilization constructor
    NetworkPacket(std::string, std::string, std::string);
    //default constructor
    NetworkPacket();
    //destructor
    ~NetworkPacket();
    //print packet elements
    bool Execute();
    void PrintInfo() const;

    std::string getSrc() const;
    std::string getDst() const;
    std::string getPayload() const;

    void setSrc(std::string);
    void setDst(std::string );
    void setPayload(std::string);
};