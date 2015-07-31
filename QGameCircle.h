
#ifndef __QGAMECIRCLE_H
#define __QGAMECIRCLE_H

// tolua_begin

namespace gameCircle {

    bool isAvailable();
    void init(bool useAchievements, bool useLeaderboards, bool useWhispersync);
    void terminate();
    bool isReady();
    void showSignInPage();
    void getPlayerAlias();
    void getPlayerID();
    void showAchievementsOverlay();
    void updateAchievementProgress(const char* achievementID, int percentComplete);
    void getAllAchievements();
    void getAchievement(const char* achievementID);
    void setPopUpLocation(const char* location);
    void showLeaderboardOverlay(const char* leaderboardID);
    void getLeaderboardsList();
    void submitScore(const char* leaderboardID, int score);
    void getScores(const char* leaderboardID, const char* filter);
    void getLocalPlayerScore(const char* leaderboardID, const char* filter);
    void whispersyncFlush();
    void whispersyncSynchronize();
    void whispersyncGetKeys(const char* type);
    void whispersyncSetAccumulatingNumber(const char* name, double* delta);
    void whispersyncSetHighestNumber(const char* name, double* value);
    void whispersyncSetHighNumberList(const char* name, double* value);
    void whispersyncSetLatestNumber(const char* name, double* value);
    void whispersyncSetLatestNumberList(const char* name, double* value);
    void whispersyncSetLatestString(const char* name, const char* value);
    void whispersyncSetLatestStringList(const char* name, const char* value);
    void whispersyncSetLowestNumber(const char* name, double* value);
    void whispersyncSetLowNumberList(const char* name, double* value);
    void whispersyncSetStringSet(const char* name, const char* value);
    double whispersyncGetAccumulatingNumber(const char* name);
    double whispersyncGetHighestNumber(const char* name);
    double whispersyncGetLatestNumber(const char* name);
    char* whispersyncGetLatestString(const char* name);
    double whispersyncGetLowestNumber(const char* name);
    void whispersyncGetHighNumberList(const char* name);
    void whispersyncGetLatestNumberList(const char* name);
    void whispersyncGetLatestStringList(const char* name);
    void whispersyncGetLowNumberList(const char* name);
    void whispersyncGetStringSet(const char* name);
    
} //namespace gameCircle

// tolua_end

#endif // QGAMECIRCLE_H
