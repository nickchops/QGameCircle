
#include "QGameCircle.h"
#include "s3eGameCircle.h"
#include "QLuaHelpers.h"
#include "lua.h"

using namespace quick;

namespace gameCircle {

//------------------------------------------------------------------------------
//C++ callbacks -> Lua events:

int32 InitializationCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "initialization");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 PlayerAliasCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "playerAlias");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 PlayerIdCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "playerId");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementsOverlayCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "achievementsOverlay");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementUpdateProgressCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "achievementUpdateProgress");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 GetAchievementsCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "getAchievements");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 GetLeaderboardsCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "getLeaderboards");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LeaderboardOverlayCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "leaderboardOverlay");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LeaderboardSubmitScoreCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "leaderboardSubmitScore");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AllScoresCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "allScores");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LocalPlayerScoreCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "localPlayerScore");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 *  for handling responses to whispersyncflush()Callback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "*  for handling responses to whispersyncflush()");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 WhispersyncStatusCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncStatus");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 WhispersyncKeysCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncKeys");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 WhispersyncDataListCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncDataList");
    //LUA_EVENT_SET_BOOLEAN("???", ???);
    //LUA_EVENT_SET_STRING("???", ???);
    //LUA_EVENT_SET_INTEGER("???", ???);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

//------------------------------------------------------------------------------
//Functions:

bool isAvailable()
{
    return (bool)s3eGameCircleAvailable();
}

void init(bool useAchievements, bool useLeaderboards, bool useWhispersync)
{
    //Register all callbacks here:
    s3eGameCircleRegister(S3E_GAMECIRCLE_INITIALIZATION, InitializationCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_PLAYER_ALIAS, PlayerAliasCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_PLAYER_ID, PlayerIdCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_ACHIEVEMENTS_OVERLAY, AchievementsOverlayCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_ACHIEVEMENT_UPDATE_PROGRESS, AchievementUpdateProgressCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_GET_ACHIEVEMENTS, GetAchievementsCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_GET_LEADERBOARDS, GetLeaderboardsCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_LEADERBOARD_OVERLAY, LeaderboardOverlayCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_LEADERBOARD_SUBMIT_SCORE, LeaderboardSubmitScoreCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_ALL_SCORES, AllScoresCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_LOCAL_PLAYER_SCORE, LocalPlayerScoreCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_WHISPERSYNC_STATUS, WhispersyncStatusCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_WHISPERSYNC_KEYS, WhispersyncKeysCallback, NULL);
    s3eGameCircleRegister(S3E_GAMECIRCLE_WHISPERSYNC_DATA_LIST, WhispersyncDataListCallback, NULL);

    int requestedFeatures = 0;
    if (useAchievements) requestedFeatures = S3E_GAMECIRCLE_ACHIEVEMENTS;
    if (useLeaderboards) requestedFeatures = requestedFeatures | S3E_GAMECIRCLE_ACHIEVEMENTS;
    if (useWhispersync) requestedFeatures = requestedFeatures | S3E_GAMECIRCLE_ACHIEVEMENTS;
    
    s3eGameCircleInitialize(requestedFeatures);
}

void terminate()
{
    //Un-register all callbacks here:
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_INITIALIZATION, InitializationCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_PLAYER_ALIAS, PlayerAliasCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_PLAYER_ID, PlayerIdCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_ACHIEVEMENTS_OVERLAY, AchievementsOverlayCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_ACHIEVEMENT_UPDATE_PROGRESS, AchievementUpdateProgressCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_GET_ACHIEVEMENTS, GetAchievementsCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_GET_LEADERBOARDS, GetLeaderboardsCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_LEADERBOARD_OVERLAY, LeaderboardOverlayCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_LEADERBOARD_SUBMIT_SCORE, LeaderboardSubmitScoreCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_ALL_SCORES, AllScoresCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_LOCAL_PLAYER_SCORE, LocalPlayerScoreCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_WHISPERSYNC_STATUS, WhispersyncStatusCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_WHISPERSYNC_KEYS, WhispersyncKeysCallback);
    s3eGameCircleUnRegister(S3E_GAMECIRCLE_WHISPERSYNC_DATA_LIST, WhispersyncDataListCallback);

    s3eGameCircleTerminate();
}

