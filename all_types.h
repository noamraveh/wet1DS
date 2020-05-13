//
// Created by Noam Raveh on 13/05/2020.
//

#ifndef WET1DS_ALL_TYPES_H
#define WET1DS_ALL_TYPES_H

#include "FinalAVLTree.h"
#include "LinkedList.h"
class SongData;
class ArtistData;
class MainArtistData;
class StreamData;

class SongData{
    int id;
    ListNode<StreamData>* stream_node; //linked list node
public:
    explicit SongData(int id=0);

    SongData(int id,ListNode<StreamData> * new_stream_node);

    ~SongData();

    SongData (SongData & song) = default;

    SongData &operator=(SongData &song) = delete;

    bool operator<(const SongData &song);

    bool operator==(const SongData &song);

    ListNode<StreamData>* getStreamNode();

    int getNumStreams();

    int getSongID();
};

class StreamData{
    int num_of_streams;
    AVLTree<ArtistData> *artists_tree;
    friend class Diesel;
public:

    explicit StreamData(int num);

    ~StreamData();

    int getNumStreams();
};


class MainArtistData{
    int id;
    int num_songs;
    SongData** songs_array;
    ListNode<StreamData>** stream_node_array;
    ArtistData** artist_data_array;
public:
    explicit MainArtistData (int artist_id);

    MainArtistData (int artist_id, int num_songs,ListNode<StreamData>* stream_node);

    ~MainArtistData();

    int getNumSongs();

    SongData** getSongsArray();

    void updateArtistData(int songID ,ArtistData* artist);

    void initArtistDataArray(ArtistData* artist);

    ListNode<StreamData>** getNodesArray();


    bool operator <(const MainArtistData &artistInfo);

    bool operator ==(const MainArtistData &artistInfo);

    int getNumStreams(int song_id);

    SongData* getSongData(int song_id);
};


class ArtistData{
private:
    int artist_id;
    AVLTree<SongData>* songs_tree;
public:
    explicit ArtistData (int id);
    ArtistData(int i,int size);

    void createSongsTreeFromArr(SongData** array);

    ~ArtistData();

    bool operator < (ArtistData & artist_data);
    bool operator ==(const ArtistData & artist_data);

    AVLTree<SongData>* getSongsTree();

    int getArtistID();
};

#endif //WET1DS_ALL_TYPES_H
