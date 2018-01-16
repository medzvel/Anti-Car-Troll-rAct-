//Anti car troll include by RogueDrifter Jan 15th 2018.

#if defined _AntiCarTroll_included
    #endinput
#endif

#define _AntiCarTroll_included

#include <a_samp>

new AllVehicles[MAX_VEHICLES], ActTimer[MAX_PLAYERS], bool:VehicleTaken[MAX_VEHICLES], VehicleTempOwner[MAX_VEHICLES], pVehicleID[MAX_PLAYERS], ResetTAct[MAX_PLAYERS], bool:ActAntiSpam[MAX_PLAYERS], bool:AntiJackBug[MAX_PLAYERS], SafeTimer;

#if defined OnPlayerEnterVehicleACT
forward OnPlayerEnterVehicleACT(playerid, vehicleid, ispassenger);
#endif

#if defined OnPlayerConnectACT
forward OnPlayerConnectACT(playerid);
#endif

#if defined OnPlayerDisconnectACT
forward OnPlayerDisconnectACT(playerid, reason);
#endif

#if defined OnPlayerExitVehicleACT
forward OnPlayerExitVehicleACT(playerid, vehicleid);
#endif
#if defined OnPlayerDeathACT
forward OnPlayerDeathACT(playerid, killerid, reason);
#endif

#if defined OnPlayerStateChangeACT
forward OnPlayerStateChangeACT(playerid,newstate,oldstate);
#endif

// UN-Comment this part if you want it to ban.
//#define BanVersion

// Un-Comment this part if you want to use the OnPlayerCarTroll(playerid,vehicleid) function manually.
//#define ManualUse

// Un-Comment this part if you want the safe-extreme mode, will remove the player from the vehicle.
//#define Extreme_Safe

#if defined FILTERSCRIPT

forward OnFilterScriptInitACT();
public OnFilterScriptInit()
{
		print("		[[--|| rACT V1.0 ||--]]		");
		print("		[[--|| Anti car troll by RogueDrifter V 1.0 ||--]]		");
		print("		[[--|| Successfully Loaded! ||--]]		");
		SafeTimer = SetTimer("SafeReset",5000,true);
			#if defined OnFilterScriptInitACT
		return OnFilterScriptInitACT();
		#else
		return 1;
  			#endif
}

forward OnFilterScriptExitACT();
public OnFilterScriptExit()
{
	for(new i=0;i<MAX_PLAYERS;i++)
	{
		KillTimer(ActTimer[i]);
	}
	KillTimer(SafeTimer);
	#if defined OnFilterScriptExitACT
		return OnFilterScriptExitACT();
		#else
		return 1;
  			#endif
}

#else

forward OnGameModeInitACT();
public OnGameModeInit()
{
		print("		[[--|| rACT V1.0 ||--]]		");
		print("		[[--|| Anti car troll by RogueDrifter V 1.0 ||--]]		");
		print("		[[--|| Successfully Loaded! ||--]]		");
		SafeTimer = SetTimer("SafeReset",5000,true);
		#if defined OnGameModeInitACT
		return OnGameModeInitACT();
		#else
		return 1;
  			#endif
}

forward OnGameModeExitACT();
public OnGameModeExit()
{
	for(new i=0;i<MAX_PLAYERS;i++)
	{
		KillTimer(ActTimer[i]);
	}
	KillTimer(SafeTimer);
	#if defined OnGameModeExitACT
		return OnGameModeExitACT();
		#else
		return 1;
  			#endif
}

#endif

stock IsPEnExCar(playerid)
{
	new playeranim = GetPlayerAnimationIndex(playerid);
	if (((playeranim == 1041) || (playeranim == 1012)) || (playeranim == 1025) || (playeranim == 1044) ||
	(playeranim == 1010) || (playeranim == 1011) || (playeranim == 1024 || (playeranim == 1043) || (playeranim == 1009))) return 1;
 	else return 0;
}

forward SafeReset();
public SafeReset()
{
    for(new i=0; i<MAX_PLAYERS; i++)
	{
    	if(GetPlayerState(i)== PLAYER_STATE_DRIVER && AllVehicles[GetPlayerVehicleID(i)] != i )
    	{
			AllVehicles[GetPlayerVehicleID(i)]= i;
			VehicleTaken[GetPlayerVehicleID(i)]= true;
    		}
		}
	for(new x=0; x<MAX_VEHICLES; x++)
	{
		if(AllVehicles[x] != -1)
		{
			if(GetPlayerState(AllVehicles[x]) != PLAYER_STATE_DRIVER) AllVehicles[x] = -1;
			}
		if(AllVehicles[x] == -1 && VehicleTaken[x])
		{
			VehicleTaken[x]= false;
			}
		}
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	for(new i=0;i<MAX_PLAYERS;i++)
	{
		if(!ispassenger && !AntiJackBug[playerid] && i != playerid && GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER)
		{
			AntiJackBug[playerid]=true;
			SetTimerEx("sActReset",6000,false,"d",playerid);
			AntiJackBug[i]=true;
			SetTimerEx("sActReset",6000,false,"d",i);
			}
		}
		#if defined OnPlayerEnterVehicleACT
		return OnPlayerEnterVehicleACT(playerid, vehicleid, ispassenger);
		#else
		return 1;
  			#endif
}

