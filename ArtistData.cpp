#include "ArtistData.h"

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