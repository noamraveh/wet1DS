//
// final
//

#include "all_types.h"

SongData::SongData(int id) :id(id),stream_node(nullptr){}

SongData::SongData(int id, ListNode<StreamData> *new_stream_node)
        :id(id),stream_node(new_stream_node){}

SongData::~SongData() {
    stream_node = nullptr;
}

bool SongData::operator<(const SongData &song) {
    return id < song.id;
}

bool SongData::operator==(const SongData &song) {
    return id == song.id;
}

ListNode<StreamData> *SongData::getStreamNode() {
    return stream_node;
}

int SongData::getNumStreams() {
    return stream_node->data->getNumStreams();
}

int SongData::getSongID() {
    return id;
}


StreamData::StreamData(int num): num_of_streams(num){
    artists_tree = new AVLTree<ArtistData>();
}

StreamData::~StreamData() {
    delete artists_tree;
}

int StreamData::getNumStreams() {
    return num_of_streams;
}


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


ArtistData::ArtistData(int id) : artist_id(id),songs_tree(nullptr){
    songs_tree = new AVLTree<SongData>();
}

ArtistData::ArtistData(int i, int size) : artist_id(i),songs_tree(nullptr) {
    songs_tree = new AVLTree<SongData>(size);

}

void ArtistData::createSongsTreeFromArr(SongData **array) {
    songs_tree->fillTreeFromArray(array);
}

ArtistData::~ArtistData() {
    delete songs_tree;
}

bool ArtistData::operator<(ArtistData &artist_data) {
    return artist_id < artist_data.artist_id;
}

bool ArtistData::operator==(const ArtistData &artist_data) {
    return artist_id == artist_data.artist_id;
}

AVLTree<SongData> *ArtistData::getSongsTree() {
    return songs_tree;
}

int ArtistData::getArtistID() {
    return artist_id;
}
