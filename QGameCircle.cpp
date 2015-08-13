
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
    
    s3eGameCircleStatus status = (s3eGameCircleStatus)systemData;
    switch(status)
    {
        case S3E_GAMECIRCLE_INITIALIZING:
            LUA_EVENT_SET_STRING("status", "initializing");
            break;
        case S3E_GAMECIRCLE_CANNOT_INITIALIZE:
            LUA_EVENT_SET_STRING("status", "cannotInitialize");
            break;
        case S3E_GAMECIRCLE_SERVICE_CONNECTED:
            LUA_EVENT_SET_STRING("status", "connected");
            break;
        case S3E_GAMECIRCLE_NOT_AUTHORIZED:
            LUA_EVENT_SET_STRING("status", "notAuthorized");
            break;
        case S3E_GAMECIRCLE_NOT_AUTHENTICATED:
        default:
            LUA_EVENT_SET_STRING("status", "notAuthenticated");
            break;
    }
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 PlayerAliasCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "playerAlias");
    LUA_EVENT_SET_STRING("alias", (char*)systemData);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 PlayerIdCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "playerId");
    LUA_EVENT_SET_STRING("id", (char*)systemData);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementsOverlayCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "achievementsOverlay");
    LUA_EVENT_SET_BOOLEAN("success", (s3eResult)systemData == S3E_RESULT_SUCCESS ? true : false);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 AchievementUpdateProgressCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "achievementUpdateProgress");
    s3eGameCircleAchievementUpdateResult* result = (s3eGameCircleAchievementUpdateResult*)systemData;
    LUA_EVENT_SET_BOOLEAN("success", result->m_Result == S3E_RESULT_SUCCESS ? true : false);
    LUA_EVENT_SET_BOOLEAN("newlyUnlocked", result->m_NewlyUnlocked);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// I've made the values match QGooglePlayServices equivalents where possible
