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

    data.push_back({ "Treatment", treatment });
    int i = 1;
    for (auto it = wounds.begin(); it != wounds.end(); ++it) {
        data.push_back({ "Wound" + i, *it });
        i++;
    }

    return data;
}

nlohmann::json ReturnHome::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({ "RaidTime", raidTime });
    int i = 1;
    for (auto it = wounds.begin(); it != wounds.end(); ++it) {
        data.push_back({ "Wound" + i, *it });
        i++;
    }

    return data;
}

nlohmann::json CursorOnInfo::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({ "Wound", wound });

    return data;
}

nlohmann::json CursorOffInfo::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({ "Wound", wound });

    return data;
}
