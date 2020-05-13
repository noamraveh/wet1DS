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
    explicit SongData(int id=0);

    SongData(int id,ListNode<StreamData> * new_stream_node);

    ~SongData();

    SongData (SongData & song) = default;

    SongData &operator=(SongData &song) = delete;

    bool operator<(const SongData &song);

    bool operator==(const SongData &song);

    ListNode<StreamData>* getStreamNode();

    int getNumStreams();

    int getSongID();
};



#endif //WET1DS_SONGDATA_H
