#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#define check "debug"
//define max value
#define MAX_HP 999
#define MAX_LEVEL 10
#define MAX_PHOENIX 5
#define MAX_GIL 999
#define MAX_ANTIDOTE 5
//knight
#define maxDraBag 14
#define maxLanBag 16
#define maxPaBag  2147483647
#define maxNorBag 19

//define min value
#define MIN_GIL 1

#define MADBEAR_GIL 100
#define BANDIT_GIL 150
#define LORDLUPIN_GIL 450
#define ELF_GIL 750
#define TROLL_GIL 800
//BaseDamage
#define MADBEAR_DAMAGE 10
#define BANDIT_DAMAGE 15
#define LORDLUPIN_DAMAGE 45
#define ELF_DAMAGE 75
#define TROLL_DAMAGE 95

//KnightDamage
#define LANCELOT_DAMAGE 0.05
#define PALADIN_DAMAGE 0.06
#define DRA_DAMAGE 0.075
#include "main.h"

// #define DEBUG

//prototype classes
class BaseBag;
class BaseKnight;
class BaseItem;
class Events;
class KnightAdventure;
class node;
class LinkedList;
class PaBag;
class DraBag;
class NorBag;
class LanBag;
class Bandit;
class MadBear;
class LordLupin;
class Elf;
class Tornbery;
class QueenOfCards;
class NinaDeRings;
class DurianGarden;
class OmegaWeapon;
class Hades;
class Ultimecia;
class Antidote;
class PhoneixDown;

//enum types
enum OpponentType {MADBEAR = 0, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEENOFCARDS, NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES, ULTIMECIA};
enum ItemType {ANTIDOTE=0,PHOENIX};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };


// Additional function
bool checkPaladin(int maxhp);
bool checkLancelot(int maxhp);
bool checkDragon(int maxhp);
KnightType getTypeHp(int maxHp);

/*  BEGIN NODE CLASS  */
class node{
    public:
    BaseItem* data;
    node* next;
    node(BaseItem* data); ;
};
/*  END NODE CLASS  */


/*  BEGIN LINKEDLIST CLASS  */
class LinkedList
{
private:
    node *head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    void append(BaseItem* data);
    void erase(BaseItem *value);
    void remove(int index);
    void push_front(BaseItem* data);
    void swap(node * item);
    node* find(ItemType);
    node* front() const;
    void setSize(int size){
        this->size=size;
    }
    int getSize() const{
        return size;
    }
    void setHead(node*);    
    void thow1Item();
};
/*  END LINKEDLIST CLASS  */


/*  BEGIN BASEBAG CLASS  */
class BaseBag {
protected:
    bool checkFull;
    LinkedList ItemList;
    int capacity;
    int currentSize;
public:
    BaseBag();
    ~BaseBag();
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    bool useItem(ItemType itemType, BaseKnight* knight);
    BaseItem* getAndCheck(ItemType ItemType, BaseKnight* knight);
    void throw1Item();
};
/*  END BASEBAG CLASS  */


/*  BEGIN KNIGHT CLASSES  */
class PaBag      :public BaseBag{
    public:
    PaBag(int phoenixdownI,int antidote);
    bool insertFirst(BaseItem *item);
};
class DraBag     :public BaseBag{
    public:
    DraBag(int phoenixdownI, int antidote);
    bool insertFirst(BaseItem *item);
};
class LanBag     :public BaseBag{
    public:
    LanBag(int phoenixdownI, int antidote);
    bool insertFirst(BaseItem *item);
};
class NorBag     :public BaseBag{
    public:
    NorBag(int phoenixdownI, int antidote);
    bool insertFirst(BaseItem *item);
};
/*  END KNIGHT CLASSES  */


/*  BEGIN BASEOPPONENT CLASS  */
class BaseOpponent{
protected:
    int baseDamage;
    int level;
    int gil;
    OpponentType type;
public:
    int getLevel();
    int getGil();
    OpponentType getType();
    int getBaseDamage();
};
/*  END BASEOPPENENT CLASS  */


/*  BEGIN OPPONENT CLASSES  */
class MadBear       :public BaseOpponent{
public:
    MadBear(int, int);
};
class Bandit        :public BaseOpponent{
public:
    Bandit(int stage, int eventId);
};
class LordLupin     :public BaseOpponent{
public:
    LordLupin(int, int);
};
class Elf           :public BaseOpponent{
public:
    Elf(int stage, int eventId);
};
class  Troll        :public BaseOpponent{
public:
    Troll(int stage, int eventId);
};
class Tornbery      :public BaseOpponent{
public:
    Tornbery(int stage, int eventId);
};
class QueenOfCards  :public BaseOpponent{
public:

    QueenOfCards(int stage, int eventId);
};
class NinaDeRings   :public BaseOpponent{
public:
    NinaDeRings();
};
class DurianGarden  :public BaseOpponent{
public:
    DurianGarden();
};
class OmegaWeapon   :public BaseOpponent{
    public:
    OmegaWeapon();
};
class Hades         :public BaseOpponent{
public:
    Hades();
};
class Ultimecia     :public BaseOpponent{
public:
    Ultimecia();
};
/*  END OPPONENT CLASSES  */


/*  BEGIN BASEKNIGHT CLASS  */
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
public:
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI,KnightType knightType);
    ~BaseKnight(){
        delete bag;
    }
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int getHp();
    bool fight(BaseOpponent *opponent);
    BaseBag* getBag();
    int getLevel();
    void setLevel(int lv);
    int getMaxhp();
    int getGil();
    int getId(){return id;}
    void setGil(int gil);
    void setHp(int hp);
    void die();
    KnightType getType();
};
/*  END BASEKNIGHT CLASS  */
    

/*  BEGIN ARMYKNIGHTS CLASS  */    
class ArmyKnights {
private:
    BaseKnight **Knightlist;
    int nKnight;
    int maxKnight;
    bool isMetOmega;
    bool isMetHades;
    bool has_Paladin_Shield;
    bool has_Lancelot_Spear;
    bool has_Guinevere_Hair;
    bool has_Excalibur_Sword;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void printInfo() const;
    void printResult(bool win) const;
    void deleteKnight(int i);
    void getPhoenix(int type);
    void transGil(int gil, int index);
    bool fightUltimecia();
};
/*  END ARMYKNIGHTS CLASS  */    


/*  BEGIN BASEITEM CLASS  */
class BaseItem {
protected:
    ItemType type;
public:
    virtual string toString()=0;
    virtual bool canUse ( BaseKnight * knight )=0;
    virtual void use ( BaseKnight * knight )=0;
    ItemType getType();
};
/*  END BASEITEM CLASS  */


/*  BEGIN ANTIDOTE AND PHOENIXDOWN CLASS  */
class Antidote : public BaseItem{
public:
    Antidote();
    string toString();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDown : public BaseItem{
protected:
    int phoenixType;
public:
    PhoenixDown(int num=1);
    string toString();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
/*  END ANTIDOTE AND PHOENIXDOWN CLASS  */


/*  BEGIN EVENTS CLASS  */
class Events {
private:
    int nEvents;
    int *eventsList;
public:
    Events(const string &file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};
/*  END EVENTS CLASS  */


/*  BEGIN KNIGHTADVENTURE CLASS  */
class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};
/*  END KNIGHTADVENTURE CLASS  */


#endif // __KNIGHT2_H__