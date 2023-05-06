#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define DEBUG 1

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};

enum ItemType
{
    PHOENIXDOWN_I_ITEM = 111,
    PHOENIXDOWN_II_ITEM,
    PHOENIXDOWN_III_ITEM,
    ANTIDOTE,

};

class BaseKnight;

class BaseOpponent
{
protected:
    string name;
    int baseDamage;
    int level;
    int gil;

public:
    void calcLevelO(int event_index, int event_id);
    string getName() const;
    int getLevel() const
    {
        return this->level;
    }

    int getGil() const
    {
        return this->gil;
    }

    int getBaseDamage() const
    {
        return this->baseDamage;
    }
};

class MadBear : public BaseOpponent
{
public:
    MadBear()
    {
        this->name = "MadBear";
        this->baseDamage = 10;
        this->gil = 100;
    }
};

enum eventType
{
    MADBEAR = 1,
    BANDIT,
    LORDLUPIN,
    ELF,
    TROLL,
    TORNBERY,
    QUEEN_OF_CARDS,
    NINA_DE_RINGS,
    VUON_SAU_RIENG,
    OMEGA_WEAPON,
    HADES,
    PHOENIXDOWN_II = 112,
    PHOENIXDOWN_III = 113,
    PHOENIXDOWN_IV = 114,
    PALADIN_SHIELD = 95,
    LENCELOT_SPEAR = 96,
    GUINEVERE_HAIR = 97,
    EXCALIBUR = 98,
    ULTIMECIA = 99
};

class Events
{
private:
    int *events;
    int num_event;

public:
    Events(const string &file_event);
    ~Events();
    int count() const;
    int get(int i) const;
    void extract_line_num(string line, int *array_address, int array_length, string delimeter);
};

class BaseItem
{
protected:
    ItemType item;
    BaseItem *next;

public:
    BaseItem(ItemType itemType) : item(itemType), next(nullptr){};
    // virtual bool canUse(BaseKnight *knight) = 0;
    // virtual void use(BaseKnight *knight) = 0;
    ItemType getItemType() const { return item; }
};

class PhoenixDown : public BaseItem
{
public:
    PhoenixDown(ItemType itemType) : BaseItem(itemType){};
};

class Antidote : public BaseItem
{
public:
    Antidote() : BaseItem(ANTIDOTE){};
};

class BaseBag
{
private:
    BaseItem *head;
    int count;

public:
    BaseBag();
    virtual bool insertFirst(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
    int getCount() const { return count; }
};

class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    double knightBaseDamage;
    BaseBag *bag;
    KnightType knightType;

public:
    bool isPaladin();
    bool isLancelot();
    bool isDragon();
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int getHP() const
    {
        return this->hp;
    }

    void decreaseHP(int HP);
    void increaseGil(int GIL);

    void setHP(int HP)
    {
        this->hp = HP;
    }

    int getLevel() const
    {
        return this->level;
    }
};

class PaladinKnight : public BaseKnight
{
private:
public:
    PaladinKnight()
    {
        this->knightType = PALADIN;
        this->knightBaseDamage = 0.06;
    }
};

class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight()
    {
        this->knightType = LANCELOT;
        this->knightBaseDamage = 0.05;
    }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight()
    {
        this->knightType = DRAGON;
        this->knightBaseDamage = 0.05;
    }
};
class NormalKnight : public BaseKnight
{
    NormalKnight()
    {
        this->knightType = NORMAL;
    }
};

class ArmyKnights
{
private:
    int numberOfKnightsLeft;

    // Array of knights
    BaseKnight *knights;
    bool paladinShield, lancelotSpear, guinevereHair, excaliburSword;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;

    BaseKnight *lastKnight() const;

    void setPaladinShield(bool value);
    void setLancelotSpear(bool value);
    void setGuinevereHair(bool value);
    void setExcaliburSword(bool value);

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
    bool win;
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &filename);
    void loadEvents(const string &file_event);
    void run();
};

#endif // __KNIGHT2_H__