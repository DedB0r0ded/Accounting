//usЕr.h
#pragma once


#include <common/common.h>


namespace accounting {


  class User {
  private:
    string email_;
    string name_;
    string pwd_;
    id_t id_;

  public:


    User() : id_{}, email_{}, name_{}, pwd_{} {}

    User(id_t id, string email, string name, string pwd)
        : id_{id}, email_{email}, name_{name}, pwd_{pwd} {}


  
    bool operator==(const User& other) const {
      return email_ == other.email_ && name_ == other.name_ &&
             pwd_ == other.pwd_ && id_ == other.id_;
    }

    bool operator!=(const User& other) const {
      return !((*this) == other);
    }
  };


}
