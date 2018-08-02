    #include <iostream>
    #include <conio.h>
    #include <windows.h>
    #include <fstream>
    #include <iomanip>
    #include <stdio.h>
    #include <limits.h>
    #include <ctime>

    #define ENTER 13
    #define ESC 27
    #define BUFFER 224
    #define UP 72
    #define DOWN 80
    #define LEFT 75
    #define RIGHT 77

    const char Filename[] = "userlist.dat";
    bool RUN = false;
    using namespace std;
    /****************************************************/
    /**< Function to go to any (x,y) cordinates on console screen */
    void gotoxy(int x,int y)
    {
        /**< A predefined data type(struct) of windows.h */
        COORD point;
        point.X=x;
        point.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);
    }
    /****************************************************/
    /**< Class to manipulate user data >**/
    class member
    {
    private:
        int Mem_No;
        char Name[20];
        char Pass[20];
        bool Mem;
        int Rem_days;
        int High_score;
        char temp_del;

        void read_pass();
        int searchfile();
        int running;
    public:
        member()
        {
            Mem_No=0000;
            strcpy(Name,"");
            strcpy(Pass,"");
            Mem = true;
            Rem_days = 999;
            High_score = 0;
            running = 0;
            temp_del = 'O';
        }
        member(member &a)
        {
            Mem_No = a.Mem_No;
            strcpy(Name,a.Name);
            strcpy(Pass,a.Pass);
            Mem = a.Mem;
            High_score = a.High_score;
            Rem_days = a.Rem_days;
            running = a.running;
            temp_del = a.temp_del;
        }
        char* getName()
        {
            return Name;
        }
        char* getPass()
        {
            return Pass;
        }
        int getMem_No()
        {
            return Mem_No;
        }
        bool getMem()
        {
            return Mem;
        }
        void putMem()
        {
            Mem = false;
        }
        int getRem_days()
        {
            return Rem_days;
        }
        void putRem_days()
        {
            Rem_days--;
        }
        int getHigh_score()
        {
            return High_score;
        }
        int getrunning()
        {
            return running;
        }
        char gettemp_del()
        {
            return temp_del;
        }
        void puttemp_del()
        {
            temp_del = 'Y';
        }
        void unputtemp_del()
        {
            temp_del = 'N';
        }
        void total_input();
        void read();
        void accessHigh_score(int input);
    };

    void member::read_pass()
    {
        int i=0;
        char ch;
        gotoxy(34,11);
        ch = _getch();
        while(ch != ENTER)
        {
            Pass[i]=ch;
            i++;
            cout<<"*";
            ch = _getch();
        }
        Pass[i]='\0';
    }

    int member::searchfile()
    {
        member user_from_file;
        ifstream filein;
        if(strcmp(Name,"admin") == 0 && strcmp(Pass,"admin") == 0)
        {
            return 1;
        }
        else
        {
            filein.open(Filename,ios::in|ios::binary);
            if(filein.is_open())
            {
                while(!filein.eof())
                {
                    filein.read((char *)&user_from_file,sizeof(user_from_file));
                    if(strcmp(Name,user_from_file.getName()) == 0 && strcmp(Pass,user_from_file.getPass()) ==0 )
                    {
                        filein.close();
                        Mem_No = user_from_file.getMem_No();
                        Rem_days = user_from_file.getRem_days();
                        Mem = user_from_file.getMem();
                        High_score = user_from_file.getHigh_score();
                        return 2;
                    }
                }
            }
        }
        return 0;
    }
    void member::total_input()
    {
        cout<<"Member No: ";
        cin>>Mem_No;
        cin.clear();
        cin.ignore(1);
        cout<<"\nUsername: ";
        cin.getline(Name,19);
        cout<<"\nPassword: ";
        cin.getline(Pass,19);
        cout<<"\nMembership Status: ";
        cin>>Mem;
        cout<<"\nRemaining Days: ";
        cin>>Rem_days;
        cout<<"\nHigh-Score: ";
        cin>>High_score;
        }

    void member::read()
        {
            gotoxy(25,10);
            cout<<"Username:";
            gotoxy(25,11);
            cout<<"Password:";
            gotoxy(34,10);
            cin.getline(Name,19);
            read_pass();
            running = searchfile();

        }

    void member::accessHigh_score(int input)
    {
        High_score = input;
    }

    /****************************************************/
    /**< Class to access admin privileges >**/
    class root
    {
        int y;
        int input;

        void list_users();
        void add_user();
        void rem_user(char to_del_name[]);
        void change_user(char Name[]);
        void display(member IN);
        void search_user();
    public:
        root()
        {
            input = 0;
            y = 1;
        }
        void access();
    };

    void root::search_user()
    {
        member user;
        ifstream filein;
        filein.open(Filename,ios::in|ios::binary);
        int Mem_No;
        char Name[20];
        int y_search = 1;
        system("CLS");
        RUN = true;
        cout<<"Search using:\n"
            <<"1.Member No.\n"
            <<"2.Username";
        gotoxy(15,y_search);
        cout<<"<-";
        while(RUN)
        {
            if(kbhit())
            {
                input = _getch();
                if(input == BUFFER)
                    input = _getch();
                if(input == UP)
                {
                    if(y_search == 1)
                    {
                        y_search = 2;
                    }
                    else
                        y_search = y_search - 1;
                }
                else if(input == DOWN)
                {
                    if(y_search == 2)
                        y_search = 1;
                    else
                        y_search = y_search + 1;
                }
                else if(input == ENTER)
                {
                    RUN = false;
                    system("CLS");
                    switch(y_search)
                    {
                    case 1:
                        cout<<"Enter Member No.\n";
                        cin>>Mem_No;
                        break;
                    case 2:
                        cout<<"Enter Username\n";
                        cin.getline(Name,19);
                        break;
                    }
                }
                system("CLS");
                cout<<"Search using:\n"
                    <<"1.Member No.\n"
                    <<"2.Username";
                gotoxy(15,y_search);
                cout<<"<-";
            }
        }
        filein.read((char *) &user,sizeof(user));
        while(!filein.eof())
        {
            if((strcmp(user.getName(),Name) == 0) || (user.getMem_No() == Mem_No))
            {
                filein.close();
                system("CLS");
                display(user);
                cout<<"\n\nPress '1' to change details of user '2' to delete the user\n";
                if(user.gettemp_del() == 'Y')
                    cout<<"'3' to restore from temporary deletion\n";
                cout<<"or any other key to go to previous menu\n";
                cin>>input;
                switch(input)
                {
                case 1:
                    change_user(user.getName());
                    system("PAUSE");
                    break;
                case 2:
                    rem_user(user.getName());
                    system("PAUSE");
                    break;
                case 3:
                    user.unputtemp_del();
                }
            }
            filein.read((char *) &user,sizeof(user));
        }
        filein.close();
        RUN = true;
    }

    void root::display(member A)
    {
        cout<<setw(9);
        cout<<A.getMem_No()<<setw(11);
        cout<<A.getName()<<setw(20);
        cout<<A.getMem()<<setw(20);
        cout<<A.getRem_days()<<setw(15);
        cout<<A.getHigh_score()<<"\n";
    }

    void root::list_users()
    {
        system("CLS");
        member user;
        ifstream filein;
        filein.open(Filename,ios::in|ios::binary);
        if(filein.is_open())
        {
            cout<<setw(10);
            cout<<"Member No."<<setw(10)
                <<"Username"<<setw(20)
                <<"Membership status"<<setw(20)
                <<"Remaining days"<<setw(15)
                <<"High-Score"<<endl;
            filein.read((char *)&user, sizeof(user));
            while(!filein.eof())
            {
                display(user);
                filein.read((char *)&user, sizeof(user));
            }
        }
    }

    void root::add_user()
    {
        member user;
        system("CLS");
        user.total_input();
        ofstream fileout;
        fileout.open(Filename,ios::app|ios::binary);
        if(fileout.is_open())
        {
            fileout.write((char *) &user, sizeof(user));
        }
    }

    void root::rem_user(char to_del_name[])
    {
        system("CLS");
        member user;
        char confirm = 'n';
        ifstream filein(Filename,ios::in|ios::binary);
        ofstream fileout("temp.dat",ios::out|ios::binary);
        cout<<endl;
        filein.read((char *) &user, sizeof(user));
        while(!filein.eof())
        {
            if(strcmp(user.getName(),to_del_name) == 0)
            {
                display(user);
                cout<<"\n Are you sure you want to delete? (y/n)";
                cin>>confirm;
                if(confirm == 'n')
                    fileout.write((char *) &user, sizeof(user));
                else if(user.gettemp_del() == 'N')
                {
                    user.puttemp_del();
                    fileout.write((char *) &user, sizeof(user));

                }
            }
            else
                fileout.write((char *) &user, sizeof(user));
            filein.read((char *) &user, sizeof(user));
        }
        filein.close();
        fileout.close();
        remove(Filename);
        rename("temp.dat",Filename);
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }

    void root::change_user(char Name[])
    {
        system("CLS");
        int pos;
        member user;
        fstream file(Filename,ios::in|ios::out|ios::binary);
        while(!file.eof())
        {
            pos = file.tellg();
            file.read((char *) &user, sizeof(user));
            if(strcmp(user.getName(), Name) == 0)
            {
                display(user);
                cout<<"\nEnter new details -\n";
                user.total_input();
                file.seekg(pos);
                file.write((char *) &user, sizeof(user));
                break;
            }
        }
        file.close();
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }

    void root::access()
    {
        system("CLS");
        RUN = true;
        cout<<"ADMIN PAGE"<<endl;
        cout<<"*List members"<<endl;
        cout<<"*Add member"<<endl;
        cout<<"*Search member"<<endl;
        cout<<"*Exit"<<endl;
        cout<<"Press UP or DOWN to navigate and ENTER to select";
        gotoxy(27,y);
        cout<<"<-";
        while(RUN)
        {
            if(kbhit())
            {
                input = _getch();
                if(input == BUFFER)
                    input = _getch();
                if(input == UP)
                {
                    if(y == 1)
                    {
                        y = 4;
                    }
                    else
                        y = y-1;
                }
                else if(input == DOWN)
                {
                    if(y == 4)
                        y = 1;
                    else
                        y = y+1;
                }
                else if(input == ENTER)
                {
                    switch(y)
                    {
                    case 1:
                        list_users();
                        system("PAUSE");
                        break;
                    case 2:
                        add_user();
                        system("PAUSE");
                        break;
                    case 3:
                        search_user();
                        break;
                    case 4:
                        exit(0);
                        break;
                    }
                }
                system("CLS");
                cout<<"ADMIN PAGE"<<endl;
                cout<<"*List members"<<endl;
                cout<<"*Add member"<<endl;
                cout<<"*Search member"<<endl;
                cout<<"*Exit"<<endl;
                cout<<"Press UP or DOWN to navigate and ENTER to select";
                gotoxy(27,y);
                cout<<"<-";
            }
        }

    }

    /****************************************************/
    /**< Classs to run game >**/
    class snake_game
    {
        int y;
        int input;
        int x_map_corner_left;
        int x_map_corner_right;
        int y_map_corner_top;
        int y_map_corner_bottom;
        member user;
        member highscore_list[10];
        int score;
        int speed;
        char body_seg[100];
        int body_seg_x_cord[100];
        int body_seg_y_cord[100];
        int body_seg_change_pos_x[100];
        int body_seg_change_pos_y[100];
        int food_x_cord;
        int food_y_cord;
        char apple;

        void print_map();
        void display_top_scores();
        void make_top_scores();
        void change_speed();
        void key_press();
        void generate_food();
        void print_snake();
        void update_highscore();
        void update_membership();

    public:
        snake_game(member user_ini)
        {
            input = 0;
            y = 2;
            x_map_corner_left = 1;
            x_map_corner_right = 36;
            y_map_corner_top = 1;
            y_map_corner_bottom = 20;
            make_top_scores();
            user = user_ini;
            speed = 3;
            score = 3;
            apple = 153;
            int i = 0;
            while(i<100)
            {
                body_seg[i] = ' ' ;
                body_seg_x_cord[i] = 18;
                body_seg_y_cord[i] = 10 + i;
                body_seg_change_pos_x[i] = 0;
                body_seg_change_pos_y[i] = -1;
                ++i;
            }
            food_x_cord = 10;
            food_y_cord = 10;
        }
        void game_menu();

    };

    void snake_game::print_map()
    {
        char boundary;
        boundary = 218;  //'┌'
        gotoxy(x_map_corner_left,y_map_corner_top);
        cout<<boundary;
        boundary = 191;  //'┐'
        gotoxy(x_map_corner_right,y_map_corner_top);
        cout<<boundary;
        boundary = 217;  //'┘'
        gotoxy(x_map_corner_right,y_map_corner_bottom);
        cout<<boundary;
        boundary = 192;  //'└'
        gotoxy(x_map_corner_left,y_map_corner_bottom);
        cout<<boundary;
        for(int i = x_map_corner_left + 1; i < x_map_corner_right; ++i)
        {
            boundary = 196; //'─'
            gotoxy(i, y_map_corner_bottom);
            cout<<boundary;
            gotoxy(i, y_map_corner_top);
            cout<<boundary;
        }
        for(int i = y_map_corner_top + 1; i < y_map_corner_bottom; ++i)
        {
            boundary = 179;  //'│'
            gotoxy(x_map_corner_left, i);
            cout<<boundary;
            gotoxy(x_map_corner_right, i);
            cout<<boundary;
        }
        gotoxy(x_map_corner_right + 5, 5);
        cout<<"PRESS ESC TO QUIT";
        gotoxy(x_map_corner_right + 5, 7);
        cout<<"PRESS ENTER TO PAUSE";
    }

    void snake_game::make_top_scores()
    {
        member temp;
        RUN = true;
        int i = 0, j = 0, k = 0;
        ifstream filein(Filename,ios::in|ios::binary);
        if(!filein)
            cout<<"ERROR";
        filein.read((char *) &highscore_list[i], sizeof(highscore_list[0]));
        while(!filein.eof() && i < 10)
        {
            j = 0;
            while(j < i && i > 0)
            {
                if(highscore_list[j].getHigh_score() < highscore_list[i].getHigh_score())
                {
                    temp = highscore_list[i];
                    k = i;
                    while(k > j)
                    {
                        highscore_list[k] = highscore_list[k - 1];
                        --k;
                    }
                    highscore_list[j] = temp;
                    break;
                }
                ++j;
            }
            ++i;
            if(i < 10)
                filein.read((char *) &highscore_list[i], sizeof(highscore_list[0]));
        }
        filein.read((char *) &temp, sizeof(temp));
        while(!filein.eof())
        {
            i = 0;
            while(i<10)
            {
                if(temp.getHigh_score() > highscore_list[i].getHigh_score())
                {
                    j = 9;
                    while(j > i)
                    {
                        highscore_list[j] = highscore_list[j - 1];
                        --j;
                    }
                    highscore_list[i] = temp;
                    break;
                }
                ++i;
            }
            i = 10;
            filein.read((char *) &temp, sizeof(temp));
        }
        filein.close();
    }

    void snake_game::display_top_scores()
    {
        RUN = true;
        int j = 9;
        while(j > 0)
        {
            if(highscore_list[j].getHigh_score() > highscore_list[j - 1].getHigh_score())
            {
                member temp;
                temp = highscore_list[j];
                highscore_list[j] = highscore_list[j - 1];
                highscore_list[j - 1] = temp;
            }
            --j;
        }

        system("CLS");
        cout<<setw(15)<<"HIGH-SCORES\n\n";
        cout<<setw(6)<<"S.No"
            <<setw(9)<<"Username"
            <<setw(7)<<"score\n";
        j = 0;
        while(j < 10)
        {
            cout<<setw(6)<<j+1
                <<setw(9)<<highscore_list[j].getName()
                <<setw(7)<<highscore_list[j].getHigh_score()<<endl;
                j++;
        }
        cout<<"Press ENTER to go to main menu";
        while(RUN)
        {
            if(_getch() == ENTER)
                RUN = false;
        }
    }

    void snake_game::change_speed()
    {
        system("CLS");
        char counter = 219;
        int i = 0, j = 0;
        speed = 3;
        while(i < speed)
        {
            gotoxy(30 + j, 9);
            cout<<counter<<" ";
            i += 1;
            j += 2;
        }
        cout<<"\n\n     LEFT or RIGHT ARROWS to increase or decrease difficulty. Enter to select";
        while(RUN)
        {
            if(kbhit())
            {
                input = _getch();
                if(input == BUFFER)
                    input = _getch();
                if(input == RIGHT && speed < 9)
                    ++speed;
                else if(input == LEFT && speed >1)
                    --speed;
                else if(input == ENTER)
                {
                    speed = 1000 - (speed * 100);
                    RUN = false;
                }
                system("CLS");
                i = 0,j = 0;
                while(i < speed)
                {
                gotoxy(30 + j, 9);
                cout<<counter<<" ";
                i += 1;
                j += 2;
                }
                cout<<"\n\n     LEFT or RIGHT ARROWS to increase or decrease difficulty. Enter to select";
            }
        }
    }

    void snake_game::key_press()
    {
        input = _getch();
        if(input == BUFFER)
            input = _getch();
        if(input == UP && body_seg_change_pos_y[0] != 1)
        {
            body_seg_change_pos_y[0] = -1;
            body_seg_change_pos_x[0] = 0;
        }
        if(input == DOWN && body_seg_change_pos_y[0] != -1)
        {
            body_seg_change_pos_y[0] = 1;
            body_seg_change_pos_x[0] = 0;
        }
        if(input == LEFT && body_seg_change_pos_x[0] != 1)
        {
            body_seg_change_pos_x[0] = -1;
            body_seg_change_pos_y[0] = 0;
        }
        if(input == RIGHT && body_seg_change_pos_x[0] != -1)
        {
            body_seg_change_pos_x[0] = 1;
            body_seg_change_pos_y[0] = 0;
        }
        if(input == ESC)
            RUN = false;
        if(input == ENTER)
        {
            system("CLS");
            gotoxy(25, 5);
            cout<<"PAUSED\n";
            system("PAUSE");
            system("CLS");
        }
    }

    void snake_game::generate_food()
    {
        if(food_x_cord == body_seg_x_cord[0] && food_y_cord == body_seg_y_cord[0])
        {
            while(RUN)
            {
                food_x_cord = rand() % (x_map_corner_right - 1) + (x_map_corner_left + 1);
                food_y_cord = rand() % (y_map_corner_bottom - 1) + (y_map_corner_top + 1);
                if(food_x_cord == x_map_corner_left || food_x_cord == x_map_corner_right || food_y_cord == y_map_corner_top || food_y_cord == y_map_corner_bottom)
                    continue;
                int i = 0;
                while(i < 100)
                {
                    if(body_seg_x_cord[i] == food_x_cord && body_seg_y_cord[i] == food_y_cord)
                        continue;
                    i++;
                }
                score++;
                body_seg[score - 1] = 'o';
                body_seg_x_cord[score] = body_seg_x_cord[score - 1];
                body_seg_y_cord[score] = body_seg_y_cord[score - 1] + 1;
                RUN = false;
            }
            RUN = true;
        }
        gotoxy(food_x_cord,food_y_cord);
        cout<<apple;
        gotoxy(x_map_corner_right + 5,9);
        cout<<"Score: "<<score;
    }

    void snake_game::update_highscore()
    {
        if(score > user.getHigh_score())
        {
            member temp;
            int pos;
            user.accessHigh_score(score);
            fstream file(Filename,ios::in|ios::out|ios::binary);
            if(file.is_open())
            {
                while(!file.eof())
                {
                    pos = file.tellg();
                    file.read((char *) &temp, sizeof(temp));
                    if(strcmpi(user.getName(), temp.getName()) == 0)
                    {
                        file.seekg(pos);
                        file.write((char *) &user, sizeof(user));
                        break;
                    }
                }
                file.close();
            }
            make_top_scores();
        }
    }

    void snake_game::update_membership()
    {
        member temp;
        int pos;
        fstream file(Filename,ios::in|ios::out|ios::binary);
        if(file.is_open())
            {
                while(!file.eof())
                {
                    pos = file.tellg();
                    file.read((char *) &temp, sizeof(temp));
                    if(strcmpi(user.getName(), temp.getName()) == 0)
                    {
                        file.seekg(pos);
                        file.write((char *) &user, sizeof(user));
                        break;
                    }
                }
                file.close();
            }
    }

    void snake_game::print_snake()
    {
        int i = 0;
        system("CLS");
        while(i<100)
            {
                body_seg[i] = ' ' ;
                body_seg_x_cord[i] = 18;
                body_seg_y_cord[i] = 10 + i;
                body_seg_change_pos_x[i] = 0;
                body_seg_change_pos_y[i] = -1;
                ++i;
            }
        score = 3;
        if(speed == 3)
            speed = 700;
        RUN = true;
        bool body_touch = false;
        i = 0;
        while(i < score)
        {
            body_seg[i] = 'o';
            i++;
        }
        while(RUN)
        {
            print_map();
            Sleep(speed);
            if(kbhit())
            {
                key_press();
            }
            i = 0;
            while(i <= score)
            {
                body_seg_x_cord[i] += body_seg_change_pos_x[i];
                body_seg_y_cord[i] += body_seg_change_pos_y[i];
                gotoxy(body_seg_x_cord[i],body_seg_y_cord[i]);
                cout<<body_seg[i];
                ++i;
            }
            i = 1;
            while(i < score)
            {
                if(body_seg_x_cord[0] == body_seg_x_cord[i] && body_seg_y_cord[0] == body_seg_y_cord[i])
                {
                    body_touch = true;
                    break;
                }
                ++i;
            }
            i = score;
            while(i > 0)
            {
                body_seg_change_pos_x[i] = body_seg_change_pos_x[i - 1];
                body_seg_change_pos_y[i] = body_seg_change_pos_y[i - 1];
                i--;
            }
            generate_food();
            if(body_seg_x_cord[0] == x_map_corner_left || body_seg_x_cord[0] == x_map_corner_right || body_seg_y_cord[0] == y_map_corner_bottom || body_seg_y_cord[0] == y_map_corner_top || body_touch)
            {
                RUN = false;
            }
        }
        i = 0;
        while(i < 10)
        {
            if(kbhit())
                {
                    if(_getch() == ENTER)
                        break;
                }
                Sleep(100);
                system("CLS");
                gotoxy(30,20 - i);
                cout<<"GAMEOVER!!";
                gotoxy(30,20 - i + 1);
                cout<<"SCORE: "<<score;
                i++;
            }
            system("CLS");
            gotoxy(30,20 - i);
            cout<<"GAMEOVER!!";
            gotoxy(30,20 - i + 1);
            cout<<"SCORE: "<<score;
            gotoxy(30,20 - i + 2);
            cout<<"NAME:"<<user.getName();
            gotoxy(30,20 - i + 3);
            system("PAUSE");
            if(user.getRem_days() > 0)
                user.putRem_days();
            if(user.getRem_days() == 0)
                user.putMem();
            update_highscore();
            update_membership();
            display_top_scores();
    }

    void snake_game::game_menu()
    {
        srand(0);
        make_top_scores();
        system("CLS");
        RUN = true;
        cout<<"/****SNAKE****/\n\n";
        cout<<"*Start Game\n";
        cout<<"*Difficulty\n";
        cout<<"*High-score\n";
        cout<<"*Exit\n\n";
        cout<<"Press UP or DOWN to navigate and ENTER to select\n\n";
        cout<<"/*HELP*/\n\n";
        cout<<"*Use ARROW KEYS or W,A,S,D to move the snake.\n";
        cout<<"*ESC to exit into menu.\n";
        cout<<"*ENTER to pause the game.\n";
        if(user.getRem_days() == 0)
            cout<<"\n\n**You have zero tries left!! Contact ADMIN**";
        else
            cout<<"\n\n**You have "<<user.getRem_days()<<" game(s) left**";
        gotoxy(13,y);
        cout<<"<-";
        while(RUN)
        {
            if(kbhit())
            {
                input = _getch();
                if(input == BUFFER)
                    input = _getch();
                if(input == UP)
                {
                    if(y == 2)
                        y = 5;
                    else
                        y = y - 1;
                }
                else if(input == DOWN)
                {
                    if(y == 5)
                        y = 2;
                    else
                        y = y + 1;
                }
                else if(input == ENTER)
                {
                    switch(y)
                    {
                    case 2:
                        if(user.getMem() == true)
                            print_snake();
                        else
                        {
                            system("CLS");
                            cout<<"NOT A MEMBER\n";
                            system("PAUSE");
                        }
                        RUN = true;
                        break;
                    case 3:
                        change_speed();
                        RUN = true;
                        break;
                    case 4:
                        display_top_scores();
                        RUN = true;
                        break;
                    case 5:
                        system("CLS");
                        exit(0);
                    }
                }
                system("CLS");
                cout<<"/****SNAKE****/\n\n";
                cout<<"*Start Game\n";
                cout<<"*Difficulty\n";
                cout<<"*High-score\n";
                cout<<"*Exit\n\n";
                cout<<"Press UP or DOWN to navigate and ENTER to select\n\n";
                cout<<"/*HELP*/\n\n";
                cout<<"*Use ARROW KEYS or W,A,S,D to move the snake.\n";
                cout<<"*ESC to exit into menu.\n";
                cout<<"*ENTER to pause the game.\n";
                if(user.getRem_days() == 0)
                    cout<<"\n\n**You have zero tries left!! Contact ADMIN**";
                else
                    cout<<"\n\n**You have "<<user.getRem_days()<<" game(s) left**";
                gotoxy(13,y);
                cout<<"<-";
            }
        }
    }
    /****************************************************/
    /**< First menu >**/
    void menu()
    {
        member user;
        root admin;
        while(user.getrunning() == 0)
        {
            user.read();
            snake_game player(user);
            switch(user.getrunning())
            {
            case 0:
                system("CLS");
                gotoxy(20,9);
                cout<<" Incorrect username or password";
                break;
            case 1:
                admin.access();
                break;
            case 2:
                player.game_menu();
                break;
            }
        }
    }
    /****************************************************/
    int main()
    {
        menu();
        return 0;
    }
