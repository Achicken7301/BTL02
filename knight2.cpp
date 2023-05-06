#include "knight2.h"

/* * * BEGIN implementation of class BaseOpponent * * */

string BaseOpponent::getName() const
{
    return this->name;
}

void BaseOpponent::calcLevelO(int event_index, int event_id)
{
    this->level = ((event_index + event_id) % 10) + 1;
}

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag()
{
    head = nullptr;
    count = 0;
}

// bool BaseBag::insertFirst(BaseItem *item)
bool BaseBag::insertFirst(BaseItem *item)
{
    // TODO:
    if (this->head == nullptr)
    {
        head = item;
    }
    this->count++;

    return true;
}

BaseItem *BaseBag::get(ItemType type)
{
    BaseItem *item;
    return item;
}

string BaseBag::toString() const
{
    string s = "";
    s += "Bag[count=";
    s += to_string(this->getCount());
    s += ";]";
    return s;
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
void BaseKnight::decreaseHP(int HP)
{
    this->hp -= HP;
}

void BaseKnight::increaseGil(int GIL)
{
    this->gil += GIL;
    if (this->gil > 999)
        this->gil = 999;
}

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    // s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(this->gil) + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    // LOAD FILE
    ifstream loadKnightsFile(file_armyknights);
    loadKnightsFile >> this->numberOfKnightsLeft;

    // Create a dynamic array of BaseKnights
    knights = new BaseKnight[this->numberOfKnightsLeft];

    // HP level phoenixdownI gil antidote
    // maxhp, level, gil, antidote, phoenixdownI
    int arr[4];

    for (int knightID = 0; knightID < this->numberOfKnightsLeft; knightID++)
    {
        loadKnightsFile >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];
        knights[knightID] = *BaseKnight::create(knightID + 1, arr[0], arr[1], arr[3], arr[4], arr[2]);
    }

    loadKnightsFile.close();

    paladinShield = false;
    lancelotSpear = false;
    guinevereHair = false;
    excaliburSword = false;
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
    BaseKnight *temp_knight = new BaseKnight();
    temp_knight->hp = maxhp;

    // HP condition => knight type
    if (temp_knight->isPaladin())
    {
        temp_knight = new PaladinKnight();
    }
    else if (temp_knight->isLancelot())
    {
        temp_knight = new LancelotKnight();
    }
    else if (temp_knight->isDragon())
    {
        temp_knight = new DragonKnight();
    }
    else
    {
        temp_knight->knightType = NORMAL;
    }

    temp_knight->id = id;
    temp_knight->hp = maxhp;
    temp_knight->maxhp = maxhp;
    temp_knight->level = level;
    temp_knight->gil = gil;

    temp_knight->bag = new BaseBag();

    // input phoenixdownI to BaseBag
    // temp_knight->phoenixdownI = phoenixdownI;

    for (size_t i = 0; i < phoenixdownI; i++)
    {
        temp_knight->bag->insertFirst(new PhoenixDown(PHOENIXDOWN_I_ITEM));
    }

    for (size_t i = 0; i < antidote; i++)
    {
        temp_knight->bag->insertFirst(new Antidote());
    }

    return temp_knight;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    return &knights[numberOfKnightsLeft - 1];
}

// Decontructor
ArmyKnights::~ArmyKnights()
{
    // printf("Run ArmyKnights's deconstructor\n");
    delete this->knights;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    BaseKnight *lKnight = lastKnight();

    if (lKnight->getLevel() >= opponent->getLevel())
    {
        lKnight->increaseGil(opponent->getGil());
        return true;
    }

    lKnight->decreaseHP(opponent->getBaseDamage() * (opponent->getLevel() - lKnight->getLevel()));

    // if lKnight.HP < 0 => check gil or bag...
}

void ArmyKnights::setPaladinShield(bool value)
{
    this->paladinShield = value;
}
void ArmyKnights::setLancelotSpear(bool value)
{
    this->lancelotSpear = value;
}
void ArmyKnights::setGuinevereHair(bool value)
{
    this->guinevereHair = value;
}
void ArmyKnights::setExcaliburSword(bool value)
{
    this->excaliburSword = value;
}

