#ifndef __TYPES_H_
#define __TYPES_H_

#include<memory>
#include<string>
#include<vector>
#include<map>

class tItem: public std::enable_shared_from_this<tItem>
{
public:
    virtual ~tItem() = default;

    template<typename T>
    std::shared_ptr<T> as() {
        static_assert(std::is_base_of<tItem, T>::value,"Not valid ype");
        return std::dynamic_pointer_cast<T>(shared_from_this());
    }

protected:
    tItem() = default;
private:
    tItem(const tItem&) = delete;
    tItem &operator=(const tItem& r) = delete;
};

class tInt: public tItem
{
public:
    tInt (int value): value(value) {};

    int value;
};

class tString: public tItem
{
public:
    tString (std::string &str): str(str) {}

    std::string str;
};

class tList: public tItem
{
public:
    tList() = default;

    std::vector<std::string> data;
};

class tDict: public tItem
{
public:
    tDict() = default;

    std::map<std::string, std::string> data;
};
#endif // __TYPES_H_
