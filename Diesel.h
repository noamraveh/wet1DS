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

StatusType Diesel::AddArtist(int artistID, int numOfSongs) {

    if (artistID<=0 || numOfSongs<=0)
        return INVALID_INPUT;
    try {
        MainArtistData temp(artistID);
        if (all_artists_tree.findData(&temp))
            return FAILURE;
        //if first artist - create zero streams node
        if (num_streams_list.isEmpty()) {
            auto zero_streams_data = new StreamData(0);
            num_streams_list.InsertFirst(zero_streams_data);
        }
        //add to main all_artists_tree and fill array with songs
        auto main_artist_data = new MainArtistData(artistID, numOfSongs,
                                                   num_streams_list.getFirstNode());
        all_artists_tree.insert(main_artist_data);


        //create artist node with songs tree
        SongData **created_array = all_artists_tree.findData(
                main_artist_data)->getSongsArray();
        auto new_artist = new ArtistData(artistID, numOfSongs);
        new_artist->createSongsTreeFromArr(created_array);
        main_artist_data->initArtistDataArray(new_artist);


        //add node to zero streams tree
        num_streams_list.getFirstNode()->data->artists_tree->insert(
                new_artist);
        total_song_count += numOfSongs;
    }
    catch (std::bad_alloc &){
        throw ALLOCATION_ERROR{};
    }
    return SUCCESS;
}

StatusType Diesel::RemoveArtist(int artistID) {
    //find artist in artist tree -> found data | log(n)
    if (artistID<=0)
        return INVALID_INPUT;
    try {
        MainArtistData search_data(artistID);
        MainArtistData *found_data = all_artists_tree.findData(
                &search_data);
        if (!found_data) //No Artist Found
            return FAILURE;
        int numSongs = found_data->getNumSongs();
        ArtistData delete_artist(artistID);
        int *listNodesFlagsArray = new int[numSongs];
        ListNode<StreamData> **arr = found_data->getNodesArray();

        //go over songs array, for each song delete artist node (will delete songs tree also)
        for (int i = 0; i < numSongs; i++) {
            ArtistData *found_artist = arr[i]->data->artists_tree->findData(
                    &delete_artist);
            if (found_artist)
                arr[i]->data->artists_tree->remove(found_artist);
            if (arr[i]->data->artists_tree->getRoot() == nullptr) {
                listNodesFlagsArray[i] = 1; //needs to be deleted afterwards
            } else {
                listNodesFlagsArray[i] = 0;
            }
        }
        for (int j = 0;
             j < numSongs; j++) { //delete ListNodes with no artists
            if (listNodesFlagsArray[j]) {
                num_streams_list.removeNode(arr[j]);
            }
        }
        delete[] listNodesFlagsArray;
        all_artists_tree.remove(found_data);
        total_song_count -= numSongs;
    }
    catch(std::bad_alloc &){
        throw ALLOCATION_ERROR{};
    }
    return SUCCESS;
}

