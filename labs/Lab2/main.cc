#include <iostream>
#include <string>
#include <vector>
#include "Playlist.h"

using namespace std;

void PrintMenu(const string &playlistName)
{
	cout << playlistName << " PLAYLIST MENU" << endl;
	cout << "a - Add song" << endl;
	cout << "d - Remove song" << endl;
	cout << "c - Change position of song" << endl;
	cout << "s - Output songs by specific artist" << endl;
	cout << "t - Output total time of playlist (in seconds)" << endl;
	cout << "o - Output full playlist" << endl;
	cout << "q - Quit" << endl;
	cout << endl;
	cout << "Choose an option:" << endl;
}

int main()
{
	string playlistTitle;
	string option;
	string songUniqueID;
	string songName;
	string songArtistName;
	string songLengthString;
	string currPosString;
	string newPosString;
	Playlist userPlaylist;
	int songLength;

	cout << "Enter playlist's title:" << endl;
	getline(cin, playlistTitle);
	cout << endl;

	PrintMenu(playlistTitle);
	getline(cin, option);

	while (option != "q")
	{
		if (option == "o")
		{
			cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
			vector<int> listOfSongs = userPlaylist.GetTotalPlaylist();

			if (listOfSongs.size() == 0)
			{
				cout << "Playlist is empty" << endl;
				cout << endl;
			}
			else
			{
				for (unsigned int i = 0; i < listOfSongs.size(); i++)
				{
					cout << listOfSongs.at(i) << "." << endl;
					userPlaylist.GetSongAtIndex(listOfSongs.at(i))->PrintPlaylistNode();
					cout << endl;
				}
			}
		}
		else if (option == "a")
		{
			cout << "ADD SONG" << endl;

			cout << "Enter song's unique ID:" << endl;
			getline(cin, songUniqueID);

			cout << "Enter song's name:" << endl;
			getline(cin, songName);

			cout << "Enter artist's name:" << endl;
			getline(cin, songArtistName);

			cout << "Enter song's length (in seconds):" << endl;
			getline(cin, songLengthString);
			cout << endl;
			songLength = stoi(songLengthString);

			if (userPlaylist.Find(songUniqueID) != nullptr)
			{
				cout << "This song is already in the playlist!" << endl;
			}
			else
			{
				PlaylistNode *newSong = new PlaylistNode(songUniqueID, songName, songArtistName, songLength);
				userPlaylist.Append(newSong);
			}
		}
		else if (option == "d")
		{
			cout << "REMOVE SONG" << endl;

			cout << "Enter song's unique ID:" << endl;
			getline(cin, songUniqueID);

			PlaylistNode *result = userPlaylist.Find(songUniqueID);

			if (result)
			{
				cout << "\"" << result->GetSongName() << "\"" << " removed." << endl;
				userPlaylist.Remove(result);
				cout << endl;
			}
			else
			{
				cout << "Cannot find song with ID \"" << songUniqueID << "\"" << endl;
			}
		}
		else if (option == "c")
		{
			cout << "CHANGE POSITION OF SONG" << endl;
			cout << "Enter song's current position:" << endl;
			getline(cin, currPosString);
			int currPos = stoi(currPosString);

			cout << "Enter new position for song:" << endl;
			getline(cin, newPosString);
			int newPos = stoi(newPosString);

			if (newPos > userPlaylist.numOfSongs)
				newPos = userPlaylist.numOfSongs;

			if (currPos < 1)
				currPos = 1;

			PlaylistNode *songAtCurrPos = userPlaylist.GetSongAtIndex(currPos);
			userPlaylist.ChangePosition(currPos, newPos);

			cout << "\"" << songAtCurrPos->GetSongName() << "\" moved to position " << newPos << endl;
			cout << endl;
		}
		else if (option == "s")
		{
			cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
			cout << "Enter artist's name:" << endl;
			getline(cin, songArtistName);
			cout << endl;

			vector<int> listOfSongs = userPlaylist.GetSongsByArtist(songArtistName);

			for (unsigned int i = 0; i < listOfSongs.size(); i++)
			{
				cout << listOfSongs.at(i) << "." << endl;
				userPlaylist.GetSongAtIndex(listOfSongs.at(i))->PrintPlaylistNode();
				cout << endl;
			}
		}
		else if (option == "t")
		{
			cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
			int totalTime = userPlaylist.GetTotalTimeOfPlaylist();
			cout << "Total time: " << totalTime << " seconds" << endl;
			cout << endl;
		}

		PrintMenu(playlistTitle);
		getline(cin, option);
	}

	return 0;
}