/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
#include "g_local.h"

#define	MISSILE_PRESTEP_TIME	50

/* rkh oscpack definitions for c++ wrappers */
//#include "../osc/test.h"
#include "../osc/osc.h"
// test comment
// test comment 2
/*
================
G_ExplodeMissile

Explode a missile without an impact
================
*/
void G_ExplodeMissile( gentity_t *ent ) {

// rkh - added this conditional to try to turn on/off exploding
// works - now add g_homing and g_plasma and checks for ent->type on each

//	trap_SendServerCommand( -1, va("print\"%s\"", ent->classname ));
/*
	if ((g_homing_status.integer==1)&&(g_homing_persist.integer==1)) {
	if ((strcmp(ent->classname, "bfg"))&&(g_plasma_persist.integer==1)) {
		ent->nextthink = level.time + 60;
	}
	else if ((strcmp(ent->classname, "plasma"))&&(g_bfg_persist.integer==1)) {
		ent->nextthink = level.time + 60;
	}
	else {
    */

// end rkh
	vec3_t		dir;
	vec3_t		origin;

	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );
	SnapVector( origin );
	G_SetOrigin( ent, origin );

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( dir ) );

	ent->freeAfterEvent = qtrue;

	// splash damage
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent
			, ent->splashMethodOfDeath ) ) {
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
		}
	}

	//trap_SendServerCommand( -1, va("print \"explode\""));
	// rkh - osc send flag
	int i;

	if (osc_send_projectile.integer == 1)
	{
		osc_projectile_vars currentProjectile;
		currentProjectile.ownernum = ent->r.ownerNum;
		currentProjectile.projectilenum = ent->s.number;//ent->entityNum;
		//currentProjectile.hostname = osc_projectile_hostname.string;
		currentProjectile.port = osc_projectile_port.string;
		currentProjectile.origin[0] = ent->r.currentOrigin[0];
		currentProjectile.origin[1] = ent->r.currentOrigin[1];
		currentProjectile.origin[2] = ent->r.currentOrigin[2];
		currentProjectile.bounce = 0;
		currentProjectile.explode = 1;
		currentProjectile.classname = ent->classname;
//		sendOSCmessage_projectile(currentProjectile);

		if(slork_switch.integer == 0) {
			currentProjectile.hostname = osc_projectile_hostname.string;

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile); //, "explode");
		}
		else if(slork_switch.integer == 1) {

		    switch (currentProjectile.ownernum) {
			case 0:
				currentProjectile.hostname = osc_hostname1.string;
				break;
			case 1:
				currentProjectile.hostname = osc_hostname2.string;
				break;
			case 2:
				currentProjectile.hostname = osc_hostname3.string;
				break;
			case 3:
				currentProjectile.hostname = osc_hostname4.string;
				break;
			case 4:
				currentProjectile.hostname = osc_hostname5.string;
				break;
			case 5:
				currentProjectile.hostname = osc_hostname6.string;
				break;
			case 6:
				currentProjectile.hostname = osc_hostname7.string;
				break;
			case 7:
				currentProjectile.hostname = osc_hostname8.string;
				break;
			case 8:
				currentProjectile.hostname = osc_hostname9.string;
				break;
			case 9:
				currentProjectile.hostname = osc_hostname10.string;
				break;
			case 10:
				currentProjectile.hostname = osc_hostname11.string;
				break;
			case 11:
				currentProjectile.hostname = osc_hostname12.string;
				break;
			case 12:
				currentProjectile.hostname = osc_hostname13.string;
				break;
			case 13:
				currentProjectile.hostname = osc_hostname14.string;
				break;
			case 14:
				currentProjectile.hostname = osc_hostname15.string;
				break;
			case 15:
				currentProjectile.hostname = osc_hostname16.string;
				break;
			case 16:
				currentProjectile.hostname = osc_hostname17.string;
				break;
			case 17:
				currentProjectile.hostname = osc_hostname18.string;
				break;
			case 18:
				currentProjectile.hostname = osc_hostname19.string;
				break;
			case 19:
				currentProjectile.hostname = osc_hostname20.string;
				break;
			default:
				currentProjectile.hostname = osc_client_hostname.string;
			}

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile);//, "homing");
		}
		else if(slork_switch.integer > 1) {

			// send all osc data to slork_switch.integer number of clients
			for(i = 0; i<slork_switch.integer; i++) {

				//currentClient.hostname = currentClient.hostnames[i];

			     switch (i) {
				case 0:
					currentProjectile.hostname = osc_hostname1.string;
					break;
				case 1:
					currentProjectile.hostname = osc_hostname2.string;
					break;
				case 2:
					currentProjectile.hostname = osc_hostname3.string;
					break;
				case 3:
					currentProjectile.hostname = osc_hostname4.string;
					break;
				case 4:
					currentProjectile.hostname = osc_hostname5.string;
					break;
				case 5:
					currentProjectile.hostname = osc_hostname6.string;
					break;
				case 6:
					currentProjectile.hostname = osc_hostname7.string;
					break;
				case 7:
					currentProjectile.hostname = osc_hostname8.string;
					break;
				case 8:
					currentProjectile.hostname = osc_hostname9.string;
					break;
				case 9:
					currentProjectile.hostname = osc_hostname10.string;
					break;
				case 10:
					currentProjectile.hostname = osc_hostname11.string;
					break;
				case 11:
					currentProjectile.hostname = osc_hostname12.string;
					break;
				case 12:
					currentProjectile.hostname = osc_hostname13.string;
					break;
				case 13:
					currentProjectile.hostname = osc_hostname14.string;
					break;
				case 14:
					currentProjectile.hostname = osc_hostname15.string;
					break;
				case 15:
					currentProjectile.hostname = osc_hostname16.string;
					break;
				case 16:
					currentProjectile.hostname = osc_hostname17.string;
					break;
				case 17:
					currentProjectile.hostname = osc_hostname18.string;
					break;
				case 18:
					currentProjectile.hostname = osc_hostname19.string;
					break;
				case 19:
					currentProjectile.hostname = osc_hostname20.string;
					break;
				default:
					currentProjectile.hostname = osc_client_hostname.string;
					break;
				}

				if(osc_bundle.integer == 1)
					sendOSCbundle_projectile(currentProjectile);
				else
					sendOSCmessage_projectile(currentProjectile);//, "homing");
			}
		}
	}

	trap_LinkEntity( ent );
	}


