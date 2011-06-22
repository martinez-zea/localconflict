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


//initialization of string vectos to compare against enum integers
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
string modNames_es[] = {
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


 string teamNames_es[] = {
    "CIVIL",
    "EJERCITO ROJO",
    "EJERCITO AZUL",
    "ESPECTADOR",
    "NUMERO EJERCITOS"
};

string numbers_male[] = {
    "cero",
    "uno",
    "dos",
    "tres",
    "cuatro",
    "cinco",
    "seis",
    "siete",
    "ocho",
    "nueve",
    "diez",
    "once",
    "doce",
    "trece",
    "catorce",
    "quince",
    "dieciseis",
    "diecisiete",
    "dieciocho",
    "diecinueve",
    "veinte",
    "veintiuno",
    "treinta",
    "cuarenta",
    "cincuenta",
    "sesenta",
    "setenta",
    "ochenta",
    "noventa",
    "cien",
    "doscientos",
    "trescientos",
    "cuatrocientos",
    "quinientos",
    "seiscientos",
    "setecientos",
    "novecientos",
    "mil",
    "diez mil",
    "cien mil",
    "un millón",
    "mil millones",
    "un billón",
    "mil billones",
    "un trillón",
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

    BASE_PATH = XML.getValue("q3:screenshot_path","");
    cout << "path: " << BASE_PATH << endl;
    //osc
    receiver.setup(osc_receive_port);

    status = "reporter ready, waiting for frag messages";



    //files watch for screenshot directory

        IMG_DIR.setVerbose(false);
        filesInDir = IMG_DIR.listDirAlpha(BASE_PATH); //TODO set this in xml

        if(filesInDir == 0){
            //lastImageName = NULL;
            currentImageName = "";

        }else{
            for(int i = 0; i < filesInDir; i++){
                cout << IMG_DIR.getName(i) << endl;
            }
            currentImageName = IMG_DIR.getPath(0);
            lastPicture.setUseTexture(true);
            lastPicture.loadImage(currentImageName);
            cout << "loaded: " << IMG_DIR.getName(0) << endl;
            //lastImageName = currentImageName;
        }
        cout << "files: " << filesInDir<< endl;
        lastFilesInDir = filesInDir;
        newImage = false;

        victim_message = "";
        killcount = 0;


}

//--------------------------------------------------------------
void testApp::update(){

    int num_message;

        //files watch
    IMG_DIR.reset();
    filesInDir = IMG_DIR.listDirAlpha(BASE_PATH); //TODO set this in xml

    if(lastFilesInDir != filesInDir){
        newImage = true;
        //currentImageName = IMG_DIR.getPath(filesInDir - 1);
        lastPicture.setUseTexture(true);
        lastPicture.loadImage(IMG_DIR.getPath(0));
        cout << "New File Written: " << IMG_DIR.getName(0) << endl;
    }else{
        newImage = false;
    }
    lastFilesInDir = filesInDir;

    //receive osc msg
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        //messages with info about death and the player
        if(m.getAddress() == "/death"){

            //adds to killingcount
            killcount++;
            num_message = int(ofRandom(0,3));

           ///aca el asunto de osc
           victim = m.getArgAsString(0);
           killer = m.getArgAsString(1);
           n_mod = m.getArgAsInt32(2);
           n_splashMod = m.getArgAsInt32(3);
           lastkilled = m.getArgAsString(4);
           lasthurt = m.getArgAsString(5);
           n_lasthurt_mod = m.getArgAsInt32(6);
           n_team = m.getArgAsInt32(7);
            newscreenshot = m.getArgAsInt32(8);
            excellent = m.getArgAsInt32(9);

            //language filters
           #ifdef EN
           mod = modNames_en[n_mod];
           //splashMod = modNames_en[n_splashMod];
           //lasthurt_mod = modNames_en[n_lasthurt_mod];
           //team = teamNames_en[n_team];
           #endif
           #ifdef ES
            mod = modNames_es[n_mod];
            //splashMod = modNames_es[n_mod];
           //lasthurt_mod = modNames_es[n_lasthurt_mod];
           //team = teamNames_es[n_team];
           #endif
           cout << "||||||||||||| new death |||||||||||" << endl;
            cout << "========== player info ==========" <<endl;
           cout << "victim:  " << victim << endl;
           cout << "killer:  " << killer << endl;
           cout << "mod number:  " << n_mod << endl;
           cout << "last killed:  " << lastkilled << endl;
           cout << "last hurt:  " << lasthurt << endl;
           cout << "team number: " << n_team << endl;
           cout << "mod name:  " << mod << endl;
           cout << "last hurt mode: " << lasthurt_mod << endl;
           cout << "team name: " << team << endl;
            cout << "new image: " << newscreenshot << endl;
            cout << "excellent: " << excellent << endl;

        }
        // messages w info about team, only for CTF gamemode'
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
            almost_capture = m.getArgAsInt32(11);
            carrying_own_flag = m.getArgAsInt32(12);
            carrying_enemy_flag = m.getArgAsInt32(13);


            //language filters
            #ifdef EN
            team_t = teamNames_en[n_team_t] ;
            #endif
            #ifdef ES
            team_t = teamNames_es[n_team_t];
            if(team_t == "EJERCITO ROJO") enemy_team_t = "EJERCITO AZUL";
            if(team_t == "EJERCITO AZUL") enemy_team_t = "EJERCITO ROJO";
            #endif

            // print all messages for debugging
            cout << "========== team info ==========" << endl;
            cout << "team num:  " << n_team_t << endl;
            cout << "team name:  " << team_t << endl;
            cout << "captures:  " << captures << endl;
            cout << "base defense: " << basedefense << endl;
            cout << "team flag recoverys: " << flagrecovery << endl;
            cout << "frag carrier: " << fragcarrier << endl;
            cout << "assists: " << assists << endl;
            cout << "last hurt carrier:  " << lastfraggedcarrier << endl;
            cout << "flag sience: " << flagsince << endl;
            cout << "last fragged carrier:  " << lastfraggedcarrier << endl;
            cout << "almost capture: " << almost_capture << endl;
            cout << "own flag: " << carrying_own_flag << endl;
            cout << "enemy flag" << carrying_enemy_flag << endl;
        }
            //create victim message

            if(excellent == 1){
                excellent_complement = "El " + enemy_team_t + " ha llevado a cabo una agresiva ofensiva militar, dando de baja a varios integrantes del " + team_t + " en un corto lapso de tiempo, otorgandole una ventaja militar sobre el oponente.";
            } else if(excellent == 0){
                excellent_complement = "";
            }

            if(carrying_own_flag == 1 && carrying_enemy_flag == 0){

                flag_complement =  "El combatiente fue interceptado mientras intentaba recuperar la bandera oficial de su bando.  La posesion de la bandera enemiga es el principal objetivo militar que del conflicto, ya que esta concede el control de las posiciones enemigas al grupo que las capture.";

            } else if(carrying_own_flag == 0 && carrying_enemy_flag == 1){

                flag_complement = "El combatiente fue interceptado mientras intentaba capturar la bandera enemiga. La posesion de la bandera enemiga es el principal objetivo militar que del conflicto, ya que esta concede el control de las posiciones enemigas al grupo que las capture.";

            } else if(carrying_enemy_flag == 0 && carrying_own_flag == 0){

                flag_complement = "";

            }

            if(captures == 0){
                captures_complement = "  En lo que va corrido del conflicto, el" + team_t + " no ha capturado la bandera del " + enemy_team_t + ".";
            } else if(captures == 1){
                captures_complement = "  En lo que va corrido del conflicto, el " + team_t + " ha capturado la bandera del " + enemy_team_t + " en una ocasion.";
            }else if(captures > 1){
                captures_complement = "  En lo que va corrido del conflicto, el " + team_t + " ha capturado la bandera del " + enemy_team_t + " en " + numbers_male[captures] + " ocasiones.";
            }


            if( killcount > 1 && killcount < 22){
                victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[killcount] + " personas entre los combatientes de ambos bandos";
            }else if(killcount >= 22){
                switch(killcount){
                    case 30:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[22] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 40:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[23] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 50:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[24] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 60:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[25] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 770:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[26] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 80:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[27] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 90:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[28] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 100:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[29] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 200:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[30] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 300:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[31] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 400:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[32] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 500:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[33] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 600:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[34] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 800:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[35] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 900:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[36] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 1000:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[37] + " personas entre los combatientes de ambos bandos";
                        break;
                    case 10000:
                        victims_complement = "  Segun fuentes oficiales, desde el comienzo de los enfrentamientos han muerto " + numbers_male[38] + " personas entre los combatientes de ambos bandos";
                        break;
                    default:
                        victims_complement = "";
                        break;
                    }
            switch(num_message){
                case 0:
                    heading = "Otra baja en el " + team_t;
                    victim_message = "El soldado " + victim + " del " + team_t + " murio por impacto de " + mod + " durante intensos enfrentamientos sostenidos entre las fuerzas del Ejercito Azul y los rebeldes del Ejercito Rojo." + excellent_complement;
                    //cout << "victim message :" << victim_message << endl;
                    break;
                case 1:

                    heading = "Muere otro combatiente en el conflicto local";
                    victim_message = "Muere un integrante del " + team_t + " durante un intercambio armado con " + mod + ".";
                    break;

                case 2:
                    heading = "Mas victimas en combates entre Rojos y Azules";
                    victim_message = victim + " ,del " + team_t + ", fue asesinado por " + killer + " quien uso " + mod + ".  El hecho ocurre en medio de el duro enfrentamiento que se desarrolla por el control de las banderas enemigas entre el Ejercito Rojo y Azul";
                    break;
            }


            article = victim_message + excellent_complement + flag_complement + captures_complement + victims_complement;
            //send the message to the web app
            if(newscreenshot == 1){
                saveNew(heading, article, IMG_DIR.getPath(0));
                cout << "sent message and image" << endl;
            }else if(newscreenshot == 0){
                saveNew(heading, article);
                cout << "sent message " << endl;

            }
        }
    }




}

//--------------------------------------------------------------
void testApp::draw(){

    //image display
    if(filesInDir > 0){

        lastPicture.draw(0, 0);
    }

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

/*
Continua la pugna entre el Ejercito Azul y los Rebeldes Rojos por el control del complejo arquitectonico Hydronex

Desde las(time) del dia (date), son frecuentes los enfrentamientos entre las fuerzas azules y los rebeldes rojos, facciones que se pelean por el control de las baderas del oponente.  Hasta el momento (kills) han resultado muertos como causa de la violencia. Los voceros de ambos bandos no han manifestado voluntad de negociacion, por el contrario, se espera que los combates continuen hasta que alguna de las partes logre la captura de 3 banderas enemigas, lo que significaria el control del territorio enemigo.




*/
