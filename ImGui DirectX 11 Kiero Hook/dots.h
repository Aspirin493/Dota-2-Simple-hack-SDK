// dllmain.cpp : Defines the entry point for the DLL application.

#pragma once
///////////////////////////////////////////
//////////////// Defines   //////////////
///////////////////////////////////////////

#define ui unsigned long long
#define cc const char*
#define u64 ui
#pragma once
#define _int64 long long
#define n2hex(x) (n2hexstr(x).c_str())
#define InRange(x, a, b) (x >= a && x <= b)
#define getBit(x) (InRange((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (InRange(x, '0', '9') ? x - '0': 0))
#define getByte(x) (getBit(x[0]) << 4 | getBit(x[1]))
#define VT_METHOD(region, index) (*(ui*)(*(ui*)region + index * 8))
#define Colors(r,g,b) (\(u32)r |\(u32)(g << 8) | \(u32)(b << 16) | \(u32)(255 << 24)\)

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900


///////////////////////////////////////////
//////////////// Includes    //////////////
///////////////////////////////////////////


#include "logger.h"

#include <ctime>
#include <string>
#include <Psapi.h>
#include <iostream>
#include "vector.h"
#include <algorithm>
#include <vector>
#include <array>
#include <ctime>
#include <chrono>
#include <thread>
#include <queue>
#include <set>
#include "prototypes.h"

#include <stdint.h>
 ////////////////////////////////////////////////////
///////////// Globals //////////////////////////////
////////////////////////////////////////////////////




u64 GetStatePointer;

int temp;
int LocalPlayerIndex = 0;
int LocalPlayerTeam = 0;
int heroescount = 0;
std::set<CBaseEntity*>Hero;
CBaseEntity* Heroes[10] = { 0,0,0,0,0,0,0,0,0,0 };

std::set<CBaseEntity*> Entities; //// Heroes, Illusions , etc.
std::set<CBaseEntity*> AllEntities; //// All new created entities
std::set<CDOTA_Ability*> Abilities;

DrawManaData ManaDraw[5];

Enemy Enemies[5];

int state = 0;
int heroesInArray = 0;
bool Init = 0;
int count = 0;
bool hooked = 0;
float tempfloat = 0;

Matrix WorldMatrix;
u64 RenderSystemPtr;
u64 OrigFunc;
CGameEntitySystem* EntSystem;
u64 Panorama2;
Panorama* panoramaptr;
u64 RenderSystem;
u64 RenderSystemobj;

bool InGame = 0;
bool VMTBegin = 0;
bool gotheroes = 0;
int Red = 0xFF0000FF; // RGBA  ABGR
int Green = 0xFF00FF00;
ui tempOnAddEntity, tempRunFrame;
int highestindex = 0;

bool gotent = 0;
CBaseEntity* localent = nullptr;
u64 Schema;
u64 m_iHealth, m_iMaxHealth, m_flMana, m_flMaxMana, m_iCurrentLevel, m_hAbilities, m_lifeState, m_hReplicatingOtherHeroModel, m_iTeamNum, m_hOwnerEntity, m_clrRender,
m_iGlowType, m_glowColorOverride, a_m_iLevel, a_m_iManaCost, a_m_flCooldownLength, a_m_fCooldown, a_m_bHidden, m_Glow, m_iHealthBarOffset,
m_pGameSceneNode, m_vecAbsOrigin, m_fGameTime, m_nGameState, m_iTaggedAsVisibleByTeam, m_bDormant;



bool one = 0;
bool once = 0;
int counter_dev = 0;
int counter = 0;
Particle* particle1;
Particle* particle2;
Particle* particle0;
FVector mypos;
FVector2 myposscreen;
bool once2 = 0;
bool lplayer = 0;




// Globals:script

bool zeus;
bool axe;
bool pudge;
bool heroscript = 0;
int zuus_counter = 0;
int pudge_counter = 0;
int zuus_blowcounter = 1;
float pudge_hookrange = 1300;
float axe_ultirange = 150;
CDOTA_Ability* Ultimate = nullptr;




////////////////////////////////////////////////////
///////////// Classes //////////////////////
////////////////////////////////////////////////////



class CGameEntitySystem;
class CEntityInstance;
class CBaseEntity;
class C_DOTAPlayer;
class CDOTA_Ability;
class CEntityIdentities;
class EntityIdentityList;
class CEntitySystem;
class MemberInfo;
class ClassDescription;








class CEntityInstance
{
public:
    CBaseEntity* entity;//00
    void* baseinfo;//8
    int64_t handle;//1
    int64_t unk1;//1
    const char* internalName;//18
    const char* entityName;//20
    void* unk2;
    void* unk3;
    void* unk4;
    void* unk5;
    CEntityInstance* PrevEnt; // 0x50
    CEntityInstance* NextEnt; // 0x58
    void* unkptr;
    void* unkptr2;
    void* unkptr3;

    cc GetName()
    {
        cc name;
        if (this->internalName)
        {
            name = this->internalName;
            return name;

        }
        else
        {
            if (this->entityName)
            {
                name = this->entityName;
                return name;
            }
            else
            {
                name = "Unknown";
                return name;
            }
        }
    }
    cc GetBaseClass()
    {
        if (!***(cc***)((ui)this + 0x8))
        {
            return "unknown";
        }
        return ***(cc***)((ui)this + 0x8);
    }
    bool IsHero()
    {
        if (!strcmp("C_DOTA_BaseNPC_Hero", GetBaseClass())) // 0 means identical
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};





#define EntityHandle unsigned int
#define MAX_ENTITIES_IN_LIST 512
#define MAX_ENTITY_LISTS 64
#define MAX_TOTAL_ENTITIES MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS





class CEntityIdentities
{
public:
    CEntityInstance m_pIdentities[MAX_ENTITIES_IN_LIST];
};


class EntityIdentityList
{
public:
    CEntityIdentities* m_pIdentityList;
};


#define ClearEntityDatabaseMode_t char
#define CEntityHandle unsigned int
#define EntitySpawnInfo_t char

class CEntitySystem {
public:
    virtual void n_0();
    virtual void BuildResourceManifest(void); // 01
    virtual void n_2();
    virtual void n_3();
    virtual void n_4();
    virtual void n_5();
    virtual void n_6();
    virtual void AddRefKeyValues(void const*); // 7
    virtual void ReleaseKeyValues(void const*); // 8
    virtual void n_9();
    virtual void n_10();
    virtual void ClearEntityDatabase(void); // 11
    virtual CEntityInstance* FindEntityProcedural(const char *...);
    virtual CEntityInstance* OnEntityParentChanged(CEntityInstance*, CEntityInstance*); //13
    virtual CEntityInstance* OnAddEntity(CEntityInstance*, CEntityHandle); // 14
    virtual CEntityInstance* OnRemoveEntity(CEntityInstance*, CEntityHandle); // 15
    virtual void n_16();
    virtual void SortEntities(int, EntitySpawnInfo_t*, int*, int*); // 17
    virtual void n_18();
    virtual void n_19();
    virtual void n_20();
    virtual void n_21();
};

class CGameEntitySystem : public CEntitySystem
{
public:

