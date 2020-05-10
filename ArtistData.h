//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_ARTISTDATA_H
#define WET1DS_ARTISTDATA_H

#include "FinalAVLTree.h"
#include "SongData.h"
#include "LinkedList.h"
#include "StreamData.h"
#include "MainArtistData.h"

class ArtistData{
private:
    int artist_id;
    AVLTree<SongData>* songs_tree;
public:
    ArtistData(int i,int size) : artist_id(i),songs_tree(size) {}

    void createSongsTreeFromArr(SongData* array){
        songs_tree.fillTreeFromArray(array);
    }

    ~ArtistData() = default;


    AVLTree<SongData> *getSongsTree() {
        return songs_tree;
    }
};

#endif //WET1DS_ARTISTDATA_H
