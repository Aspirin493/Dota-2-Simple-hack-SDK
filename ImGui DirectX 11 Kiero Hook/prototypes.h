#pragma once
#define cc const char*
#define Colors(r,g,b) (\(u32)r |\(u32)(g << 8) | \(u32)(b << 16) | \(u32)(255 << 24)\)
#define u64 unsigned long long
#define VT_METHOD(region, index) (*(ui*)(*(ui*)region + index * 8))
#define ui unsigned long long
#include <Windows.h>
#include <iostream>
#include "vector.h"
#include <set>
u64 CEngineClient;

u64 ParticleManager;


class CGameEntitySystem;
class CEntityInstance;
class CBaseEntity;
class C_DOTAPlayer;
class CDOTA_Ability;
class Matrix
{
public:
	float m[16];
};
struct Vector3
{
	float x, y, w;
};

struct DrawManaData
{
	int x, y, current, max;
	bool hidden;
};

struct AbilityWarning
{
	cc ability;
	bool onScreen;
	int x, y;
};

struct Enemy {
	float mana, maxMana;
	int x, y;
	std::time_t timestamp;
	bool onScreen, isAlive, inVision;
};

struct Vector4
{
	float x, y, z, w;
};

class FVector {
public:
	float x;
	float y;
	float z;
};

class FVector2
{
public:
	float x, y;
};
enum class DotaUnitOrder_t : int {
	DOTA_UNIT_ORDER_NONE = 0,
	DOTA_UNIT_ORDER_MOVE_TO_POSITION = 1,
	DOTA_UNIT_ORDER_MOVE_TO_TARGET = 2,
	DOTA_UNIT_ORDER_ATTACK_MOVE = 3,
	DOTA_UNIT_ORDER_ATTACK_TARGET = 4,
	DOTA_UNIT_ORDER_CAST_POSITION = 5,
	DOTA_UNIT_ORDER_CAST_TARGET = 6,
	DOTA_UNIT_ORDER_CAST_TARGET_TREE = 7,
	DOTA_UNIT_ORDER_CAST_NO_TARGET = 8,
	DOTA_UNIT_ORDER_CAST_TOGGLE = 9,
	DOTA_UNIT_ORDER_HOLD_POSITION = 10,
	DOTA_UNIT_ORDER_TRAIN_ABILITY = 11,
	DOTA_UNIT_ORDER_DROP_ITEM = 12,
	DOTA_UNIT_ORDER_GIVE_ITEM = 13,
	DOTA_UNIT_ORDER_PICKUP_ITEM = 14,
	DOTA_UNIT_ORDER_PICKUP_RUNE = 15,
	DOTA_UNIT_ORDER_PURCHASE_ITEM = 16,
	DOTA_UNIT_ORDER_SELL_ITEM = 17,
	DOTA_UNIT_ORDER_DISASSEMBLE_ITEM = 18,
	DOTA_UNIT_ORDER_MOVE_ITEM = 19,
	DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO = 20,
	DOTA_UNIT_ORDER_STOP = 21,
	DOTA_UNIT_ORDER_TAUNT = 22,
	DOTA_UNIT_ORDER_BUYBACK = 23,
	DOTA_UNIT_ORDER_GLYPH = 24,
	DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH = 25,
	DOTA_UNIT_ORDER_CAST_RUNE = 26,
	DOTA_UNIT_ORDER_PING_ABILITY = 27,
	DOTA_UNIT_ORDER_MOVE_TO_DIRECTION = 28,
	DOTA_UNIT_ORDER_PATROL = 29,
	DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION = 30,
	DOTA_UNIT_ORDER_RADAR = 31,
	DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK = 32,
	DOTA_UNIT_ORDER_CONTINUE = 33,
	DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED = 34,
	DOTA_UNIT_ORDER_CAST_RIVER_PAINT = 35,
	DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT = 36,
};
enum PlayerOrderIssuer_t : int {
	DOTA_ORDER_ISSUER_SELECTED_UNITS = 0,
	DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY = 1,
	DOTA_ORDER_ISSUER_HERO_ONLY = 2,
	DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY = 3
};
enum OrderQueueBehavior_t : int {
	DOTA_ORDER_QUEUE_DEFAULT = 0,
	DOTA_ORDER_QUEUE_NEVER = 1,
	DOTA_ORDER_QUEUE_ALWAYS = 2,
};
class ParticleNames
{

public:
	cc truesight = "particles/items_fx/necronomicon_true_sight.vpcf";
	cc aegisrespawn = "particles/items_fx/aegis_respawn.vpcf";
	cc aurashivas = "particles/items_fx/aura_shivas.vpcf";
	cc auravlads = "particles/items_fx/aura_vlads_ring.vpcf";
	cc auraendurance = "particles/items_fx/aura_endurance.vpcf";
	cc teleport_start = "particles/items2_fx/teleport_start.vpcf";
	cc teleport_end = "particles/items2_fx/teleport_end.vpcf";
	cc invoker_sunstrike = "particles/units/heroes/hero_invoker/invoker_sun_strike_team.vpcf";
	cc charge_target = "particles/units/heroes/hero_spirit_breaker/spirit_breaker_charge_target_mark.vpcf";
};
ParticleNames particlename;


