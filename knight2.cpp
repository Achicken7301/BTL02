#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem *item)
{
    // TODO:
}

BaseItem *BaseBag::get(ItemType type)
{
    // TODO:
}

string BaseBag::toString() const
{
    // TODO:
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    // s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(this->gil) + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    // LOAD FILE
    string text;
    fstream loadKnightsFile(file_armyknights);

    // Get number of knights
    getline(loadKnightsFile, text);
    this->numberOfKnightsLeft = stoi(text);

    // Create a dynamic array of BaseKnights
    knights = new BaseKnight[this->numberOfKnightsLeft];

    // HP level phoenixdownI gil antidote
    // maxhp, level, gil, antidote, phoenixdownI
    int arr[4];
    int knightID = 0;

    while (getline(loadKnightsFile, text))
    {
        std::stringstream ss(text); // create a stringstream from the string
        std::string token;
        int i = 0;

        while (getline(ss, token, ' '))
        {
            arr[i] = std::stoi(token); // convert each token to an integer and store it in the array
            i++;
        }

        knights[knightID] = *BaseKnight::create(knightID + 1, arr[0], arr[1], arr[3], arr[4], arr[2]);
        knightID++;
    }

    loadKnightsFile.close();
}

bool BaseKnight::isPaladin()
{
    if (this->hp <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= this->hp; i++)
    {
        if (this->hp % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool BaseKnight::isLancelot()
{
    return (this->hp == 888) ? true : false;
}

bool BaseKnight::isDragon()
{
    // TODO:Pythagoras: abc, acb, bac, bca, cba, cab
    if (this->hp == 345 || this->hp == 354 || this->hp == 435 || this->hp == 453 || this->hp == 534 || this->hp == 543)
    {
        return true;
    }
    return false;
}

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight *temp_knight = new BaseKnight;
    temp_knight->id = id;
    temp_knight->hp = maxhp;
    temp_knight->maxhp = maxhp;

    // HP condition => knight type
    if (temp_knight->isPaladin())
    {
        temp_knight->knightType = PALADIN;
    }
    else if (temp_knight->isLancelot())
    {
        temp_knight->knightType = LANCELOT;
    }
    else if (temp_knight->isDragon())
    {
        temp_knight->knightType = DRAGON;
    }
    else
    {
        temp_knight->knightType = NORMAL;
    }

    temp_knight->level = level;
    temp_knight->gil = gil;
    temp_knight->antidote = antidote;

    return temp_knight;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    return &knights[numberOfKnightsLeft - 1];
}

// Decontructor
ArmyKnights::~ArmyKnights()
{
    printf("This is deconstructor\n");
    delete this->knights;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    // TODO:
    cout << "Army Knights Fight" << endl;
}

bool ArmyKnights::adventure(Events *events)
{
    // TODO:
    cout << "Army Knights adventure" << endl;
}

int ArmyKnights::count() const
{
    return this->numberOfKnightsLeft;
}

bool ArmyKnights::hasPaladinShield() const
{
    // TODO:
    return this->PaladinShield;
}

bool ArmyKnights::hasLancelotSpear() const
{
    // TODO:
    return this->LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const
{
    // TODO:
    return this->guinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const
{
    // TODO:
    return this->excaliburSword;
}

void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() // Contructor
{
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure() // Decontructor
{
    delete this->armyKnights;
    delete this->events;
}

void KnightAdventure::loadArmyKnights(const string &filename)
{
    cout << "Loading " << filename << endl;
    armyKnights = new ArmyKnights(filename);
    armyKnights->printInfo();
}

void KnightAdventure::loadEvents(const string &)
{
    // TODO:
}

void KnightAdventure::run()
{
    // TODO:
}

/* * * END implementation of class KnightAdventure * * */