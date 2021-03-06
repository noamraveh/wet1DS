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

    explicit StreamData(int num);

    ~StreamData();

    int getNumStreams();
};

#endif //WET1DS_STREAMDATA_H
