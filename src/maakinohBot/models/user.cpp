#include <maakinohBot/models/user.hpp>

#include <nlohmann/json.hpp>

void MaakinohBot::Models::User::parse(std::string jsonString)
{
    ParseableObject::parse(jsonString);
    auto j = nlohmann::json::parse(jsonString);

    this->id = j["id"].get<int>();
    this->is_bot


}
