#include <string>
#include <vector>

using namespace std;

class PlaylistNode
{
private:
	string uniqueID;
	string songName;
	string artistName;
	int songLength;
	PlaylistNode *nextNodePtr;

public:
	PlaylistNode();
	PlaylistNode(PlaylistNode &);
	PlaylistNode(string, string, string, int);
	void InsertAfter(PlaylistNode *);
	void SetNext(PlaylistNode *);
	string GetID();
	string GetSongName();
	string GetArtistName();
	int GetSongLength();
	PlaylistNode *GetNext();
	void PrintPlaylistNode();
};

class Playlist
{
public:
	PlaylistNode *head;
	PlaylistNode *tail;
	int numOfSongs;

	Playlist();
	~Playlist();
	void Append(PlaylistNode *);
	void Remove(PlaylistNode *);
	void ChangePosition(int, int);

	PlaylistNode *Find(const std::string songUniqueID);
	PlaylistNode *GetSongAtIndex(int index);
	std::vector<int> GetSongsByArtist(const std::string artistName);
	std::vector<int> GetTotalPlaylist();
	int GetIndexOfSong(PlaylistNode *song);
	int GetTotalTimeOfPlaylist();
};