/*
=================
G_HomingMissle: rkh homing mod
=================
*/
/*
void G_HomingMissle( gentity_t *ent )
{
	gentity_t *target = NULL;
	gentity_t *rad = NULL;
	vec3_t dir, dir2, raddir, start;
//	while ((rad = findradius(rad, ent->r.currentOrigin, 1000)) != NULL)
// rkh - added g_homing_radius.integer as radius for homing scan for entities/clients
	while ((rad = findradius(rad, ent->r.currentOrigin, g_homing_radius.integer)) != NULL)

	{
		if (!rad->client)
			continue;
		if((rad != ent->parent) && (ent->parent->client->pers.homing_parent_only == 1))
			continue;
		//enable parent homing when triggered
		// was: if ((rad == ent->parent)
		if ((rad == ent->parent) && (ent->parent->client->pers.homing_parent==0))
			continue;
		if (rad->health <=0)
			continue;
		if (rad->client->sess.sessionTeam == TEAM_SPECTATOR)
			continue;
		if ( (g_gametype.integer == GT_TEAM || g_gametype.integer == GT_CTF) && rad->client->sess.sessionTeam == rad->parent->client->sess.sessionTeam)
			continue;
		if (!visible (ent, rad))
			continue;

		VectorSubtract(rad->r.currentOrigin, ent->r.currentOrigin, raddir);
		raddir[2] += 16;
		if ((target == NULL) || (VectorLength(raddir) < VectorLength(dir)))
		{
			target = rad;
			VectorCopy(raddir, dir);
		}
	}

	if (target != NULL)
	{
//		int test = foo(1);// test rkh
//client->ps.clientNum
		VectorCopy( ent->r.currentOrigin, start );
		VectorCopy( ent->r.currentAngles, dir2 );
		VectorNormalize(dir);
		VectorScale(dir, 0.2, dir);
		VectorAdd(dir, dir2, dir);
		VectorNormalize(dir);
		VectorCopy( start, ent->s.pos.trBase );
//		VectorScale( dir, test, ent->s.pos.trDelta ); //test rkh
		VectorScale( dir, g_homing_speed.integer, ent->s.pos.trDelta ); //400
//		VectorScale( dir, testfoo, ent->s.pos.trDelta );
//		trap_SendServerCommand( -1, va("print \"this is a test\""));
		SnapVector( ent->s.pos.trDelta );
		VectorCopy (start, ent->r.currentOrigin);
		VectorCopy (dir, ent->r.currentAngles);
	}

	// rkh - added for persist-ending in homing missles
	if ((strcmp(ent->classname, "bfg")) && (g_plasma_homing_persist.integer==0)) {
			ent->nextthink = level.time + 60;
			ent->think = G_ExplodeMissile;
	}
	else if ((strcmp(ent->classname, "plasma")) && (g_bfg_homing_persist.integer==0)) {
			ent->nextthink = level.time + 60;
			ent->think = G_ExplodeMissile;
	}
	else {
		ent->nextthink = level.time + 60;
	}
	//rkh - original
	ent->nextthink = level.time + 100;

/* ===================================================================================
This is where missle characteristics are sent out over OSC...

ent->s.number;		individual entity number per level
ent->classname;		classname e.g. "rocket"
ent-r.ownerNum;		pwner/shooter of each rocket entity
ent->r.currentOrigin[0]	coordinate (x?)
ent->r.currentOrigin[1]	coordinate (y?)
ent->r.currentOrigin[2]	coordinate (z?)

=================================================================================== */
	// RKH - send rocket position out over OSC
	/*
	int i;

	if (osc_send_projectile.integer == 1)
	{
		osc_projectile_vars currentProjectile;
		currentProjectile.ownernum = ent->r.ownerNum;
		currentProjectile.projectilenum = ent->s.number;//ent->entityNum;
		//currentProjectile.hostname = osc_projectile_hostname.string;
		currentProjectile.port = osc_projectile_port.string;
		currentProjectile.origin[0] = ent->r.currentOrigin[0];
		currentProjectile.origin[1] = ent->r.currentOrigin[1];
		currentProjectile.origin[2] = ent->r.currentOrigin[2];
		currentProjectile.bounce = 0;
		currentProjectile.explode = 0;
		currentProjectile.classname = ent->classname;


//		sendOSCmessage_projectile(currentProjectile);

		if(slork_switch.integer == 0) {
			currentProjectile.hostname = osc_projectile_hostname.string;

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile); //, "explode");
		}
		else if(slork_switch.integer == 1) {

		    switch (currentProjectile.ownernum) {
			case 0:
				currentProjectile.hostname = osc_hostname1.string;
				break;
			case 1:
				currentProjectile.hostname = osc_hostname2.string;
				break;
			case 2:
				currentProjectile.hostname = osc_hostname3.string;
				break;
			case 3:
				currentProjectile.hostname = osc_hostname4.string;
				break;
			case 4:
				currentProjectile.hostname = osc_hostname5.string;
				break;
			case 5:
				currentProjectile.hostname = osc_hostname6.string;
				break;
			case 6:
				currentProjectile.hostname = osc_hostname7.string;
				break;
			case 7:
				currentProjectile.hostname = osc_hostname8.string;
				break;
			case 8:
				currentProjectile.hostname = osc_hostname9.string;
				break;
			case 9:
				currentProjectile.hostname = osc_hostname10.string;
				break;
			case 10:
				currentProjectile.hostname = osc_hostname11.string;
				break;
			case 11:
				currentProjectile.hostname = osc_hostname12.string;
				break;
			case 12:
				currentProjectile.hostname = osc_hostname13.string;
				break;
			case 13:
				currentProjectile.hostname = osc_hostname14.string;
				break;
			case 14:
				currentProjectile.hostname = osc_hostname15.string;
				break;
			case 15:
				currentProjectile.hostname = osc_hostname16.string;
				break;
			case 16:
				currentProjectile.hostname = osc_hostname17.string;
				break;
			case 17:
				currentProjectile.hostname = osc_hostname18.string;
				break;
			case 18:
				currentProjectile.hostname = osc_hostname19.string;
				break;
			case 19:
				currentProjectile.hostname = osc_hostname20.string;
				break;
			default:
				currentProjectile.hostname = osc_client_hostname.string;
			}

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile);//, "homing");
		}
		else if(slork_switch.integer > 1) {

			// send all osc data to slork_switch.integer number of clients
			for(i = 0; i<slork_switch.integer; i++) {

				//currentClient.hostname = currentClient.hostnames[i];

			     switch (i) {
				case 0:
					currentProjectile.hostname = osc_hostname1.string;
					break;
				case 1:
					currentProjectile.hostname = osc_hostname2.string;
					break;
				case 2:
					currentProjectile.hostname = osc_hostname3.string;
					break;
				case 3:
					currentProjectile.hostname = osc_hostname4.string;
					break;
				case 4:
					currentProjectile.hostname = osc_hostname5.string;
					break;
				case 5:
					currentProjectile.hostname = osc_hostname6.string;
					break;
				case 6:
					currentProjectile.hostname = osc_hostname7.string;
					break;
				case 7:
					currentProjectile.hostname = osc_hostname8.string;
					break;
				case 8:
					currentProjectile.hostname = osc_hostname9.string;
					break;
				case 9:
					currentProjectile.hostname = osc_hostname10.string;
					break;
				case 10:
					currentProjectile.hostname = osc_hostname11.string;
					break;
				case 11:
					currentProjectile.hostname = osc_hostname12.string;
					break;
				case 12:
					currentProjectile.hostname = osc_hostname13.string;
					break;
				case 13:
					currentProjectile.hostname = osc_hostname14.string;
					break;
				case 14:
					currentProjectile.hostname = osc_hostname15.string;
					break;
				case 15:
					currentProjectile.hostname = osc_hostname16.string;
					break;
				case 16:
					currentProjectile.hostname = osc_hostname17.string;
					break;
				case 17:
					currentProjectile.hostname = osc_hostname18.string;
					break;
				case 18:
					currentProjectile.hostname = osc_hostname19.string;
					break;
				case 19:
					currentProjectile.hostname = osc_hostname20.string;
					break;
				default:
					currentProjectile.hostname = osc_client_hostname.string;
					break;
				}

				if(osc_bundle.integer == 1)
					sendOSCbundle_projectile(currentProjectile);
				else
					sendOSCmessage_projectile(currentProjectile);//, "homing");
			}
		}
	}

}
*/
/*
================
G_BounceMissile

================
*/
void G_BounceMissile( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	if ( ent->s.eFlags & EF_BOUNCE_HALF ) {
		VectorScale( ent->s.pos.trDelta, 0.65, ent->s.pos.trDelta );
		// check for stop
		if ( trace->plane.normal[2] > 0.2 && VectorLength( ent->s.pos.trDelta ) < 40 ) {
			G_SetOrigin( ent, trace->endpos );
			return;
		}
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;

	int i;

	if (osc_send_projectile.integer == 1)
	{
		osc_projectile_vars currentProjectile;
		currentProjectile.ownernum = ent->r.ownerNum;
		currentProjectile.projectilenum = ent->s.number;//ent->entityNum;
		//currentProjectile.hostname = osc_projectile_hostname.string;
		currentProjectile.port = osc_projectile_port.string;
		currentProjectile.origin[0] = ent->r.currentOrigin[0];
		currentProjectile.origin[1] = ent->r.currentOrigin[1];
		currentProjectile.origin[2] = ent->r.currentOrigin[2];
		currentProjectile.bounce = 1;
		currentProjectile.explode = 0;
		currentProjectile.classname = ent->classname;


//		sendOSCmessage_projectile(currentProjectile);

		if(slork_switch.integer == 0) {
			currentProjectile.hostname = osc_projectile_hostname.string;

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile); //, "explode");
		}
		else if(slork_switch.integer == 1) {

		    switch (currentProjectile.ownernum) {
			case 0:
				currentProjectile.hostname = osc_hostname1.string;
				break;
			case 1:
				currentProjectile.hostname = osc_hostname2.string;
				break;
			case 2:
				currentProjectile.hostname = osc_hostname3.string;
				break;
			case 3:
				currentProjectile.hostname = osc_hostname4.string;
				break;
			case 4:
				currentProjectile.hostname = osc_hostname5.string;
				break;
			case 5:
				currentProjectile.hostname = osc_hostname6.string;
				break;
			case 6:
				currentProjectile.hostname = osc_hostname7.string;
				break;
			case 7:
				currentProjectile.hostname = osc_hostname8.string;
				break;
			case 8:
				currentProjectile.hostname = osc_hostname9.string;
				break;
			case 9:
				currentProjectile.hostname = osc_hostname10.string;
				break;
			case 10:
				currentProjectile.hostname = osc_hostname11.string;
				break;
			case 11:
				currentProjectile.hostname = osc_hostname12.string;
				break;
			case 12:
				currentProjectile.hostname = osc_hostname13.string;
				break;
			case 13:
				currentProjectile.hostname = osc_hostname14.string;
				break;
			case 14:
				currentProjectile.hostname = osc_hostname15.string;
				break;
			case 15:
				currentProjectile.hostname = osc_hostname16.string;
				break;
			case 16:
				currentProjectile.hostname = osc_hostname17.string;
				break;
			case 17:
				currentProjectile.hostname = osc_hostname18.string;
				break;
			case 18:
				currentProjectile.hostname = osc_hostname19.string;
				break;
			case 19:
				currentProjectile.hostname = osc_hostname20.string;
				break;
			default:
				currentProjectile.hostname = osc_client_hostname.string;
			}

			if(osc_bundle.integer == 1)
				sendOSCbundle_projectile(currentProjectile);
			else
				sendOSCmessage_projectile(currentProjectile);//, "homing");
		}
		else if(slork_switch.integer > 1) {

			// send all osc data to slork_switch.integer number of clients
			for(i = 0; i<slork_switch.integer; i++) {

				//currentClient.hostname = currentClient.hostnames[i];

			     switch (i) {
				case 0:
					currentProjectile.hostname = osc_hostname1.string;
					break;
				case 1:
					currentProjectile.hostname = osc_hostname2.string;
					break;
				case 2:
					currentProjectile.hostname = osc_hostname3.string;
					break;
				case 3:
					currentProjectile.hostname = osc_hostname4.string;
					break;
				case 4:
					currentProjectile.hostname = osc_hostname5.string;
					break;
				case 5:
					currentProjectile.hostname = osc_hostname6.string;
					break;
				case 6:
					currentProjectile.hostname = osc_hostname7.string;
					break;
				case 7:
					currentProjectile.hostname = osc_hostname8.string;
					break;
				case 8:
					currentProjectile.hostname = osc_hostname9.string;
					break;
				case 9:
					currentProjectile.hostname = osc_hostname10.string;
					break;
				case 10:
					currentProjectile.hostname = osc_hostname11.string;
					break;
				case 11:
					currentProjectile.hostname = osc_hostname12.string;
					break;
				case 12:
					currentProjectile.hostname = osc_hostname13.string;
					break;
				case 13:
					currentProjectile.hostname = osc_hostname14.string;
					break;
				case 14:
					currentProjectile.hostname = osc_hostname15.string;
					break;
				case 15:
					currentProjectile.hostname = osc_hostname16.string;
					break;
				case 16:
					currentProjectile.hostname = osc_hostname17.string;
					break;
				case 17:
					currentProjectile.hostname = osc_hostname18.string;
					break;
				case 18:
					currentProjectile.hostname = osc_hostname19.string;
					break;
				case 19:
					currentProjectile.hostname = osc_hostname20.string;
					break;
				default:
					currentProjectile.hostname = osc_client_hostname.string;
					break;
				}

				if(osc_bundle.integer == 1)
					sendOSCbundle_projectile(currentProjectile);
				else
					sendOSCmessage_projectile(currentProjectile);//, "homing");
			}
		}
	}
}




