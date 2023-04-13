#include "DomeEvents.h"

nlohmann::json WoundStart::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({ "Wound", wound });

    return data;
}

nlohmann::json WoundEnd::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({"Wound", wound});

    return data;
}

nlohmann::json Heal::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({
            {"Treatment", treatment}
    });

    return data;
}

nlohmann::json ReturnHome::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({
            {"RaidTime", raidTime}
    });

    return data;
}
