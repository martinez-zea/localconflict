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
#include "testApp.h"


#ifdef EN
string modNames_en[] = {
    "UNKNOWN",
	"SHOTGUN",
	"GAUNTLET",
	"MACHINEGUN",
	"GRENADE",
	"GRENADE_SPLASH",
	"ROCKET",
	"ROCKET_SPLASH",
	"PLASMA",
	"PLASMA_SPLASH",
	"RAILGUN",
	"LIGHTNING",
	"BFG",
	"BFG_SPLASH",
	"WATER",
	"SLIME",
	"LAVA",
	"CRUSH",
	"TELEFRAG",
	"FALLING",
	"SUICIDE",
	"TARGET_LASER",
	"TRIGGER_HURT",
	"GRAPPLE"
};

 string teamNames_en[] = {
    "CIVIL",
    "RED ARMY",
    "BLUE ARMY",
    "ESPECTATOR",
    "TEAM_NUM_TEAMS" // dont know what this is, included just in case
};
#endif

#ifdef ES
 const string modNames_es = {
    "DESCONOCIDO",
	"ESCOPETA",
	"MOTOSIERRA",
	"AMETRALLDORA",
	"GRANADA",
	"ESQUIRLAS DE GRANADA",
	"ROCKET",
	"ESQUIRLAS DE ROCKET",
	"PLASMA",
	"RADIACION DE PLASMA",
	"LASER",
	"ARMA DE RAYOS",
	"ARMA DE ALTO IMPACTO",
	"ESQUIRLA DE ARMA DE ALTO IMPACTO",
	"AHOGO",
	"DESMEMBRAMIENTO",
	"INCINERACION EN LAVA",
	"APLASTAMIENTO",
	"TELEFRAG",
	"CAIDA DE ALTURA",
	"SUICIDIO",
	"TARGET_LASER",
	"TRIGGER_HURT",
	"GRAPPLE"
};

 const string teamNames_es = {
    "CIVIL",
    "EJERCITO ROJO",
    "EJERCITO AZUL",
    "ESPECTADOR",
    "NUMERO EJERCITOS"
};
#endif

void testApp::saveNew(string headline, string body, string image){
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist = NULL;
    static const char buff[] = "Expect:";


    curl_global_init(CURL_GLOBAL_ALL);

    //fill the message field
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "headline",
                 CURLFORM_COPYCONTENTS, headline.c_str(),
                 CURLFORM_END);


    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "body",
                 CURLFORM_COPYCONTENTS, body.c_str(),
                 CURLFORM_END);

    cout << curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "image",
                 CURLFORM_FILE, image.c_str(),
                 CURLFORM_END) << endl;

    // fill the submit field
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "submit",
                 CURLFORM_COPYCONTENTS, "send",
                 CURLFORM_END);

    curl = curl_easy_init();

    headerlist = curl_slist_append(headerlist, buff);

    if(curl){

        curl_easy_setopt(curl, CURLOPT_URL, url_post.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);

        status = "upload done";

        //cleanup
        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(headerlist);
    }
}

void testApp::saveNew(string headline, string body){
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist = NULL;
    static const char buff[] = "Expect:";


    curl_global_init(CURL_GLOBAL_ALL);

    //fill the message field
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "headline",
                 CURLFORM_COPYCONTENTS, headline.c_str(),
                 CURLFORM_END);


    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "body",
                 CURLFORM_COPYCONTENTS, body.c_str(),
                 CURLFORM_END);

    // fill the submit field
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "submit",
                 CURLFORM_COPYCONTENTS, "send",
                 CURLFORM_END);

    curl = curl_easy_init();

    headerlist = curl_slist_append(headerlist, buff);

    if(curl){

        curl_easy_setopt(curl, CURLOPT_URL, url_post.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);

        status = "upload done";

        //cleanup
        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(headerlist);
    }
}


