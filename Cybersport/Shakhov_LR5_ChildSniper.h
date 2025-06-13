#ifndef SHAKHOV_LR5_CHILDSNIPER_H
#define SHAKHOV_LR5_CHILDSNIPER_H

#include "Shakhov_LR5_AbstractPlayer.h"

class Sniper : public Player {
private:
    int headshotAccuracy;
    int longRangeKills;

protected:
    istream& input(istream& in) override;
    ostream& output(ostream& out) const override;

public:
    Sniper();
    Sniper(int id, const string& nick, int rat, int hsa, int lrk);
    Sniper(const Sniper& other);
    explicit Sniper(const string& nick); // Конструктор преобразования
    ~Sniper() override = default;

    void playRole() override;
    int calculateImpact() override;

    // Геттеры
    int getHeadshotAccuracy() const { return headshotAccuracy; }
    int getLongRangeKills() const { return longRangeKills; }

    // Сеттеры
    void setHeadshotAccuracy(int hsa) { headshotAccuracy = hsa; }
    void setLongRangeKills(int lrk) { longRangeKills = lrk; }

    void upgradeScope();
    void validate() override;
    unique_ptr<Sniper> operator+(const Sniper& other) const;
};

#endif