#ifndef TINYCOMPILER_JSON_H
#define TINYCOMPILER_JSON_H

#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

namespace tinycompiler{
    struct Json;
    
    using JsonObject = std::unordered_map<std::string, Json>;
    using JsonArray = std::vector<Json>;

    struct Json: std::variant<
        std::nullptr_t,
        bool,
        float,
        std::string,
        std::vector<std::string>,
        JsonObject,
        JsonArray
    >{
        using variant::variant;
    
    };
}

#endif