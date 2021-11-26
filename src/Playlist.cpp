#include "../header/Playlist.hpp"
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include "../header/Song.hpp"
#include <iostream>

using namespace std;

Playlist::Playlist(string n)
{
   name = n;
}

void Playlist::display()
{
   std::string option = "B";
   while (option != "E")
   {
      std::cout << name << std::endl;
      display_songs();

      std::cout << "(AS) - ADD SONG" << std::endl;
      // std::cout << std::endl;
      std::cout << "(DS) - DELETE SONG" << std::endl;
      // std::cout << std::endl;
      std::cout << "(HS) - HIDE/UNHIDE SONG" << std::endl;
      // std::cout << std::endl;
      std::cout << "(P) - PLAY" << std::endl;
      // std::cout << std::endl;
      std::cout << "(PS) - PLAY SONG" << std::endl;
      // std::cout << std::endl;
      std::cout << "(S) - SHUFFLE" << std::endl;
      // std::cout << std::endl;
      std::cout << "(A) - ANALYTICS" << std::endl;
      // std::cout << endl;
      std::cout << "(E) - EXIT" << std::endl;
      cout << endl;
      std::cout << "ENTER OPTION:" << endl;

      std::cin >> option;

      if (option == "AS")
      {
         std::string name;
         std::string artist;
         double length;
         Song *temp = nullptr;
         char duplicate;
         std::cout << endl;
         std::cin.ignore();
         cout << "Enter song name:" << endl;
         std::getline(std::cin, name);
         cout << endl;
         cout << "Enter artist name:" << endl;
         std::getline(std::cin, artist);
         cout << endl;
         cout << "Enter song length (in minutes):" << endl;
         cin >> length;
         cout << endl;
         temp = new Song(name, artist, length);

         if (song_exists(temp))
         {
            cout << "Add song again? - Song already exists in playlist" << endl;
            cout << "Enter (y/n):" << endl;
            cin >> duplicate;
            cout << endl;
            if (duplicate == 'y')
            {
               Playable *new_song = new Song(name, artist, length);
               add_song(new_song);
               delete temp;
            }
         }
         else
         {
            Playable *new_song = new Song(name, artist, length);
            add_song(new_song);
         }
      }

      else if (option == "DS")
      {
         cout << endl;
         delete_song();
      }

      else if (option == "HS")
      {
         cout << endl;
         hide_unhide_song();
      }

      else if (option == "P")
      {
         cout << endl;
         play();
      }
      else if (option == "PS")
      {
         cout << endl;
	 string s;
	 string a;
	 cin.ignore();
	 cout << "Enter song name:" << endl;
         std::getline(std::cin, s);
         cout << endl;
         cout << "Enter artist name:" << endl;
         std::getline(std::cin, a);
         cout << endl;
	      
         play_song(s,a);
      }
      else if (option == "S")
      {
         cout << endl;
         shuffle();
      }
      else if (option == "A")
      {
         cout << endl;
         analytics();
      }
      else if (option != "E")
      {
	  cout << "Invalid input, try again." << endl;
      }
   }
}

bool Playlist::song_exists(Playable *curr)
{
   for (unsigned int i = 0; i < songs.size(); i++)
   {
      if (songs.at(i)->get_artist() == curr->get_artist() && songs.at(i)->get_name() == curr->get_name() && songs.at(i)->get_length() == curr->get_length())
      {
         return true;
      }
   }
   return false;
}

void Playlist::display_songs()
{
   for (unsigned int i = 0; i < songs.size(); i++)
   {
      std::cout << songs.at(i)->get_name() << " - " << songs.at(i)->get_artist() << endl;
   }
   cout << endl;
}

void Playlist::add_song(string name, string artist, double length){
 	Song* temp = new Song(name, artist, length);
    songs.push_back(temp);
}


void Playlist::add_song(Playable *song)
{
   songs.push_back(song);
}

void Playlist::delete_song()
{
   int input;
   string title;
   int order;
   cout << "Enter 1 if you want to delete a song by titles" << endl;
   cout << "Enter 2 if you want to delete a song by order" << endl;
   cin >> input;
   if(input == 1)
   {
	cout << "Enter title: ";
	cin.ignore();
        getline(cin, title);
	for(int i = 0; i < songs.size(); i++) {
	    if(songs.at(i)->get_name() == title) {
		songs.erase(songs.begin()+i);
		return;
	    }
	}
	cout << "Can't find the song" << endl;
   }
   else if(input == 2)
   {
	cout << "Enter the order: ";
	cin >> order;
	if(order < 1 || order > songs.size()){
	    cout << "Invalid order" << endl;
	    return;
	}
	else {
	    songs.erase(songs.begin()+order-1);
	}
   }
   else 
   {
	cout << "Invalid input" << endl;
	return;
   }

   
}