//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowTitle("Local Conflict -- reporter, the eye in the battle field");
    ofSetVerticalSync(true);
    ofBackground(0,0,0);

    //Read the config settings file
    XML.loadFile("localConflict_settings.xml");

    osc_receive_port = XML.getValue("lc:server:osc_receive_port", 1234);
    url_post = XML.getValue("lc:server:post_url", " ");


    //osc
    receiver.setup(osc_receive_port);

    status = "reporter ready, waiting for frag messages";

    //initialization of string vectos to compare against enum integers

}

//--------------------------------------------------------------
void testApp::update(){

    //receive osc msg
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if(m.getAddress() == "/death"){
           ///aca el asunto de osc
           victim = m.getArgAsString(0);
           killer = m.getArgAsString(1);
           n_mod = m.getArgAsInt32(2);
           n_splashMod = m.getArgAsInt32(3);
           lastkilled = m.getArgAsString(4);
           lasthurt = m.getArgAsString(5);
           n_lasthurt_mod = m.getArgAsInt32(6);
           n_team = m.getArgAsInt32(7);

            //language filters
           #ifdef EN
           //mod = modNames_en[n_mod];
           splashMod = modNames_en[n_mod];
           lasthurt_mod = modNames_en[n_lasthurt_mod];
           //team = teamNames_en[n_team];
           #endif
           #ifdef ES
            mod = modNames_es[n_mod];
            splashMod = modNames_es[n_mod];
           lasthurt_mod = modNames_es[n_lasthurt_mod];
           //team = teamNames_es[n_team];
           #endif

           cout << "victim:  " << victim << endl;
           cout << "killer:  " << killer;
           cout << "mod number:  " << n_mod << endl;
           cout << "last killed:  " << lastkilled << endl;
           cout << "last hurt:  " << lasthurt << endl;
           cout << "team number: " << n_team << endl;
           cout << "mod name:  " << mod;
           cout << "last hurt mode" << lasthurt_mod;
           cout << "team name: " << team << endl;



        }
        if(m.getAddress() == "/team"){
           ///aca el asunto de osc

           n_team_t = m.getArgAsInt32(0);
            //int			location;
            captures = m.getArgAsInt32(1);
            basedefense = m.getArgAsInt32(2);
            carrierdefense = m.getArgAsInt32(3);
            flagrecovery = m.getArgAsInt32(4);
            fragcarrier = m.getArgAsInt32(5);
            assists = m.getArgAsInt32(6);
            lasthurtcarrier = m.getArgAsFloat(7);
            lastreturnedflag = m.getArgAsFloat(8);
            flagsince = m.getArgAsFloat(9);
            lastfraggedcarrier = m.getArgAsFloat(10);

            //language filters
            #ifdef EN
            team_t = teamNames_en[n_team_t] ;
            #endif
            #ifdef ES
            team_t = modNames_es[n_team_t];
            #endif

            // print all messages for debugging
            cout << "team num:  " << n_team_t << endl;
            cout << "team name:  " << team_t << endl;
            cout << "captures:  " << captures << endl;
            cout << "base defense: " << basedefense << endl;
            cout << "team flag recoverys: " << flagrecovery << endl;
            cout << "frag carrier: " << fragcarrier << endl;
            cout << "assists: " << assists << endl;
            cout << "last hurt carrier:  " << endl;
            cout << "flag sience: " << flagsince << endl;
            cout << "last fragged carrier:  " << lastfraggedcarrier << endl;

        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofDrawBitmapString("osc receive port: " + ofToString(osc_receive_port), 10, 20);
    ofDrawBitmapString("posting to: " + url_post, 10, 40);
    ofDrawBitmapString("---------------------------", 10, 70);
    ofDrawBitmapString("status: "+status, 10, 100);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 's') {
        saveNew("hola", "oueaaoen.", "data/img/conflicto_local_1.png");
        saveNew("otra", "sin imagen");
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

