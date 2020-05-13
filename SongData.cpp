#include "SongData.h"


SongData::SongData(int id) :id(id),stream_node(nullptr){}

SongData::SongData(int id, ListNode<StreamData> *new_stream_node)
        :id(id),stream_node(new_stream_node){}

SongData::~SongData() {
    stream_node = nullptr;
}

bool SongData::operator<(const SongData &song) {
    return id < song.id;
}

bool SongData::operator==(const SongData &song) {
    return id == song.id;
}

ListNode<StreamData> *SongData::getStreamNode() {
    return stream_node;
}

int SongData::getNumStreams() {
    return stream_node->data->getNumStreams();
}

int SongData::getSongID() {
    return id;
}