#ifdef MISSIONPACK
/*
================
ProximityMine_Explode
================
*/
static void ProximityMine_Explode( gentity_t *mine ) {
	G_ExplodeMissile( mine );
	// if the prox mine has a trigger free it
	if (mine->activator) {
		G_FreeEntity(mine->activator);
		mine->activator = NULL;
	}
}

/*
================
ProximityMine_Die
================
*/
static void ProximityMine_Die( gentity_t *ent, gentity_t *inflictor, gentity_t *attacker, int damage, int mod ) {
	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + 1;
}

/*
================
ProximityMine_Trigger
================
*/
void ProximityMine_Trigger( gentity_t *trigger, gentity_t *other, trace_t *trace ) {
	vec3_t		v;
	gentity_t	*mine;

	if( !other->client ) {
		return;
	}

	// trigger is a cube, do a distance test now to act as if it's a sphere
	VectorSubtract( trigger->s.pos.trBase, other->s.pos.trBase, v );
	if( VectorLength( v ) > trigger->parent->splashRadius ) {
		return;
	}


	if ( g_gametype.integer >= GT_TEAM ) {
		// don't trigger same team mines
		if (trigger->parent->s.generic1 == other->client->sess.sessionTeam) {
			return;
		}
	}

	// ok, now check for ability to damage so we don't get triggered thru walls, closed doors, etc...
	if( !CanDamage( other, trigger->s.pos.trBase ) ) {
		return;
	}

	// trigger the mine!
	mine = trigger->parent;
	mine->s.loopSound = 0;
	G_AddEvent( mine, EV_PROXIMITY_MINE_TRIGGER, 0 );
	mine->nextthink = level.time + 500;

	G_FreeEntity( trigger );
}

