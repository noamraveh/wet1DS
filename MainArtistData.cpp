#include "MainArtistData.h"

MainArtistData::MainArtistData(int artist_id) : id(artist_id),num_songs(0),songs_array(
        nullptr),stream_node_array(nullptr),artist_data_array(nullptr){}

MainArtistData::MainArtistData(int artist_id, int num_songs,
                               ListNode<StreamData> *stream_node) : id(artist_id),num_songs(num_songs) {
    songs_array = new SongData*[num_songs];
    stream_node_array = new ListNode<StreamData>*[num_songs];
    artist_data_array = new ArtistData*[num_songs];
    for(int i=0; i<num_songs; i++){
        SongData* new_song = new SongData(i,stream_node);
        songs_array[i] = new_song;
        stream_node_array[i] = stream_node;
    }
}

MainArtistData::~MainArtistData() {
    delete[] songs_array; //everything else was deleted by this point
    delete[] stream_node_array;
    delete[] artist_data_array;
}

int MainArtistData::getNumSongs() {
    return num_songs;
}

SongData **MainArtistData::getSongsArray() {
    return songs_array;
}

void MainArtistData::updateArtistData(int songID, ArtistData *artist) {
    artist_data_array[songID] = artist;
}

void MainArtistData::initArtistDataArray(ArtistData *artist) {
    for (int i=0 ; i<num_songs; i++){
        updateArtistData(i,artist);
    }
}

ListNode<StreamData> **MainArtistData::getNodesArray() {
    return stream_node_array;
}

bool MainArtistData::operator<(const MainArtistData &artistInfo) {
    return id < artistInfo.id;
}

bool MainArtistData::operator==(const MainArtistData &artistInfo) {
    return id == artistInfo.id;
}

int MainArtistData::getNumStreams(int song_id) {
    if (song_id>=num_songs)
        return -1;
    return songs_array[song_id]->getNumStreams();
}

SongData *MainArtistData::getSongData(int song_id) {
    if (song_id>=num_songs){
        return nullptr;
    }
    return songs_array[song_id];
}
