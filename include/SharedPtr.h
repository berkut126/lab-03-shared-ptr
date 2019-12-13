// Copyright 2019 Andrey Ivanov <berkut126@gmail.com>
// Created by rooted on 13.12.2019.
//
#pragma once
#include <header.hpp>

template <typename T>
class SharedPtr {
public:
    SharedPtr(){
        ptr = nullptr;
        counter = new std::atomic_uint(0);
    }
    explicit SharedPtr(T* pr){
        this->ptr = pr;
        counter = new std::atomic_uint(1);
    }
    SharedPtr(const SharedPtr& r){
        ptr = r.ptr;
        counter = r.counter;
        ++(*counter);
    }
    SharedPtr(SharedPtr&& r) noexcept {
        ptr = std::move(r.ptr);
        counter = std::move(counter);
    }
    ~SharedPtr(){
        if(*counter == 1){
            delete ptr;
            delete counter;
        }
        else{
            --counter;
            ptr = nullptr;
            delete counter;
        }
    }
    auto operator= (const SharedPtr& r) -> SharedPtr&{
        r.swap(*this);
        return *this;
    }
    auto operator= (SharedPtr&& r) noexcept -> SharedPtr& {
        std::move(r).swap(*this);
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const{
        return ptr != nullptr;
    }
    auto operator*() const -> T&{
        return *ptr;
    }
    auto operator->() const -> T*{
        return ptr;
    }

    auto get() -> T*{
        if(ptr == nullptr){
            return 0;
        }
        else{
            std::cout << *ptr << std::endl;
            return ptr;
        }
    }
    void reset(){
        delete ptr;
        ptr = nullptr;
        counter = 0;
    }
    void reset(T* pr){
        if(counter != 0) counter = 0;
        this->ptr = pr;
        counter = std::atomic_uint(1);
    }
    void swap(SharedPtr& r){
        std::swap(ptr, r.ptr);
        std::swap(counter, r.counter);
    }
    [[nodiscard]] auto use_count() const -> size_t{
        if(ptr != nullptr){
            return *counter;
        }
        else{
            return 0;
        }
    }

private:
    T *ptr;
    std::atomic_uint *counter;
};