/*
================
ProximityMine_Activate
================
*/
static void ProximityMine_Activate( gentity_t *ent ) {
	gentity_t	*trigger;
	float		r;

	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + g_proxMineTimeout.integer;

	ent->takedamage = qtrue;
	ent->health = 1;
	ent->die = ProximityMine_Die;

	ent->s.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav" );

	// build the proximity trigger
	trigger = G_Spawn ();

	trigger->classname = "proxmine_trigger";

	r = ent->splashRadius;
	VectorSet( trigger->r.mins, -r, -r, -r );
	VectorSet( trigger->r.maxs, r, r, r );

	G_SetOrigin( trigger, ent->s.pos.trBase );

	trigger->parent = ent;
	trigger->r.contents = CONTENTS_TRIGGER;
	trigger->touch = ProximityMine_Trigger;

	trap_LinkEntity (trigger);

	// set pointer to trigger so the entity can be freed when the mine explodes
	ent->activator = trigger;
}

/*
================
ProximityMine_ExplodeOnPlayer
================
*/
static void ProximityMine_ExplodeOnPlayer( gentity_t *mine ) {
	gentity_t	*player;

	player = mine->enemy;
	player->client->ps.eFlags &= ~EF_TICKING;

	if ( player->client->invulnerabilityTime > level.time ) {
		G_Damage( player, mine->parent, mine->parent, vec3_origin, mine->s.origin, 1000, DAMAGE_NO_KNOCKBACK, MOD_JUICED );
		player->client->invulnerabilityTime = 0;
		G_TempEntity( player->client->ps.origin, EV_JUICED );
	}
	else {
		G_SetOrigin( mine, player->s.pos.trBase );
		// make sure the explosion gets to the client
		mine->r.svFlags &= ~SVF_NOCLIENT;
		mine->splashMethodOfDeath = MOD_PROXIMITY_MINE;
		G_ExplodeMissile( mine );
	}
}

