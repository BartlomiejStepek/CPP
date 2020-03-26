//Bartlomiej Stepek
#include "Morphology.h"
#include <iostream>
#include <sstream>
#include <vector>

class BitmapExt : public Bitmap {
    public:
    unsigned rangeX;
    unsigned rangeY;
    unsigned rangeZ;
    bool ***array;

    BitmapExt(unsigned x, unsigned y, unsigned z) {
        rangeX = x;
        rangeY = y;
        rangeZ = z;

        array = new bool**[rangeX];
        for(unsigned int i = 0; i < x; i++) {
            array[i] = new bool*[rangeY];
            for(unsigned j = 0; j < y; j++)
                array[i][j] = new bool [rangeZ];
        }

        for(unsigned i = 0; i < x; i++)
            for(unsigned j = 0; j < y; j++)
                for(unsigned k = 0; k < z; k++)
                    array[i][j][k] = false;
    }

    BitmapExt(const BitmapExt& toCopy) {
        rangeX = toCopy.rangeX;
        rangeY = toCopy.rangeY;
        rangeZ = toCopy.rangeZ;

        array = new bool**[rangeX];
        for(unsigned int i = 0; i < rangeX; i++) {
            array[i] = new bool*[rangeY];
            for(unsigned j = 0; j < rangeY; j++)
                array[i][j] = new bool [rangeZ];
        }

        for(unsigned i = 0; i < rangeX; i++)
            for(unsigned j = 0; j < rangeY; j++)
                for(unsigned k = 0; k < rangeZ; k++)
                    array[i][j][k] = toCopy.array[i][j][k];
    }

    unsigned sx() const {
        return this->rangeX;
    }
    unsigned sy() const {
        return this->rangeY;
    }
    unsigned sz() const {
        return this->rangeZ;
    }
    bool& operator()(unsigned x, unsigned y, unsigned z){
        return array[x][y][z];
    }
    bool operator()(unsigned x, unsigned y, unsigned z) const {
        return array[x][y][z];
    }
};

std::ostream& operator << (std::ostream& out, const Bitmap& map) {
    out << "{\n";
    for(unsigned i = 0; i < map.sx(); i++) {
        out << " {\n";
        for(unsigned j = 0; j < map.sy(); j++) {
            out << "  {";
            for(unsigned k = 0; k < map.sz(); k++) {
                if(map(i,j,k) == true)
                    out << "1";
                else
                    out << "0";

                if(k != map.sz()-1)
                    out << ",";
            }
            if(j == map.sy()-1)
                out << "}\n";
            else
                out << "},\n";
        }
        if(i == map.sx()-1)
            out << " }\n";
        else
            out << " },\n";
    }
    out << "}";
    return out;
}
class Inversion : public Transformation {
    public:
    void transform( Bitmap& map ){
        for(unsigned i = 0; i < map.sx(); i++) {
            for(unsigned j = 0; j < map.sy(); j++) {
                for(unsigned k = 0; k < map.sz(); k++) {
                    if(map(i,j,k))
                        map(i,j,k) = false;
                    else
                        map(i,j,k) = true;
                }
            }
        }
    }
};

class Erosion : public Transformation {
public:
    void transform( Bitmap& map ) {
        unsigned *array = new unsigned [map.sx() * map.sy() * map.sz() * 3];
        int counter = 0;
        bool is_white;
        for(unsigned i = 0; i < map.sx(); i++) {
            for(unsigned j = 0; j < map.sy(); j++) {
                for(unsigned k = 0; k < map.sz(); k++) {
                    is_white = false;
                    if(i > 0 && !map(i-1, j, k))
                        is_white = true;
                    if(i < map.sx() - 1 && !map(i+1, j, k))
                        is_white = true;
                    if(j > 0 && !map(i, j-1, k))
                        is_white = true;
                    if(j < map.sy() - 1 && !map(i, j+1, k))
                        is_white = true;
                    if(k > 0 && !map(i, j, k-1))
                        is_white = true;
                    if(k < map.sz() - 1 && !map(i, j, k+1))
                        is_white = true;

                    if(is_white && map(i,j,k)) {
                        array[counter] = i;
                        array[counter + 1] = j;
                        array[counter + 2] = k;
                        counter += 3;
                    }
                }
            }
        }
        int a = 0;
        for(int i = 0; i < counter/3; i++) {
            map(array[a],array[a+1],array[a+2]) = false;
            a+=3;
        }
        delete[] array;
    }
};

