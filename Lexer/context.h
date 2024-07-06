#ifndef CONTEXT_H
#define CONTEXT_H
#include<string>
#include <map>
#include "symbol.h"

class Context{
private:
    std::map<std::string, Symbol> table;
protected:
    Context* prev;    
public:
    Context(Context* ctx):prev(ctx){}
    void put(const std::string& key, const Symbol& value);
    Symbol* get(std::string_view key);
};
#endif //CONTEXT_H