StatusType Diesel::AddToSongCount(int artistID, int songID) {
    //find  artist and get song, song linked list node
    if (artistID<=0 || songID<0)
        return INVALID_INPUT;
    try {
        MainArtistData wanted_artist(artistID);
        MainArtistData *found_artist = all_artists_tree.findData(
                &wanted_artist);
        if (!found_artist)
            return FAILURE;
        if (found_artist->getNumSongs() < songID)
            return INVALID_INPUT;
        SongData *found_song = found_artist->getSongData(songID);
        if (!found_song) {
            return FAILURE;
        }
        ListNode<StreamData> *found_stream_node = found_song->getStreamNode();

        //check if streams+1 node exists if it doesn't - create listNode
        int current_stream_num = found_stream_node->data->getNumStreams();
        ListNode<StreamData> *next_node = num_streams_list.getNextNode(
                found_stream_node);
        if (num_streams_list.getLastNode() == found_stream_node ||
            next_node->data->getNumStreams() != current_stream_num + 1) {
            auto next_stream_num = new StreamData(current_stream_num + 1);
            next_node = num_streams_list.InsertNode(found_stream_node,
                                                    next_stream_num);
        }
        //remove song from current tree
        ArtistData search_artist(artistID);
        AVLTree<ArtistData> *original_tree = found_stream_node->data->artists_tree;
        ArtistData *artist = original_tree->findData(&search_artist);
        artist->getSongsTree()->remove(found_song);

        //if needed remove artist from artist tree
        if (artist->getSongsTree()->getRoot() == nullptr) {
            original_tree->remove(artist);
        }
        //if need remove node from linked list
        if (original_tree->getRoot() == nullptr) {
            num_streams_list.removeNode(found_stream_node);
        }
        //if needed add artist to artist tree, then add song to song tree
        SongData *to_add_song = new SongData(songID, next_node);

        AVLTree<ArtistData> *to_add_tree = next_node->data->artists_tree;
        ArtistData *add_artist = to_add_tree->findData(&search_artist);
        if (!add_artist) {
            ArtistData *to_add_artist = new ArtistData(artistID);
            to_add_tree->insert(to_add_artist);
            ArtistData *added_artist = to_add_tree->findData(to_add_artist);
            added_artist->getSongsTree()->insert(to_add_song);
            found_artist->updateArtistData(songID,
                                           added_artist); // update artistData array
        } else {
            add_artist->getSongsTree()->insert(to_add_song);
            found_artist->updateArtistData(songID,
                                           add_artist);// update artistData array
        }

        //update array ptr in main tree

        found_artist->getSongsArray()[songID] = to_add_song;
        found_artist->getNodesArray()[songID] = next_node;
    }
    catch (std::bad_alloc &){
        throw ALLOCATION_ERROR{};
    }
    return SUCCESS;
}

StatusType Diesel::NumberOfStreams(int artistID, int songID, int *streams) {
    if (artistID<=0 || songID<0)
        return INVALID_INPUT;
    try {
        MainArtistData search_data(artistID);
        MainArtistData *found_data = all_artists_tree.findData(&search_data);
        if (!found_data)
            return FAILURE;
        int num_streams = found_data->getNumStreams(songID);
        if (num_streams < 0)
            return INVALID_INPUT;
        *streams = num_streams;
    }
    catch (std::bad_alloc &){
        throw ALLOCATION_ERROR{};
    }
    return SUCCESS;
}

StatusType Diesel::GetRecommendedSongs(int to_print, int *artists, int *songs) {
    try {
        if (to_print <= 0)
            return INVALID_INPUT;
        if (to_print > total_song_count)
            return FAILURE;
        int i = 0;
        ListNode<StreamData> *current_node = num_streams_list.getLastNode();
        while (current_node) {
            current_node->data->artists_tree->resetCurrent();
            TreeNode<ArtistData> *current_artist = current_node->data->artists_tree->getCurrent();
            while (current_artist) {
                current_artist->getData()->getSongsTree()->resetCurrent();
                TreeNode<SongData> *current_song = current_artist->getData()->getSongsTree()->getCurrent();
                while (current_song) {
                    if (i >= to_print) {
                        current_artist->getData()->getSongsTree()->resetCurrent();
                        current_node->data->artists_tree->resetCurrent();
                        return SUCCESS;
                    }
                    artists[i] = current_artist->getData()->getArtistID();
                    songs[i] = current_song->getData()->getSongID();
                    i++;
                    current_artist->getData()->getSongsTree()->updateCurrent();
                    current_song = current_artist->getData()->getSongsTree()->getCurrent();
                }
                current_node->data->artists_tree->updateCurrent();
                current_artist = current_node->data->artists_tree->getCurrent();
            }
            current_node = num_streams_list.getPrevNode(current_node);
        }
    }
    catch (std::bad_alloc &){
        throw ALLOCATION_ERROR{};
    }
    return SUCCESS;
}


#endif //WET1DS_DIESEL_H
