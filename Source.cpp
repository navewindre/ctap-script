#include <Windows.h>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;
using ulong_t = unsigned long;

static constexpr const byte DUCK = VK_LMENU;
static constexpr const byte JUMP = VK_SPACE;
static constexpr const byte ATTACK = VK_LBUTTON;
static constexpr const byte EXIT_KEY = VK_F6;
static constexpr const byte CTAP_KEY = VK_LSHIFT;

byte scan_code( ulong_t key ) {
	const auto result = MapVirtualKey( key, MAPVK_VK_TO_VSC );
	return static_cast< byte >( result );
}

void press_key( byte key ) {
	keybd_event( key, scan_code( key ), 0, 0 );
}

void release_key( byte key ) {
	keybd_event( key, scan_code( key ), KEYEVENTF_KEYUP, 0 );
}

void ctap( ) {
	//credits to http://www.teamfortress.tv/43199/ctap-macro-w-timings

	press_key( DUCK );
	std::this_thread::sleep_for( 0.15s );
	release_key( DUCK );
	press_key( JUMP );
	press_key( ATTACK );
	release_key( JUMP );
	std::this_thread::sleep_for( 0.1s );
	release_key( ATTACK );
}

int main( ) {
	auto window = FindWindowA( 0, "Team Fortress 2" );

	if ( !window ) {
		printf( "tf2 not found" );
		system( "pause" );
		return 1;
	}

	while ( !( GetAsyncKeyState( EXIT_KEY ) & 0x8000 ) ) {
		if ( GetAsyncKeyState( CTAP_KEY ) & 0x1 ) {
			ctap( );
		}

		std::this_thread::sleep_for( 0.01ms );
	}
}