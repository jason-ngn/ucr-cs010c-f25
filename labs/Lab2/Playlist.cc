#include <iostream>
#include <string>
#include <vector>
#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode()
{
	this->uniqueID = "none";
	this->songName = "none";
	this->artistName = "none";
	this->songLength = 0;
	this->nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string ID, string songNameInput, string artistNameInput, int songLengthInput)
{
	this->uniqueID = ID;
	this->songName = songNameInput;
	this->artistName = artistNameInput;
	this->songLength = songLengthInput;
	this->nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode *song)
{
	if (this->nextNodePtr == nullptr)
	{
		this->nextNodePtr = song;
	}
	else
	{
		PlaylistNode *tempSong = this->nextNodePtr;
		this->nextNodePtr = song;
		song->nextNodePtr = tempSong;
	}
}

void PlaylistNode::SetNext(PlaylistNode *song)
{
	this->nextNodePtr = song;
}

string PlaylistNode::GetID()
{
	return this->uniqueID;
}

string PlaylistNode::GetSongName()
{
	return this->songName;
}

string PlaylistNode::GetArtistName()
{
	return this->artistName;
}

int PlaylistNode::GetSongLength()
{
	return this->songLength;
}

PlaylistNode *PlaylistNode::GetNext()
{
	return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode()
{
	cout << "Unique ID: " << this->uniqueID << endl;
	cout << "Song Name: " << this->songName << endl;
	cout << "Artist Name: " << this->artistName << endl;
	cout << "Song Length (in seconds): " << this->songLength << endl;
}

Playlist::Playlist()
{
	this->head = nullptr;
	this->tail = nullptr;
	numOfSongs = 0;
}

Playlist::~Playlist()
{
	PlaylistNode *curr = this->head;
	while (this->head != nullptr)
	{
		this->head = this->head->GetNext();
		delete curr;
		curr = this->head;
	}
}

PlaylistNode::PlaylistNode(PlaylistNode &copy)
{
	this->uniqueID = copy.GetID();
	this->songName = copy.GetSongName();
	this->artistName = copy.GetArtistName();
	this->songLength = copy.GetSongLength();
	this->nextNodePtr = copy.GetNext();
}

void Playlist::Append(PlaylistNode *song)
{
	if (head == nullptr)
	{
		head = song;
		tail = song;
	}
	else
	{
		tail->SetNext(song);
		tail = song;
	}
	numOfSongs++;
}

void Playlist::Remove(PlaylistNode *song)
{
	if (head == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (head == song)
	{
		head = song->GetNext();
	}
	else if (tail == song)
	{
		PlaylistNode *currNode = head;
		PlaylistNode *prevNode = nullptr;

		while (currNode->GetNext() != nullptr)
		{
			currNode = currNode->GetNext();
			prevNode = currNode;
		}

		prevNode->SetNext(nullptr);
		tail = prevNode;
	}
	else
	{
		PlaylistNode *currNode = head;
		PlaylistNode *prevNode = nullptr;

		while (currNode != song)
		{
			prevNode = currNode;
			currNode = currNode->GetNext();
		}

		prevNode->SetNext(song->GetNext());
	}

	numOfSongs--;
	delete song;
}

PlaylistNode *Playlist::Find(const string songUniqueID)
{
	PlaylistNode *currSong = this->head;
	PlaylistNode *found = nullptr;
	while (currSong != nullptr)
	{
		if (currSong->GetID() == songUniqueID)
		{
			found = currSong;
		}

		currSong = currSong->GetNext();
	}

	return found;
}

void Playlist::ChangePosition(int originalPos, int newPos)
{
	PlaylistNode *origSong = GetSongAtIndex(originalPos);
	PlaylistNode *songAtNewPos = GetSongAtIndex(newPos);
	PlaylistNode *songAtPrevPos = GetSongAtIndex(newPos - 1);

	if (originalPos == 1)
	{
		head = origSong->GetNext();

		if (songAtNewPos->GetNext() == nullptr)
		{
			tail->SetNext(origSong);
			origSong->SetNext(nullptr);
			tail = origSong;
		}
		else
		{
			origSong->SetNext(songAtNewPos->GetNext());
			songAtNewPos->SetNext(origSong);
		}
	}
	else if (originalPos == 5)
	{
		PlaylistNode *currNode = head;
		PlaylistNode *prevNode = nullptr;

		while (currNode->GetNext() != nullptr)
		{
			prevNode = currNode;
			currNode = currNode->GetNext();
		}
		tail = prevNode;
		prevNode->SetNext(nullptr);

		if (newPos == 1)
		{
			origSong->SetNext(head);
			head = origSong;
		}
		else
		{
			origSong->SetNext(songAtNewPos);
			songAtPrevPos->SetNext(origSong);
		}
	}
	else
	{
		PlaylistNode *currNode = head;
		PlaylistNode *prevNode = nullptr;

		while (currNode != origSong)
		{
			prevNode = currNode;
			currNode = currNode->GetNext();
		}

		prevNode->SetNext(origSong->GetNext());

		if (newPos == 1)
		{
			origSong->SetNext(head);
			head = origSong;
		}
		else if (newPos == numOfSongs)
		{
			tail->SetNext(origSong);
			origSong->SetNext(nullptr);
			tail = origSong;
		}
		else if (originalPos - newPos > 0)
		{
			origSong->SetNext(songAtNewPos);
			songAtPrevPos->SetNext(origSong);
		}
		else if (newPos - originalPos > 0)
		{
			origSong->SetNext(songAtNewPos->GetNext());
			songAtNewPos->SetNext(origSong);
		}
	}
}

PlaylistNode *Playlist::GetSongAtIndex(int index)
{
	int counter = 1;
	PlaylistNode *currNode = head;
	PlaylistNode *found = nullptr;

	while (currNode != nullptr)
	{
		if (counter == index)
		{
			found = currNode;
		}
		currNode = currNode->GetNext();
		counter++;
	}
	return found;
}

int Playlist::GetIndexOfSong(PlaylistNode *song)
{
	int counter = 1;
	PlaylistNode *currNode = head;
	int index = 0;

	while (currNode != nullptr)
	{
		if (currNode == song)
		{
			index = counter;
		}
		currNode = currNode->GetNext();
		counter++;
	}
	return index;
}

vector<int> Playlist::GetSongsByArtist(const string artistName)
{
	PlaylistNode *currNode = head;
	vector<int> listOfSongs;

	while (currNode != nullptr)
	{
		if (currNode->GetArtistName() == artistName)
		{
			listOfSongs.push_back(GetIndexOfSong(currNode));
		}
		currNode = currNode->GetNext();
	}

	return listOfSongs;
}

int Playlist::GetTotalTimeOfPlaylist()
{
	int time = 0;
	PlaylistNode *currNode = head;
	while (currNode != nullptr)
	{
		time += currNode->GetSongLength();
		currNode = currNode->GetNext();
	}
	return time;
}

vector<int> Playlist::GetTotalPlaylist()
{
	int counter = 1;
	PlaylistNode *currNode = head;
	vector<int> listOfSongs;
	while (currNode != nullptr)
	{
		listOfSongs.push_back(counter);
		counter++;
		currNode = currNode->GetNext();
	}
	return listOfSongs;
}