class Diletation : public Transformation {
public:
    void transform( Bitmap& map) {
        unsigned *array = new unsigned [map.sx() * map.sy() * map.sz() * 3];
        int counter = 0;
        bool is_black;
        for(unsigned i = 0; i < map.sx(); i++) {
            for(unsigned j = 0; j < map.sy(); j++) {
                for(unsigned k = 0; k < map.sz(); k++) {
                    is_black = false;
                    if(i > 0 && map(i-1, j, k))
                        is_black = true;
                    if(i < map.sx() - 1 && map(i+1, j, k))
                        is_black = true;
                    if(j > 0 && !map(i, j-1, k))
                        is_black = true;
                    if(j < map.sy() - 1 && map(i, j+1, k))
                        is_black = true;
                    if(k > 0 && map(i, j, k-1))
                        is_black = true;
                    if(k < map.sz() - 1 && map(i, j, k+1))
                        is_black = true;

                    if(is_black && !map(i,j,k)) {
                        array[counter] = i;
                        array[counter + 1] = j;
                        array[counter + 2] = k;
                        counter += 3;
                    }
                }
            }
        }
        int a = 0;
        for(int i = 0; i < counter/3; i++) {
            map(array[a],array[a+1],array[a+2]) = true;
            a+=3;
        }
        delete[] array;
    }
};

class Reset : public Transformation {
public:
    void transform( Bitmap& map) {
        for(unsigned i = 0; i < map.sx(); i++)
            for(unsigned j = 0; j < map.sy(); j++)
                for(unsigned k = 0; k < map.sz(); k++)
                        map(i,j,k) = false;
    }
};

class Averaging : public Transformation {
public:
    void transform( Bitmap& map ) {
        unsigned *array = new unsigned [map.sx() * map.sy() * map.sz() * 4];
        int counter = 0, counter_black = 0, counter_white = 0;
        for(unsigned i = 0; i < map.sx(); i++) {
            for(unsigned j = 0; j < map.sy(); j++) {
                for(unsigned k = 0; k < map.sz(); k++) {
                    counter_black = 0; counter_white = 0;
                    if(i > 0) {
                        if(!map(i-1, j, k))
                            counter_white++;
                        else
                            counter_black++;
                    }
                    if(i < map.sx() - 1){
                        if(!map(i+1, j, k))
                            counter_white++;
                        else
                            counter_black++;
                    }
                    if(j > 0) {
                        if(!map(i, j-1, k))
                            counter_white++;
                        else
                            counter_black++;
                    }
                    if(j < map.sy() - 1){
                        if(!map(i, j+1, k))
                            counter_white++;
                        else
                            counter_black++;
                    }
                    if(k > 0) {
                        if(!map(i, j, k-1))
                            counter_white++;
                        else
                            counter_black++;
                    }
                    if(k < map.sz() - 1){
                        if(!map(i, j, k+1))
                            counter_white++;
                        else
                            counter_black++;
                    }

                    if((counter_black > 3 && !map(i,j,k)) || (counter_white > 3 && map(i,j,k))) {
                        array[counter] = i;
                        array[counter + 1] = j;
                        array[counter + 2] = k;
                        if(counter_black > 3)
                            array[counter + 3] = 1;
                        else
                            array[counter + 3] = 0;
                        counter+=4;
                    }
                }
            }
        }
        int a = 0;
        for(int i = 0; i < counter/4; i++) {
            if(array[a+3] == 1)
                map(array[a],array[a+1],array[a+2]) = true;
            else
                map(array[a],array[a+1],array[a+2]) = false;
            a+=4;
        }
        delete[] array;
    }
};

class CombinationOfTransformations : public Transformation{

public:
    std::vector <Transformation*> array;
    void addTransformation(Transformation* p) {
        array.push_back(p);
    }
    void transform( Bitmap& map ) {
        for(int i = 0; i < array.size(); i++)
            array[i]->transform(map);
    }
};