    void* unk;
    //void* unk2; 
    //void* unk3;, remove because of vtable

    CEntityIdentities* m_pEntityList[MAX_ENTITY_LISTS];

    CBaseEntity* GetBaseEntity(int index)
    {
        if (index <= -1 || index >= MAX_TOTAL_ENTITIES)
            return nullptr;

        //std::cout << "m_pEntityList: " << std::hex << (uintptr_t)m_pEntityList << std::endl;

        int listToUse = (index / MAX_ENTITIES_IN_LIST);
        if (!m_pEntityList[listToUse]) {
            printf("Tried to Use an EntityList does that not exist yet! List #%d\n", listToUse);
            return nullptr;
        }
        if (m_pEntityList[listToUse]->m_pIdentities[index % MAX_ENTITIES_IN_LIST].entity) {
            return m_pEntityList[listToUse]->m_pIdentities[index % MAX_ENTITIES_IN_LIST].entity;
        }
        else {
            return nullptr;
        }
    }
    int GetHighestEntityIndex()
    {

        return *(int*)((uintptr_t)this + 0x2090);
    }
};
CGameEntitySystem* entsystem;


class CHandle;
class LocalHero
{
public:
    CBaseEntity* pEnt;
    C_DOTAPlayer* pPlayer;
    int health = 0;
    float mana = 0;
    int Abilities[32];
    bool SeenByEnemy = 0;
    bool IsOnSentry = 0;
    bool GetAbilities()
    {
        for (int i = 0; i < 32; i++)
        {
            Abilities[i] = *(BYTE*)((ui)pEnt + m_hAbilities + i * 4);
        }
        return true;
    }
}localhero;

class CDOTA_Ability
{
public:

    ui* vtable;//00
    char shit[2]; //08
    CEntityInstance* instance; //0x0010

    int GetIndex()
    {
        return this->instance->handle & 0x7FFF;
        //& 0x7fff
    }
    void FindAbilities()
    {
        IsCooldownReady = *(_IsCooldownReady*)(*(ui*)this + 0x728);
        IsInAbilityPhase = *(_IsInAbilityPhase*)(*(ui*)this + 0x838);
        GetCastRange = *(_GetCastRange*)(*(ui*)this + 0x7A0);
    }
    bool CanBeUsed()
    {


        bool iscooldownready = IsCooldownReady(this);
        bool AbilityPhase = IsInAbilityPhase(this);



        if (iscooldownready && !AbilityPhase)
        {
            return true;
        }
        return false;
    }
    int GetAbilityDamage()
    {

        if (!oGetAbilityDamage)
        {
            oGetAbilityDamage = (_oGetAbilityDamage)VT_METHOD(this, 279);

        }
        int it = oGetAbilityDamage(this);
        return it;
    }
    int GetLevel()
    {
        return *(int*)((ui)this + 0x5A8);
    }



};



int GetLocalPlayer()
{
    int tempint = 0;
    GetLocalPlayerIndex((ui*)CEngineClient, &tempint, 0);
    return tempint + 1;
}


class CBaseEntity
{

public:
    ui* vtable;//00
    char shit[2]; //08
    CEntityInstance* instance; //0x0010




    struct Info
    {
        bool IsSeen = 0;
    }unitinfo;
    cc GetBaseClass()
    {


        if (***(cc***)(*(ui*)((ui)this + 0x10) + 0x8))
        {
            return ***(cc***)(*(ui*)((ui)this + 0x10) + 0x8);

        }

        else
        {
            return "Unknown";
        }
    }
    float GetMoveSpeed()
    {
        if (!GetIdealMoveSpeed)
        {
            GetIdealMoveSpeed = *(_GetIdealMoveSpeed*)(*(ui*)this + 0x6F8);
        }
        return GetIdealMoveSpeed(this);
    }
    Vector GetForward()
    {
        Vector result = { 0,0,0 };
        Vector* empty = &result;


        if (!oGetVector)
        {
            oGetVector = *(_GetVector*)(*(ui*)this + 0x1F0);
        }
        oGetVector(this, &result, nullptr, nullptr);
        return result;
    }
    int GetHealthBarOffset()
    {
        return *(int*)((ui)this + m_iHealthBarOffset);
    }

