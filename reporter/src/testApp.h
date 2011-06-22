#ifndef _TEST_APP
#define _TEST_APP

/*
  _
 | |
 | |____  _____
 |_|    \(___  )
  _| | | |/ __/
 |_|_|_|_(_____)
 -------------------------
 http://martinez-zea.info

 Copyright 2011 by Camilo Martinez & Gabriel Zea

 Project:
 Author:

 ----------------------------------------------------------

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 ----------------------------------------------------------
 */
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include "ofxDirList.h"

#define IN_PORT 6662
#define ES  //idioma de los reportajes

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		///XML stuff
		ofxXmlSettings XML;

		ofImage lastPicture;
		//image directory

		int osc_receive_port;
        string url_post; //where to post data

		///interact with django app
		void saveNew(string headline, string body, string image);
		void saveNew(string headline, string body);

        int num_victims; //victims since started reporting

        ofxDirList IMG_DIR;
        string BASE_PATH;
        int filesInDir; //total images in dir
        int lastFilesInDir;
        //to check if theres new images in directory
        string lastImageName;
        string currentImageName;
        bool    newImage;

		string status;

		///osc
		ofxOscReceiver  receiver;

    //death info
  string victim;
  string killer;
  int  n_mod;
  int  n_splashMod;
  string lastkilled;	// last client that this client killed
  string   lasthurt;	// last client that damaged this client
  int   n_lasthurt_mod;		// type of damage the client did
  int n_team;
  string mod;
  string splashMod;
  string lasthurt_mod;
  string team;
  int newscreenshot;
  int excellent;
//team info

  int n_team_t;
  string team_t;
  string enemy_team_t;
  //int			location;
  int		captures;
  int		basedefense;
  int		carrierdefense;
  int		flagrecovery;
  int		fragcarrier;
  int		assists;
  float		lasthurtcarrier;
  float		lastreturnedflag;
  float		flagsince;
  float		lastfraggedcarrier;
  int       almost_capture;
  int       carrying_own_flag;
  int       carrying_enemy_flag;


//general info
    int killcount;
//methos of dead enum
enum mods{
	MOD_UNKNOWN,
	MOD_SHOTGUN,
	MOD_GAUNTLET,
	MOD_MACHINEGUN,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_ROCKET,
	MOD_ROCKET_SPLASH,
	MOD_PLASMA,
	MOD_PLASMA_SPLASH,
	MOD_RAILGUN,
	MOD_LIGHTNING,
	MOD_BFG,
	MOD_BFG_SPLASH,
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_TARGET_LASER,
	MOD_TRIGGER_HURT,
	MOD_GRAPPLE
};

string victim_message;
string heading;
string article;
string victims_complement;
string flag_complement;
string almost_capture_complement;
string excellent_complement;
string captures_complement;
};


#endif

/*

ioquake3 original typedef enums.  Mission Pack values nont included here

typedef enum {
	MOD_UNKNOWN,
	MOD_SHOTGUN,
	MOD_GAUNTLET,
	MOD_MACHINEGUN,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_ROCKET,
	MOD_ROCKET_SPLASH,
	MOD_PLASMA,
	MOD_PLASMA_SPLASH,
	MOD_RAILGUN,
	MOD_LIGHTNING,
	MOD_BFG,
	MOD_BFG_SPLASH,
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_TARGET_LASER,
	MOD_TRIGGER_HURT,
#ifdef MISSIONPACK
	MOD_NAIL,
	MOD_CHAINGUN,
	MOD_PROXIMITY_MINE,
	MOD_KAMIKAZE,
	MOD_JUICED,
#endif
	MOD_GRAPPLE
} meansOfDeath_t;
*/


