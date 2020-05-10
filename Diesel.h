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
#include "SongData.h"

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

        //add to main all_artists_tree and fill array with songs
        MainArtistData main_artist_data(artistID, numOfSongs);
        all_artists_tree.insert(main_artist_data);

        //add linked list node ptr to each song
        main_artist_data.updateStreamsToZero(num_streams_list.getFirstNode());

        //create artist node with songs tree
        SongData* created_array = all_artists_tree.findData(main_artist_data)->getArray();
        ArtistData new_artist(artistID,numOfSongs);
        new_artist.createSongsTreeFromArr(created_array);

        //add node to zero streams tree
        zero_streams_tree->insert(new_artist);

        return SUCCESS;
    }

    StatusType RemoveArtist(int artistID){
        //find artist in artist tree -> found data | log(n)
        if (artistID<=0)
            return INVALID_INPUT;
        MainArtistData search_data(artistID,-1);
        MainArtistData* found_data = all_artists_tree.findData(search_data);
        if (!found_data)
            return FAILURE;

        //go over array, for each song delete song tree
        SongData* arr = found_data->getArray();
        for (int i=0; i< found_data->getNumSongs();i++){
            if (arr[i] == nullptr){}

        }
        //while deleting, change songs in array to nullptr
        //delete artist node from linked list node tree
        //if needed, delete linked list node
    }

    StatusType AddToSongCount(int artistID, int songID){
        //find  artist and get song, song linked list node
        if (artistID<=0 || songID<0)
            return INVALID_INPUT;
        MainArtistData wanted_artist(artistID,-1);
        MainArtistData* found_artist = all_artists_tree.findData(wanted_artist);
        if (!found_artist)
            return FAILURE;
        SongData* found_song = found_artist->getSongData(songID);
        if (!found_song){
            return FAILURE;
        }
        ListNode<StreamData>* found_stream_node = found_song->getStreamNode();

        //check if streams+1 node exists if it doesn't - create listNode
        int current_stream_num = found_stream_node->data.getNumStreams();
        ListNode<StreamData>* next_node = num_streams_list.getNextNode(found_stream_node);
        if (next_node->data.getNumStreams() != current_stream_num + 1){
            StreamData next_stream_num(current_stream_num + 1);
            next_node = num_streams_list.InsertNode(*found_stream_node,next_stream_num);
        }
        //remove song from current tree
        ArtistData search_artist(artistID,0);
        ArtistData* artist = found_stream_node->data.artists_tree->findData(search_artist);
        //search_artist = found_stream_node->data.artists_tree->findData(search_artist); // need to create copy ctor to artist data
        artist->getSongsTree()->remove();
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