public OnPlayerConnect(playerid)
{
	ActAntiSpam[playerid]=false;
	AntiJackBug[playerid]=false;
	ActTimer[playerid] = SetTimerEx("AntiCarTroll",2500,true,"d",playerid);
		#if defined OnPlayerConnectACT
		return OnPlayerConnectACT(playerid);
		#else
		return 1;
  			#endif
}

forward AntiCarTroll(playerid);
public AntiCarTroll(playerid)
{
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
	if(VehicleTaken[i] && GetPlayerVehicleID(playerid) == i && playerid != VehicleTempOwner[i] && !AntiJackBug[playerid] && !AntiJackBug[VehicleTempOwner[i]] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPEnExCar(playerid))
	{
	    #if defined ManualUse
	    #if defined OnPlayerCarTroll
	    	return OnPlayerCarTroll(playerid,i);
    	#endif
	    #else
		new pName[MAX_PLAYER_NAME],actmsg[80];
		GetPlayerName(playerid,pName,sizeof(pName));
  		#if defined Extreme_Safe
		if(!ActAntiSpam[playerid])
		{
		    ActAntiSpam[playerid]=true;
			SetPlayerHealth(playerid,0);
			format(actmsg,sizeof(actmsg),".: Server has scanned %s for Car Troll Cheats :.",pName);
			SendClientMessageToAll(0xAA3333AA,actmsg);
			}
	    #else
		#if defined BanVersion
		format(actmsg,sizeof(actmsg),".: Server has banned %s, reason: Car Troll Cheats :.",pName);
		#else
        format(actmsg,sizeof(actmsg),".: Server has kicked %s, reason: Car Troll Cheats :.",pName);
		#endif
		if(!ActAntiSpam[playerid])
		{
		    ActAntiSpam[playerid]=true;
			SendClientMessageToAll(0xFF0000A,actmsg);
			SetTimerEx("ActDelay",250,false,"d",playerid);
			}
		#endif
			#endif
		}
	}
	return 1;
}

#if defined ManualUse
	#if defined OnPlayerCarTroll
	forward OnPlayerCarTroll(playerid,vehicleid);
	#endif

#else

forward ActDelay(playerid);
public ActDelay(playerid)
{
	#if defined BanVersion
	Ban(playerid);
	#else
	Kick(playerid);
	#endif
	return 1;
}

#endif

forward ActReset(playerid);
public ActReset(playerid)
{
	VehicleTaken[pVehicleID[playerid]] = false;
	VehicleTempOwner[pVehicleID[playerid]] = -1;
	return 1;
}

forward sActReset(playerid);
public sActReset(playerid)
{
	AntiJackBug[playerid]=false;
	return 1;
}

public OnPlayerStateChange(playerid,newstate,oldstate)
{
		if(newstate == PLAYER_STATE_DRIVER)
		{
		    pVehicleID[playerid] = GetPlayerVehicleID(playerid);
	    	if(!VehicleTaken[pVehicleID[playerid]])
			{
			    KillTimer(ResetTAct[playerid]);
			    pVehicleID[playerid] = GetPlayerVehicleID(playerid);
				VehicleTaken[pVehicleID[playerid]] = true;
				VehicleTempOwner[pVehicleID[playerid]] = playerid;
			}
		}
		else if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
		{
		ResetTAct[playerid] = SetTimerEx("ActReset",500,false,"d",playerid);
		}
		#if defined OnPlayerStateChangeACT
		return OnPlayerStateChangeACT(playerid,newstate,oldstate);
		#else
		return 1;
  			#endif
}

public OnPlayerDeath(playerid, killerid, reason)
{
    ActAntiSpam[playerid]=false;
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		ResetTAct[playerid] = SetTimerEx("ActReset",500,false,"d",playerid);
	    }
		#if defined OnPlayerDeathACT
		return OnPlayerDeathACT(playerid, killerid, reason);
		#else
		return 1;
  			#endif
}

public OnPlayerExitVehicle(playerid,vehicleid)
{
	ResetTAct[playerid] = SetTimerEx("ActReset",500,false,"d",playerid);
	#if defined OnPlayerExitVehicleACT
		return OnPlayerExitVehicleACT(playerid, vehicleid);
		#else
		return 1;
  			#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	KillTimer(ActTimer[playerid]);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    VehicleTaken[GetPlayerVehicleID(playerid)] =false;
	    VehicleTempOwner[GetPlayerVehicleID(playerid)] = -1;
	    }
		#if defined OnPlayerDisconnectACT
		return OnPlayerDisconnectACT(playerid, reason);
		#else
		return 1;
  			#endif
}

#if defined _ALS_OnPlayerStateChange
  #undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange OnPlayerStateChangeACT

#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect OnPlayerConnectACT

#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect OnPlayerDisconnectACT

#if defined _ALS_OnPlayerExitVehicle
  #undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif

#define OnPlayerExitVehicle OnPlayerExitVehicleACT

#if defined _ALS_OnPlayerDeath
  #undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath OnPlayerDeathACT

#if defined _ALS_OnFilterScriptInit
  #undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit OnFilterScriptInitACT

#if defined _ALS_OnFilterScriptExit
  #undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit OnFilterScriptExitACT

#if defined _ALS_OnGameModeInit
  #undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit OnGameModeInitACT

#if defined _ALS_OnGameModeExit
  #undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit OnGameModeExitACT

#if defined _ALS_OnPlayerEnterVehicle
  #undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif

#define OnPlayerEnterVehicle OnPlayerEnterVehicleACT
