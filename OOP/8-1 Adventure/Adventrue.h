#include"ListGraph.h"
#include"random_int.h"


class Adventrue{
public:

    void startgame(){
    //input game settings
        cout << "the size of each floor is?" << endl;
        cin >> sizeof_floor;
        cout << "the level of floors is?" << endl;
        cin >> levelof_floors;
    //initialize data
        win = withprincess = 0;
        a.resize(sizeof_floor*sizeof_floor*levelof_floors,"neutral");
        stair_index.resize(2*levelof_floors-2);
        for(int it=0;it < levelof_floors;it++){
            initfloor(it);
        }
        //add stairs to floor0, floor1 , …… , floorlevelof_floors-2
        for(int it=0;it < levelof_floors-1;it++){
            initstairs(it);
        }
        init_monster();
        init_princess();
        inlobby();
        do{
            a.listEdges_ofnode(presence);
            console();
        }while(entered_newroom());
    }

    /// @brief after gameover ask the player if he want another round
    /// @return 
    int Menu(){
        cout << "Want a new game? y/n" << endl;
        string temp;
        cin >> temp;
        if(temp == "y")
            return 1;
        else
            return 0;
    }

private:
    
    int sizeof_floor;
    int levelof_floors;
    ListGraph<string> a;
    int withprincess;
    int win;
    int presence;
    int monster_index,princess_index,lobby_index;
    int selftalk_counter=0;
    int selctalk_seq[12];
    vector<int> stair_index;

