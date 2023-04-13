#include "DomeEvents.h"

#include <nlohmann/json.hpp>

std::string WoundStart::serializeToJSON() const
{
    std::string intro = Events::serializeToJSON();

    nlohmann::json data = {
            {"Herida", wound}
    };

    std::string information = intro + data.dump();

    return information;
}

std::string WoundEnd::serializeToJSON() const
{
    std::string intro = Events::serializeToJSON();

    nlohmann::json data = {
            {"Herida", wound}
    };

    std::string information = intro + data.dump();

    return information;
}

//std::string Heal::serializeToJSON() const
//{
//    std::string intro = Events::serializeToJSON();
//
//    nlohmann::json data = {
//            {"Tratamiento", treatment},
//    };
//
//    std::string information = intro + data.dump();
//
//    return information;
//}

std::string ReturnHome::serializeToJSON() const
{
    std::string intro = Events::serializeToJSON();

    nlohmann::json data = {
            {"TiempoRaid", raidTime},
    };

    std::string information = intro + data.dump();

    return information;
}
