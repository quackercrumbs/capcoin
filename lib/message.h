#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

/*
 *
 *  TODO: For message types, use enum
 *
 *  @brief: This class is used to encapsulate messages sent over to the CapCoin network
 *  
 *
 */ 

class Message {

public:
    
    /**
     *
     * Creates a message wrapper with the request type and request data
     *
     */
    Message(std::string type, std::string data); 

    /**
     *
     * Returns message type
     *
     */
    std::string GetType();

    /**
     *
     * Returns the serialized data
     *
     */
    std::string GetData();

private:
    /*
     *
     * string:type, the type of request this is to the network
     * string:data, the serialize data set to the network
     *
     */ 
    std::string type_;
    std::string data_;

};


#endif