    /// @brief add edges to "sizeof_floor" sized square
    /// @param it 
    /// @param size 
    void initfloor(const int & floor){
        int x=floor*sizeof_floor*sizeof_floor;
        for(int it = x;it < x+sizeof_floor;it++){
            if(it % sizeof_floor == 0){
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it+1,"south");
            }
            else if(it % sizeof_floor == sizeof_floor - 1){
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it-1,"north");
            }else{
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it+1,"south");
                a.AddEdge(it,it-1,"north");
            }
        }

        for(int it = x+sizeof_floor;it < x+sizeof_floor*(sizeof_floor-1);it++){
            if(it % sizeof_floor == 0){
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it+1,"south");
            }else if(it % sizeof_floor == sizeof_floor - 1){
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it-1,"north");
            }else{
                a.AddEdge(it,it+sizeof_floor,"east");
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it+1,"south");
                a.AddEdge(it,it-1,"north");
            }
        }

        for(int it = x+sizeof_floor*(sizeof_floor-1);it < x+sizeof_floor*sizeof_floor;it++){
            if(it % sizeof_floor == 0){
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it+1,"south");
            }else if(it % sizeof_floor == sizeof_floor - 1){
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it-1,"north");
            }else{
                a.AddEdge(it,it-1,"north");
                a.AddEdge(it,it-sizeof_floor,"west");
                a.AddEdge(it,it+1,"south");
            }
        }
        //cout << floor <<" floor inited!" << endl;
    }

    /// @brief intall stairs "it"th floor;by randomly choosing 2 rooms and add double-directed edge to adj[index+size^2]
    /// @param it 
    /// @param size 
    void initstairs(const int & floor){
        int stair1,stair2;
        int x=floor*sizeof_floor*sizeof_floor;
        stair1 = RandomCreatFunc(x,x+sizeof_floor*sizeof_floor-1);
        do{
            stair2 = RandomCreatFunc(x,x+sizeof_floor*sizeof_floor-1);
        }while(stair2 == stair1);
        stair_index[2*floor]=stair1;
        stair_index[2*floor+1]=stair2;
        a.AddEdge(stair1 , stair1+sizeof_floor*sizeof_floor,"up");
        a.AddEdge(stair1+sizeof_floor*sizeof_floor , stair1,"down");
        a.AddEdge(stair2 , stair2+sizeof_floor*sizeof_floor,"up");
        a.AddEdge(stair2+sizeof_floor*sizeof_floor , stair2,"down");
    }

    /// @brief randomly place a monster
    void init_monster(){
        monster_index = RandomCreatFunc(0,sizeof_floor*sizeof_floor*levelof_floors-1);
        a.alterVnode_value(monster_index,"monster");
    }

    /// @brief randomly place a princess
    void init_princess(){
        do{
            princess_index = RandomCreatFunc(0,levelof_floors*sizeof_floor*sizeof_floor-1);
        }while(monster_index == princess_index);
        a.alterVnode_value(princess_index,"princess");
    }

    /// @brief randomly choose a looby in the fisrt floor and inform the player.
    void inlobby(){
        do{
            lobby_index = RandomCreatFunc(0,sizeof_floor*sizeof_floor-1);
        }while(lobby_index == monster_index || lobby_index == princess_index);
        a.alterVnode_value(lobby_index,"lobby");
        presence=lobby_index;
        cout << "Welcome to the lobby.";
    }

    /// @brief 控制台函数，用户可以输入各种指令，包括移动、作弊、自言自语
    void console(){
        string instruction;
        int temp;
        cin >> instruction;
        //case 1:go
        if(instruction == "go"){
            cin >> instruction;
            temp = a.find_edge(presence,instruction);
            if(temp == -1){
                cout << "Invalid choice!" <<endl;
                console();
            }else
                presence = temp;
        //case 2:cheat
        }else if(instruction == "cheat"){
            cheat();
            console();
        //case 3:talk
        }else if(instruction == "talk"){
            cin >> instruction >> instruction ;
            if(instruction == "myself")
                talk_to_myself();
            else if (instruction == "princess")
                talk_to_princess();
            else
                cout << "Invalid input!" << endl;
            console();
        }else if(instruction == "location"){
            cout << "You're at room " << presence << endl;
            console();
        }else if(instruction == "win"){
            win = 1;
            presence = lobby_index;
            withprincess = 1;
            return;
        }
        else{
            cout << "Invalid input!" << endl;
            console();
        }
    }

    /// @brief 进入一个新房间进行的操作，可能遇到monster，遇到公主，回到lobby；其中回到lobby是判断游戏胜利的重要因素，遇到monster是失败的重要因素
    /// @return 
    int entered_newroom(){

    //case 1:monster
        if(a.getVnode_value(presence) == "monster"){
            win = 0;
            gameover();
            return 0;
    //case 2:back to lobby
        }else if(a.getVnode_value(presence) == "lobby"){
            if(withprincess){
                win = 1;
                gameover();
                return 0;
            }else
                return 1;
    //case 3:get princess
        }else if(a.getVnode_value(presence) == "princess"){
            a.alterVnode_value(presence,"neutral");
            cout << "Congrats! You've found the princess!" << endl;
            withprincess = 1;
            return 1;
    //case 4:neutral land
        }else
            return 1;

    }

    /// @brief when faced with monster or coming back to lobby with princess, the game is over.
    void gameover(){
        if(win){
            cout << "You've saved the princess and honored the kingdom!";
            cout << "You are victorious.";
        }else{
            cout << "You've awakened the monster!!! There's no chance escaping." <<endl;
            cout << "You failed the Kingdom! Now die with disgrace!"<< endl;
        }
            cout << "Game Over!" << endl;
    }

    void cheat(){
        cout << "the lobby is in " << lobby_index << endl;
        cout << "the monster is in " <<monster_index << endl;
        cout << "the princess is in "<< princess_index << endl;
        for(int it=0;it<levelof_floors-1;it++){
            cout << "the stairs of floor " << it << " is in " << stair_index[2*it] << " and "<<stair_index[2*it+1] << endl;
        }
    }

    void talk_to_myself(){
        if(selftalk_counter % 12 == 0){
            selftalk_counter = 0;
            RandomArray(selctalk_seq,12);
        }
        switch(selctalk_seq[selftalk_counter]){
            case 1:cout << "Wubba lubba dub dub!" << endl;break;
            case 2:cout << "Riti Tikki Tabi biiiaaatch!" << endl;break;
            case 3:cout << "And That's the wa-a-a-a-y the news goes!" << endl;break;
            case 4:cout << "Hit the sack, Jack!" << endl;break;
            case 5:cout << "Uh-oh! Somersalt jump!" << endl;break;
            case 6:cout << "AIDS!" << endl;break;
            case 7:cout << "Tha's way I always say \"Shum shum, shi-i-i-lipidi dub\"!" << endl;break;
            case 8:cout << "Grassss tastes ba-a-d-ah!" << endl;break;
            case 9:cout << "No jumping in the sewer!" << endl;break;
            case 10:cout << "Burger time!" << endl;break;
            case 11:cout << "Rubber baby baby bunker!" << endl;break;
            case 12:cout << "Lick lick lick my balls! Ha ha ha! Yeah! Say that all the time!" << endl;break;
        }
        selftalk_counter++;
    }

    void talk_to_princess(){
        
    }

};