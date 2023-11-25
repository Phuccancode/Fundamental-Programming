#include "knight.h"
string line2;
string line3;
string file_mush_ghost, file_merlin_pack, file_asclepius_pack;
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout<< "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void readFile(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    rescue=-1;
    ifstream in(file_input);
    if(in.is_open()){
    in>>HP; in>>level; in>>remedy; in>>maidenkiss; in>>phoenixdown;
    getline(in, line2);
    getline(in, line2);
    string temp;
    getline(in, temp);
    int iString = 0;
    while(temp[iString] != ','){
        file_mush_ghost += temp[iString];
        iString++;
    }
    iString++;
    while(temp[iString] != ','){
        file_asclepius_pack += temp[iString];
        iString++;
    }
    iString++;
    while(temp[iString] != '\0'){
        file_merlin_pack += temp[iString];
        iString++;
    }
    }   3 
    in.close();
}
int slsukien(string line2){
    stringstream ss(line2);
    string tmp;
    int count=0;
    while(ss>>tmp){
        count++;
    }
    return count;
}
bool checkprime(int n){
    for(int i=2;i*i<n;i++){
        if(n%i==0){
            return false;
        }
    }
    return n>1;
}
int upprime(int n){
    if(checkprime(n)) n++;
    while(!checkprime(n)){
        n++;
    }
    return n;
}
void tachso(string &s){
    int index=0;
    while(s[index]!='\0'){
        if(s[index]==','){ s[index]=' ';}
        index++;
    }
};
int slnarr(int *arr,int n){
    int maxx=arr[0];
    for(int i=1;i<n;i++){
        if(arr[i]>maxx){
            maxx=arr[i];
        };
    }
    return maxx;
}
int snnarr(int *arr,int n){
    int minn=arr[0];
    for(int i=1;i<n;i++){
        if(arr[i]<minn){
            minn=arr[i];
        };
    }
    return minn;
}
int findindexfirst (int arr[],int n,int key){
    for(int i=0;i<n;i++){
        if(arr[i]==key){
            return i;
        }
    }
}
int findindexlast (int arr[],int n,int key){
    for(int i=n-1;i>=0;i--){
        if(arr[i]==key){
            return i;
        }
    }
}
void findSecondLargest(int arr[],int &max2_3x,int &max2_3i,int n2) {
    int max1 = -1e9;
    max2_3x= -1e9;     
    if(n2>2){
        n2=3;
        if((arr[0]==arr[1]&&arr[1]==arr[2])){
            max2_3x=-5;
            max2_3i=-7;
            return;
        }
    }else{
        if(n2==2){
            if((arr[0]==arr[1])){
            max2_3x=-5;
            max2_3i=-7;
            return;
            }
        }
        if(n2==1){
            max2_3x=-5;
            max2_3i=-7;
            return;
        }
    }
    for (int i = 0; i < n2; i++) {
        if (arr[i] > max1) {
            max2_3x = max1;
            max2_3i=findindexfirst (arr,3,max1);
            max1 = arr[i];
        }
        else if (arr[i] > max2_3x && arr[i] < max1) {
            max2_3x = arr[i];
            max2_3i=i;
        }
        
    }
}
bool checkfindmerlin(int n){
    if(n==-1)return 0;
    if(n!=-1)return 1;
}
bool checkmerlin(string s){
    for(int i=0;i<s.length();i++){
        s[i]=tolower(s[i]);
    }
    return    checkfindmerlin(s.find("m"))
            &&checkfindmerlin(s.find("e"))
            &&checkfindmerlin(s.find("r"))
            &&checkfindmerlin(s.find("l"))
            &&checkfindmerlin(s.find("i"))
            &&checkfindmerlin(s.find("n"));
}
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    readFile(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    bool checkmeetmerlin=true;
    bool king=false;
    if(HP==999){
        king=true;
    }
    bool lancelot=true;
    if(HP==1){
        lancelot=false;
    }
    else{
    for(int i=2;i<=sqrt(HP);i++){
        if(HP%i==0){
            lancelot=false;
            break;
        }
    }
    }
    string temp;
    int event,mushroom=0, oldLevel, fog=0,count=1,levelO,HPmax=HP;
    stringstream ss(line2);
    float baseDamage;
    bool checkasc=true;
    while(ss>>temp){
        string mushroom_event_13;
        if(temp.length()>2){
            mushroom_event_13 = temp.substr(2);
            event = 13;
        }
        else{
        event=stoi(temp);
        }

        bool checkmushroom=false;
        bool checkfog=false;
        if(mushroom){
            mushroom--;
            if(mushroom==1)
            checkmushroom=true;
        }
        if(fog){
            fog--;
            if(fog==1)
                checkfog=true;
        }
        //cout<<event<<endl;

        switch (event){
            case 1:baseDamage=1;
            break;
            case 2:baseDamage=1.5;
            break;
            case 3:baseDamage=4.5;
            break;
            case 4:baseDamage=7.5;
            break;
            case 5:baseDamage=9.5;
            break;
        }
        if(event==0){
            rescue=1;
            display(HP, level, remedy,  maidenkiss, phoenixdown,  rescue);
            return;
        }
        if(event>=1 && event<=5){
            int b=count%10;
            levelO=count>6?(b>5?b:5):b;
            if(level>levelO||king||lancelot){
                if(level<10){
                level++;
                }
            }
            else if(level<levelO){
                
                int damage=baseDamage*levelO*10;
                HP-=damage;
            }
        }
        else if(event==6 && !mushroom && !fog){
            int b=count%10;
            levelO=count>6?(b>5?b:5):b;
            if(level>levelO||king||lancelot){
                level=level>=9?10:level+2;
            }
            else if(level<levelO){
                if(remedy>0){
                    remedy--;
                }
                else{
                    mushroom=4;
                    HP=HP<5?1:HP/5;
                }
            }
        }
        else if(event==7 && !mushroom && !fog){
            int b=count%10;
            levelO=count>6?(b>5?b:5):b;
            if(level>levelO||king||lancelot){
                level=level>=9?10:level+2;
            }
            else if(level<levelO){
                if(maidenkiss>0){
                    maidenkiss--;
                }
                else {
                fog=4;
                oldLevel=level;
                level=1;
                }
            }
        }
        else if(event==11){
            int n1 = ((level + phoenixdown) % 5 + 1 ) * 3;
            int s1 = 0, tmp = 99, sum=0;
            for(int i = 0; i < n1; i++){        
                sum += tmp;
                tmp =- 2;
                s1+=sum;
            }
            HP = HP + s1 % 100 ;
            HP=upprime(HP);
            HP=HP<HPmax?HP:HPmax;
        }
        else if(event==12){
            if(HP>1){
                int f1=1,f2=1;
                while(HP>f2){
                    f2+=f1;
                    f1=f2-f1;
                }
                HP=f1;
            }
        }
        else if(event==13){
            int n2;
            string namma;
            ifstream file13(file_mush_ghost);
            if(file13.is_open()){
                file13>>n2;
                getline(file13,namma);
                getline(file13,namma);
                tachso(namma);
                stringstream q(namma);
                string tach;
                int arr[1000];
                for(int i=0;i<n2;i++){
                    q>>tach;
                    arr[i]=stoi(tach);
                }
                for(int i=0;i<mushroom_event_13.length();i++){
                    if(mushroom_event_13[i]-'0'<5&&mushroom_event_13[i]-'0'>0){
                        if(mushroom_event_13[i]-'0'==1){
                            HP=HP-(findindexlast(arr,n2,slnarr(arr,n2))+findindexlast(arr,n2,snnarr(arr,n2)));
                        }
                        else if(mushroom_event_13[i]-'0'==2){
                            int i=0,mtx=-2,mti=-3;
                            bool checkdd=true;
                            if(n2==1){
                                mtx=arr[0];
                                mti=0;
                            }
                            else{
                                i=0;
                                while(i<n2-1){
                                    if(arr[i]>arr[i+1]){
                                        mtx=arr[i];
                                        mti=i;
                                        break;
                                    }
                                    i++;
                                }
                                while(i<n2-1){
                                    if(arr[i]<=arr[i+1]){
                                        checkdd=false;
                                        break;
                                    }
                                    i++;
                                }
                                if(!checkdd){
                                    mtx=-2;
                                    mti=-3;
                                }
                                i=0;
                                //daygiam
                                while(i<n2-1){
                                    if(arr[i]<=arr[i+1]){
                                        checkdd=false;
                                        break;
                                    
                                    }
                                    i++;
                                }
                                
                                if(checkdd){
                                    mtx=arr[0];
                                    mti=0;
                                }
                                checkdd=true;
                                //daytang
                                i=0;
                                while(i<n2-1){
                                    
                                    if(arr[i]>=arr[i+1]){
                                        checkdd=false;
                                        break;
                                    }
                                    i++;
                                }
                                if(checkdd){
                                    mtx=arr[n2-1];
                                    mti=n2-1;
                                }
                                i=0;
                                while(i<n2-1){
                                    if(arr[i]==arr[i+1]){
                                        mtx=-2;
                                        mti=-3;
                                    }
                                    i++;
                                }
                            }
                            HP=HP-(mtx+mti);
                            
                        }   
                        else if(mushroom_event_13[i]-'0'==3||mushroom_event_13[i]-'0'==4){
                            int vi_arr[1000];
                            for(int i=0;i<n2;i++){
                                vi_arr[i]=arr[i]<0?-arr[i]:arr[i];                           
                                vi_arr[i]=(17*vi_arr[i]+9)%257;
                            }
                            if(mushroom_event_13[i]-'0'==3){
                                HP=HP-(findindexfirst(vi_arr,n2,slnarr(vi_arr,n2))+findindexfirst(vi_arr,n2,snnarr(vi_arr,n2)));
                            }
                            if(mushroom_event_13[i]-'0'==4){
                                int max2_3x, max2_3i;
                                findSecondLargest(vi_arr,max2_3x,max2_3i,n2);
                                HP=HP-(max2_3x+max2_3i);
                            }
                        }
                    }
                    if(HP<=0){
                        if(phoenixdown>0){
                        phoenixdown--;
                        HP=HPmax;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
            file13.close();
        }
        else if(event==15&&remedy<99){
            remedy++;
        }
        else if(event==16&&maidenkiss<99){
            maidenkiss++;
        }
        else if(event==17&&phoenixdown<99){
            phoenixdown++;
        }
        else if(event==19&&checkasc){
            int r1,c1;
            string ascline;
            checkasc=false;
            ifstream ascFile(file_asclepius_pack);
            if(ascFile.is_open()){
                ascFile>>r1>>c1; 
                getline(ascFile,ascline); 
                for(int i=0;i<r1;i++){
                    getline(ascFile,ascline);
                    string temp;
                    stringstream ascss(ascline);
                    int item=0;
                    while(ascss>>temp){
                        if(stoi(temp)==16&&remedy<99&&item<3){
                            remedy++; item++;         
                        }
                        else if(stoi(temp)==17&&maidenkiss<99&&item<3){
                            maidenkiss++; item ++;
                        }
                        else if(stoi(temp)==18&&phoenixdown<99&&item<3){
                            phoenixdown++; item++;
                        }
                    }
                }
            }
            ascFile.close();
        }
        else if(event==99){
            if(king||(lancelot&&level>7)||level==10){
                level=10;
            }
            else {
                rescue=0;
                display(HP, level, remedy,  maidenkiss, phoenixdown,  rescue); 
                return;
            }
        }
        else if(event==18&&checkmeetmerlin){
            checkmeetmerlin=false;
            ifstream merlinFile(file_merlin_pack);
            int n9;
            string smerlin;
            if(merlinFile.is_open()){
                merlinFile>>n9;
                getline(merlinFile,smerlin);
                for(int i=0;i<n9;i++){
                    getline(merlinFile,smerlin);
                    if(checkfindmerlin(smerlin.find("Merlin"))||checkfindmerlin(smerlin.find("merlin")))
                    {
                        HP+=3;
                    }
                    else if(checkmerlin(smerlin)){
                        HP+=2;
                    }
                }
                HP=HP<HPmax?HP:HPmax;
            }
            merlinFile.close();
        }
        
        HP=HP<HPmax?HP:HPmax;
        if(remedy>0&&mushroom) {checkmushroom=true;remedy--;mushroom=0;}
        if(maidenkiss>0&&fog) {checkfog=true;maidenkiss--;fog=0;}
        if(HP<=0){
            if(phoenixdown>0){
                phoenixdown--;
                HP=HPmax; 
                mushroom=0;
                fog=0;
            }
            else{
                rescue=0;
                display(HP, level, remedy,  maidenkiss, phoenixdown,  rescue);
                return;
            }
        }
        if(checkmushroom)
            HP=HP*5>HPmax?HPmax:HP*5;
        if(checkfog)
            level=oldLevel;        
        
        if(HP>0 && slsukien(line2)==count){
            rescue=1;
            display(HP, level, remedy,  maidenkiss, phoenixdown,  rescue);
            break;
        }
        display(HP, level, remedy,  maidenkiss, phoenixdown,  rescue);
        count++;
    }
}
