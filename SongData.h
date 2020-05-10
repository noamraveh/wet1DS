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
public:
    SongData(int id=0):id(id),stream_node(nullptr){}
    SongData(int id,ListNode<StreamData> * new_stream_node):id(id),stream_node(new_stream_node){}
    ~SongData() = default;

    SongData (SongData & song) = default;
    SongData &operator=(SongData &song) = delete;
    bool operator>(const SongData &song){
        return id > song.id;
    }
    bool operator==(const SongData &song){
        return id == song.id;
    }
    ListNode<StreamData>* getStreamNode(){
        return stream_node;
    }

    void setStreamNode(ListNode<StreamData> *new_stream_node) {
        stream_node = new_stream_node;
    }

    //SongData():id(0) {}
};



#endif //WET1DS_SONGDATA_H
