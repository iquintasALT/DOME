#include "DomeEvents.h"

#include <nlohmann/json.hpp>

std::string WoundStart::serializeToJSON() const
{
    nlohmann::json data = {
            {"Evento", std::to_string(gameEvent)},
            {"Tiempo", time},
            {"Herida", wound}
    };

    std::string information = data.dump();

    return information;
}

Events* WoundStart::clone() const
{
    return new WoundStart(time, wound);
}


std::string WoundEnd::serializeToJSON() const
{
    nlohmann::json data = {
            {"Evento", std::to_string(gameEvent)},
            {"Tiempo", time},
            {"Herida", wound}
    };

    std::string information = data.dump();

    return information;
}

Events* WoundEnd::clone() const
{
    return new WoundEnd(time, wound);
}


std::string Shoot::serializeToJSON() const
{
    return Events::serializeToJSON();
}

Events* Shoot::clone() const
{
    return new Shoot(time);
}
