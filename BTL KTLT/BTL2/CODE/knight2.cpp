#include "knight2.h"
/* * * BEGIN implementation of class Events * * */

Events::Events(const string &file_events)
{
    nEvents=0;
    eventsList=nullptr;
    ifstream fileInput(file_events);    
    if(fileInput.is_open()){
        fileInput>>nEvents;
        eventsList = new int[nEvents];
        for(int i=0;i<nEvents;++i){
            fileInput>>eventsList[i];
        }
    }
    fileInput.close();
}


Events::~Events()
{
    if(eventsList) delete eventsList;
    nEvents=0;
}
int Events::count() const
{
    return nEvents;
};
int Events::get(int i) const{
    return eventsList[i];
};
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI, KnightType KnightType)
{
    this->id=id;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->knightType=KnightType;
    if(knightType==PALADIN) this->bag=new PaBag(phoenixdownI,antidote);
    else if (knightType==LANCELOT) this->bag=new LanBag(phoenixdownI,antidote);
    else if(knightType==DRAGON) this->bag= new DraBag(phoenixdownI,antidote);
    else this->bag=new NorBag(phoenixdownI,antidote);
}

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight *BaseKnight:: create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
   return new BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI, getTypeHp(maxhp));
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
   
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
KnightType getTypeHp(int maxHp)
{
    if(checkDragon(maxHp)) return DRAGON;
    else if (checkLancelot(maxHp)) return LANCELOT;
    else if(checkPaladin(maxHp)) return PALADIN;
    else return NORMAL;
}

int BaseKnight::getHp()
{
    return hp;
}

int BaseKnight::getMaxhp()
{
    return maxhp;
}

int BaseKnight::getGil()
{
    return gil;
}

void BaseKnight::setGil(int gil)
{
    this->gil=gil;
}

void BaseKnight::setHp(int hp)
{
    this->hp=hp;
}

void BaseKnight::die()
{   
    if(hp<=0){
        if(bag->useItem(PHOENIX,this)) 
        {
            return;
        }
        else if(gil>=100){
            gil-=100;
            hp=maxhp/2;
            return;
        }
    }
    else bag->useItem(PHOENIX,this);
}

KnightType BaseKnight::getType()
{
    return knightType;
}
BaseBag *BaseKnight::getBag()
{
    return bag;
}

int BaseKnight::getLevel()
{
    return level;
}

void BaseKnight::setLevel(int lv)
{
    level=lv;
}

bool BaseKnight::fight(BaseOpponent* opponent)
{
    if(opponent -> getType() >=MADBEAR 
    && opponent -> getType() <=TROLL)
    {   
        if (level >= opponent -> getLevel()||knightType==LANCELOT||knightType==PALADIN) 
        {   
            gil+=opponent->getGil();
            return true;
        }
        else
        {
            hp -= opponent -> getBaseDamage() * (opponent -> getLevel() - level);
            die();
            return false;
        }
    }
    else if (opponent->getType()==TORNBERY){
        if(level>= opponent->getLevel()) 
        {
            level+=level<10;
            return true;
        }
        if(knightType==DRAGON) return true;
        else 
        {
            if(antidote>0) 
            {   
                antidote--;
                bag->useItem(ANTIDOTE,this);
            }
            else
            {   
                for(int i=0;i<3;i++){
                    bag->throw1Item();
                }
                hp-=10;
                die();
            }
            return false;
        }
        return true;
    }
    else if(opponent->getType()==QUEENOFCARDS)
    {
        if(level>=opponent->getLevel()){
            gil*=2;
            return true;
        }
        else if(knightType!=PALADIN) {
            gil/=2; return false;
        }
        return true;
    }
    else if(opponent->getType()==NINADERINGS){
        if (knightType == PALADIN && hp < (maxhp / 3))
        {
            setHp(hp + maxhp / 5);
        }
        else if (gil >= 50 && hp < (maxhp / 3))
        {
            setGil(gil - 50);
            setHp(hp + maxhp / 5);
        }
        return true;
    }
    else if(opponent->getType()==DURIANGARDEN)
    {   
        hp=maxhp; return true;
    }
    else if(opponent->getType()==HADES){
        
        if(level==MAX_LEVEL||(knightType==PALADIN&&level>=8)){
    
            return true;
        }
        else 
        {
            hp=0;
            die(); 
            return false;
        }
    }
    return true;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    // BaseKnight* lknight = lastKnight(); // last knight
    //     cout << ";"; lknight->toString();
    
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";"+ lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}


