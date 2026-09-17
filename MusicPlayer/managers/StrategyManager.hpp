#pragma once
#include "../strategies/CustomPlayingStrategy.hpp"
#include "../strategies/RandomStrategy.hpp"
#include "../strategies/SequentialStrategy.hpp"
#include "../strategies/IPlayingStrategy.hpp"
#include <iostream>
#include "../enums/PlayStrategyType.hpp"

class StrategyManager
{
    SequentialStrategy *sq;
    CustomPlayingStrategy *cs;
    RandomPlayingStrategy *rn;
    StrategyManager()
    {
        sq = new SequentialStrategy();
        cs = new CustomPlayingStrategy();
        rn = new RandomPlayingStrategy();
    }
    static StrategyManager *instance;

public:
    static StrategyManager *getInstance()
    {
        if (!instance)
        {
            instance = new StrategyManager();
        }
        return instance;
    }

    IPlayingStrategy *getStrategy(PlayStrategyType type)
    {
        switch (type)
        {
        case PlayStrategyType::CUSTOM:
        {
            std::cout << "Switched to Custom Play Strategy\n";
            return cs;
            break;
        }
        case PlayStrategyType::RANDOM:
        {
            std::cout << "Switched to Random Play Strategy\n";
            return rn;
            break;
        }
        case PlayStrategyType::SEQUENTIAL:
        {
            std::cout << "Switched to Sequential Play Strategy\n";
            return sq;
            break;
        }
        default:
            throw std::runtime_error("Invalid Strategy");
            return nullptr;
            break;
        }
    }
    ~StrategyManager()
    {
        delete sq;
        delete cs;
        delete rn;
    }
};

StrategyManager *StrategyManager::instance = nullptr;