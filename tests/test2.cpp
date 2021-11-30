#include <iostream>

#include "../header/User_Menu.hpp"
#include "../header/Private_Playlist.hpp"
#include "../header/Private_Song.hpp"
#include "../header/Public_Song.hpp"
#include "../header/Public_Playlist.hpp"

using namespace std;

int main() 
{
	cout << "======================" << endl;
	cout << "Create Playlist Test" << endl;
	cout << "======================" << endl;
	cout << endl;
	User_Menu* menu = new User_Menu();
	menu->public_add_playlist();
        menu->public_access_playlist();
	cout << endl;
        cout << "======================" << endl;
        cout << "Create Playlist Test Finished" << endl;
        cout << "======================" << endl;
	cout << endl;
        cout << "======================" << endl;
        cout << "Delete a Song in Playlist Test" << endl;
        cout << "======================" << endl;
	Public_Playlist* playlist = new Public_Playlist("New Playlist");
	playlist->add_song("Happy birthday", "anonymouse", 2);
	playlist->display_songs();
	playlist->delete_song();
	playlist->display_songs();
        cout << "======================" << endl;
        cout << "Delete a Song in Playlist Test Finished" << endl;
        cout << "======================" << endl;
}

