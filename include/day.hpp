#ifndef AOC2024_DAY_HPP
#define AOC2024_DAY_HPP

#include <filesystem>
#include <functional>
#include <map>
#include <memory>

class Day
{
public:
    virtual ~Day() = default;
    virtual std::pair<std::string, std::string> run(const std::filesystem::path& input_path) = 0;
    virtual unsigned int get_day_number() const = 0;
    virtual std::string get_day_name() const = 0;
};

class DayFactory
{
public:
    using Creator = std::function<std::unique_ptr<Day>()>;

    // Singleton instance
    static DayFactory& instance()
    {
        static DayFactory factory;
        return factory;
    }

    void register_day(unsigned int day_number, Creator creator) { creators[day_number] = creator; }

    std::unique_ptr<Day> create_day(unsigned int day_number)
    {
        auto it = creators.find(day_number);
        if (it != creators.end())
        {
            return it->second();
        }
        return nullptr;
    }

    std::map<unsigned int, Creator> get_all_days() const { return creators; }

private:
    std::map<unsigned int, Creator> creators;
};

template <typename T, unsigned int DayNumber>
class DayRegistrar
{
public:
    DayRegistrar()
    {
        DayFactory::instance().register_day(DayNumber, []() { return std::make_unique<T>(); });
    }
};

#define REGISTER_DAY(ClassName, DayNumber) static DayRegistrar<ClassName, DayNumber> ClassName##_registrar;

#endif  // AOC2024_DAY_HPP