    bool IsIllusion()
    {
        if (*(ui*)((ui)this + m_hReplicatingOtherHeroModel) != 0xFFFFFFFF)
        {
            return true;
        }
        return false;
    }
    bool IsHero()
    {
        if (!strcmp("C_DOTA_BaseNPC_Hero", this->GetBaseClass())) // 0 means identical
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool IsAbility()
    {
        if (!strcmp("C_DOTABaseAbility", this->GetBaseClass())) // 0 means identical
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool IsSeenByEnemy()
    {
        if (*(int*)((ui)this + m_iTaggedAsVisibleByTeam) == 14)
        {
            return true;
        }
        return false;
    }
    bool IsSeenGemSentry()
    {
        if (HasModifier(this, "modifier_truesight"))
        {
            return true;
        }
        return false;
    }
    bool IsChargedByBreaker()
    {
        if (HasModifier(this, "modifier_spirit_breaker_charge_of_darkness_vision"))
        {
            return true;
        }
        return false;
    }
    void SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
    {
        if (*(BYTE*)((ui)this + m_clrRender + 0) == r && *(BYTE*)((ui)this + m_clrRender + 1) == g && *(BYTE*)((ui)this + m_clrRender + 2) == b && *(BYTE*)((ui)this + m_clrRender + 3) == a)
        {
            return;
        }
        *(BYTE*)((ui)this + m_clrRender + 0) = r;
        *(BYTE*)((ui)this + m_clrRender + 1) = g;
        *(BYTE*)((ui)this + m_clrRender + 2) = b;
        *(BYTE*)((ui)this + m_clrRender + 3) = a;
        OnColorChanged((ui*)this);
    }
    cc GetName()
    {
        cc name;
        if (*(cc*)(*(ui*)((ui)this + 0x10) + 0x18))
        {
            name = *(cc*)(*(ui*)((ui)this + 0x10) + 0x18);
            return name;

        }
        else
        {
            if (*(cc*)(*(ui*)((ui)this + 0x10) + 0x20))
            {
                name = *(cc*)(*(ui*)((ui)this + 0x10) + 0x20);
                return name;
            }
            else
            {
                name = "Unknown";
                return name;
            }
        }
    }
    float GetMaxMana()
    {
        return *(float*)((ui)this + m_flMaxMana);
    }
    int GetManaPerc()
    {
        return (int)((this->GetMana() / this->GetMaxMana()) * 100);
    }
    Vector GetAbsOrigin()
    {

        ui gamescenenode = *(ui*)((ui)this + m_pGameSceneNode);
        return *(Vector*)(gamescenenode + m_vecAbsOrigin);
    }

    bool IsDormant() 
    {
        return *(bool*)((ui)this + m_bDormant);
    }
    

    bool WorldToScreen(Vector& abs, FVector& screen, int& x, int& y)
    {
        FVector2 result;
        x = 0;
        y = 0;

        abs = this->GetAbsOrigin();
        int healthbaroffset = this->GetHealthBarOffset();
        abs.z += healthbaroffset;

        bool bResult = W2S(abs, &x, &y, nullptr);


        if (bResult)
        {

            Vector4 myvec = { 0.0,0.0,0.0,0.0 };
            float dif;


            myvec.w = ((abs.x * WorldMatrix.m[12]) + (abs.y * WorldMatrix.m[13])) + ((abs.z * WorldMatrix.m[14]) + WorldMatrix.m[15]);
            myvec.y = ((abs.x * WorldMatrix.m[4]) + (abs.y * WorldMatrix.m[5])) + ((abs.z * WorldMatrix.m[6]) + WorldMatrix.m[7]);
            if (myvec.w >= 0.001)
            {
                dif = 1.0f / myvec.w;
            }
            else
            {
                dif = 100000.0f;

            }
            myvec.x = (((abs.y * WorldMatrix.m[1]) + (abs.x * WorldMatrix.m[0])) + ((abs.z * WorldMatrix.m[2]) + WorldMatrix.m[3]));
            myvec.z = (((abs.x * WorldMatrix.m[8]) + (abs.y * WorldMatrix.m[9]) + (abs.z * WorldMatrix.m[10]) + WorldMatrix.m[11]));
            screen.y = myvec.y / myvec.w;
            screen.x = myvec.x / myvec.w;
            screen.z = myvec.z / myvec.w;
        }


        if (x < 0 || y < 0)
        {
            return 0;
        }

        return bResult;

    }

    int GetHealth()
    {
        return *(int*)((ui)this + m_iHealth);
    }
    float GetMana() {
        return *(float*)((ui)this + m_flMana);
    }
    int GetTeam()
    {
        if ((ui)this <= 0)
        {
            return 0;
        }
        return *(unsigned short*)((ui)this + m_iTeamNum);
    }
    int GetUnitIndex()
    {
        return this->instance->handle & 0x7FFF;
        //& 0x7fff
    }
    int GetOwnerIndex()
    {
        if ((ui)this)
        {
            return *(int*)((ui)this + m_hOwnerEntity) & 0x7FFF;
        }
        return 0;
    }
    bool IsAlive()
    {
        if (*(BYTE*)((ui)this + m_lifeState) == 0)
        {
            return true;
        }
        return false;
    }
    bool IsEnemy()
    {

        if (!LocalPlayerTeam)
        {
            int LocalPlayerIndex = GetLocalPlayer();
            if (!localhero.pEnt)
            {
                for (int i = 0; i < entsystem->GetHighestEntityIndex(); i++)
                {
                    auto ent = entsystem->GetBaseEntity(i);
                    auto ownerindex = ent->GetOwnerIndex();
                    if (ownerindex == LocalPlayerIndex)
                    {
                        localhero.pEnt = ent;
                        localhero.pPlayer = localhero.pEnt->GetPlayer();
                        LocalPlayerTeam = localhero.pEnt->GetTeam();

                        break;
                    }
                }
            }

        }


        if (this->GetTeam() != LocalPlayerTeam)
        {
            return true;
        }
        return false;
    }
    bool IsLocalEntity()
    {
        int Index = this->GetOwnerIndex();
        if (!LocalPlayerIndex)
        {
            LocalPlayerIndex = GetLocalPlayer();
        }
        if (Index == LocalPlayerIndex)
        {
            return true;
        }
        return false;
    }
    C_DOTAPlayer* GetPlayer()
    {
        for (int i = 0; i < 12; i++)
        {
            if (!LocalPlayerIndex)
            {
                LocalPlayerIndex = GetLocalPlayer();
            }
            auto OwnerIndex = this->GetOwnerIndex();
            auto ent = entsystem->GetBaseEntity(i);
            auto Index = ent->GetUnitIndex();
            if (Index == OwnerIndex)
            {
                return *(C_DOTAPlayer**)ent;
            }
        }
    }
    //DotaUnitOrder_t order, int entHandle, Vector movePosition, int abilityIndex,PlayerOrderIssuer_t orderIssuer, CDotaBaseNPC* entity, OrderQueueBehavior_t queueBehavior, bool showEffect
    void SpellPointTarget(int AbilityIndex, CBaseEntity* target)
    {
        Vector position = target->GetAbsOrigin();
        float movespeed = target->GetMoveSpeed();
        Vector forward = target->GetForward();
        position = position + (forward * movespeed);
        if (localhero.pPlayer == nullptr) { localhero.pPlayer = localhero.pEnt->GetPlayer(); }
        PrepareUnitOrders(localhero.pPlayer, DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_POSITION, 0, position, AbilityIndex, PlayerOrderIssuer_t::DOTA_ORDER_ISSUER_HERO_ONLY, this, 0, OrderQueueBehavior_t::DOTA_ORDER_QUEUE_DEFAULT, 0);
    }
    void SpellNoTarget(int AbilityIndex)
    {
        Vector empty = { 0,0,0 };
        PrepareUnitOrders(localhero.pPlayer, DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_NO_TARGET, NULL, empty, AbilityIndex, PlayerOrderIssuer_t::DOTA_ORDER_ISSUER_HERO_ONLY, this, 0, OrderQueueBehavior_t::DOTA_ORDER_QUEUE_DEFAULT, 0);
    }
    void SpellTarget(int AbilityIndex, CBaseEntity* target)
    {
        Vector empty = { 0,0,0 };
        PrepareUnitOrders(localhero.pPlayer, DotaUnitOrder_t::DOTA_UNIT_ORDER_CAST_TARGET, target->GetUnitIndex(), empty, AbilityIndex, PlayerOrderIssuer_t::DOTA_ORDER_ISSUER_HERO_ONLY, this, 0, OrderQueueBehavior_t::DOTA_ORDER_QUEUE_DEFAULT, 0);
    }
};//(C_DOTAPlayer* player, DotaUnitOrder_t order, int entHandle, Vector movePosition, int abilityIndex, PlayerOrderIssuer_t orderIssuer, CBaseEntity* entity, bool queue, OrderQueueBehavior_t queueBehavior, bool showEffect);

class MemberInfo
{
public:
    cc name; //0x0000
    ui* unk4; //0x0008
    int Offset; //0x0010

};
MemberInfo* temps;



class ClassDescription
{
public:
    ui* self; //0x0000
    cc Name; //0x0008
    ui* void1; //0x0010
    uint32_t Unknown; //0x0018
    uint16_t MembersCount; //0x001C
    char pad_001E[10]; //0x001E
    MemberInfo* memberinfo; //0x0028

    ui GetOffset(cc offset) // m_bIsPhantom
    {

        for (int i = 0; i <= MembersCount; i++)
        {
            temps = (MemberInfo*)((ui)(this->memberinfo) + i * 0x20);
            cc thisname = temps->name;
            if (!thisname) { break; }
            if (!strcmp(offset, thisname))
            {
                return temps->Offset;
            }
            CMSG("%d ) Offset: %s  | %d\n ", i, temps->name, temps->Offset);


        }
        return 0;
    }
};

////////////////////////////////////////////////////
////////////// Prototypes //////////////////////////////
////////////////////////////////////////////////////







////////////////////////////////////////////////////
////////////// Global functions //////////////////////////////
////////////////////////////////////////////////////




int GetGameState()
{
    if (*(ui*)GetStatePointer)
    {
        return *(int*)(*(ui*)GetStatePointer + 0x58);
    }
    return 0;
}

ui FPat(const ui& start_address, const ui& end_address, const char* target_pattern) {
    const char* pattern = target_pattern;

    ui first_match = 0;

    for (ui position = start_address; position < end_address; position++) {
        if (!*pattern)
            return first_match;

        const unsigned char pattern_current = *reinterpret_cast<const unsigned char*>(pattern);
        const unsigned char memory_current = *reinterpret_cast<const unsigned char*>(position);

        if (pattern_current == '\?' || memory_current == getByte(pattern)) {
            if (!first_match)
                first_match = position;

            if (!pattern[2])
                return first_match;

            pattern += pattern_current != '\?' ? 3 : 2;
        }
        else {
            pattern = target_pattern;
            first_match = 0;
        }
    }

    return NULL;
}

ui FPat(const char* module, const char* target_pattern) {
    MODULEINFO module_info = { 0 };

    if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &module_info, sizeof(MODULEINFO)))
        return NULL;

