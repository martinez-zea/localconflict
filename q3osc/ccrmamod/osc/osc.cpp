
//#include "test.h"
#include "osc.h"
#include "../game/g_local.h"
#include <string>
#include <sstream>
//#include "../ui/menudef.h"			// rkh

#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"
#include "oscpack/ip/IpEndpointName.h"
//#include "oscpack/osc/OscReceivedElements.h"
//#include "oscpack/osc/OscPacketListener.h"
//#define ADDRESS "127.0.0.1"
//#define ADDRESS "192.168.1.77"
//#define PORT 6662
//7000


/*
int maxRockets = 100;           // no longer const
int currentsize;
int* a = new int[max];  // allocated on heap
int n = 0;

//--- Read into the array
    n++;
    if (n >= max) {
        max = max * 2;            // double the previous size
        int* temp = new int[max]; // create new bigger array.
        for (int i=0; i<n; i++) {
            temp[i] = a[i];       // copy values to new array.
        }
        delete [] a;              // free old array memory.
        a = temp;                 // now a points to new array.
    }
}
*/

// if dynamic IP is enabled, ip's will be selected from an array populated by the user
// currently, ips are set in the client and assed in
void getIPAddress (int index){

}

#define OUTPUT_BUFFER_SIZE 2048
void sendOSCmessage_projectile(osc_projectile_vars currentProjectile) //, char *type)
{
//	std::string classname = currentProjectile.classname;
//	std::string slash = "/";

	std::string str(currentProjectile.port);
	std::istringstream strin(str);
	int port;
	strin >> port;
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

	UdpTransmitSocket socket( IpEndpointName( currentProjectile.hostname, port ));
	p.Clear();

//	p << osc::BeginMessage((slash + classname).c_str())
	p << osc::BeginMessage("/projectile")
            << currentProjectile.classname
	    << (int)currentProjectile.ownernum
	    << (int)currentProjectile.projectilenum
	    << (float)currentProjectile.origin[0]
	    << (float)currentProjectile.origin[1]
	    << (float)currentProjectile.origin[2]
	    << (int)currentProjectile.targetnum
	    << (int)currentProjectile.bounce
	    << (int)currentProjectile.explode
	  << osc::EndMessage;

	if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}




}

void sendOSCbundle_projectile(osc_projectile_vars currentProjectile)
{
	std::string str(currentProjectile.port);
	std::istringstream strin(str);
	int port;
	strin >> port;
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

	UdpTransmitSocket socket( IpEndpointName( currentProjectile.hostname, port ));
	p.Clear();

	p << osc::BeginBundle()
		<< osc::BeginMessage( "/classname" ) << currentProjectile.classname << osc::EndMessage
		<< osc::BeginMessage( "/projectilenum" ) << (int)currentProjectile.projectilenum << osc::EndMessage
		<< osc::BeginMessage( "/origin" ) << (float)currentProjectile.origin[0] << (float)currentProjectile.origin[1] << (float)currentProjectile.origin[2] << osc::EndMessage
//		<< osc::BeginMessage( "/originy" ) << currentProjectile.origin[1] << osc::EndMessage
//		<< osc::BeginMessage( "/originz" ) << currentProjectile.origin[2] << osc::EndMessage
		<< osc::BeginMessage( "/ownernum" ) << currentProjectile.ownernum << osc::EndMessage
		<< osc::BeginMessage( "/targetnum" ) << currentProjectile.targetnum << osc::EndMessage
		<< osc::BeginMessage( "/bounce" ) << currentProjectile.bounce << osc::EndMessage
		<< osc::BeginMessage( "/explode" ) << currentProjectile.explode << osc::EndMessage
	<< osc::EndBundle;

	if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}

void sendOSCmessage(osc_client_vars currentClient)
{
	std::string str(currentClient.port);
	std::istringstream strin(str);
	int port;
	strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];
   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, port ));
   p.Clear();

	p << osc::BeginMessage( "/player" )
	    << currentClient.classname
	    << (int)currentClient.clientnum
	    << (float)currentClient.origin[0]
	    << (float)currentClient.origin[1]
	    << (float)currentClient.origin[2]
	  << osc::EndMessage;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}

