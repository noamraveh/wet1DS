//
// Created by Carmel David & Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_DIESEL_H
#define WET1DS_DIESEL_H

#include "MainArtistData.h"
#include "StreamData.h"
#include "ArtistData.h"
#include "library1.h"
#include "LinkedList.h"
#include "FinalAVLTree.h"
#include "SongData.h"

class Diesel {
    AVLTree<MainArtistData> all_artists_tree;
    LinkedList<StreamData> num_streams_list;
    int total_song_count;
public:
    Diesel():total_song_count(0){}

    ~Diesel() = default;

    StatusType AddArtist(int artistID, int numOfSongs);

    StatusType RemoveArtist(int artistID);

    StatusType AddToSongCount(int artistID, int songID);

    StatusType NumberOfStreams(int artistID, int songID, int *streams);

    StatusType GetRecommendedSongs(int to_print, int *artists, int *songs);

    class ErrorCodes : public std::exception {
    };

    class ALLOCATION_ERROR : public ErrorCodes{

    };
};

#endif //WET1DS_DIESEL_H
