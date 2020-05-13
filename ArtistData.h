//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_ARTISTDATA_H
#define WET1DS_ARTISTDATA_H

#include "FinalAVLTree.h"

class SongData;


class ArtistData{
private:
    int artist_id;
    AVLTree<SongData>* songs_tree;
public:
    explicit ArtistData (int id);
    ArtistData(int i,int size);

    void createSongsTreeFromArr(SongData** array);

    ~ArtistData();

    bool operator < (ArtistData & artist_data);
    bool operator ==(const ArtistData & artist_data);

    AVLTree<SongData>* getSongsTree();

    int getArtistID();
};


#endif //WET1DS_ARTISTDATA_H
    