    const ui start_address = ui(module_info.lpBaseOfDll);
    const ui end_address = start_address + module_info.SizeOfImage;

    return FPat(start_address, end_address, target_pattern);
}
inline ui GetAbsoluteAddress(ui instruction_ptr, int offset, int size)
{
    return instruction_ptr + *reinterpret_cast<int32_t*>(instruction_ptr + offset) + size;
}

template <typename T>
bool HookVMT(T* ESystem, void* MyFunc, ui* original, ui FuncIndex)
{

    u64* Table = (u64*)(*(u64*)ESystem);
    ui* Func2Hook = (ui*)((ui)Table + FuncIndex * 8);

    DWORD OldProtect;
    original = (ui*)*(ui*)Func2Hook;
    // oRunFrame = (_oRunFrame)original;
    VirtualProtect((LPVOID)Func2Hook, sizeof(void*), PAGE_EXECUTE_READWRITE, &OldProtect);

    *Func2Hook = (ui)MyFunc;


    DWORD NewProtect;
    VirtualProtect((LPVOID)Func2Hook, sizeof(void*), OldProtect, &NewProtect);



    return true;
}
template <typename T>
bool UnhookVMT(T* ESystem, void* MyFunc, ui FuncIndex)
{

    u64* Table = (u64*)(*(u64*)ESystem);
    ui* Func2Hook = (ui*)((ui)Table + FuncIndex * 8);

    DWORD OldProtect;
    // oRunFrame = (_oRunFrame)original;
    VirtualProtect((LPVOID)Func2Hook, sizeof(void*), PAGE_EXECUTE_READWRITE, &OldProtect);

    *Func2Hook = (ui)MyFunc;


    DWORD NewProtect;
    VirtualProtect((LPVOID)Func2Hook, sizeof(void*), OldProtect, &NewProtect);



    return true;
}


void exithack()
{
    CMSG(" .....\n");
    CMSG("Uninjecting.....\n");
    Logger::FATAL("Uninjecting.....");
    CMSG(" .....\n");
    Sleep(7000);
    //FreeLibraryAndExitThread((HMODULE)GetModuleHandle("hacker.dll"), 0);
}


ui CreateInterface(const char* szModule, const char* szInterface) {


    pCreateInterface = (_CreateInterface)GetProcAddress(GetModuleHandleA(szModule), "CreateInterface");


    return (ui)pCreateInterface(szInterface, 0);


}
ui* tempdog;



void RemoveHeroes(CGameEntitySystem* Ptr, CBaseEntity* EntityInstance, int r8)
{
    //std::remove(AllEntities.begin(), AllEntities.end(), EntityInstance);

    AllEntities.erase(EntityInstance);
    Entities.erase(EntityInstance);
    //std::remove(Entities.begin(), Entities.end(), EntityInstance);

    hkOnRemoveEntity(Ptr, EntityInstance, r8);
}
void IterateHeroes(CGameEntitySystem* Ptr, CBaseEntity* EntityInstance, int r8)
{

    AllEntities.insert(EntityInstance);
    if (!gotent) { gotent = true; }

    hkOnAddEntity(Ptr, EntityInstance, r8);

}
////////////////////////////////////////////////////
////////////// Global functions //////////////////////////////
////////////////////////////////////////////////////



















int drawManaIndex = 0;
int eindex = 0;

class CBaseEntity;
void IterateEntities()
{   
    
    CBaseEntity* entity = nullptr;
    for (int i = 0; i < entsystem->GetHighestEntityIndex(); i++)
    {

        CBaseEntity* ent = entsystem->GetBaseEntity(i);
        if (ent && ent->instance)
        {
            if (ent->IsHero())
            {

                if (ent->IsAlive()) //////////////// ALIVE ENTITY
                {
                    if (!once2)
                    {
                        //CLRMSG(&Red, "Found hero %s | %p\n", ent->GetName(), ent);
                       // CMD("say Pyckuu kopa6JI, idi naxui");
                        // CMD("say Got my hero {}",ent->GetName());
                    }

                    if (!ent->IsEnemy() && !ent->IsIllusion()) ///////////////////  ALLY / NOT ILLUSION
                    {
                        if (!one && ent->IsLocalEntity())
                        {

                            u64 localplayer = FPat("client.dll", "40 57 48 83 EC 20 48 8B ? ? ? ? ? 48 8B FA 48 85 C9 74 46 48 8B 01 FF 90 48 04 00 00 84 C0 74 39 48 89 5C 24 30 48 8B");
                            localhero.pPlayer = *(C_DOTAPlayer**)GetAbsoluteAddress(localplayer + 0x6, 3, 7);


                            one = true;
                            localhero.pEnt = ent;
                            localhero.GetAbilities();
                            LocalPlayerTeam = ent->GetTeam();
                            cc localheroname = localhero.pEnt->GetName();
                            CLRMSG(&Red, "Found hero:%s , %p\n", localheroname, localhero.pEnt);
                            if (!heroscript)

                            {
                                if (!strcmp(localheroname, "npc_dota_hero_zuus"))
                                {
                                    CLRMSG(&Red, "ZUUS ACTIVATED\n");
                                    zeus = true;
                                    heroscript = true;
                                }
                                else
                                    if (!strcmp(localheroname, "npc_dota_hero_pudge"))
                                    {
                                        CLRMSG(&Red, "PUDGE ACTIVATED\n");
                                        pudge = true;
                                        heroscript = true;
                                    }
                                    else if (!strcmp(localheroname, "npc_dota_hero_axe"))
                                    {
                                        CLRMSG(&Red, "AXE ACTIVATED\n");
                                        axe = true;
                                        heroscript = true;
                                    }
                            }

                            //pPanelList = panoramaptr->GetPanelList();


                           // CUIPanel* newpanel = panoramaptr->CreatePanel(panoramaptr, "Manas");
                            //newpanel->BLoadLayout("<root> < Panel style =\"background-color:#FFFFFFFF;width:700px;height:900px;\"> </Panel></root>");

                           // CMSG("Created Panel\n");
                        }

                        if (ent->IsSeenByEnemy())
                        {
                            // particle0 = new Particle;
                            particle0 = pt->Create(particlename.aurashivas, ParticleAttachment_t::PATTACH_ABSORIGIN, ent, 0, 0);
                            FVector color = { 255,0,0 };
                            FVector range = { 250,250,0 };
                            FVector idk = { 10,0,0 };
                            particle0->SetControlPoint(1, color);
                            particle0->SetControlPoint(2, range);
                            particle0->SetControlPoint(3, idk);
                        }
                        else
                        {
                            PM->DeleteParticle(particlename.aurashivas, ent, 1);
                            // delete particle0;
                        }
                        if (ent->IsSeenGemSentry())
                        {
                            // particle1 = new Particle;
                            particle1 = pt->Create(particlename.truesight, ParticleAttachment_t::PATTACH_OVERHEAD_FOLLOW, ent, 0, 0);
                            FVector color = { 255,100,100 };
                            FVector range = { 100,255,0 };
                            FVector idk = { 10,0,0 };
                            particle1->SetControlPoint(1, color);
                            particle1->SetControlPoint(2, range);
                            particle1->SetControlPoint(3, idk);
                        }
                        else
                        {
                            PM->DeleteParticle(particlename.truesight, ent, 1);
                            // delete particle1;
                        }
                        if (ent->IsChargedByBreaker())
                        {
                            //   particle2 = new Particle;
                            particle2 = pt->Create(particlename.charge_target, ParticleAttachment_t::PATTACH_HEALTHBAR, ent, 0, 0);
                            FVector color = { 255,100,100 };
                            FVector range = { 100,255,0 };
                            FVector idk = { 10,0,0 };
                            particle2->SetControlPoint(1, color);
                            particle2->SetControlPoint(2, range);
                            particle2->SetControlPoint(3, idk);
                        }
                        else
                        {
                            PM->DeleteParticle(particlename.charge_target, ent, 1);
                            // delete particle2;
                        }
                    }
                    else ////////////////  The entity is not an ally
                    {
                        if (ent->IsIllusion())
                        {
                            ent->SetColor(0, 0, 255, 180);//  ABGR
                        }
                        else //////////////////////// The Entity is ENEMY           NOT ILLUSION
                        {   
                            Enemy data;

                            int x = 0;
                            int y = 0;

                            Vector abs = ent->GetAbsOrigin();

                            std::time_t tnow = std::time(0);

                            bool onScreen = W2S(abs, &x, &y, nullptr);

                            data.mana = ent->GetMana();
                            data.maxMana = ent->GetMaxMana();
                            data.x = x - 70;
                            data.y = y - ent->GetHealthBarOffset() / 100 * 10;
                            data.onScreen = onScreen;
                            data.isAlive = ent->IsAlive();
                            data.inVision = ent->IsDormant();


                            Enemies[eindex] = data;
                            eindex += 1;
                            

                            if (heroscript && localhero.pEnt)  ///// Scripts
                            {



                                if (pudge && GetAsyncKeyState(VK_F1)) //// script:pudge
                                {
                                    if (Ultimate == nullptr)
                                    {
                                        Ultimate = FindAbilityByName(localhero.pEnt, "pudge_meat_hook");
                                        Ultimate->FindAbilities();

                                    }
                                    Vector empty = { 0,0,0 };
                                    float range = GetCastRange(Ultimate);
                                    float bonus = GetCastRangeBonus(localhero.pEnt, empty, Ultimate->GetIndex());
                                    pudge_hookrange = range + bonus;
                                    bool IsEntInRange = IsEntityInRange(localhero.pEnt, ent, pudge_hookrange);
                                    if (IsEntInRange)
                                    {
                                        bool CanUse = Ultimate->CanBeUsed();
                                        if (localhero.pEnt->IsAlive() && CanUse)
                                        {
                                            Vector front = ent->GetForward();
                                            localhero.pEnt->SpellPointTarget(localhero.Abilities[0], ent);

                                        }
                                    }
                                }





                                else if (axe) /// script:axe
                                {
                                    if (Ultimate == nullptr)
                                    {
                                        Ultimate = FindAbilityByName(localhero.pEnt, "axe_culling_blade");
                                        Ultimate->FindAbilities();

                                    }
                                    Vector empty = { 0,0,0 };
                                    float range = GetCastRange(Ultimate);
                                    float bonus = GetCastRangeBonus(localhero.pEnt, empty, Ultimate->GetIndex());
                                    int ultidamage = Ultimate->GetAbilityDamage();
                                    int level = Ultimate->GetLevel();
                                    if (level == 1) //250/350/450
                                    {
                                        ultidamage = 250;
                                    }
                                    else if (level == 2)
                                    {
                                        ultidamage = 350;
                                    }
                                    else if (level == 3)
                                    {
                                        ultidamage = 450;
                                    }

                                    axe_ultirange = range + bonus + 50;
                                    if (ent->GetHealth() <= ultidamage && IsEntityInRange(localhero.pEnt, ent, axe_ultirange))
                                    {
                                        bool CanUse = Ultimate->CanBeUsed();
                                        if (localhero.pEnt->IsAlive() && CanUse)
                                        {

                                            localhero.pEnt->SpellTarget(localhero.Abilities[5], ent);

                                        }
                                    }

                                }
                                else if (zeus) /// script:pudge
                                {
                                    if (GetAsyncKeyState(VK_F1) & 1)
                                    {
                                        if (zuus_blowcounter != 5)
                                        {
                                            zuus_blowcounter++;
                                            CLRMSG(&Green, "Zuus counter: %d\n", zuus_blowcounter);
                                        }
                                    }
                                    if (GetAsyncKeyState(VK_F2) & 1)
                                    {
                                        if (zuus_blowcounter != 1)
                                        {
                                            zuus_blowcounter--;
                                            CLRMSG(&Red, "Zuus counter: %d\n", zuus_blowcounter);
                                        }
                                    }
                                    if (Ultimate == nullptr)
                                    {
                                        Ultimate = FindAbilityByName(localhero.pEnt, "zuus_thundergods_wrath");
                                        Ultimate->FindAbilities();

                                    }



                                    int ultidamage = 0;
                                    int level = Ultimate->GetLevel();
                                    if (level == 1) //300/425/550
                                    {
                                        ultidamage = 300;
                                    }
                                    else if (level == 2)
                                    {
                                        ultidamage = 425;
                                    }
                                    else if (level == 3)
                                    {
                                        ultidamage = 550;
                                    }
                                    if (ent->GetHealth() <= ultidamage)
                                    {
                                        zuus_counter++;

                                        bool CanUse = Ultimate->CanBeUsed();
                                        if (zuus_counter >= zuus_blowcounter && localhero.pEnt->IsAlive() && CanUse)
                                        {
                                            zuus_counter = 0;
                                            localhero.pEnt->SpellNoTarget(localhero.Abilities[5]);

                                        }
                                    }
                                }
                            }

                        }


                    }
                }
            }



        }


    }
    if (zuus_counter > 0) zuus_counter = 0;


    drawManaIndex = 0;
    eindex = 0;
}

void hkRunFrame(ui* parameter)
{
    if (IsInGame()) /////////// if we are ingame and playing
    {
        state = GetGameState();
        if (state == DOTA_GAMERULES_PREGAME || state == DOTA_GAMERULES_GAME_IN_PROGRESS)

        {/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (!InGame)
            {
                ClientCMDUnrestricted = (_ClientCMDUnrestricted)VT_METHOD(CEngineClient, 36);
                Logger::DEBUG("join in match");

                InGame = true;

            }
            if (!LocalPlayerIndex)
            {
                LocalPlayerIndex = GetLocalPlayer();
            }
            if (!VMTBegin)
            {
                PM = *(CDOTA_ParticleManager**)ParticleManager;
                CreateParticle = (_CreateParticle)VT_METHOD(PM, 7);

                VMTBegin = true;
                // HookVMT(EntSystem, IterateHeroes, (ui*)hkOnAddEntity, 14); /////////OnAddEntity
                // HookVMT(EntSystem, RemoveHeroes, (ui*)hkOnRemoveEntity, 15);
            }

            IterateEntities();


        }
    }//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    if (!IsInGame() && InGame == true) ////////// Not In Game/ disconnect / quit /exitmatch
    {
        if (true) // gotoent not work
        {   
            Logger::DEBUG("disconnected from match");
            localhero.pEnt = nullptr;
            localhero.pPlayer = nullptr;
            Ultimate = nullptr;
            CMSG("Exiting match\n");
            InGame = false;
            zuus_counter = 0;
            zeus = 0;
            axe = 0;
            pudge = 0;
            heroscript = false;
            gotent = 0;
            state = 0;
            Entities.clear();
            LocalPlayerIndex = 0;
            LocalPlayerTeam = 0;
            one = false;
            once2 = false;
            localhero.pEnt = nullptr;

            for (int i = 0; i < 5; i++)
            {   
                Enemy data;

                data.mana = 0;
                data.maxMana =0;
                data.x = 0;
                data.y = 0;
                data.onScreen = false;
                data.isAlive = false;

                Enemies[i] = data;
            }
            
            MyParticles.clear();
            AllEntities.clear();
            MyParticles.clear();
        }
    }


    RunFrame(parameter);
}



void GetModules()
{

    /// Console

    CMSG = (_CMSG)GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConMsg@@YAXPEBDZZ");
    CLRMSG = (_CLRMSG)GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConColorMsg@@YAXAEBVColor@@PEBDZZ");

    DEVMSG = (_DEVMSG)GetProcAddress(GetModuleHandleA("tier0.dll"), "?DevMsg@@YAXPEBDZZ");

    //////////  Functions

    u64 OnColorChangedPtr = FPat("client.dll", "40 53 48 83 EC ? 48 8B D9 48 8B 89 ? ? ? ? 48 8B 01 0F B6 93 ? ? ? ? FF 50 08 48 8B CB 48 83 C4");
    //48 89 5C ? ? 57 48 83 EC ? 41 0F B6 ? 48 8B DA 40 3A BA ? ? ? ? 74 29 48 8B 8A ? ? ? ? 0F 57 C0");
    if (!OnColorChangedPtr)
    {
        CMSG("Failed to Get OnColorChanged");
        Logger::ERR("Failed to Get OnColorChanged");

        exithack();
    }
    OnColorChanged = (_OnColorChanged)OnColorChangedPtr;

    u64 HasModifierPtr = FPat("client.dll", "40 53 55 41 56 48 83 EC 20 4C 8B F2 48 8B E9 E8 ? ? ? ? 4D 8B C6 48 8D 54 24 40 48 8B D8 48 8D 48 20 FF 15 ? ? ? ? 44 0F B7 44 24 40");

    if (!HasModifierPtr)
    {
        CLRMSG(&Red, "Failed to get HasModifierPtr\n");
        Logger::ERR("Failed to get HasModifierPtr");

        exithack();
    }
    HasModifier = (_HasModifier)HasModifierPtr;


    u64 GetPanelTypePtr = FPat("panorama.dll", "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 20 80 3D ? ? ? ? ? 48 8B EA 48 8B F1 75 6E B9 98 00 00 00 E8");
    if (!GetPanelTypePtr)                     //48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 20 80 3D ? ? ? ? ? 48 8B EA 48 8B F1 75 6E B9 98 00 00 00 E8 ? ? ? ? 48 8B D8 48 85 C0
    {
        CMSG("Failed to Get GetPanelTypePTR\n");
        Logger::ERR("Failed to get GetPanelTypePTR");
        exithack();
    }
    oGetPanelType = (_GetPanelType)GetPanelTypePtr;

    u64 CreateParticlePtr = FPat("client.dll", "40 53 48 83 EC 60 33 DB 45 8B D8 8B C3 41 83 F9 FF 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 85 C0 74 2B 48 63 48");
    //40 53 48 83 EC 60 33 DB 45 8B D8 8B C3 41 83 F9 FF 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 85 C0 74 2B 48 63 48 58 44 8B 90 B8 00 00 00
    if (!CreateParticlePtr)
    {
        CLRMSG(&Red, "Failed to get CreateParticlePtr");
        Logger::ERR("Failed to get CreateParticlePtr");

        exithack();
    }
    ParticleManager = GetAbsoluteAddress(CreateParticlePtr + 0xA0, 3, 7);

    RenderSystemPtr = FPat("client.dll", "40 56 41 56 48 83 EC 68 48 89 9C 24 80 00 00 00 49 8B F0 48 89 7C 24 60 48 8B F9 4C 8B F2 4D 85 C9");
    if (!RenderSystemPtr)
    {
        CLRMSG(&Red, "Failed to get pRenderSystemptr\n");
        Logger::ERR("Failed to get pRenderSystemptr");

        exithack();
    }
    RenderSystem = GetAbsoluteAddress(RenderSystemPtr + 0xCF, 3, 7);
    u64 DestroyParticlePtr = FPat("client.dll", "83 FA FF 0F 84 ? ? ? ? 48 89 74 24 18 57 48 83 EC 30 48 63 81 80 00 00 00 41 0F B6 F0 48 89 6C 24 48");
    //           83 FA FF 0F 84 ? ? ? ? 48 89 74 24 18 57 48 83 EC 30 48 63 81 80 00 00 00 41 0F B6 F0 48 89 6C 24 48 48 8B F9 33 ED 44 8B CD 85 C0
    if (!DestroyParticlePtr)
    {
        CLRMSG(&Red, "Failed to get DestroyParticlePtr\n");
        Logger::ERR("Failed to get DestroyParticlePtr");

        exithack();
    }
    DestroyParticle = (_DestroyParticle)DestroyParticlePtr;

    u64 entfindPat = FPat("client.dll", "48 83 EC ? 83 3A 02 7D 12 48 8D 0D ? ? ? ? 48 83 C4 ? 48 FF 25 ? ? ? ? 48 89 5C ? ? 48 8D 0D ? ? ? ? 48 89 6C");
    if (!entfindPat)
    {
        CLRMSG(&Red, "Failed to get EntSystem\n");
        Logger::ERR("Failed to get EntSystem");

        exithack();
    }
    u64 CGameEntSystem = *(u64*)GetAbsoluteAddress(entfindPat + 0x5F, 3, 7);
    //EntSystem = new CGameEntitySystem();
    entsystem = (CGameEntitySystem*)CGameEntSystem;
    CMSG("EntSystem: %p\n", (ui)entsystem);

    u64 GetEntIndexPtr = FPat("client.dll", "48 83 EC ? 4C 8B 0D ? ? ? ? 48 8B 49 ? 49 83 C1 ? 48 85 C9 75 08 8D 41 FF 48 83 C4");
    if (!entfindPat)
    {
        CLRMSG(&Red, "Failed to get GetEntIndex\n");
        Logger::ERR("Failed to get GetEntIndex");

        exithack();
    }
    GetEntIndex = (_GetEntityIndex)GetEntIndexPtr;

    u64 GetStatePtr = FPat("client.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 17 48 63 48 ? 83 F9 0B 77 0E 48 8B C1 48 8D 0D ? ? ? ? 8B 04 81");
    if (!GetStatePtr)
    {
        CMSG("Failed to get GetStatePtr\n");
        Logger::ERR("Failed to get GetStatePtr");

        exithack();
    }
    GetStatePointer = GetAbsoluteAddress(GetStatePtr, 3, 7);
    u64 IsEntityInRangePtr = FPat("client.dll", "48 89 5C ? ? 48 89 74 ? ? 57 48 83 EC ? 0F 29 74 ? ? 0F 28 F2 48 8B F2 48 85 D2 74 61");
    if (!IsEntityInRangePtr)
    {
        CMSG("Failed to get IsEntityInRangePtr\n");
        Logger::ERR("Failed to get IsEntityInRangePtr");

        exithack();

    }
    IsEntityInRange = (_IsEntityInRange)IsEntityInRangePtr;


    ///////////////////////////////////
    //u64 W2SX = FPat("client.dll", "48 8B C4 48 83 EC 48 4C 8D 48 D8 F3 0F 11 48 E8 4C 8D 40 18 F3 0F 11 50 EC 48 8D 50 10 F3 0F 11 58 F0 48 8D 48 E8 48 C7 40 D8 00 00 00 00 C7 40 E0");
   /**if (!W2SX)
    {
        CMSG("Failed to get W2SX\n");

        exithack();

    }
    W2SX = (_W2SX)W2SX;*/
    u64 W2SPtr = FPat("client.dll", "40 56 41 56 48 83 EC 68 48 89 9C 24 80 00 00 00 49 8B F0 48 89 7C 24 60 48 8B F9 4C 8B F2 4D 85 C9 74 2D F3 0F 10 01");
    if (!W2SPtr)
    {
        CMSG("Failed to get W2SPtr\n");
        Logger::ERR("Failed to get W2SPtr");

        exithack();

    }
    W2S = (_W2S)W2SPtr;
    /////////////////////////////////////


    u64 OnTVPtr = FPat("client.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B ? ? ? ? ? 48 8B F2 41 8B 38 48 8B E9 48 85 DB 74 42 48 8B 03");
    if (!OnTVPtr)
    {
        CMSG("Failed to get OnTVPtr\n");
        Logger::ERR("Failed to get OnTVPtr");

        exithack();

    }
    u64 FindAbilityPtr = FPat("client.dll", "40 55 48 83 EC 20 48 8B EA 48 85 D2 75 15 48 8D ? ? ? ? ? FF 15 ? ? ? ? 33 C0 48 83 C4 20 5D C3 48 89 74 24 38");
    if (!FindAbilityPtr)
    {
        CMSG("Failed to get FindAbilityPtr\n");
        Logger::ERR("Failed to get FindAbilityPtr");

        exithack();
    }
    FindAbilityByName = (_FindAbilityByName)FindAbilityPtr;
    u64 PrepareOrdersPtr = FPat("client.dll", "4C 89 4C 24 20 44 89 44 24 18 89 54 24 10 48 89 4C 24 08 55 53 56 57 41 55 41 56 41 57 48 8D 6C 24 C0 48 81 EC 40 01 00 00");
    if (!PrepareOrdersPtr)
    {
        CMSG("Failed to get PrepareOrdersPtr\n");
        Logger::ERR("Failed to get PrepareOrdersPtr");

        exithack();
    }
    PrepareUnitOrders = (_PrepareUnitOrders)PrepareOrdersPtr;

    u64 GetSpecialValueForPtr = FPat("client.dll", "44 88 4C 24 20 53 55 57 48 83 EC 40 41 8B D8 48 8B EA 48 8B F9 41 83 F8 FF 75 08 8B 99 A8 05 00 00 FF CB");
    if (!GetSpecialValueForPtr)
    {
        CMSG("Failed to get GetSpecialValueForPtr\n");
        Logger::ERR("Failed to get GetSpecialValueForPtr");

        exithack();
    }
    GetSpecialValueFor = (_GetSpecialValueFor)GetSpecialValueFor;

    u64 GetCastRangeBonusPtr = FPat("client.dll", "4C 8B DC 49 89 5B 10 49 89 7B 18 55 49 8D 6B B8 48 81 EC 40 01 00 00 B8 FF FF FF FF 41 0F 29 73 E8 48 8B F9 89 44 24 2C");
    if (!GetCastRangeBonusPtr)
    {
        CMSG("Failed to get GetCastRangeBonusPtr\n");
        Logger::ERR("Failed to get GetCastRangeBonusPtr");

        exithack();
    }
    GetCastRangeBonus = (_GetCastRangeBonus)GetCastRangeBonusPtr;

    DWORD tmpProtect;
    VirtualProtect((LPVOID)(OnTVPtr + 0x80), 2, PAGE_EXECUTE_READWRITE, &tmpProtect);
    //VirtualProtect((LPVOID)(OnTVPtr + 0x84), dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    *(BYTE*)(OnTVPtr + 0x80) = 0x90;
    *(BYTE*)(OnTVPtr + 0x80 + 1) = 0x90;
    VirtualProtect((LPVOID)(OnTVPtr + 0x84), 2, tmpProtect, &tmpProtect);

    /////////////// Interfaces

    CEngineClient = CreateInterface("engine2.dll", "Source2EngineToClient001");
    u64 panorama = CreateInterface("panorama.dll", "PanoramaUIEngine001");
    Schema = CreateInterface("schemasystem.dll", "SchemaSystem_001");
    u64 VGUIRenderSource = CreateInterface("client.dll", "RenderSystemSurface001");

    Panorama2 = *(ui*)(panorama + 0x28);
    panoramaptr = (Panorama*)Panorama2;
    GetLocalPlayerIndex = (_GetLocalPlayerIndex)VT_METHOD(CEngineClient, 22);
    IsInGame = (_IsInGame)VT_METHOD(CEngineClient, 26);
    RunFrame = (_RunFrame)VT_METHOD(Panorama2, 6);
    FindTypeScope = (_FindTypeScope)VT_METHOD(Schema, 13);
    //hkOnAddEntity = (_hkOnAddEntity)VT_METHOD(EntSystem, 14);
    //hkOnRemoveEntity = (_hkOnRemoveEntity)VT_METHOD(EntSystem, 15);
    CLRMSG(&Red, "Sucessfully injected\n");

    Logger::INFO("Sucessfully injected");

    CMSG("Let's hack this\n");








    HookVMT((ui*)Panorama2, hkRunFrame, (ui*)oRunFrame, 6);
    Logger::INFO("VMT hooked");
    u64 Scope = FindTypeScope(Schema, "client.dll");
    FindDeclaredClass = (_FindDeclaredClass)VT_METHOD(Scope, 2);
    ClassDescription* BaseNPC = (ClassDescription*)FindDeclaredClass(Scope, "C_DOTA_BaseNPC");
    ClassDescription* BaseNPC_Hero = (ClassDescription*)FindDeclaredClass(Scope, "C_DOTA_BaseNPC_Hero");
    ClassDescription* BaseEntity = (ClassDescription*)FindDeclaredClass(Scope, "C_BaseEntity");
    ClassDescription* C_DOTABaseAbilitya = (ClassDescription*)FindDeclaredClass(Scope, "C_DOTABaseAbility");
    ClassDescription* BaseModel = (ClassDescription*)FindDeclaredClass(Scope, "C_BaseModelEntity");
    ClassDescription* CGameSceneNode = (ClassDescription*)FindDeclaredClass(Scope, "CGameSceneNode");
    // ClassDescription* CUIPanel = (ClassDescription*)FindDeclaredClass(Scope, "CUIPanel");
   //  ui todump = CUIPanel->GetOffset("todump");
    u64 test = C_DOTABaseAbilitya->GetOffset("m_Abilityyy");
    m_iMaxHealth = BaseEntity->GetOffset("m_iMaxHealth");
    m_flMaxMana = BaseNPC->GetOffset("m_flMaxMana");
    m_iHealth = BaseEntity->GetOffset("m_iHealth");
    m_iTeamNum = BaseEntity->GetOffset("m_iTeamNum");
    m_flMana = BaseNPC->GetOffset("m_flMana");
    m_vecAbsOrigin = BaseEntity->GetOffset("m_vecAbsOrigin");
    m_hAbilities = BaseNPC->GetOffset("m_hAbilities");
    m_hOwnerEntity = BaseEntity->GetOffset("m_hOwnerEntity");
    m_clrRender = BaseEntity->GetOffset("m_clrRender");
    m_clrRender = BaseNPC->GetOffset("m_clrRender");
    m_lifeState = BaseEntity->GetOffset("m_lifeState");
    m_bDormant = BaseEntity->GetOffset("m_bDormant");
    

    m_clrRender = BaseModel->GetOffset("m_clrRender");
    m_hReplicatingOtherHeroModel = BaseNPC_Hero->GetOffset("m_hReplicatingOtherHeroModel");
    m_iTaggedAsVisibleByTeam = BaseNPC->GetOffset("m_iTaggedAsVisibleByTeam");
    m_vecAbsOrigin = CGameSceneNode->GetOffset("m_vecAbsOrigin");
    m_pGameSceneNode = BaseEntity->GetOffset("m_pGameSceneNode");
    m_iHealthBarOffset = BaseNPC->GetOffset("m_iHealthBarOffset");


    return;
}


void OnInject()  ////////////////////////////////////////////////////////////////////////////////////
{

    GetModules();


}

