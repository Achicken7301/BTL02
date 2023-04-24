#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType
{ /* TODO: */ };

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};

class BaseBag;
class BaseOpponent;

class Events
{
public:
    int count() const;
    int get(int i) const;
};

class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag *bag;
    KnightType knightType;

public:
    bool isPaladin();
    bool isLancelot();
    bool isDragon();
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class PaladinKnight : public BaseKnight
{
};

class LancelotKnight : public BaseKnight
{
};
class DragonKnight : public BaseKnight
{
};
class NormalKnight : public BaseKnight
{
};
class BaseItem
{
public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class BaseBag
{
public:
    virtual bool insertFirst(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
};

class ArmyKnights
{
private:
    int numberOfKnightsLeft;
    BaseKnight *knights;
    bool PaladinShield, LancelotSpear, guinevereHair, excaliburSword;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;

    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &filename);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__