#pragma once

#include <string>
#include <vector>
class User
{
public:
    User(int id);
    ~User();
    int getId();
    void setId(int id);

    int getHp();
    void setHp(int hp);
    int getMp();
    void setMp(int mp);
    std::string getAbout();
    void setAbout(std::string about);
    std::string getPhilosophy();
    void setPhilosophy(std::string philosophy);
    std::string getName();
    std::string getPassword();
    std::string getAddress();
    int getMoney();
    void setMoney(int money);
    int getPoints();
    void setPoints(int points);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getCamX();
    void setCamX(int camx);
    int getCamY();
    void setCamY(int camy);
    int getLevel();
    void setLevel(int level);
    int getNextLevelXp();
    void setNextLevelXp(int xp);
    int getXp();
    void setXp(int xp);
    std::string about();
    std::string getAll(int id);
    std::string getAll(std::string colName);
    std::string update(int col, std::string newdata);
    void  updateAll(std::string colName, std::string newdata);
    int getUserProfile();
    void setProfile(int fileId);
    int getUserCover();
    void setCover(int fileId);
    bool hasDirectory();
    std::string getDirectory();
    void setDirectory();
    bool checkId();
private:
    void updateDatas();
    std::string m_filename;
    std::string m_data;
    std::vector<std::string> m_datas;
    int m_id;
};
