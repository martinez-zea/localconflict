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

void testApp::saveNew(string headline, string body, string image){
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist = NULL;
    static const char buff[] = "Expect:";

    //string *m = "painter";

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
}

//--------------------------------------------------------------
void testApp::update(){

    //receive osc msg
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        if(m.getAddress() == "/saveSms"){
           ///aca el asunto de osc
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