struct ParticleCollection;


typedef void(__fastcall* _CMSG)(cc format, ...);
_CMSG CMSG = 0;

typedef void(__fastcall* _CLRMSG)(int*, ...);
_CLRMSG CLRMSG = 0;

typedef void(__fastcall* _DEVMSG)(cc format, ...);
_DEVMSG DEVMSG = 0;

typedef void(__fastcall* _hkOnAddEntity)(CGameEntitySystem* pointer, CBaseEntity* essence, int handle);
_hkOnAddEntity hkOnAddEntity;

typedef void(__fastcall* _hkOnRemoveEntity)(CGameEntitySystem* pointer, CBaseEntity* essence, int handle);
_hkOnRemoveEntity hkOnRemoveEntity;

typedef void* (__fastcall* _CreateInterface)(cc, int);
_CreateInterface pCreateInterface;

typedef int(__fastcall* _GetLocalPlayerIndex)(ui*, int*, int);
_GetLocalPlayerIndex GetLocalPlayerIndex;

typedef float* (__fastcall* _GetViewMatrix)(ui*, int);
_GetViewMatrix GetViewMatrix;

typedef bool(__fastcall* _IsInGame)(void);
_IsInGame IsInGame;

typedef int(__fastcall* _GetEntityIndex)(ui* example);
_GetEntityIndex GetEntIndex;

typedef void(__fastcall* _RunFrame)(ui*);
_RunFrame RunFrame;

typedef bool(__fastcall* _HasModifier)(CBaseEntity* entity, cc ModifierName);
_HasModifier HasModifier;



typedef CDOTA_Ability* (__fastcall* _FindAbilityByName)(CBaseEntity* entity, cc name);
_FindAbilityByName FindAbilityByName;

typedef bool(__fastcall* _CanBeExecuted)(CDOTA_Ability*);
_CanBeExecuted CanBeExecuted;

typedef bool(_fastcall* _IsCooldownReady)(CDOTA_Ability*);
_IsCooldownReady IsCooldownReady;

typedef bool(_fastcall* _IsInAbilityPhase)(CDOTA_Ability*);
_IsInAbilityPhase IsInAbilityPhase;

typedef int(_fastcall* _GetCastRange)(CDOTA_Ability*);
_GetCastRange GetCastRange;

typedef int(_fastcall* _oGetAbilityDamage)(CDOTA_Ability*);
_oGetAbilityDamage oGetAbilityDamage;

typedef float(_fastcall* _GetCastRangeBonus)(CBaseEntity*, Vector, int);
_GetCastRangeBonus GetCastRangeBonus;




typedef int(__fastcall* _GetSpecialValueFor)(CDOTA_Ability*, cc);
_GetSpecialValueFor GetSpecialValueFor;


typedef void(_fastcall* _PrepareUnitOrders)(C_DOTAPlayer* player, DotaUnitOrder_t order, int entHandle, Vector movePosition, int abilityIndex, PlayerOrderIssuer_t orderIssuer, CBaseEntity* entity, bool queue, OrderQueueBehavior_t queueBehavior, bool showEffect);
_PrepareUnitOrders PrepareUnitOrders;


typedef bool(__fastcall* _W2S)(Vector&, int* x, int* y, ui*);
_W2S W2S;


typedef void(__fastcall* _GetVector)(CBaseEntity*, Vector*, Vector*, Vector*);
_GetVector oGetVector;

typedef float(__fastcall* _GetIdealMoveSpeed)(CBaseEntity*);
_GetIdealMoveSpeed GetIdealMoveSpeed;
///////////////////////////
/////////////////////////

typedef void(_fastcall* _oRunFrame)(ui*);
_oRunFrame oRunFrame;

typedef int(__fastcall* _GetState)(void);
_GetState GetState;

typedef bool(__fastcall* _IsEntityInRange)(CBaseEntity*, CBaseEntity*, float);
_IsEntityInRange IsEntityInRange;

