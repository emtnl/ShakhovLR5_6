#ifndef SHAKHOV_LR5_MULTI_TACTICALAI_H
#define SHAKHOV_LR5_MULTI_TACTICALAI_H

#include "Shakhov_LR5_ParentSniper.h"
class Strategist : public Player, public TacticalAI {
private:
    int successRate;
    int mapKnowledge;

protected:
    istream& input(istream& in) override;
    ostream& output(ostream& out) const override;

public:
    Strategist();
    Strategist(int id, const string& nick, int rat, int rate, int ledge);
    Strategist(const Strategist& other);
    explicit Strategist(const string& nick); // Конструктор преобразования
    ~Strategist() override = default;

    void playRole() override;
    int calculateImpact() override;

    // Геттеры
    int getSuccessRate() const { return successRate; }
    int getMapKnowledge() const { return mapKnowledge; }

    // Сеттеры
    void setSuccessRate(int rate) { successRate = rate; }
    void setMapKnowledge(int ledge) { mapKnowledge = ledge; }

    void predictEnemyMove();
    void validate() override;
    string& operator[](int index) { return TacticalAI::operator[](index); }
    const string& operator[](int index) const { return TacticalAI::operator[](index); }
};

#endif
