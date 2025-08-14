#ifndef CONTEXT_H
#define CONTEXT_H
#include<string>
#include <unordered_map>
#include "symbol.h"

namespace tinycompiler{
    class Context{
private:
    std::unordered_map<std::string, Symbol> table;
protected:
    Context* prev;    
public:
    Context(Context* ctx):prev(ctx){}
    void put(const std::string& key, const Symbol& value);
    Symbol* get(std::string_view key);
};
}
#endif //CONTEXT_H