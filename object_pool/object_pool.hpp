#pragma once
#include <memory>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include "exceptions.hpp"
template<class Object>
class Object_Pool final{
public:
    Object_Pool(Object_Pool&&) noexcept = default;
    Object_Pool& operator=(Object_Pool&&) noexcept = default;
    Object_Pool(Object_Pool const&) = delete;
    Object_Pool& operator=(Object_Pool const&) = delete;

    explicit Object_Pool(size_t pool_size) :
        data(new size_t[pool_size*sizeof(Object)]), free_object_marks(pool_size, true), capacity(pool_size){//data uniq ptr какие проблемы решает этот умный указ
        for (size_t i = 0; i < pool_size; ++i)
            free_objects.push_back(get_object_ptr(i)); //! кусок памяти непрерывный а я создаю еще один хотя можно ф-ию доступа  по индексу
    }

    template <typename ... Args>
    Object& allocate(Args&& ...args){
        if (free_objects.empty())
            throw Exceptions("Memory can't be allocated for a new object in the pool");
        Object* object_ptr = free_objects[free_objects.size() - 1];
        new(object_ptr) Object{ std::forward<Args>(args)... };
        free_object_marks[object_ptr - get_object_ptr(0)] = false;
        free_objects.pop_back();
        return *object_ptr;
    }

    void free(Object& object){
        Object* object_ptr = &object;
        if (object_ptr < get_object_ptr(0) || object_ptr > get_object_ptr(capacity - 1))
            throw Exceptions("You can't free objects from this pool.");
        if constexpr (std::is_class_v<Object> && !std::is_pod_v<Object>)
            object.~Object();
        free_object_marks[object_ptr - get_object_ptr(0)] = true;
        free_objects.push_back(object_ptr);
    }

    ~Object_Pool(){
        if constexpr (std::is_class_v<Object> && !std::is_pod_v<Object>)
            for (size_t i = 0; i < capacity; ++i)
                if (!free_object_marks[i])
                    get_object_ptr(i)->~Object();
        delete data;
    }
private:
    Object* get_object_ptr(size_t position) noexcept{
        return static_cast<Object*>(data.get() + position * sizeof(Object));
    }
    std::unique_ptr<size_t[]> data;
    std::vector<Object*> free_objects;
    std::vector<bool> free_object_marks;
    size_t capacity;
};