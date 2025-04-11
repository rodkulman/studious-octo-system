#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <windows.h>

// This constant indicates whether the city considers itself as a connection
const bool CITY_CONSIDERS_ITSELF = true;

// ensure an interger is read from the user
int readInt(std::string prompt)
{
    int retVal;
    bool success = false;

    do
    {
        std::cout << prompt;

        // gets user input
        std::string input;
        std::getline(std::cin, input);

        // attempts to convert
        std::stringstream ss(input);
        ss >> retVal;

        // check if the conversion was successful and if there are any extra characters in the input
        success = !ss.fail() && ss.eof();
    } while (!success);

    return retVal;
}

// ensure an integer is read from the user and is in a specific range
int readIntRange(std::string prompt, int minInclusive, int maxInclusive)
{
    int retVal;
    bool success = false;

    do
    {
        retVal = readInt(prompt);

        // check if the value is in range
        success = (retVal >= minInclusive && retVal <= maxInclusive);
    } while (!success);

    return retVal;
}

int readIntOptional(std::string prompt, int defaultValue)
{
    int retVal;
    bool success = false;

    do
    {
        std::cout << prompt;

        // gets user input
        std::string input;
        std::getline(std::cin, input);

        if (input.length() == 0)
        {
            return defaultValue;
        }

        // attempts to convert
        std::stringstream ss(input);
        ss >> retVal;

        // check if the conversion was successful and if there are any extra characters in the input
        success = !ss.fail() && ss.eof();
    } while (!success);

    return retVal;
}

void MakeCityConnections(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    int seed = readIntOptional("Digite a seed para gerar as conexões (ou vazio para aleatório): ", 0);

    if (seed == 0)
    {
        std::random_device rd;
        seed = rd();

        std::cout << "Seed gerada: " << seed << std::endl;
    }

    std::mt19937 rnd(seed);

    for (int i = 0; i < cityAmount; i++)
    {
        for (int j = 0; j < cityAmount; j++)
        {
            cityConnections[i][j] = i == j ? true : rnd() % 2 == 0;
        }
    }
}

