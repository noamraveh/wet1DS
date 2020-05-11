//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_STREAMDATA_H
#define WET1DS_STREAMDATA_H

#include "FinalAVLTree.h"
#include "ArtistData.h"

class StreamData{
    int num_of_streams;
    AVLTree<ArtistData> *artists_tree;
    friend class Diesel;
public:
    explicit StreamData(int num): num_of_streams(num){
        artists_tree = new AVLTree<ArtistData>();
    }
    ~StreamData() {
       delete artists_tree;
    }

    int getNumStreams() {
        return num_of_streams;
    }
};
#endif //WET1DS_STREAMDATA_H