typedef bool(__fastcall* _IsIllusion)(CBaseEntity*);
_IsIllusion IsIllusion;


typedef ui(__fastcall* _FindTypeScope)(ui, cc);
_FindTypeScope FindTypeScope;

typedef ui* (__fastcall* _FindDeclaredClass)(ui, cc);
_FindDeclaredClass FindDeclaredClass;
typedef void* (__fastcall* _OnColorChanged)(ui*);
_OnColorChanged OnColorChanged;

typedef void(__fastcall* _SendMessageToChat)(CBaseEntity*, int mode, int ID, cc message);
_SendMessageToChat SendMSG;

typedef void(_fastcall* _ClientCMDUnrestricted)(ui*, ...);
_ClientCMDUnrestricted ClientCMDUnrestricted;

template<typename... Args>
void CMD(Args...args)
{
	ClientCMDUnrestricted((ui*)CEngineClient, args...);
	return;
}






/*template<typename TYPE, u64 size>
class Array {
public:
	u64 count = 0;
	TYPE elements[size] = { 0 };
	template<typename ... T>
	TYPE* Add(T... t) {
		elements[count++] = { t... };
		return &elements[count - 1];
	}
	void Set(u64 i, TYPE& ref) {
		elements[i] = ref;
	}
	void Trim() {
		elements[--count] = { 0 };
	}
	void RemoveAndShift(u64 INDEX) {
		for (u64 i = INDEX; i < count; i++) {
			if (*(u64*)&elements[i + 1])
				Set(i, elements[i + 1]);
			else { Trim(); return; }
		}
	}
	TYPE& operator[](u64 i) {
		return elements[i];
	}
	TYPE* begin() { return &elements[0]; }
	TYPE* end() { return &elements[count]; }
}; */




enum ParticleAttachment_t : int
{
	PATTACH_INVALID = -1,
	PATTACH_ABSORIGIN = 0,
	PATTACH_ABSORIGIN_FOLLOW,
	PATTACH_CUSTOMORIGIN,
	PATTACH_CUSTOMORIGIN_FOLLOW,
	PATTACH_POINT,
	PATTACH_POINT_FOLLOW,
	PATTACH_EYES_FOLLOW,
	PATTACH_OVERHEAD_FOLLOW,
	PATTACH_WORLDORIGIN,
	PATTACH_ROOTBONE_FOLLOW,
	PATTACH_RENDERORIGIN_FOLLOW,
	PATTACH_MAIN_VIEW,
	PATTACH_WATERWAKE,
	PATTACH_CENTER_FOLLOW,
	PATTACH_CUSTOM_GAME_STATE_1,
	PATTACH_HEALTHBAR,
	MAX_PATTACH_TYPES
};
enum GameState : int
{
	DOTA_GAMERULES_STATE_INIT = 0,
	DOTA_GAMERULES_WAIT_FOR_PLAYERS_TO_LOAD,
	DOTA_GAMERULES_HERO_SELECTION,
	DOTA_GAMERULES_STRATEGY_TIME,
	DOTA_GAMERULES_PREGAME,
	DOTA_GAMERULES_GAME_IN_PROGRESS,
	DOTA_GAMERULES_POSTGAME,
	DOTA_GAMERULES_DISCONNECT,
	DOTA_GAMERULES_TEAM_SHOWCASE,
	DOTA_GAMERULES_CUSTOM_GAME_SETUP,
	DOTA_GAMERULES_WAIT_FOR_MAP_TO_LOAD
};
//////////////////////////
//////////////////////////
//////////////////////////
struct ParticleCollection;
struct ParticleStruct
{
	cc ParticleName; //0x0000
	u64 PATTACH; //0x0008
	CBaseEntity* entitys; //0x0010
	char pad[200];
};

class CDOTA_ParticleManager;
CDOTA_ParticleManager* PM;


typedef void(__fastcall* _SetControlPoint)(u64, int, FVector&);
_SetControlPoint SetControlPoint;

typedef void(__fastcall* _DestroyParticle)(CDOTA_ParticleManager*, unsigned int, bool);
_DestroyParticle DestroyParticle;

typedef void(__fastcall* _CreateParticle)(CDOTA_ParticleManager*, u64 handle, ParticleStruct*);
_CreateParticle CreateParticle;


typedef void(__fastcall* _SetControlPointFunction)(u64*, u64, FVector&);
_SetControlPointFunction SetControlPointFunction;


class Particle;
std::set<Particle*> MyParticles;

class CDOTA_ParticleManager
{
public:

