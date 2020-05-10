//
// Created by Noam Raveh on 07/05/2020.
//

#ifndef WET1DS_ARTISTDATA_H
#define WET1DS_ARTISTDATA_H

class SongData;


class ArtistData{
private:
    int artist_id;
    AVLTree<SongData>* songs_tree;
public:
    explicit ArtistData (int id): artist_id(id),songs_tree(nullptr){}
    ArtistData(int i,int size) : artist_id(i),songs_tree(nullptr) {
        songs_tree = new AVLTree<SongData>(size);

    }

    void createSongsTreeFromArr(SongData** array){
        songs_tree->fillTreeFromArray(array);
    }

    ~ArtistData() = default;

    bool operator < (ArtistData & artist_data){
        return artist_id < artist_data.artist_id;
    }
    bool operator ==(const ArtistData & artist_data){
        return artist_id == artist_data.artist_id;
    }
    AVLTree<SongData>* getSongsTree() {
        return songs_tree;
    }
};

#endif //WET1DS_ARTISTDATA_H
    
