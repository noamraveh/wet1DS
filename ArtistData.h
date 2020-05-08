//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_ARTISTDATA_H
#define WET1DS_ARTISTDATA_H

#include "FinalAVLTree.h"
#include "SongData.h"
#include "LinkedList.h"
#include "StreamData.h"

class ArtistData{
    int artist_id;
    AVLTree<SongData> songs_tree;
    //ListNode<StreamData>* stream_node;
public:
    ArtistData(int id,int num_songs,int num_streams):artist_id(id){
        for(int i=0; i<=num_songs; i++){
            SongData new_song(i,num_streams);
            songs_tree.insert(new_song);
        }
    }

    void initArtistArray(int num_songs,SongData* array){
        songs_tree.inorderToArray(num_songs,array);
    }
    void updateSongListNodeptrs(ListNode<StreamData>* stream_node){

    }
    ~ArtistData();

};

#endif //WET1DS_ARTISTDATA_H
