#ifndef SEED_H
#define SEED_H

class Seed
{
    public:
        Seed(int width, int height, const bool* p);
        Seed();
        ~Seed();
        const bool* get();
        void next_generation();
        long int getGen();
        long int getCells();
        const int* getCangedCells();
        int getChangedSize();
    private:
        int width;
        int height;
        long int gen;
        long int cells;
        bool* area[2];
        //short unsigned* changeArray[2];
        int* points[2];
        bool* duplicatesCheck;
        long int pointsSize;
        short unsigned changeGen;
        bool alive(int c);
        void cellChanged(int c);
};
#endif // SEED_H
