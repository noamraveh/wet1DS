//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_MAINARTISTDATA_H
#define WET1DS_MAINARTISTDATA_H

#include "FinalAVLTree.h"
#include "LinkedList.h"
#include "SongData.h"
class ArtistData;
class StreamData;

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

#endif //WET1DS_MAINARTISTDATA_H