void PrintCityConnections(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    for (int i = 0; i < cityAmount; i++)
    {
        std::cout << "[";

        for (int j = 0; j < cityAmount; j++)
        {
            std::cout << cityConnections[i][j];
            if (j < cityAmount - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }
}

void CountCityInOut(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    int city = readIntRange("Digite o número da cidade (1 - " + std::to_string(cityAmount) + "): ", 1, cityAmount) - 1;

    int countOut = 0;
    for (int j = 0; j < cityAmount; j++)
    {
        if (!CITY_CONSIDERS_ITSELF && j == city)
            continue;

        if (cityConnections[city][j])
        {
            countOut++;
        }
    }

    int countIn = 0;
    for (int i = 0; i < cityAmount; i++)
    {
        if (!CITY_CONSIDERS_ITSELF && i == city)
            continue;

        if (cityConnections[i][city])
        {
            countIn++;
        }
    }

    std::cout << "Cidade " << city + 1 << " tem " << countOut << " conexões de saída e " << countIn << " conexões de entrada." << std::endl;
}

void GetMaxConnectionCity(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    std::vector<int> cityConnectionCount(cityAmount, 0);
    int cityMax = 0;

    for (int i = 0; i < cityAmount; i++)
    {
        for (int j = 0; j < cityAmount; j++)
        {
            if (!CITY_CONSIDERS_ITSELF && i == j)
                continue;

            if (cityConnections[i][j])
            {
                cityConnectionCount[i]++;
            }
        }

        // check if the current city has more connections than the current max
        // first time, i == cityMax, so it will always be false
        if (cityConnectionCount[i] > cityConnectionCount[cityMax])
        {
            cityMax = i;
        }
    }

    std::cout << "Cidade " << cityMax + 1 << " tem a maior quantidade de conexões (" << cityConnectionCount[cityMax] << ")" << std::endl;
}

void CheckIfAllConnectionsBothWays(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    int city = readIntRange("Digite o número da cidade (1 - " + std::to_string(cityAmount) + "): ", 1, cityAmount) - 1;
    bool success = true;

    for (int i = 0; i < cityAmount; i++)
    {
        // in this case, the city is not considered a connection to itself
        // so we ignore the constant CITY_CONSIDERS_ITSELF
        if (i == city)
            continue;

        if (!cityConnections[city][i] || !cityConnections[i][city])
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        std::cout << "Cidade " << city + 1 << " tem conexões em ambas as direções com todas as outras cidades." << std::endl;
    }
    else
    {
        std::cout << "Cidade " << city + 1 << " não tem conexões em ambas as direções com todas as outras cidades." << std::endl;
    }
}

void GetAllArriveToCity(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    int city = readIntRange("Digite o número da cidade (1 - " + std::to_string(cityAmount) + "): ", 1, cityAmount) - 1;

    std::cout << "Cidades que tem saída para a cidade " << city + 1 << ": ";

    bool foundFirst = false;
    for (int i = 0; i < cityAmount; i++)
    {
        if (!CITY_CONSIDERS_ITSELF && i == city)
            continue;

        if (cityConnections[i][city])
        {
            if (foundFirst)
            {
                std::cout << ", ";
            }
            else
            {
                foundFirst = true;
            }
            std::cout << i + 1;
        }
    }

    if (!foundFirst)
    {
        std::cout << "nenhuma";
    }

    std::cout << std::endl;
}

void CheckForLockedCities(int cityAmount, std::vector<std::vector<bool>> &cityConnections)
{
    std::vector<int> lockedCities(0);
    std::vector<int> onlyInCities(0);
    std::vector<int> onlyOutCities(0);

    for (int city = 0; city < cityAmount; city++)
    {
        // first, check if the city has any entries
        bool hasEntry = false;
        for (int i = 0; i < cityAmount; i++)
        {
            if (i == city)
                continue;

            if (cityConnections[i][city])
            {
                hasEntry = true;
                break;
            }
        }

        // secondly, check if the city has any exits
        bool hasExit = false;
        for (int j = 0; j < cityAmount; j++)
        {
            if (city == j)
                continue;

            if (cityConnections[city][j])
            {
                hasExit = true;
                break;
            }
        }

        // if the city has no entries and no exits, it is a locked city
        if (!hasEntry && !hasExit)
        {
            lockedCities.push_back(city + 1);
        }
        // if the city has no entries and has exits, it is an only out city
        else if (!hasEntry && hasExit)
        {
            onlyOutCities.push_back(city + 1);
        }
        // finally, if the city has entries and no exits, it is an only in city
        else if (hasEntry && !hasExit)
        {
            onlyInCities.push_back(city + 1);
        }
    }

    std::cout << "Cidades que não tem conexões com nenhuma outra cidade: ";
    if (lockedCities.size() == 0)
    {
        std::cout << "nenhuma";
    }
    else
    {
        for (int i = 0; i < lockedCities.size(); i++)
        {
            std::cout << lockedCities[i];
            if (i < lockedCities.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Cidades que só tem conexões de entrada: ";
    if (onlyInCities.size() == 0)
    {
        std::cout << "nenhuma";
    }
    else
    {
        for (int i = 0; i < onlyInCities.size(); i++)
        {
            std::cout << onlyInCities[i];
            if (i < onlyInCities.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Cidades que só tem conexões de saída: ";
    if (onlyOutCities.size() == 0)
    {
        std::cout << "nenhuma";
    }
    else
    {
        for (int i = 0; i < onlyOutCities.size(); i++)
        {
            std::cout << onlyOutCities[i];
            if (i < onlyOutCities.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

int main()
{
    // ensure input and output are treated as UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    int cityAmount = readIntRange("Digite o número de cidades (1 - 10): ", 1, 10);

    std::vector<std::vector<bool>> cityConnections(cityAmount, std::vector<bool>(cityAmount, false));

    MakeCityConnections(cityAmount, cityConnections);
    PrintCityConnections(cityAmount, cityConnections);

    bool running = true;
    while (running)
    {
        std::string input;

        std::cout << "Escolha um comando: ";
        std::getline(std::cin, input);

        if (input == "exit")
        {
            running = false;
        }
        else if (input == "print")
        {
            PrintCityConnections(cityAmount, cityConnections);
        }
        else if (input == "make")
        {
            MakeCityConnections(cityAmount, cityConnections);
            PrintCityConnections(cityAmount, cityConnections);
        }
        else if (input == "count")
        {
            CountCityInOut(cityAmount, cityConnections);
        }
        else if (input == "max")
        {
            GetMaxConnectionCity(cityAmount, cityConnections);
        }
        else if (input == "both")
        {
            CheckIfAllConnectionsBothWays(cityAmount, cityConnections);
        }
        else if (input == "arrive")
        {
            GetAllArriveToCity(cityAmount, cityConnections);
        }
        else if (input == "lock")
        {
            CheckForLockedCities(cityAmount, cityConnections);
        }
        else
        {
            std::cout << "Comandos disponíveis: " << std::endl;

            std::cout << "\tprint: mostra a matrix de cidades" << std::endl;
            std::cout << "\tmake: gera novas conexões entre as cidades" << std::endl;
            std::cout << "\tcount: conta as conexões de entrada e saída de uma cidade" << std::endl;
            std::cout << "\tmax: mostra a cidade com mais conexões" << std::endl;
            std::cout << "\tboth: verifica se uma cidade tem conexões em ambas as direções com todas as outras cidades" << std::endl;
            std::cout << "\tarrive: mostra as cidades que tem saída para uma cidade" << std::endl;
            std::cout << "\tlock: mostra as cidades que não tem conexões com nenhuma outra cidade" << std::endl;
            std::cout << "\texit: termina o aplicativo" << std::endl;
        }
    }

    return 0;
}