/*
================
ProximityMine_Player
================
*/
static void ProximityMine_Player( gentity_t *mine, gentity_t *player ) {
	if( mine->s.eFlags & EF_NODRAW ) {
		return;
	}

	G_AddEvent( mine, EV_PROXIMITY_MINE_STICK, 0 );

	if( player->s.eFlags & EF_TICKING ) {
		player->activator->splashDamage += mine->splashDamage;
		player->activator->splashRadius *= 1.50;
		mine->think = G_FreeEntity;
		mine->nextthink = level.time;
		return;
	}

	player->client->ps.eFlags |= EF_TICKING;
	player->activator = mine;

	mine->s.eFlags |= EF_NODRAW;
	mine->r.svFlags |= SVF_NOCLIENT;
	mine->s.pos.trType = TR_LINEAR;
	VectorClear( mine->s.pos.trDelta );

	mine->enemy = player;
	mine->think = ProximityMine_ExplodeOnPlayer;
	if ( player->client->invulnerabilityTime > level.time ) {
		mine->nextthink = level.time + 2 * 1000;
	}
	else {
		mine->nextthink = level.time + 10 * 1000;
	}
}
#endif

/*
================
G_MissileImpact
================
*/
void G_MissileImpact( gentity_t *ent, trace_t *trace ) {
	gentity_t		*other;
	qboolean		hitClient = qfalse;
#ifdef MISSIONPACK
	vec3_t			forward, impactpoint, bouncedir;
	int				eFlags;
#endif
	other = &g_entities[trace->entityNum];

	// check for bounce
	if ( !other->takedamage &&
		( ent->s.eFlags & ( EF_BOUNCE | EF_BOUNCE_HALF ) ) ) {
		G_BounceMissile( ent, trace );
		G_AddEvent( ent, EV_GRENADE_BOUNCE, 0 );
		return;
	}

#ifdef MISSIONPACK
	if ( other->takedamage ) {
		if ( ent->s.weapon != WP_PROX_LAUNCHER ) {
			if ( other->client && other->client->invulnerabilityTime > level.time ) {
				//
				VectorCopy( ent->s.pos.trDelta, forward );
				VectorNormalize( forward );
				if (G_InvulnerabilityEffect( other, forward, ent->s.pos.trBase, impactpoint, bouncedir )) {
					VectorCopy( bouncedir, trace->plane.normal );
					eFlags = ent->s.eFlags & EF_BOUNCE_HALF;
					ent->s.eFlags &= ~EF_BOUNCE_HALF;
					G_BounceMissile( ent, trace );
					ent->s.eFlags |= eFlags;
				}
				ent->target_ent = other;
				return;
			}
		}
	}
#endif
	// impact damage
	if (other->takedamage) {
		// FIXME: wrong damage direction?
		if ( ent->damage ) {
			vec3_t	velocity;

			if( LogAccuracyHit( other, &g_entities[ent->r.ownerNum] ) ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				hitClient = qtrue;
			}
			BG_EvaluateTrajectoryDelta( &ent->s.pos, level.time, velocity );
			if ( VectorLength( velocity ) == 0 ) {
				velocity[2] = 1;	// stepped on a grenade
			}
			G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity,
				ent->s.origin, ent->damage,
				0, ent->methodOfDeath);
		}
	}

