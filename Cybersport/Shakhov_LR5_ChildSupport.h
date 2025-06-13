#ifndef SHAKHOV_LR5_CHILDSUPPORT_H
#define SHAKHOV_LR5_CHILDSUPPORT_H

#include "Shakhov_LR5_AbstractPlayer.h"
#include "Shakhov_LR5_ChildSniper.h"

class Support : public Player {
private:
    int healsPerMatch;
    int utilityUsage;

protected:
    istream& input(istream& in) override;
    ostream& output(ostream& out) const override;
    

public:
    Support();
    Support(int id, const string& nick, int rat, int hpm, int util);
    Support(const Support& other);
    explicit Support(const string& nick); // Конструктор преобразования
    ~Support() override = default;

    void playRole() override;
    int calculateImpact() override;

    // Геттеры
    int getHealsPerMatch() const { return healsPerMatch; }
    int getUtility10() const { return utilityUsage; }
    void setHealsPerMatch(int hpm) { healsPerMatch = hpm; }
    void setUtilityUsage(int util) { utilityUsage = util; }

    void deployShield();
    void validate() override;
    unique_ptr<Support> operator+(const Support& other) const;
};
#endif