bool isReady()
{
    return s3eGameCircleIsReady();
}

void showSignInPage()
{
    s3eGameCircleShowSignInPage();
}

void getPlayerAlias()
{
    s3eGameCircleGetPlayerAlias();
}

void getPlayerID()
{
    s3eGameCircleGetPlayerID();
}

void showAchievementsOverlay()
{
    s3eGameCircleShowAchievementsOverlay();
}

void updateAchievementProgress(const char* achievementID, int percentComplete)
{
    s3eGameCircleUpdateAchievementProgress(achievementID, percentComplete);
}

void getAllAchievements()
{
    s3eGameCircleGetAllAchievements();
}

void getAchievement(const char* achievementID)
{
    s3eGameCircleGetAchievement(achievementID);
}

void setPopUpLocation(const char* location)
{
    s3eGameCircleSetPopUpLocation(location);
}

void showLeaderboardOverlay(const char* leaderboardID)
{
    s3eGameCircleShowLeaderboardOverlay(leaderboardID);
}

void getLeaderboardsList()
{
    s3eGameCircleGetLeaderboardsList();
}

void submitScore(const char* leaderboardID, int score)
{
    s3eGameCircleSubmitScore(leaderboardID, score);
}

void getScores(const char* leaderboardID, const char* filter)
{
    s3eGameCircleGetScores(leaderboardID, filter);
}

void getLocalPlayerScore(const char* leaderboardID, const char* filter)
{
    s3eGameCircleGetLocalPlayerScore(leaderboardID, filter);
}

void whispersyncFlush()
{
    s3eGameCircleWhispersyncFlush();
}

void whispersyncSynchronize()
{
    s3eGameCircleWhispersyncSynchronize();
}

void whispersyncGetKeys(const char* type)
{
    s3eGameCircleWhispersyncGetKeys(type);
}

void whispersyncSetAccumulatingNumber(const char* name, double* delta)
{
    s3eGameCircleWhispersyncSetAccumulatingNumber(name, delta);
}

void whispersyncSetHighestNumber(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetHighestNumber(name, value);
}

void whispersyncSetHighNumberList(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetHighNumberList(name, value);
}

void whispersyncSetLatestNumber(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetLatestNumber(name, value);
}

void whispersyncSetLatestNumberList(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetLatestNumberList(name, value);
}

void whispersyncSetLatestString(const char* name, const char* value)
{
    s3eGameCircleWhispersyncSetLatestString(name, value);
}

void whispersyncSetLatestStringList(const char* name, const char* value)
{
    s3eGameCircleWhispersyncSetLatestStringList(name, value);
}

void whispersyncSetLowestNumber(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetLowestNumber(name, value);
}

void whispersyncSetLowNumberList(const char* name, double* value)
{
    s3eGameCircleWhispersyncSetLowNumberList(name, value);
}

void whispersyncSetStringSet(const char* name, const char* value)
{
    s3eGameCircleWhispersyncSetStringSet(name, value);
}

double whispersyncGetAccumulatingNumber(const char* name)
{
    return s3eGameCircleWhispersyncGetAccumulatingNumber(name);
}

double whispersyncGetHighestNumber(const char* name)
{
    return s3eGameCircleWhispersyncGetHighestNumber(name);
}

double whispersyncGetLatestNumber(const char* name)
{
    return s3eGameCircleWhispersyncGetLatestNumber(name);
}

const char* whispersyncGetLatestString(const char* name)
{
    return s3eGameCircleWhispersyncGetLatestString(name);
}

double whispersyncGetLowestNumber(const char* name)
{
    return s3eGameCircleWhispersyncGetLowestNumber(name);
}

void whispersyncGetHighNumberList(const char* name)
{
    s3eGameCircleWhispersyncGetHighNumberList(name);
}

void whispersyncGetLatestNumberList(const char* name)
{
    s3eGameCircleWhispersyncGetLatestNumberList(name);
}

void whispersyncGetLatestStringList(const char* name)
{
    s3eGameCircleWhispersyncGetLatestStringList(name);
}

void whispersyncGetLowNumberList(const char* name)
{
    s3eGameCircleWhispersyncGetLowNumberList(name);
}

void whispersyncGetStringSet(const char* name)
{
    s3eGameCircleWhispersyncGetStringSet(name);
}

} //namespace gameCircle
