#include "StreamData.h"

StreamData::StreamData(int num): num_of_streams(num){
    artists_tree = new AVLTree<ArtistData>();
}

StreamData::~StreamData() {
    delete artists_tree;
}

int StreamData::getNumStreams() {
    return num_of_streams;
}