#ifdef MISSIONPACK
	if( ent->s.weapon == WP_PROX_LAUNCHER ) {
		if( ent->s.pos.trType != TR_GRAVITY ) {
			return;
		}

		// if it's a player, stick it on to them (flag them and remove this entity)
		if( other->s.eType == ET_PLAYER && other->health > 0 ) {
			ProximityMine_Player( ent, other );
			return;
		}

		SnapVectorTowards( trace->endpos, ent->s.pos.trBase );
		G_SetOrigin( ent, trace->endpos );
		ent->s.pos.trType = TR_STATIONARY;
		VectorClear( ent->s.pos.trDelta );

		G_AddEvent( ent, EV_PROXIMITY_MINE_STICK, trace->surfaceFlags );

		ent->think = ProximityMine_Activate;
		ent->nextthink = level.time + 2000;

		vectoangles( trace->plane.normal, ent->s.angles );
		ent->s.angles[0] += 90;

		// link the prox mine to the other entity
		ent->enemy = other;
		ent->die = ProximityMine_Die;
		VectorCopy(trace->plane.normal, ent->movedir);
		VectorSet(ent->r.mins, -4, -4, -4);
		VectorSet(ent->r.maxs, 4, 4, 4);
		trap_LinkEntity(ent);

		return;
	}
#endif

	if (!strcmp(ent->classname, "hook")) {
		gentity_t *nent;
		vec3_t v;

		nent = G_Spawn();
		if ( other->takedamage && other->client ) {

			G_AddEvent( nent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
			nent->s.otherEntityNum = other->s.number;

			ent->enemy = other;

			v[0] = other->r.currentOrigin[0] + (other->r.mins[0] + other->r.maxs[0]) * 0.5;
			v[1] = other->r.currentOrigin[1] + (other->r.mins[1] + other->r.maxs[1]) * 0.5;
			v[2] = other->r.currentOrigin[2] + (other->r.mins[2] + other->r.maxs[2]) * 0.5;

			SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth
		} else {
			VectorCopy(trace->endpos, v);
			G_AddEvent( nent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
			ent->enemy = NULL;
		}

		SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth

		nent->freeAfterEvent = qtrue;
		// change over to a normal entity right at the point of impact
		nent->s.eType = ET_GENERAL;
		ent->s.eType = ET_GRAPPLE;

		G_SetOrigin( ent, v );
		G_SetOrigin( nent, v );

		ent->think = Weapon_HookThink;
		ent->nextthink = level.time + FRAMETIME;

		ent->parent->client->ps.pm_flags |= PMF_GRAPPLE_PULL;
		VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);

		trap_LinkEntity( ent );
		trap_LinkEntity( nent );

		return;
	}

	// is it cheaper in bandwidth to just remove this ent and create a new
	// one, rather than changing the missile into the explosion?

	if ( other->takedamage && other->client ) {
		G_AddEvent( ent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
		ent->s.otherEntityNum = other->s.number;
	} else if( trace->surfaceFlags & SURF_METALSTEPS ) {
		G_AddEvent( ent, EV_MISSILE_MISS_METAL, DirToByte( trace->plane.normal ) );
	} else {
		G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
	}

	ent->freeAfterEvent = qtrue;

	// change over to a normal entity right at the point of impact
	ent->s.eType = ET_GENERAL;

	SnapVectorTowards( trace->endpos, ent->s.pos.trBase );	// save net bandwidth

	G_SetOrigin( ent, trace->endpos );

	// splash damage (doesn't apply to person directly hit)
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius,
			other, ent->splashMethodOfDeath ) ) {
			if( !hitClient ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
			}
		}
	}

	trap_LinkEntity( ent );
}

