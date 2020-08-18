class Casillas{
protected:
    int bonus; // 0 = nada, 1 = serpiente, 2 = escalera.

public:
    Casillas();
    Casillas(int);
    int getBonus();
    void setBonus(int);
};
