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
		int osc_receive_port;
        string url_post; //where to post data

		///interact with django app
		string saveNew(string headline, string body, string image);

		string status;

		///osc
		ofxOscReceiver  receiver;

};

#endif
