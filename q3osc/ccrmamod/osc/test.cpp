
#include "test.h"
#include "osc.h"
#include "../game/g_local.h"
#include <string>
#include <sstream>
//#include "../ui/menudef.h"			// rkh

#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"
#include "oscpack/ip/IpEndpointName.h"

//#define ADDRESS "127.0.0.1"
//#define ADDRESS "192.168.1.77"
//#define PORT 6662 
//7000

#define OUTPUT_BUFFER_SIZE 2048

void sendOSCmessage(osc_client_vars currentClient)
{

std::string str(currentClient.port);
std::istringstream strin(str);
int port;
strin >> port;

   char buffer[OUTPUT_BUFFER_SIZE];
   osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
//    UdpTransmitSocket socket( IpEndpointName( ADDRESS, PORT ) );
//    UdpTransmitSocket socket( IpEndpointName( hostname, int(portnumber) ) );
//    UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, int(currentClient.port)) );
   UdpTransmitSocket socket( IpEndpointName( currentClient.hostname, port ));
   p.Clear();

   p << osc::BeginBundle(currentClient.clientnum)
	<< osc::BeginMessage( "/port" ) << port << osc::EndMessage
	<< osc::BeginMessage( "/client" ) << currentClient.clientnum << osc::EndMessage
	<< osc::BeginMessage( "/originx" ) << currentClient.origin[0] << osc::EndMessage
	<< osc::BeginMessage( "/originy" ) << currentClient.origin[1] << osc::EndMessage
	<< osc::BeginMessage( "/originz" ) << currentClient.origin[2] << osc::EndMessage
	<< osc::EndBundle;

   if(p.IsReady()){ socket.Send( p.Data(), p.Size() );}
}

/*void sendOSCmessage(int clientno, char *hostname, char *portnumber)
{

std::string str(portnumber);
std::istringstream strin(str);
int port;

strin >> port;

    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
//    UdpTransmitSocket socket( IpEndpointName( ADDRESS, PORT ) );
//    UdpTransmitSocket socket( IpEndpointName( hostname, int(portnumber) ) );
    UdpTransmitSocket socket( IpEndpointName( hostname, port) );

   p.Clear();


    p << osc::BeginMessage( "/test3" )
            << clientno << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

        //p << osc::BeginBundleImmediate
        p << osc::BeginBundle(1234)
            << osc::BeginMessage( "/message_one" ) << 1 << 2 << 3 << 4 << osc::EndMessage
            << osc::BeginMessage( "/message_two" ) << 1 << 2 << 3 << 4 << osc::EndMessage
            << osc::BeginMessage( "/message_three" ) << 1 << 2 << 3 << 4 << osc::EndMessage
            << osc::BeginMessage( "/message_four" ) << 1 << 2 << 3 << 4 << osc::EndMessage
            << osc::EndBundle;
        //assertEqual( ps.IsReady(), true );
    socket.Send( p.Data(), p.Size() );


    //p << osc::BeginBundleImmediate
   p << osc::BeginBundle()    
        << osc::BeginMessage( "/test1" ) << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" ) << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
   // assertEqual( p.IsReady(), true );
    socket.Send( p.Data(), p.Size() );



    // send a bundle
    p.Clear();
    p << osc::BeginBundle();

        p << osc::BeginMessage( "/no_arguments" )
            << osc::EndMessage;

       p << osc::BeginMessage( "/a_bool" )
            << true << osc::EndMessage;

         p << osc::BeginMessage( "/a_bool" )
            << false << osc::EndMessage;

        p << osc::BeginMessage( "/a_bool" )
            << (bool)1234 << osc::EndMessage;

        p << osc::BeginMessage( "/nil" )
            << osc::Nil << osc::EndMessage;

        p << osc::BeginMessage( "/inf" )
            << osc::Infinitum << osc::EndMessage;

        p << osc::BeginMessage( "/an_int" ) << 1234 << osc::EndMessage;

        p << osc::BeginMessage( "/a_float" )
            << 3.1415926f << osc::EndMessage;

        p << osc::BeginMessage( "/a_char" )
            << 'c' << osc::EndMessage;

        p << osc::BeginMessage( "/an_rgba_color" )
            << osc::RgbaColor(0x22334455) << osc::EndMessage;

//        p << osc::BeginMessage( "/a_midi_message" )
//            << MidiMessage(0x7F) << osc::EndMessage;

//        p << osc::BeginMessage( "/an_int64" )
//            << (int64)(0xFFFFFFF) << osc::EndMessage;

        p << osc::BeginMessage( "/a_time_tag" )
            << osc::TimeTag(0xFFFFFFFUL) << osc::EndMessage;

        p << osc::BeginMessage( "/a_double" )
            << (double)3.1415926 << osc::EndMessage;

        p << osc::BeginMessage( "/a_string" )
            << "hello world" << osc::EndMessage;

        p << osc::BeginMessage( "/a_symbol" )
            << osc::Symbol("foobar") << osc::EndMessage;

        // blob
        {
            char blobData[] = "abcd";

            p << osc::BeginMessage( "/a_blob" )
                << osc::Blob( blobData, 4 )
                << osc::EndMessage;
        }

    p << osc::EndBundle;
    socket.Send( p.Data(), p.Size() );
*/




// Define int foo(int) in some C++ module:
int foo(int i)
{

//    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );

/*
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test1" ) 
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" ) 
            << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;

    transmitSocket.Send( p.Data(), p.Size() );
*/

//    char buffer[IP_MTU_SIZE];
//    osc::OutboundPacketStream p( buffer, IP_MTU_SIZE );
/*    UdpTransmitSocket socket( IpEndpointName( ADDRESS, PORT ) );
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
*/
/*
    p.Clear();
    p << osc::BeginMessage( "/test1" )
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    // test1 message with too few arguments
    p.Clear();
    p << osc::BeginMessage( "/test1" )
            << true << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    // test1 message with too many arguments
    p.Clear();
    p << osc::BeginMessage( "/test1" )
            << true << 23 << (float)3.1415 << "hello" << 42 << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    // test1 message with wrong argument type
    p.Clear();
    p << osc::BeginMessage( "/test1" )
            << true << 1.0 << (float)3.1415 << "hello" << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    p.Clear();
    p << osc::BeginMessage( "/test2" )
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );
*/
    // send four /test3 messages, each with a different type of argument
 /*   p.Clear();
    p << osc::BeginMessage( "/test3" )
            << true << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    p.Clear();
    p << osc::BeginMessage( "/test3" )
            << 23 << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    p.Clear();
    p << osc::BeginMessage( "/test3" )
            << (float)3.1415 << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );

    p.Clear();
    p << osc::BeginMessage( "/test3" )
           << "hello" << osc::EndMessage;
    socket.Send( p.Data(), p.Size() );
*/
    return (100);
};



