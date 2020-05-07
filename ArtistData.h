//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_ARTISTDATA_H
#define WET1DS_ARTISTDATA_H

#include "AVLtree.h"
#include "SongData.h"
#include "LinkedList.h"
#include "StreamData.h"

class ArtistData{
    int artist_id;
    AVLTree<SongData> songs_tree;
    ListNode<StreamData>* stream_node;
public:
    ArtistData(int id,int num_songs,stream_node):artist_id(id),stream_node(stream_node){
        for(int i=0; i<=num_songs; i++){
            SongData new_song(id,stream_node);
            songs_tree.insert(new_song);
        }
    }
    ~ArtistData();

};

#endif //WET1DS_ARTISTDATA_H
