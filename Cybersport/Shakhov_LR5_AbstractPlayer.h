#ifndef SHAKHOV_LR5_ABSTRACTPLAYER_H
#define SHAKHOV_LR5_ABSTRACTPLAYER_H

#include "Shakhov_LR5_defPlayer.h"
//����������� input output � ��������
//������� �� ������
//�������� ����� � input
//������������ ����
//��������������� ���
//��������� � map ������ �������� �������
//������������ ����
//������������ ������������ � �����

class Player {
private:
    int playerId;
    string nickname;
    int rating;

protected:
    virtual istream& input(istream& in) = 0;  
    virtual ostream& output(ostream& out) const = 0;

public:
    Player();
    Player(int id, const string& nick, int rat);
    explicit Player(int pid);
    virtual ~Player() = default;

    // �������
    int getPlayerId() const { return playerId; }
    string getNickname() const { return nickname; }
    int getRating() const { return rating; }

    // �������
    void setPlayerId(int id) { playerId = id; }   
    void setNickname(const string& nick) { nickname = nick; }
    void setRating(int rat) { rating = rat; }

    // ����� ����������� ������
    virtual void playRole() = 0;
    virtual int calculateImpact() = 0;

    // ���������
    virtual void validate();

    // ���������� ����������
    friend bool operator==(const Player& p1, const Player& p2);
    friend istream& operator>>(istream& in, Player& obj);
    friend ostream& operator<<(ostream& out, const Player& obj);
};

#endif