//
// Created by Carmel David & Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_DIESEL_H
#define WET1DS_DIESEL_H

#include "MainArtistData.h"
#include "StreamData.h"
#include "ArtistData.h"
#include "Library1.h"
#include "LinkedList.h"
#include "FinalAVLTree.h"

class Diesel {
    AVLTree<MainArtistData> all_artists_tree;
    LinkedList<StreamData> num_streams_list;
    AVLTree<ArtistData>* zero_streams_tree;
public:
    Diesel() {
        StreamData zero_streams_data(0);
        num_streams_list.InsertFirst(zero_streams_data);
        zero_streams_tree = num_streams_list.getFirstNode()->data.artists_tree;
    };

    ~Diesel() = default;

    StatusType AddArtist(int artistID, int numOfSongs){

        if (artistID<=0 || numOfSongs<=0)
            return INVALID_INPUT;

        //create artist node with songs tree
        ArtistData new_artist(artistID,numOfSongs,0);

        //add to main all_artists_tree
        MainArtistData main_artist_data(artistID, numOfSongs);
        all_artists_tree.insert(main_artist_data);

        //fill array with songs from songs tree
        new_artist.initArtistArray(numOfSongs,main_artist_data.getArray());

        //add linked list node ptr to each song
        new_artist.updateSongListNodeptrs(num_streams_list.getFirstNode());

        //add node to zero streams tree
        zero_streams_tree->insert(new_artist);

        return SUCCESS;
    }

    StatusType RemoveArtist(int artistID){

    }

    StatusType AddToSongCount(int artistID, int songID){
        if (artistID<=0 || songID<0)
            return INVALID_INPUT;
        MainArtistData search_data(artistID,-1);
        MainArtistData* found_data = all_artists_tree.findData(search_data);
        if (!found_data)
            return FAILURE;
        SongData* found_song = found_data->getSongData(songID);
        ListNode<StreamData>* found_stream_node = found_song->getStreamNode();
        //check if streams+1 node exists
        if (num_streams_list.getNextNode(found_stream_node)->data.getNumStreams() != found_stream_node->data.getNumStreams()+1){
            StreamData next_stream_num(found_stream_node->data.getNumStreams() + 1);
            num_streams_list.InsertNode(*found_stream_node,next_stream_num);
        }
        //remove song from current tree
        //if needed remove artist from artist tree
        //if need remove node from linked list
        //if needed add artist to artist tree
        //add song to song tree, change count num and node ptr
    }

    StatusType NumberOfStreams(int artistID, int songID, int *streams){
        if (artistID<=0 || songID<0)
            return INVALID_INPUT;
        MainArtistData search_data(artistID,-1);
        MainArtistData* found_data = all_artists_tree.findData(search_data);
        if (!found_data)
            return FAILURE;
        int num_streams = found_data->getNumStreams(songID);
        if (num_streams<0)
            return INVALID_INPUT;
        *streams = num_streams;
        return SUCCESS;
    }

    StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs);
};




#endif //WET1DS_DIESEL_H
