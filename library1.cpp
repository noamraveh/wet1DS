//
// final
//

#include "library1.h"
#include "Diesel.h"

void *Init(){
    auto *DS = new Diesel();
    return (void*) DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((Diesel*)DS)->AddArtist(artistID,numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((Diesel*)DS)->RemoveArtist(artistID);
}

StatusType AddToSongCount(void *DS, int artistID, int songID){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((Diesel*)DS)->AddToSongCount(artistID,songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){
    if(DS == nullptr)
        return INVALID_INPUT;

    return ((Diesel*)DS)->NumberOfStreams(artistID,songID,streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    if(DS == nullptr)
        return INVALID_INPUT;
    if (numOfSongs <= 0 ){
        return ALLOCATION_ERROR;
    }
    return ((Diesel*)DS)->GetRecommendedSongs(numOfSongs,artists,songs);
}

void Quit(void** DS){
    if(*DS != nullptr){
        delete ((Diesel *)*DS);
        *DS = nullptr;
    }
}