/*
================
G_RunMissile
================
*/
void G_RunMissile( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			passent;

	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// if this missile bounced off an invulnerability sphere
	if ( ent->target_ent ) {
		passent = ent->target_ent->s.number;
	}
#ifdef MISSIONPACK
	// prox mines that left the owner bbox will attach to anything, even the owner
	else if (ent->s.weapon == WP_PROX_LAUNCHER && ent->count) {
		passent = ENTITYNUM_NONE;
	}
#endif
	else {
		// ignore interactions with the missile owner
		passent = ent->r.ownerNum;
	}
	// trace a line from the previous position to the current position
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, passent, ent->clipmask );

	if ( tr.startsolid || tr.allsolid ) {
		// make sure the tr.entityNum is set to the entity we're stuck in
		trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, passent, ent->clipmask );
		tr.fraction = 0;
	}
	else {
		VectorCopy( tr.endpos, ent->r.currentOrigin );
	}
	//rkh homing mod
	//Missile_Smooth_H(ent,origin,&tr);

	trap_LinkEntity( ent );

	if ( tr.fraction != 1 ) {
		// never explode or bounce on sky
		if ( tr.surfaceFlags & SURF_NOIMPACT ) {
			// If grapple, reset owner
			if (ent->parent && ent->parent->client && ent->parent->client->hook == ent) {
				ent->parent->client->hook = NULL;
			}
			G_FreeEntity( ent );
			return;
		}
		G_MissileImpact( ent, &tr );
		if ( ent->s.eType != ET_MISSILE ) {
			return;		// exploded
		}
	}
#ifdef MISSIONPACK
	// if the prox mine wasn't yet outside the player body
	if (ent->s.weapon == WP_PROX_LAUNCHER && !ent->count) {
		// check if the prox mine is outside the owner bbox
		trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, ENTITYNUM_NONE, ent->clipmask );
		if (!tr.startsolid || tr.entityNum != ent->r.ownerNum) {
			ent->count = 1;
		}
	}
#endif
	// check think function after bouncing
	G_RunThink( ent );
}


//=============================================================================

/*
=================
fire_plasma

=================
*/
gentity_t *fire_plasma (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);


	bolt = G_Spawn();
	bolt->classname = "plasma";

    //rhk commented
    /*
	if (self->client->pers.homing_status ==1)
	{
		bolt->nextthink = level.time + 60;
		//bolt->think = G_HomingMissle;
		bolt->damage = 15; //0;
		bolt->splashDamage = 15;
		bolt->splashRadius = 20;
	} else {
		bolt->nextthink = level.time + g_plasma_time.integer;//10000;
		bolt->think = G_ExplodeMissile;
		bolt->damage = 100//0;
		bolt->splashDamage = 0;
		bolt->splashRadius = 20;
	}
    */
    //rhk commented

	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
/*
comentado por rhk
was: g_plasma_bounce.integer
*/	//if (self->client->pers.plasma_bounce == 1) {
	  //bolt->s.eFlags = EF_BOUNCE;
	//}
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_PLASMAGUN;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	//bloque comentado por rhk*
	bolt->damage = 20;
	bolt->splashDamage = 15;
	bolt->splashRadius = 20;

	bolt->methodOfDeath = MOD_PLASMA;
	bolt->splashMethodOfDeath = MOD_PLASMA_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );

    /* MZ commented
	// rkh - adding homing on plasma

	if (self->client->pers.homing_status ==1)
		VectorScale( dir, g_homing_speed.integer, bolt->s.pos.trDelta );
	else
		VectorScale( dir, g_plasma_speed.integer, bolt->s.pos.trDelta );
    */

//	VectorScale( dir, 2000, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

//=============================================================================


/*
=================
fire_grenade
=================
*/
gentity_t *fire_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "grenade";
	bolt->nextthink = level.time + 2500;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_GRENADE_LAUNCHER;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
    /* MZ commented
	// rkh - global turn off of damage
	//if (g_weapondamage.integer == 0)
		//bolt->damage = 100;
	//else
		//bolt->damage = 0;
    */

	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 150;
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

//=============================================================================