bool ArmyKnights::adventure(Events *events)
{
    // cout << "Army Knights adventure" << endl;
    BaseOpponent *opponent;

    for (int index = 0; index <= events->count(); index++)
    {
        switch (events->get(index))
        {
        case MADBEAR:
            // printf("Meet MadBear\n");
            opponent = new MadBear();
            opponent->calcLevelO(index, MADBEAR);
            fight(opponent);
            break;

        case BANDIT:
            // printf("Meet BANDIT\n");
            break;

        case LORDLUPIN:
            // printf("Meet LORDLUPIN\n");
            break;

        case ELF:
            // printf("Meet ELF\n");
            break;

        case TROLL:
            // printf("Meet TROLL\n");
            break;

        case TORNBERY:
            // printf("Meet TORNBERY\n");
            break;

        case QUEEN_OF_CARDS:
            // printf("Meet QUEEN_OF_CARDS\n");
            break;

        case NINA_DE_RINGS:
            // printf("Meet NINA_DE_RINGS\n");
            break;

        case VUON_SAU_RIENG:
            // printf("Meet VUON_SAU_RIENG\n");
            break;

        case OMEGA_WEAPON:
            // printf("Meet OMEGA_WEAPON\n");
            break;
        case HADES:
            // printf("Meet HADES\n");
            break;

        case PHOENIXDOWN_II:
            // printf("Meet PHOUNIXDOWN_II\n");
            break;

        case PHOENIXDOWN_III:
            // printf("Meet PHOUNIXDOWN_III\n");
            break;

        case PHOENIXDOWN_IV:
            // printf("Meet PHOUNIXDOWN_IV\n");
            break;

        case PALADIN_SHIELD:
            // printf("Meet PALADIN_SHIELD\n");
            setPaladinShield(true);
            break;

        case LENCELOT_SPEAR:
            // printf("Meet LENCELOT_SPEAR\n");
            setLancelotSpear(true);
            break;

        case GUINEVERE_HAIR:
            // printf("Meet GUINEVERE_HAIR\n");
            setGuinevereHair(true);
            break;

        case EXCALIBUR:
            // printf("Meet EXCALIBUR\n");
            setExcaliburSword(true);
            break;

        case ULTIMECIA:
            if (hasExcaliburSword())
                printInfo();
            return true;
            break;

        default:
            break;
        }

        printInfo();
    }
}

int ArmyKnights::count() const
{
    return this->numberOfKnightsLeft;
}
bool ArmyKnights::hasPaladinShield() const
{
    return this->paladinShield;
}
bool ArmyKnights::hasLancelotSpear() const
{
    return this->lancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const
{
    return this->guinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const
{
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
    // cout << "Loading " << filename << endl;
    armyKnights = new ArmyKnights(filename);
}

void KnightAdventure::loadEvents(const string &file_event)
{
    // cout << "Loading " << file_event << endl;
    events = new Events(file_event);
};

void KnightAdventure::run()
{
    // TODO:
    armyKnights->printResult(armyKnights->adventure(events));
}

/* * * END implementation of class KnightAdventure * * */

/* * * BEGIN implementation of class Events * * */

/**
 * @brief Caculate the num of element from file (just in event)
 *
 * @return number of events (int)
 */
int Events::count() const
{
    return this->num_event;
};

/**
 * @brief Lấy mã sự kiện
 *
 * @param i
 * @return mã sự kiện ở vị trí thứ i
 */
int Events::get(int i) const
{
    return Events::events[i];
};

Events::Events(const string &file_event)
{
    string line;
    ifstream myfile(file_event);
    getline(myfile, line);
    this->num_event = stoi(line);
    this->events = new int[this->num_event];
    int pos = myfile.tellg();
    while (getline(myfile, line))
    {
        extract_line_num(line, this->events, this->num_event, " ");
    }
    myfile.seekg(0); // set file pointer to the beginning of the file
    myfile.close();
};

Events::~Events()
{
    // printf("Run Event's Decontructor\n");
    delete this->events;
    this->events = nullptr;
}

/**
 * @brief Method to load file
 *
 * @param line
 * @param array_address
 * @param array_length
 * @param delimeter
 */
void Events::extract_line_num(string line, int *array_address, int array_length, string delimeter)
{
    int length = line.length();
    int i = 0;
    // Generate variable tmp to store substring fron line string
    int line_blank;
    string line_num;

    // 5 is element value of kngiht's propertise
    while (i < array_length)
    {
        int line_blank = line.find(delimeter);
        string line_num;
        line_num = line.substr(0, line_blank);
        array_address[i] = std::stoi(line_num);
        i++;
        line = line.substr(line_blank + 1, length - line_blank);
    }
}

/* * * END implementation of class Events * * */
