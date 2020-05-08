//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_SONGDATA_H
#define WET1DS_SONGDATA_H

#include "LinkedList.h"
#include "StreamData.h"

class SongData{
    int id;
    ListNode<StreamData>* stream_node; //linked list node
    int num_streams;
public:
    SongData() = default
    SongData(int id,int num_streams):id(id),stream_node(nullptr),num_streams(num_streams){};
    ~Song()
    int getSongID();
    ArtistData* getArtist();
    int getNumStreams();
    Song (Song & song) = default;
    Song &operator=(Song &song) = delete;
    bool operator>(const Song &song);
    bool operator==(const Song &song);
    ListNode<StreamData>* getStreamNode(){
        return stream_node;
    }

    void setStreamNode(ListNode<StreamData> *new_stream_node) {
        stream_node = new_stream_node;
    }
};

Song::Song(int id):id(id) {}

Song::Song() {

}

#endif //WET1DS_SONGDATA_H