	u64* vtable; //0x0008

	struct ParticleCollection
	{

		u64* vtable; //0x0008

	}; //Size: 0x0010
	struct NewParticleEffect
	{
	public:

		u64* vtable; //0x0008
		ui* unk0; //0x0010
		ui* NewParticleEffectPtrNext; //0x0018
		ui* unk1; //0x0018
		ParticleCollection* ParticleCollectionPtr; //0x0020

	}; //Size: 0x0028
	struct ParticleItem
	{
		ui* unk0; //0x0000
		ui* unk1; //0x0008
		NewParticleEffect* NewParticleEffectPtr; //0x0010
		ui* unk2; //0x0018
		uint32_t Handle; //0x0020
	}; //Size: 0x0058
	struct ParticleList
	{
		ParticleItem* items[100]; //0x0000
	}; //Size: 0x0008

	uint32_t GetParticleCount()
	{
		return *(uint32_t*)((ui)this + 0x80);
	}

	ParticleList* GetParticleList() //0x0090
	{
		return *(ParticleList**)((ui)this + 0x88);
	}
	uint32_t CurrentHandle() //0x00A0
	{
		return *(uint32_t*)((ui)this + 0x98);
	}
	void IncHandle() {

		*(uint32_t*)((ui)this + 0x98) = (uint32_t)(CurrentHandle() + 1);
	}

	void DeleteParticle(cc _name, CBaseEntity* entity, bool bImmediately);


};

class Particle
{
public:
	cc name;
	ParticleAttachment_t attachtype;
	unsigned long handle;
	CBaseEntity* ent;
	float duration;
	float lifespan;
	bool bye = 0;
	Particle(cc _name, ParticleAttachment_t _attachtype, CBaseEntity* entitys, float _duration, float _lifespan)
	{
		name = _name;
		attachtype = _attachtype;
		ent = entitys;
		ParticleStruct particle{ name, attachtype, ent };


		PM = *(CDOTA_ParticleManager**)ParticleManager;

		handle = PM->CurrentHandle(); // particle handle
		CreateParticle(PM, handle, &particle);
		PM->IncHandle();
	}
	Particle() {};
	void SetControlPoint(u64 index, FVector& data)
	{

		unsigned long particlecount = PM->GetParticleCount();
		CDOTA_ParticleManager::ParticleList* MyList = PM->GetParticleList();
		for (int i = 0; i < particlecount; i++)
		{
			//CMSG("%d)Particle handle %dn \n",i, MyList->items[i]->Handle);
			if (MyList->items[i]->Handle == handle)
			{
				if (!SetControlPointFunction)
				{
					SetControlPointFunction = (_SetControlPointFunction)(VT_METHOD((MyList->items[i]->NewParticleEffectPtr->ParticleCollectionPtr), 15));
				}
				SetControlPointFunction((ui*)(MyList->items[i]->NewParticleEffectPtr->ParticleCollectionPtr), index, data);
			}
		}
		return;
	}
};

void CDOTA_ParticleManager::DeleteParticle(cc _name, CBaseEntity* entity, bool bImmediately)
{
	for (Particle* myprt : MyParticles)
	{
		if (myprt->name == _name)
		{
			if (myprt->ent == entity)
			{
				DestroyParticle(PM, myprt->handle, bImmediately);
				MyParticles.erase(myprt);
				return;
			}
		}
	}
	return;
}






class ParticleContainer
{
public:

	ui count = 0;
	ui size = 0;

	Particle* Add(cc _name, ParticleAttachment_t _attach, CBaseEntity* _ent, float _duration, float _lifespan)
	{
		Particle* particle = new Particle(_name, _attach, _ent, _duration, _lifespan);
		//particle = {_name, _attach, _ent, _duration, _lifespan};
		//Particle* particleptr = &particle;

		MyParticles.insert(particle);
		return particle;
	}
	void Remove(Particle* param)
	{
		;
		for (Particle* particle : MyParticles)
		{
			if (particle->name == param->name && particle->ent == param->ent && particle->attachtype == param->attachtype)
			{
				//MyParticles.erase(particle);
				//MyParticles.erase(std::find(MyParticles.begin(), MyParticles.end(), particle));

				MyParticles.erase(particle);

				break;
			}

		}
		;

	}
	Particle* Create(cc _name, ParticleAttachment_t _attach, CBaseEntity* _ent, float _duration, float _lifespan)
	{
		if (!PM->vtable)
		{
			PM = *(CDOTA_ParticleManager**)ParticleManager;
		}
		bool isEmpty = MyParticles.empty();
		if (MyParticles.size() >= 1)
		{
			for (Particle* particle : MyParticles)
			{
				if (particle->name == _name)
				{
					if (particle->ent == _ent)
						return particle;
				}
			}
		}
		return Add(_name, _attach, _ent, _duration, _lifespan);
	}
};