void ArmyKnights::getPhoenix(int type)
{
    BaseItem* tmp = new PhoenixDown(type);
    for(int i=0;i<nKnight;i++){
        int index=nKnight-1-i;
        if(Knightlist[index]->getBag()->insertFirst(tmp))
        return;
    }
    delete tmp;
}
bool ArmyKnights::fightUltimecia()
{   
    int UltHp=5000;
    if (has_Excalibur_Sword) return true;
    if (!has_Paladin_Shield || !has_Lancelot_Spear || !has_Guinevere_Hair) 
    {   
        for(int i=maxKnight-1;i>=0;i--){
            deleteKnight(i);
        }
        return false;
    }
    for (int i=nKnight-1; i >= 0; --i)
    {
        KnightType type=Knightlist[i]->getType();
        if (type == LANCELOT||type== DRAGON || type==PALADIN){
            double baseDmg9;
            switch(type)
            {
                case LANCELOT:
                    baseDmg9=LANCELOT_DAMAGE;
                    break;
                case PALADIN:
                    baseDmg9=PALADIN_DAMAGE;
                    break;
                case DRAGON:
                    baseDmg9=DRA_DAMAGE;
                    break;
            }
            int damage = (Knightlist[i]->getLevel() * Knightlist[i]->getHp() * baseDmg9);
            UltHp -= damage;
            if (UltHp <= 0) return true;
            deleteKnight(i);
        }
        else 
        {
            if (i==0) 
            {   
                for(int i=maxKnight-1;i>=0;i--){
                deleteKnight(i);
                }
                return false;
            }
            continue;
        }
    }
    return false;
}

void ArmyKnights::deleteKnight(int i)
{
    if(Knightlist[i]){
        delete Knightlist[i];
        Knightlist[i]=nullptr;
        --nKnight;
    }
}

void ArmyKnights::transGil(int overGil, int index)
{
    while(overGil>0 && index>=0)
    {
        int currentGil=Knightlist[index]->getGil();
        currentGil+=overGil;
        if(currentGil>999)
        {
            overGil=currentGil - 999;
            currentGil=999;
        }
        else overGil=0;
        Knightlist[index]->setGil(currentGil);
        index--;
    }
}


/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    if(armyKnights) delete armyKnights;
    if(events) delete events;
}

void KnightAdventure::loadArmyKnights(const string & file_armyknights)
{
    armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string &file_events)
{
    events=new Events(file_events);
}

void KnightAdventure::run()
{
    armyKnights -> printResult (armyKnights -> adventure(events));
}

/* * * END implementation of class KnightAdventure * * */

bool checkPaladin(int maxhp)
{
    for(int i=2;i*i<=maxhp;i++){
        if(maxhp%i==0) return false;
    }
    return maxhp>1;
}

bool checkLancelot(int maxhp)
{
    return maxhp==888;
}

bool checkDragon(int maxhp)
{   
    return  maxhp==345||maxhp==354||maxhp==435
            ||maxhp==453||maxhp==534||maxhp==543; 
}

ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    Knightlist=nullptr;
    nKnight=0;
    ifstream in(file_armyknights);
    if(in.is_open()){
        in>>nKnight;
        maxKnight=nKnight;
        this->Knightlist=new BaseKnight*[nKnight];
        for(int i=0;i<nKnight;i++){
            int HP, level, phoenixdownI, gil, antidote;
            in>>HP>>level>>phoenixdownI>> gil>> antidote;
            Knightlist[i]=BaseKnight::create(i+1,HP,level,gil,antidote,phoenixdownI);
        }
    }
    in.close();
    isMetHades=false;
    isMetOmega=false;
    has_Paladin_Shield = false;
    has_Excalibur_Sword= false;
    has_Guinevere_Hair = false;
    has_Lancelot_Spear = false;
}

