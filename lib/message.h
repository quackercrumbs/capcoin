#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <breep/util/serialization.hpp>

struct Message {

    std::string type_;
    std::string data_;

};

breep::serializer& operator<<(breep::serializer& s, Message m) {

    s << m.type_;
    s << m.data_;
    return s;

}

breep::deserializer& operator>>(breep::deserializer& d, Message& m) {

    std::string type, data;
    d >> type;
    d >> data;
    m.type_ = type; 
    m.data_ = data;
    return d;

}

#endif
