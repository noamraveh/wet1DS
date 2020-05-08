//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_MAINARTISTDATA_H
#define WET1DS_MAINARTISTDATA_H
#include "SongData.h"
#include "FinalAVLTree.h"

class MainArtistData{
    int id;
    int num_songs;
    SongData* songs_array;
public:

    MainArtistData (int artist_id, int num_songs): id(artist_id),num_songs(num_songs) {
        songs_array = new SongData[num_songs];
    }

    ~MainArtistData(){
        delete[] songs_array; //everything else was deleted by this point
    }

    SongData* getArray(){
        return songs_array;
    }
    void updateSongListNodeptrs(ListNode<StreamData>* stream_node){
        for(int i=0;i<num_songs;i++){
            songs_array[i].setStreamNode(stream_node);
        }

    }
    bool operator <(const MainArtistData &artistInfo){
        return id < artistInfo.id;
    }

    bool operator ==(const MainArtistData &artistInfo){
        return id == artistInfo.id;
    }

    int getNumStreams(int song_id){
        if (song_id>num_songs)
            return -1;
        return songs_array[song_id].getNumStreams();
    }

    SongData* getSongData(int song_id){
        if (song_id>num_songs)
            return nullptr;
    }
};

#endif //WET1DS_MAINARTISTDATA_H