ArmyKnights::~ArmyKnights()
{
    for(int i=0;i<maxKnight;i++){
        if(Knightlist[i])
        delete Knightlist[i];
    }
    if(Knightlist) delete Knightlist;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{   
    if (opponent -> getType() >= MADBEAR 
        && opponent -> getType()<=TROLL)
    {
        int index = nKnight - 1;
        if(Knightlist[index] -> fight(opponent) == false)
        {   
            if (Knightlist[index] -> getHp() <= 0)
            {
                deleteKnight(index);   
            }
        }
        if(Knightlist[index]&&Knightlist[index]->getGil()>999)
        {
            transGil(Knightlist[index]->getGil()-999,index-1);
            Knightlist[index]->setGil(999);
        }

        if(nKnight<=0) return false;
        return true;
    }
    else if(opponent->getType()==TORNBERY){
        int index=nKnight-1;
        if(Knightlist[index]->fight(opponent)==false){
            if(Knightlist[index]->getHp()<=0)
            { 
            deleteKnight(index);
            }
        }
        if(nKnight<=0) return false;
        return true;
    }
    else if(opponent->getType()==QUEENOFCARDS)
    {
        int index=nKnight-1;
        Knightlist[index]->fight(opponent);
        if(Knightlist[index]->getGil()>999){
            transGil(Knightlist[index]->getGil()-999,index-1);
            Knightlist[index]->setGil(999);
        }
        return true;
    }
    else if(opponent->getType()==NINADERINGS)
    {
        int index=nKnight-1;
        Knightlist[index]->fight(opponent);
        return true;
    }
    else if(opponent->getType()==DURIANGARDEN)
    {
        int index=nKnight-1;
        Knightlist[index]->fight(opponent);
        return true;
    }
    else if(opponent->getType()==OMEGAWEAPON)
    {
        if(isMetOmega) return true;
        int index=nKnight-1;
        if (Knightlist[index]->getType() == DRAGON ||
            Knightlist[index]->getLevel()==10 && 
            (Knightlist[index]->getHp() == Knightlist[index]->getMaxhp()))
        {
            isMetOmega = true;
            Knightlist[index]->setLevel(10);
            Knightlist[index]->setGil(999);
            return true;
        }
        else
        {
            Knightlist[index]->setHp(0);
           Knightlist[index]->die();
            if (Knightlist[index]->getHp() <= 0) deleteKnight(index);
            else return true;
        }
    if (nKnight <= 0) return false;
    return true;
    }
    else if(opponent->getType()==HADES)
    {   
        if(isMetHades) return true;
        int index=nKnight-1;
            if(Knightlist[index]->fight(opponent)==true){
                has_Paladin_Shield=true;
                isMetHades=true;
                return true;
            }
            else 
            {
                if(Knightlist[index]->getHp()>0) return true;
                deleteKnight(index);
            }
        if(nKnight<=0) return false;
    }
    return true;
}

bool ArmyKnights::adventure(Events *events)
{   
    bool result=true;
    BaseOpponent* newOpponent;
    int n=events->count();
    for(int i=0;i<n;i++){
        if (nKnight <= 0)
        {
            result = false;
            break;
        }
        if(events->get(i)==1){
            newOpponent = new MadBear(i, 1);
            result=fight(newOpponent);
        }
        else if(events->get(i)==2){
            newOpponent = new Bandit(i, 2);
            result=fight(newOpponent);
        }
        else if(events->get(i)==3){
            newOpponent = new LordLupin(i, 3);
            result=fight(newOpponent);
        }
        else if(events->get(i)==4){
            newOpponent = new Elf(i, 4);
            result=fight(newOpponent);
        }
        else if(events->get(i)==5){
            newOpponent = new Troll(i, 5);
            result=fight(newOpponent);
        }
        else if(events->get(i)==6){
            newOpponent = new Tornbery(i, 6); 
            result=fight(newOpponent);
        }
        else if(events->get(i)==7){
            newOpponent = new QueenOfCards(i, 7);
            result=fight(newOpponent);
        }
        else if(events->get(i)==8){
            newOpponent = new NinaDeRings();
            result=fight(newOpponent);
        }
        else if(events->get(i)==9){
            newOpponent = new DurianGarden();
            result=fight(newOpponent);
        }
        else if(events->get(i)==10){
            newOpponent = new OmegaWeapon();
            result=fight(newOpponent);
        }
        else if(events->get(i)==11){
            newOpponent = new Hades();
            if(isMetHades==false){
                result=fight(newOpponent);
            } 
        }
        else if(events->get(i)==112){
            getPhoenix(2);
        }
        else if(events->get(i)==113){
            getPhoenix(3);
        }
        else if(events->get(i)==114){
            getPhoenix(4);
        }
        else if(events->get(i)==95){
            has_Paladin_Shield = true;
        }
        else if(events->get(i)==96){
            has_Lancelot_Spear = true;
        }
        else if(events->get(i)==97){
            has_Guinevere_Hair = true;
        }
        else if(events->get(i)==98){
            if (has_Lancelot_Spear && has_Guinevere_Hair && has_Paladin_Shield)
            has_Excalibur_Sword = true;
        }
        else if(events->get(i)==99){
            result= fightUltimecia();
        }
        printInfo();
    }
    return result;
}

int ArmyKnights::count() const
{
    return nKnight;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if(nKnight<=0) return nullptr;
    int index=maxKnight-1;
    for(int i=index;i>=0;i--){
        if(Knightlist[i]!=nullptr) 
        {
            index=i;
            break;
        }
    }
    return Knightlist[index];
}

bool ArmyKnights::hasPaladinShield() const
{
    return has_Paladin_Shield;
}

bool ArmyKnights::hasLancelotSpear() const
{
    return has_Lancelot_Spear;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return has_Guinevere_Hair;
}

bool ArmyKnights::hasExcaliburSword() const
{
    return has_Excalibur_Sword;
}

LinkedList::LinkedList()
{
    head=nullptr;
    size=0;
}

LinkedList::~LinkedList()
{
    // node* head=front();
    // while (head!=nullptr) 
    // {
    //     node* tmp=head;
    //     head=head->next;
    //     delete tmp;
    //     cout<<check;
    // }
}

void LinkedList::append(BaseItem *data)
{   
    if(head==NULL){
        head=new node(data);
        size++;
        return;
    }
    node *tmp=head;
    while(tmp->next!=NULL){
        tmp=tmp->next;
    }
    tmp->next=new node(data);
    size++;
}

void LinkedList::erase(BaseItem *value)
{
    if(head==nullptr) return;
    node* temp=head;
    if(temp->data==value){
        remove(0);
        return;
    }
    while((temp->next)->data!=value){
        temp=temp->next;
    }
    node *des=temp->next;
    temp->next=des->next;
    delete des;
    size--;
}

void LinkedList::remove(int index)
{   
    node* temp=head;
    if(head==nullptr) return;
    
    else if(index==0){
        head=head->next;
        delete temp;
        size--;
    }
    else {
        for(int i=0;i<index-1;i++){
            temp=temp->next;
        }
        node * des=temp->next;
        temp->next=des->next;
        delete des;
        size--;
    }
}

void LinkedList::push_front(BaseItem* data)
{
    node *temp=head;
    if(head==nullptr){
        append(data);
        return;
    }
    node *newNode=new node(data);
    newNode->next=temp;
    head=newNode;
    size ++;
}

void LinkedList::swap(node *item)
{
    BaseItem* tmp=head->data;
    head->data=item->data;
    item->data=tmp;
}

node *LinkedList::find(ItemType type)
{
    node* tmp=head;
    while(tmp!=nullptr){
        if(tmp->data->getType()==type){
            return tmp;
        }
        tmp=tmp->next;
    }
    return nullptr;
}

node *  LinkedList::front() const
{
    return head;
}

void LinkedList::setHead(node* newHead)
{
    head=newHead;
}

void LinkedList::thow1Item()
{
    if(size>0){
        node*tmp=head;
        head=head->next;
        size--;
        delete tmp;
    }
}

BaseBag::BaseBag()
{
    checkFull=false;
    capacity=0;
    currentSize=0;
}

BaseBag::~BaseBag()
{
    ItemList.~LinkedList();
}

bool BaseBag::insertFirst(BaseItem *item)
{
    if (checkFull) return false;
    ItemList.push_front(item);
    if (ItemList.getSize() == capacity) checkFull = true;
    return true;
}

BaseItem *BaseBag::get(ItemType itemType){
    node *tmp=this->ItemList.front();
    while(tmp!=nullptr)
    {
        if(tmp->data->getType()==itemType)
        {
            this->ItemList.swap(tmp);
            return this->ItemList.front()->data;
        }
        tmp=tmp->next;
    }
}
string BaseBag::toString() const
{       
    string s="Bag[count="+to_string(ItemList.getSize())
    +";";

    if (ItemList.getSize()==0) return s+="]";

    node* tmp=ItemList.front();
    while(tmp!=nullptr)
    {
        s+=tmp->data->toString()+',';
        tmp=tmp->next;
    }
    if (s[s.length() - 1] == ',') s[s.length() - 1] = ']';
    else s += ']';
    return s;
}
bool BaseBag::useItem(ItemType itemType, BaseKnight *knight)
{   
    
    BaseItem* item=getAndCheck(itemType,knight);
    if(item!=nullptr){ 
        item->use(knight);
        throw1Item();
        return true;
    }
    return false;
}    

BaseItem *BaseBag::getAndCheck(ItemType itemType, BaseKnight *knight)
{   
    node* tmp=ItemList.front(); 
    while (tmp!=nullptr)
    {   
        if (tmp->data->getType() == itemType && tmp->data->canUse(knight))
        {
            BaseItem* tmpItem = tmp->data ;
            tmp->data = ItemList.front()->data;
            ItemList.front()->data = tmpItem;
            return tmpItem;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

void BaseBag::throw1Item()
{  
    if(ItemList.front()==nullptr) return;
    this->ItemList.thow1Item();
}
ItemType BaseItem::getType()
{
    return type;
}



bool PaBag::insertFirst(BaseItem *item)
{
    if(checkFull) return false;
    ++currentSize;
    ItemList.push_front(item);
    if(ItemList.getSize()==maxPaBag) checkFull=true;
    return true;
}

PaBag::PaBag(int phoenixdownI, int antidote)
{
    capacity = maxPaBag;
    for(int i=0;i<phoenixdownI;i++){
        this->insertFirst(new PhoenixDown());
    }
    for(int i=0;i<antidote;i++){
        this->insertFirst(new Antidote());
    }
}
bool DraBag::insertFirst(BaseItem *item)
{
    if(checkFull) return false;
        ItemList.push_front(item);
        if(ItemList.getSize()==maxDraBag) checkFull=true;
        return true;
}

DraBag::DraBag(int phoenixdownI, int antidote)
{
    capacity = maxDraBag;
        for(int i=0;i<phoenixdownI;i++){
         this->insertFirst(new PhoenixDown());
    }
}

bool LanBag::insertFirst(BaseItem *item)
{
    if(checkFull) return false;
    ItemList.push_front(item);
    if(ItemList.getSize()==maxLanBag) checkFull=true;
    return true;
}

LanBag::LanBag(int phoenixdownI, int antidote)
{
    capacity = maxLanBag;
    for(int i=0;i<phoenixdownI;i++){
       this->insertFirst(new PhoenixDown());
    }
    for(int i=0;i<antidote;i++){
        this->insertFirst(new Antidote());
    }
}

bool NorBag::insertFirst(BaseItem *item)
{
    if(checkFull) return false;
    ItemList.push_front(item);
    if(ItemList.getSize()==maxNorBag) checkFull=true;
    return true;
}

NorBag::NorBag(int phoenixdownI, int antidote)
{
    capacity = maxNorBag;
        for(int i=0;i<phoenixdownI;i++){
      this->insertFirst(new PhoenixDown());
    }
    for(int i=0;i<antidote;i++){
       this->insertFirst(new Antidote());
    }
}
Antidote::Antidote(){
    type=ANTIDOTE;
}
string Antidote::toString()
{
    return "Antidote";
}
bool Antidote::canUse(BaseKnight *knight)
{   
    return true;
}
void Antidote::use(BaseKnight*knight)
{
    return;
}
int BaseOpponent::getLevel()
{
    return level;
}

int BaseOpponent::getGil()
{
    return gil;
}

int BaseOpponent::getBaseDamage()
{
    return baseDamage;
}


OpponentType BaseOpponent::getType()
{
    return type;
}

MadBear::MadBear(int stage, int eventId)
{  
    type = MADBEAR;
    level=(stage+eventId)%10+1;
    baseDamage=MADBEAR_DAMAGE;
    gil=MADBEAR_GIL;
}

Bandit::Bandit(int stage, int eventId){
    type = BANDIT;
    level=(stage+eventId)%10+1;
    baseDamage=BANDIT_DAMAGE;
    gil=BANDIT_GIL;
}

LordLupin::LordLupin(int stage, int eventId)
{
    type = LORDLUPIN;
    level=(stage+eventId)%10+1;
    baseDamage=LORDLUPIN_DAMAGE;
    gil=LORDLUPIN_GIL;
}

Elf::Elf(int stage, int eventId)
{
    type = ELF;
    level=(stage+eventId)%10+1;
    baseDamage=ELF_DAMAGE;
    gil=ELF_GIL;
}

Troll::Troll(int stage, int eventId)
{
    type = TROLL;
    level=(stage+eventId)%10+1;
    baseDamage=TROLL_DAMAGE;
    gil=TROLL_GIL;
}

Tornbery::Tornbery(int stage, int eventId)
{
    type = TORNBERY;
    level=(stage+eventId)%10+1;
}
QueenOfCards::QueenOfCards(int stage, int eventId)
{
    type = QUEENOFCARDS;
    level=(stage+eventId)%10+1;
}

PhoenixDown::PhoenixDown(int num)
{
    phoenixType=num;
    type=PHOENIX;
}

string PhoenixDown::toString()
{   
    if(phoenixType==1) return "PhoenixI";
    if(phoenixType==2) return "PhoenixII";
    if(phoenixType==3) return "PhoenixIII";
    return "PhoenixIV";      
}

bool PhoenixDown::canUse(BaseKnight *knight)
{
    int hp      = knight->getHp() ;
    int maxhp   = knight->getMaxhp() ;
    if (phoenixType == 1 && hp <= 0) return true;
    else if (phoenixType == 2 && hp < (maxhp / 4)) return true;
    else if (phoenixType == 3 && hp < (maxhp / 3)) return true;
    else if (phoenixType == 4 && hp < (maxhp / 2)) return true;
    return false;
}

void PhoenixDown::use(BaseKnight *knight)
{   
    int hp =knight->getHp() ;
    int maxhp =knight->getMaxhp() ;
    if (phoenixType == 1 || phoenixType == 2) knight->setHp(maxhp);
    else if (phoenixType == 3)
    {
        if (hp <= 0) knight->setHp((maxhp / 3));
        else knight->setHp((maxhp / 4) + hp);
    }
    else {
        if (hp <= 0) knight->setHp((maxhp / 2));
        else knight->setHp((maxhp / 5) + hp);
    }
}

NinaDeRings::NinaDeRings()
{
    type=NINADERINGS;
}

DurianGarden::DurianGarden()
{
    type=DURIANGARDEN;
}

OmegaWeapon::OmegaWeapon()
{
    type=OMEGAWEAPON;
}

Hades::Hades()
{
    type=HADES;
}

Ultimecia::Ultimecia()
{
    type=ULTIMECIA;
}

node::node(BaseItem *data)
{
    this->data=data;
    next=nullptr;
}