/*
=================
fire_bfg
=================
*/
gentity_t *fire_bfg (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "bfg";
/* COMMENTED BY mz
	if (self->client->pers.homing_status ==1)
	{
		bolt->nextthink = level.time + 60; // change how nextthink is set for control over homing exploding?
		//bolt->think = G_HomingMissle;
		bolt->damage = 0;
		bolt->splashDamage = 0;
		bolt->splashRadius = 90;
	} else {
		bolt->nextthink = level.time + g_bfg_time.integer;//1000000;
		bolt->think = G_ExplodeMissile;
		bolt->damage = 0;
		bolt->splashDamage = 0;
		bolt->splashRadius = 20;
	}
    */
    //comentarios rhk
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
    //fin
	if (self->client->pers.bfg_bounce == 1) {
	  bolt->s.eFlags = EF_BOUNCE;
	}
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_BFG;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
    //bloque comentado rhk
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 120;
    //fin
	bolt->methodOfDeath = MOD_BFG;
	bolt->splashMethodOfDeath = MOD_BFG_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
    /*MZ commented
	// rkh - adding homing on bfg
	if (self->client->pers.homing_status ==1)
		VectorScale( dir, g_homing_speed.integer, bolt->s.pos.trDelta );
	else
		VectorScale( dir, g_bfg_speed.integer, bolt->s.pos.trDelta );

    */
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

//=============================================================================

/*
=================
fire_rocket
=================
*/
gentity_t *fire_rocket (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "rocket";
/*
	if (self->client->pers.homing_status ==1)
	{
		bolt->nextthink = level.time + 60;
		//bolt->think = G_HomingMissle;
		bolt->damage = 15;//15
		bolt->splashDamage = 100; //100
		bolt->splashRadius = 90;
	} else {
		bolt->nextthink = level.time + g_rocket_time.integer;//15000;
		bolt->think = G_ExplodeMissile;
		bolt->damage = 100; //100
		bolt->splashDamage = 100; //100
		bolt->splashRadius = 120;
	}
*/
    bolt->nextthink = level.time + g_rocket_time.integer;//15000;
    bolt->think = G_ExplodeMissile;
    bolt->damage = 100; //100
    bolt->splashDamage = 100; //100
    bolt->splashRadius = 120;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_ROCKET_LAUNCHER;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->methodOfDeath = MOD_ROCKET;
	bolt->splashMethodOfDeath = MOD_ROCKET_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;
	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );

	//if (self->client->pers.homing_status ==1)
		//VectorScale( dir, g_homing_speed.integer, bolt->s.pos.trDelta );
	//else
		//VectorScale( dir, 900, bolt->s.pos.trDelta );
//		VectorScale( dir, foo(1), bolt->s.pos.trDelta );	//rkh test foo
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

/*
=================
Missle_Smooth_H rkh homing mod
=================
*/

void Missile_Smooth_H( gentity_t *ent, vec3_t origin, trace_t *tr) {
	int touch[MAX_GENTITIES];
	vec3_t mins, maxs;
	int num;

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES);
	VectorAdd(origin, ent->r.mins, mins);
	VectorAdd(origin, ent->r.maxs, maxs);
	VectorCopy(origin,ent->s.pos.trBase);
	ent->s.pos.trTime = level.time;
}

/*
=================
fire_grapple
=================
*/
gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*hook;

	VectorNormalize (dir);

	hook = G_Spawn();
	hook->classname = "hook";
	hook->nextthink = level.time + 10000;
	hook->think = Weapon_HookFree;
	hook->s.eType = ET_MISSILE;
	hook->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	hook->s.weapon = WP_GRAPPLING_HOOK;
	hook->r.ownerNum = self->s.number;
	hook->methodOfDeath = MOD_GRAPPLE;
	hook->clipmask = MASK_SHOT;
	hook->parent = self;
	hook->target_ent = NULL;

	hook->s.pos.trType = TR_LINEAR;
	hook->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	hook->s.otherEntityNum = self->s.number; // use to match beam in client
	VectorCopy( start, hook->s.pos.trBase );
	VectorScale( dir, 800, hook->s.pos.trDelta );
	SnapVector( hook->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, hook->r.currentOrigin);

	self->client->hook = hook;

	return hook;
}


#ifdef MISSIONPACK
/*
=================
fire_nail
=================
*/
#define NAILGUN_SPREAD	500

gentity_t *fire_nail( gentity_t *self, vec3_t start, vec3_t forward, vec3_t right, vec3_t up ) {
	gentity_t	*bolt;
	vec3_t		dir;
	vec3_t		end;
	float		r, u, scale;

	bolt = G_Spawn();
	bolt->classname = "nail";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_NAILGUN;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	// rkh - global turn off of damage
	if (g_weapondamage.integer == 0)
		bolt->damage = 0;
	else
		bolt->damage = 20;
//	bolt->damage = 20;
	bolt->methodOfDeath = MOD_NAIL;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time;
	VectorCopy( start, bolt->s.pos.trBase );

	r = random() * M_PI * 2.0f;
	u = sin(r) * crandom() * NAILGUN_SPREAD * 16;
	r = cos(r) * crandom() * NAILGUN_SPREAD * 16;
	VectorMA( start, 8192 * 16, forward, end);
	VectorMA (end, r, right, end);
	VectorMA (end, u, up, end);
	VectorSubtract( end, start, dir );
	VectorNormalize( dir );

	scale = 555 + random() * 1800;
	VectorScale( dir, scale, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );

	VectorCopy( start, bolt->r.currentOrigin );

	return bolt;
}


/*
=================
fire_prox
=================
*/
gentity_t *fire_prox( gentity_t *self, vec3_t start, vec3_t dir ) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "prox mine";
	bolt->nextthink = level.time + 3000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_PROX_LAUNCHER;
	bolt->s.eFlags = 0;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 0;
	bolt->splashDamage = 100;
	bolt->splashRadius = 150;
	bolt->methodOfDeath = MOD_PROXIMITY_MINE;
	bolt->splashMethodOfDeath = MOD_PROXIMITY_MINE;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;
	// count is used to check if the prox mine left the player bbox
	// if count == 1 then the prox mine left the player bbox and can attack to it
	bolt->count = 0;

	//FIXME: we prolly wanna abuse another field
	bolt->s.generic1 = self->client->sess.sessionTeam;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}
#endif