ParticleContainer* particlecontainer;
ParticleContainer* pt = new ParticleContainer;
class CUIPanel;

class CPanel2D
{
public:
	ui* vmt; //0x0000
	CUIPanel* cuipanel; //0x0008
}; //Size: 0x0010

typedef void(__fastcall* _LoadLayout)(u64*, cc, bool);
_LoadLayout LoadLayout;

class CUIPanel
{
public:
	ui* vmt; //0x0000
	CPanel2D* CPanel2DPtr; //0x0008
	cc ID; //0x0010
	ui* CUIPanel_parentPtr; //0x0018
	ui* CTopLevelWindowPtr; //0x0020
	int64_t children; //0x0028
	CUIPanel* ChildList[]; //0x0030

	CUIPanel* GetChild(int child) {
		if (child == -1) return this;
		if (child >= children) return 0;
		return ChildList[child];
	}
	void BLoadLayout(cc string)
	{
		if (!LoadLayout)
		{
			LoadLayout = (_LoadLayout)(VT_METHOD(this, 14));
		}
		LoadLayout((ui*)this, string, 1);
	}

};
class Panorama;



typedef CPanel2D* (__fastcall* _CreatePanel)(Panorama*, WORD*, cc, CUIPanel*);
_CreatePanel oCreatePanel;

typedef void(__fastcall* _GetPanelType)(WORD*, cc);
_GetPanelType oGetPanelType;


class PanelItem
{
public:
	CUIPanel* panel;


};
ui* firstpanel = nullptr;
class PanelList
{
public:
	ui* unk; //0x0000
	ui* unk1; //0x0008
	CUIPanel* FirstPanel; //0x0010


	CUIPanel* GetPanelByIndex(int index)
	{
		if (firstpanel == nullptr)
		{
			firstpanel = (ui*)((ui)this + 0x10);
		}

		if (*(ui*)((ui)firstpanel + index * 0x20))
		{
			return *(CUIPanel**)((ui)firstpanel + index * 0x20);
		}
		return (CUIPanel*)firstpanel;
	}


	/*CUIPanel* GetNext()
	{
		if (*(ui*)((ui)this + 0x20))
		{
			return *(CUIPanel**)((ui)this + 0x20);
		}
	}*/
	CUIPanel** GetFirstPanel()
	{
		return (CUIPanel**)((ui)this + 0x10);
	}

	CUIPanel** GetNextPanel(CUIPanel** item)
	{
		CUIPanel** result = item + 0x20;
		if (result)
		{
			return result;
		}
		return nullptr;
	}


};
PanelList* pPanelList;



class Panorama
{
public:

	CUIPanel* CreatePanel(Panorama* panoramaptrs, cc ID)
	{

		CUIPanel* HUD = panoramaptrs->FindPanelById("DotaHud");

		WORD result = 0;
		WORD thisresult = panoramaptrs->GetPanelType(this, result, "Panel");

		if (!oCreatePanel)
		{
			oCreatePanel = (_CreatePanel)(VT_METHOD(this, 29));
		}
		WORD some = thisresult;

		CPanel2D* mypanel = oCreatePanel(this, &some, ID, HUD);
		CUIPanel* newresult = mypanel->cuipanel;
		return newresult;

	}

	CUIPanel* FindPanelById(cc _ID)
	{
		CUIPanel* element = pPanelList->FirstPanel;
		//for (element = pPanelList->GetFirstPanel(); ; pPanelList->GetNextPanel(element))
		for (int i = 0; ; element = pPanelList->GetPanelByIndex(i++))
		{
			CMSG("Index: %d , Address: %p, ID: %s\n", i, element, element->ID);
			if (element)
			{
				if (element->ID)
				{
					bool tocheck = strcmp(element->ID, _ID);
					if (!tocheck)
					{
						return element;
					}
				}

			}
		}
		CMSG("CHEAT:   Couldn't find panel id: %s\n", _ID);
	}

	PanelList* GetPanelList()
	{
		return *(PanelList**)((ui)this + 0xF0);
	}


	WORD GetPanelType(Panorama* panoramaptrs, WORD word, cc PanelType)
	{

		WORD RESULT = 0;


		oGetPanelType(&RESULT, "Panel");
		return RESULT;
	}

};


