#ifndef SHAKHOV_LR5_PARENTSNIPER_H
#define SHAKHOV_LR5_PARENTSNIPER_H

#include "Shakhov_LR5_AbstractPlayer.h"
#include "Shakhov_LR5_ChildSniper.h"
#include "Shakhov_LR5_ChildSupport.h"




class TacticalAI {
protected:
    vector<string> strategies;

    istream& input(istream& in);
    ostream& output(ostream& out) const;

public:
    TacticalAI() = default;
    virtual ~TacticalAI() = default;

    // Геттеры
    const vector<string>& getStrategies() const { return strategies; }

    // Сеттеры
    void setStrategies(const vector<string>& strats) { strategies = strats; }

    string& operator[](int index);
    const string& operator[](int index) const;
};

#endif
