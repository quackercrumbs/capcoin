#include "message.h"

Message::Message(std::string type, std::string data) {

    type_ = type;
    data_ = data;

}

std::string Message::GetType() {

    return type_;

}

std::string Message::GetData() {

    return data_;

}