void Playlist::hide_unhide_song()
{
   cin.ignore();
   string songname = "";
   int indexOfSong = -1;
   cout << "Please enter the name of the song you would like to hide or unhide, or enter LEAVE, to return to the main menu." << endl;
   getline(cin, songname);
   cout << endl;
   if (songname.compare("LEAVE") == 0)
   {
      // display_options();
      return;
   }
   else
   {
      for (unsigned i = 0; i < songs.size(); i++)
      {
         if (songs.at(i)->get_name().compare(songname) == 0)
         {
            indexOfSong = i;
         }
      }
      if (indexOfSong == -1)
      {
         cout << "Song not found. Please try again" << endl;
         hide_unhide_song();
         return;
      }
      else
      {
         if (songs.at(indexOfSong)->get_hidden_status())
         {
            songs.at(indexOfSong)->set_hidden_status();
            cout << songs.at(indexOfSong)->get_name() << " Has been unhidden." << endl;
         }
         else
         {
            songs.at(indexOfSong)->set_hidden_status();
            cout << songs.at(indexOfSong)->get_name() << " Has been hidden." << endl;
         }
         return;
      }
   }
}

void Playlist::play(){
//bug:should check if song is hidden before playing
	if (songs.size() == 0){
  		std::cout << "Please add songs to play" << endl;
  		display();
		return;
	}

	if(songs.size() > 0){
  		std::cout << "Now playing: " << songs.at(0)->get_name() << ", by " << songs.at(0)->get_artist() << endl;
  		songs.at(0)->increment_time_played();
	}
	
	 if(songs.size() > 1){
	  std::cout << "Upcoming songs: " << endl; 
		for( unsigned int i = 1; i < songs.size(); i++){
			std::cout << songs.at(i)->get_name() << ", by " << songs.at(i)->get_artist() << endl;
			songs.at(i)->increment_time_played();

		}
	}

	
}
void Playlist::play_song(string song, string artist){
     bool found = false;
     for (unsigned int i = 0; i < songs.size(); i++) {
           if (songs.at(i)->get_name() == song && songs.at(i)->get_artist() == artist) {
               found = true;
               cout << songs.at(i)->get_name() << " - " << songs.at(i)->get_artist() << " is now playing." << endl;
               songs.at(i)->increment_time_played();
           }
       }
       if (!found) {
          cout <<  "Song is not found in current playlist." << endl;
       }
	
}

void Playlist::shuffle()
{
   if (songs.size() < 1)
   {
      cout << "Please add songs before trying to shuffle the plaaylist" << endl;
      return;
   }

   shuffled_songs = songs;

   vector<Playable *> temp;
   temp = songs;

   vector<Playable *>::iterator ptr;

   srand(time(NULL)); // setting the seed based on the current time

   int randInt = 0;

   for (int i = 0; i < songs.size(); i++)
   {
      randInt = rand() % (temp.size());
      ptr = temp.begin();
      shuffled_songs.at(i) = temp.at(randInt);
      ptr += randInt;
      temp.erase(ptr);
   }

   cout << "Songs have been shuffled, now playing playlist" << endl;
   for (int i = 0; i < shuffled_songs.size(); i++)
   {
      if (!shuffled_songs.at(i)->get_hidden_status())
      {
         cout << "Playing: " << shuffled_songs.at(i)->get_name() << " by: " << shuffled_songs.at(i)->get_artist() << " for " << shuffled_songs.at(i)->get_length() << " minutes." << endl;
         shuffled_songs.at(i)->increment_time_played(); // will need to be removed for the private playlist
      }
   }
   return;
}

void Playlist::analytics(){
//bugs: the sum function isnt working as expected
// : throws error if playlist is empty, check if playlist is empty before running through
	vector<int> v;
	int max = songs.at(0)->get_num_time_played();
	
	for(unsigned int i = 0; i < songs.size(); i++){ // find max time played
		if(songs.at(i)->get_num_time_played() > max)
		max = songs.at(i)->get_num_time_played();	
	}
	
	
	for(unsigned int i = 0; i < songs.size(); i++){ // make a vector to store all the indexes of this max val
		if (songs.at(i)->get_num_time_played() == max)
		v.push_back(i);
	}
	
	if(v.size() == 1){ // if only one instance of max val
		std::cout << "Your most played song is " << songs.at(v.at(0))->get_name() << " by " << songs.at(v.at(0))->get_artist() << endl;
	}
	
	else { // if few instances of highest val
		std::cout << "Your most played songs are : " << endl;
		for(unsigned int i = 0; i < v.size(); i++){
			std::cout << songs.at(v.at(i))->get_name() << " by " << songs.at(v.at(i))->get_artist() << endl; 
		}
			
	}
		
		
	int sum = 0; 
	for(unsigned int i = 0; i < songs.size(); i++){
		sum += songs.at(i)->get_num_time_played() * songs.at(i)->get_length(); 
	}
	
	if (sum%60 == 0)
	std::cout << "You spent " << sum/60 << " minutes listening to this playlist." << endl;
	
	else
	std::cout << "You spent " << sum/60 << " minutes and " << sum%60 << " seconds listening to this playlist." << endl;
}

	// insert implementation
// shuffled_songs = temp;

