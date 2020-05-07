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

class Diesel {
    AVLTree<MainArtistData> all_artists_tree;
    LinkedList<StreamData> num_streams_list;
    AVLTree<ArtistData>* zero_streams_tree;
public:
    Diesel() {
        StreamData zero_streams_data(0);
        num_streams_list.InsertFirst(zero_streams_data);
        zero_streams_tree = num_streams_list.first->data.artists_tree;
    };

    ~Diesel() = default;

    StatusType AddArtist(int artistID, int numOfSongs){

        if (artistID<=0 || numOfSongs<=0)
            return INVALID_INPUT;

        //add to main all_artists_tree
        MainArtistData main_artist_data(artistID, numOfSongs);
        all_artists_tree.insert(main_artist_data);

        //create artist node with tree
        ArtistData new_artist(artistID, numOfSongs,num_streams_list.first);

        //add node to zero streams tree
        zero_streams_tree->insert(new_artist);
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
        StreamData* found_stream_node = found_song->getStreamNode();

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
