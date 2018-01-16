# Anti-Car-Troll-rAct-

What is this:
First of all its a Anti car troll (rA.c.t) and what it does is it counters most if not all of the car trolling cheats now i can't give you a 100% that this will counter all but it will do its best against them and by car troll i mean people ambushing other drivers, i never saw this concept (my concept) applied anywhere and i actually don't see any anti car troll scripts around so here it is.
=====

Included Features:
I made this VERY user friendly, 3 defines:
Code:
1- 
// Un-Comment this part if you want the safe-extreme mode, will remove the player from the vehicle only. 
//#define Extreme_Safe 
2-// UN-Comment this part if you want it to ban. 
//#define BanVersion 
3- // Un-Comment this part if you want to use the OnPlayerCarTroll(playerid,vehicleid) function manually. 
//#define ManualUse  
You can use any of those but i recommend leaving all default YOU CANT USE (UNCOMMENT) MORE THAN ONE! the order is that extreme_safe will take over ban version and manual use will take over both. And its a kick by default.
======

Usage:
Very very simple, download the include from the link i will provide and do #include <name of the file> then compile, if you uncomment the safe mode or the ban version you dont have to add anything BUT if you uncomment the Manual Use you will have to use the function OnPlayerCarTroll(playerid,vehicleid) and do whatever you want to the player.
  
======
Mechanism:
When players use car troll cheats they become the drivers of a vehicle that already has a driver, so the car has 2 drivers (samp-ely impossible) so the first car driver is innocent but the second one who entered to troll is the cheater, this will detect that second player, I've seen some cheats functioning on this and i had to remove my speed boost ban because some people did troll cheats that boosted other players and BOTH players ended up banned (proves my theory of 2 drivers 1 car) so this will try to prevent that.
