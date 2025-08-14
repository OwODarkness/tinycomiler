#include "context.h"


namespace tinycompiler
{
    void Context::put(const std::string &key, const Symbol &value)
    {
        table.insert({key, value});
    }
    Symbol *Context::get(std::string_view key)
    {
        for (Context *ptr = this; ptr != nullptr; ptr = this->prev)
        {
            if (table.contains(key.data()))
            {
                return new Symbol(table.at(key.data()));
            }
        }
        return nullptr;
    }
}