//MZ
void sendOSCmessage_misc(osc_misc_vars currentClient)
{
	std::string str(currentClient.port);
	std::istringstream strin(str);
	int port;
	strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];
   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, port ));
   p.Clear();

	p << osc::BeginMessage( "/jump" )
	    << currentClient.msg
	   //<< currentClient.classname
	    //<< (int)currentClient.clientnum
	    //<< (float)currentClient.origin[0]
	    //<< (float)currentClient.origin[1]
	    //<< (float)currentClient.origin[2]
	  << osc::EndMessage;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}


void sendOSCmessage_death(osc_death_vars currentClient)
{
	std::string str(currentClient.port);
	std::istringstream strin(str);
	int port;
	strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];

   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, port ));
   p.Clear();

	p << osc::BeginMessage( "/death" )
	    << currentClient.victim
        << currentClient.killer
	    << (int)currentClient.methodOfDeath
	    << (int)currentClient.splashMethodOfDeath
        << currentClient.lastkilled	// last client that this client killed
        <<currentClient.lasthurt	// last client that damaged this client
        <<(int)currentClient.lasthurt_mod
	    <<(int)currentClient.team
	    <<(int)currentClient.image
	    <<(int)currentClient.excellent

	  << osc::EndMessage;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}

void sendOSCmessage_team(osc_team_vars teamData)
{
	std::string str(teamData.port);
	std::istringstream strin(str);
	int port;
	strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];

   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   UdpTransmitSocket socket( IpEndpointName( teamData.hostname, port ));
   p.Clear();

	p << osc::BeginMessage( "/team" )

	    <<(int)teamData.team
        <<(int)teamData.captures
        <<(int)teamData.basedefense
        <<(int)teamData.carrierdefense
        <<(int)teamData.flagrecovery
        <<(int)teamData.fragcarrier
        <<(int)teamData.assists
        <<(float)teamData.lasthurtcarrier
        <<(float)teamData.lastreturnedflag
        <<(float)teamData.flagsince
       <<(float)teamData.lastfraggedcarrier
       <<(int)teamData.almostCapture
       <<(int)teamData.carryingOwnFlag
       <<(int)teamData.carryingEnemyFlag
	  << osc::EndMessage;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}
//end MZ

void sendOSCbundle(osc_client_vars currentClient)
{

	std::string str(currentClient.port);
	std::istringstream strin(str);
	int port;
	strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];
   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, port ));
   p.Clear();

   p << osc::BeginBundle()
	<< osc::BeginMessage( "/classname" ) << currentClient.classname << osc::EndMessage
	<< osc::BeginMessage( "/client" ) << currentClient.clientnum << osc::EndMessage
	<< osc::BeginMessage( "/originx" ) << currentClient.origin[0] << osc::EndMessage
	<< osc::BeginMessage( "/originy" ) << currentClient.origin[1] << osc::EndMessage
	<< osc::BeginMessage( "/originz" ) << currentClient.origin[2] << osc::EndMessage
	<< osc::EndBundle;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}

#define PORT 7000
/*
class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m,
				const IpEndpointName& remoteEndpoint )
    {
        try{
            // example of parsing single messages. osc::OsckPacketListener
            // handles the bundle traversal.

            if( strcmp( m.AddressPattern(), "/test1" ) == 0 ){
                // example #1 -- argument stream interface
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
               // bool a1;
                osc::int32 a2;
               // float a3;
               // const char *a4;
              //  args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
 		args >> a2 >> osc::EndMessage;

                //std::cout << "received '/test1' message with arguments: "<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";

            }else if( strcmp( m.AddressPattern(), "/test2" ) == 0 ){
                // example #2 -- argument iterator interface, supports
                // reflection for overloaded messages (eg you can call
                // (*arg)->IsBool() to check if a bool was passed etc).
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bool a1 = (arg++)->AsBool();
                int a2 = (arg++)->AsInt32();
                float a3 = (arg++)->AsFloat();
                const char *a4 = (arg++)->AsString();
                if( arg != m.ArgumentsEnd() )
                    throw osc::ExcessArgumentException();

//                std::cout << "received '/test2' message with arguments: "
//                    << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
            }
        }catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
//            std::cout << "error while parsing message: "
//                << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
};

void receiveOSCmessage()
{
    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            &listener );

//    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();
}

*/

/*
class fooClass
{
	public:
	  fooClass();
	  ~fooClass();

	private:
	  int number;
};
*/
int foo(int i)
{
    return (100);
};



