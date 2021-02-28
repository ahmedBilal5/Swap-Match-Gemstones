#ifndef MENU_H
#define MENU_H

class Menu{
        bool hintOption;
        bool pauseOption;
        int menuControl;
        /*bool newGameOp;
        bool helpOp;
        bool highScoreOP;
        bool exitOp;*/
        public:
                Menu();
                void setHintOption(bool h);
                bool getHintOption();
                /*void setNewGameOp(bool h);
                bool getNewGameOp();
                void setHelpOp(bool h);
                bool getHelpOp();*/
                void setPauseOption(bool h);
                bool getPauseOption();
                /*void setHighScoreOp(bool h);
                bool getHighScoreOp();
                void setExitOP(bool h);
                bool getExitOp();*/
                void setMenuControl(int);
                int getMenuControl();
                
};
#endif
