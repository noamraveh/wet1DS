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
    SongData** songs_array;
    ListNode<StreamData>** stream_node_array;
    ArtistData** artist_data_array;
public:
    explicit MainArtistData (int artist_id): id(artist_id),num_songs(0),songs_array(
            nullptr),stream_node_array(nullptr),artist_data_array(nullptr){}
    MainArtistData (int artist_id, int num_songs,ListNode<StreamData>* stream_node): id(artist_id),num_songs(num_songs) {
        songs_array = new SongData*[num_songs];
        stream_node_array = new ListNode<StreamData>*[num_songs];
        artist_data_array = new ArtistData*[num_songs];
        for(int i=0; i<num_songs; i++){
            SongData new_song(i,stream_node);
            songs_array[i] = &new_song;
            stream_node_array[i] = stream_node;
        }
    }
    ~MainArtistData(){
        delete[] songs_array; //everything else was deleted by this point

    }

    int getNumSongs(){
        return num_songs;
    }

    SongData** getSongsArray(){
        return songs_array;
    }

    void updateArtistData(int songID ,ArtistData* artist){
        artist_data_array[songID] = artist;
    }

    void initArtistDataArray(ArtistData* artist){
        for (int i=0 ; i<num_songs; i++){
            updateArtistData(i,artist);
        }
    }

    ListNode<StreamData>** getNodesArray(){
        return stream_node_array;
    }

    void updateStreamsToZero(ListNode<StreamData>* stream_node){
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
        return songs_array[song_id];
    }
};

#endif //WET1DS_MAINARTISTDATA_H