// for easier porting and to make it easier for you to switch to some mediation
// layer when I get around to building one...
int32 GetAchievementsCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "achievementsLoaded");
    
    s3eGameCircleAchievementList* achs = (s3eGameCircleAchievementList*)systemData;
    
    LUA_EVENT_SET_INTEGER("count", achs->m_Count);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 0; t < achs->m_Count; t++)
    {
        s3eGameCircleAchievement *ach = achs->m_AchievementsList + t;
        
        LUA_EVENT_START_TABLE();
        
        LUA_EVENT_SET_STRING("id", ach->m_ID); //also in google play
        LUA_EVENT_SET_STRING("name", ach->m_Title); //also in google play
        LUA_EVENT_SET_STRING("description", ach->m_Description); //also in google play
        
        // Game circle presents unlocked and hidden separately.
        LUA_EVENT_SET_INTEGER("hidden", ach->m_Hidden); //game circle only
        LUA_EVENT_SET_BOOLEAN("unlocked", ach->m_Unlocked); //game circle only
        
        // Also setting a "status" value from those to match Google API.
        const char* achStatus;
        if (ach->m_Unlocked)
            achStatus = "unlocked";
        else if (!ach->m_Hidden)
            achStatus = "revealed";
        else
            achStatus = "hidden";
        
        LUA_EVENT_SET_STRING("status", achStatus);
       
        LUA_EVENT_SET_NUMBER("progress", ach->m_Position); //game circle only. Can be used to display achievements in a preferred order
        
        LUA_EVENT_SET_NUMBER("pointValue", ach->m_PointValue); //game circle only. Google does have points but not in the API...
        LUA_EVENT_SET_INTEGER("progress", ach->m_Progress); // 0.0->100.0. //game circle only in native API, but QGooglePlayServices mimics this
        
        LUA_EVENT_SET_STRING("description", ach->m_DateUnlocked;); //game circle only (google has similar but not "lastUpdate" integer)
        
        LUA_EVENT_SET_STRING("imageUrl", ach->m_ImageURL); //game circle only
        
        LUA_EVENT_END_AND_INDEX_TABLE(t+1); //Lua arrays start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("achievements");
    
    int   m_PointValue;
    float m_Progress;
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// Getting a list of all the boards with no score details. Not supported by Google Play.
int32 GetLeaderboardsCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "getLeaderboards");
    
    s3eGameCircleLeaderboardList* boards = (s3eGameCircleLeaderboardList*)systemData;
    
    LUA_EVENT_SET_INTEGER("count", boards->m_Count);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 0; t < boards->m_Count; t++)
    {
        s3eGameCircleLeaderboard *board = boards->m_LeaderboardsList + t;
        
        LUA_EVENT_START_TABLE();
        
        LUA_EVENT_SET_STRING("id", board->m_ID);
        LUA_EVENT_SET_STRING("name", board->m_Name);
        LUA_EVENT_SET_STRING("displayText", board->m_DisplayText);
        LUA_EVENT_SET_STRING("imageURL", board->m_ImageURL);
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("leaderboards");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LeaderboardOverlayCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "leaderboardOverlay");
    LUA_EVENT_SET_BOOLEAN("success", (s3eResult)systemData == S3E_RESULT_SUCCESS ? true : false);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LeaderboardSubmitScoreCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "leaderboardSubmitScore");
    
    s3eGameCircleLeaderboardSubmitScoreResponse* response = (s3eGameCircleLeaderboardSubmitScoreResponse*)systemData;
    
    LUA_EVENT_START_TABLE();
    
    LUA_EVENT_START_TABLE();
    LUA_EVENT_SET_BOOLEAN("rankImproved", response->m_RankImproved[S3E_GAMECIRCLE_FILTER_FRIENDS_ALL_TIME]);
    LUA_EVENT_SET_INTEGER("rank", response->m_Rank[S3E_GAMECIRCLE_FILTER_FRIENDS_ALL_TIME]
    LUA_EVENT_END_AND_NAME_TABLE("friendsAllTime");
    
    LUA_EVENT_START_TABLE();
    LUA_EVENT_SET_BOOLEAN("rankImproved", response->m_RankImproved[S3E_GAMECIRCLE_FILTER_GLOBAL_ALL_TIME]);
    LUA_EVENT_SET_INTEGER("rank", response->m_Rank[S3E_GAMECIRCLE_FILTER_GLOBAL_ALL_TIME]
    LUA_EVENT_END_AND_NAME_TABLE("globalAllTime");
    
    LUA_EVENT_START_TABLE();
    LUA_EVENT_SET_BOOLEAN("rankImproved", response->m_RankImproved[S3E_GAMECIRCLE_FILTER_GLOBAL_DAY]);
    LUA_EVENT_SET_INTEGER("rank", response->m_Rank[S3E_GAMECIRCLE_FILTER_GLOBAL_DAY]
    LUA_EVENT_END_AND_NAME_TABLE("globalDay");
    
    LUA_EVENT_START_TABLE();
    LUA_EVENT_SET_BOOLEAN("rankImproved", response->m_RankImproved[S3E_GAMECIRCLE_FILTER_GLOBAL_WEEK]);
    LUA_EVENT_SET_INTEGER("rank", response->m_Rank[S3E_GAMECIRCLE_FILTER_GLOBAL_WEEK]
    LUA_EVENT_END_AND_NAME_TABLE("GlobalWeek");
    
    LUA_EVENT_END_AND_NAME_TABLE("response");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// Used by anything that sets a set of score data. Note that as we just push
// values to a stack this function doesn't need any context of where it's
// called from
void PushScoreToLuaEvent(s3eGameCircleLeaderboardScore* sc)
{
    LUA_EVENT_SET_INTEGER("rank", sc->m_Rank); //NB: number in GC vs string in Google Play
    LUA_EVENT_SET_INTEGER("score", (int)sc->m_Score); //also in google play
    LUA_EVENT_SET_STRING("playerAlias", sc->m_PlayerAlias);
    LUA_EVENT_SET_STRING("name", sc->m_PlayerAlias); //to match google play equivalent
}

int32 AllScoresCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "allScores");
    
    s3eGameCircleLeaderboardScores* boards = (s3eGameCircleLeaderboardScores*)systemData;
    
    LUA_EVENT_SET_INTEGER("count", boards->m_NumScores);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 0; t < boards->m_NumScores; t++)
    {
        s3eGameCircleLeaderboardScore *board = boards->m_Scores + t;
        
        LUA_EVENT_START_TABLE();
        LUA_EVENT_SET_INTEGER("score", board->m_Score);
        LUA_EVENT_SET_INTEGER("rank", board->m_Rank);
        LUA_EVENT_SET_STRING("playerAlias", board->m_PlayerAlias);
        LUA_EVENT_END_AND_INDEX_TABLE(t+1); //lua indices start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("scores");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 LocalPlayerScoreCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "localPlayerScore");
    
    s3eGameCircleLeaderboardLocalPlayerScore* score = (s3eGameCircleLeaderboardLocalPlayerScore*)systemData;
    
    LUA_EVENT_SET_INTEGER("score", score->m_Score);
    LUA_EVENT_SET_INTEGER("score", rank->m_Rank); //note that rank is a string in Google but int in Amazon
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

// ---- WhisperSync callbacks ----

int32 WhispersyncStatusCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncStatus");

    s3eGameCircleWhispersyncStatus* status = (s3eGameCircleWhispersyncStatus*)systemData;

    switch (*status)
    {
    case S3E_WHISPERSYNC_DISK_WRITE_COMPLETE:
        LUA_EVENT_SET_STRING("status", "whispersyncDataUploadedToCloud");
        break;
    case S3E_WHISPERSYNC_FIRST_SYNCHRONIZE:
        LUA_EVENT_SET_STRING("status", "whispersyncFirstSynchronized");
        break;
    case S3E_WHISPERSYNC_NEW_CLOUD_DATA:
        LUA_EVENT_SET_STRING("status", "whispersyncNewCloudData");
        break;
    case S3E_WHISPERSYNC_THROTTLED:
        LUA_EVENT_SET_STRING("status", "whispersyncThrottled");
        break;
    case S3E_WHISPERSYNC_NOT_INITIALIZED:
        LUA_EVENT_SET_STRING("status", "whispersyncNotInitialized");
        break;
    }
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 WhispersyncKeysCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncKeys");
    
    s3eGameCircleGameDataMapKeys* keys = (s3eGameCircleGameDataMapKeys*)systemData;
    
    LUA_EVENT_SET_INTEGER("count", keys->m_Count);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 1; t <= keys->m_Count; t++)
    {
        LUA_EVENT_SET_STRING_AT_INDEX(t+1, keys->m_Keys + t) //lua indices start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("keys");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 WhispersyncDataListCallback(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("gameCircle");
    LUA_EVENT_SET_STRING("type", "whispersyncDataList");
    
    s3eGameCircleWhispersyncDataList* dataList = (s3eGameCircleWhispersyncDataList*)systemData;

    LUA_EVENT_SET_INTEGER("count", dataList->m_Count);
    
    char* mapType;
    switch(dataList->m_Type)
    {
    case S3E_GAMEDATA_ACCUMULATING_NUMBER:
        mapType = "accumulatingNumber"
        break;
    case S3E_GAMEDATA_HIGHEST_NUMBER:
         = "highestNumber"
        break;
    case S3E_GAMEDATA_HIGH_NUMBER_LIST:
        mapType = "highNumberList"
        break;
    case S3E_GAMEDATA_LATEST_NUMBER:
        mapType = "latestNumber"
        break;
    case S3E_GAMEDATA_LATEST_NUMBER_LIST:
        mapType = "latestNumberList"
        break;
    case S3E_GAMEDATA_LATEST_STRING:
        mapType = "latestString"
        break;
    case S3E_GAMEDATA_LATEST_STRING_LIST:
        mapType = "latestStrinmapTypegList"
        break;
    case S3E_GAMEDATA_LOW_NUMBER_LIST:
        mapType = "lowNumberList"
        break;
    case S3E_GAMEDATA_LOWEST_NUMBER:
        mapType = "lowestNumber"
        break;
    case S3E_GAMEDATA_STRING_SET:
        mapType = "stringSet"
        break;
    }
    LUA_EVENT_SET_STRING("dataType", mapType);
    
    LUA_EVENT_START_TABLE();
    
    for (int t = 1; t <= keys->m_Count; t++)
    {
        //TODO: type depends on dataList->m_Type. Need to find out what these are all meant to be...
        //void*  m_Items;
        //LUA_EVENT_SET_STRING_AT_INDEX(t+1, keys->m_Items + t) //lua indices start at 1
    }
    
    LUA_EVENT_END_AND_NAME_TABLE("items");
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

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

bool getFilterEnum(const char* prop, s3eGameCircleLeaderboardFilter* propEnum)
{
    if (strcmp(prop, "accumulatingNumber") == 0)
        *propEnum = S3E_GAMECIRCLE_FILTER_FRIENDS_ALL_TIME;
    else if (strcmp(prop, "highestNumber") == 0)
        *propEnum = S3E_GAMECIRCLE_FILTER_GLOBAL_ALL_TIME;
    else if (strcmp(prop, "highNumberList") == 0)
        *propEnum = S3E_GAMECIRCLE_FILTER_GLOBAL_DAY;
    else if (strcmp(prop, "latestNumber") == 0)
        *propEnum = S3E_GAMECIRCLE_FILTER_GLOBAL_week;
    else
    {
        IW_TRACE(Q_GAME_CIRCLE, ("Invalid filter type: %s", prop))
        return false;
    }
    return true;
}

void getScores(const char* leaderboardID, const char* filter)
{
    s3eGameCircleLeaderboardFilter filterEnum;
    
    if (getDataMapTypeEnum(type, &filterEnum) == false)
        return;
    
    s3eGameCircleGetScores(leaderboardID, filterEnum);
}

void getLocalPlayerScore(const char* leaderboardID, const char* filter)
{
    s3eGameCircleLeaderboardFilter filterEnum;
    
    if (getDataMapTypeEnum(type, &filterEnum) == false)
        return;
    
    s3eGameCircleGetLocalPlayerScore(leaderboardID, filterEnum);
}

void whispersyncFlush()
{
    s3eGameCircleWhispersyncFlush();
}

void whispersyncSynchronize()
{
    s3eGameCircleWhispersyncSynchronize();
}

bool getDataMapTypeEnum(const char* prop, s3eGameCircleGameDataMapType* propEnum)
{
    if (strcmp(prop, "accumulatingNumber") == 0)
        *propEnum = S3E_GAMEDATA_ACCUMULATING_NUMBER;
    else if (strcmp(prop, "highestNumber") == 0)
        *propEnum = S3E_GAMEDATA_HIGHEST_NUMBER;
    else if (strcmp(prop, "highNumberList") == 0)
        *propEnum = S3E_GAMEDATA_HIGH_NUMBER_LIST;
    else if (strcmp(prop, "latestNumber") == 0)
        *propEnum = S3E_GAMEDATA_LATEST_NUMBER;
    else if (strcmp(prop, "latestNumberList") == 0)
        *propEnum = S3E_GAMEDATA_LATEST_NUMBER_LIST;
    else if (strcmp(prop, "latestString") == 0)
        *propEnum = S3E_GAMEDATA_LATEST_STRING;
    else if (strcmp(prop, "latestStringList") == 0)
        *propEnum = S3E_GAMEDATA_LATEST_STRING_LIST;
    else if (strcmp(prop, "lowNumberList") == 0)
        *propEnum = S3E_GAMEDATA_LOW_NUMBER_LIST;
    else if (strcmp(prop, "lowestNumber") == 0)
        *propEnum = S3E_GAMEDATA_LOWEST_NUMBER;
    else if (strcmp(prop, "stringSet") == 0)
        *propEnum = S3E_GAMEDATA_STRING_SET;
    else
    {
        IW_TRACE(Q_GAME_CIRCLE, ("Invalid key type: %s", prop))
        return false;
    }
    return true;
}

void whispersyncGetKeys(const char* type)
{
    //Input is a string currently... prob want to just make these all numbers
    // like gameCircle.accumulatingNumber = S3E_GAMEDATA_ACCUMULATING_NUMBER
    // Prob should make the wrapper generator do that!
    s3eGameCircleGameDataMapType propEnum;
    
    if (getDataMapTypeEnum(type, &propEnum) == false)
        return;
    
    s3eGameCircleWhispersyncGetKeys(propEnum);
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
