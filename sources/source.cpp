// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include <SharedPtr.h>
int main(){
    SharedPtr a = SharedPtr(new int(5));
    auto b = a;
    *b = 7;
    std::cout << b.use_count() << std::endl;
}
