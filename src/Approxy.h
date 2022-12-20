/*
    Линейный аппроксиматор
    Документация: 
    GitHub: https://github.com/GyverLibs/Approxy
    Возможности:
    - Аппроксимирует таблицу для получения промежуточных результатов
    - Работа со всеми типами данных
    - Режим PROGMEM для хранения таблицы во Flash
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - исправлен баг в Approxy2D в режиме RAM
*/

#ifndef _Approxy_h
#define _Approxy_h

#define AP_PGM 1

// одномерный массив
template <typename TX, typename TY, bool MODE = 0>
class Approxy {
public:
    Approxy(TX* nx, TY* ny, uint16_t size) : _size(size) {
        x = nx;
        y = ny;
    }

    float get(float val) {
        if (val < X(0)) return Y(0);          // вышли слева
        else if (val >= X(_size - 1)) return Y(_size - 1);  // вышли справа
        for (int i = 0; i < _size - 1; i++) {   // поиск
            if (X(i + 1) > val) return (float)(val - X(i)) * (Y(i + 1) - Y(i)) / (X(i + 1) - X(i)) + Y(i);
        }
    }

private:
    TX X(int num) {
        if (MODE) {
            if (sizeof(TX) == 1) return (TX)pgm_read_byte(&x[num]);
            else if (sizeof(TX) == 2) return (TX)pgm_read_word(&x[num]);
            else return (TX)pgm_read_dword(&x[num]);
        } else return x[num];
    }
    TY Y(int num) {
        if (MODE) {
            if (sizeof(TY) == 1) return (TY)pgm_read_byte(&y[num]);
            else if (sizeof(TY) == 2) return (TY)pgm_read_word(&y[num]);
            else return (TY)pgm_read_dword(&y[num]);
        } else return y[num];
    }
    TX* x;
    TY* y;
    const uint16_t _size;
};

// двумерный массив
template <typename TXY, bool MODE = 0>
class Approxy2D {
public:
    Approxy2D(TXY nxy[][2], uint16_t size) : _size(size) {
        xy = nxy;
    }

    float get(float val) {
        if (val < X(0)) return Y(0);          // вышли слева
        else if (val >= X(_size - 1)) return Y(_size - 1);  // вышли справа
        for (int i = 0; i < _size - 1; i++) {   // поиск
            if (X(i + 1) > val) return (float)(val - X(i)) * (Y(i + 1) - Y(i)) / (X(i + 1) - X(i)) + Y(i);
        }
    }

private:
    TXY X(int num) {
        if (MODE) {
            if (sizeof(TXY) == 1) return (TXY)pgm_read_byte(&xy[num][0]);
            else if (sizeof(TXY) == 2) return (TXY)pgm_read_word(&xy[num][0]);
            else return (TXY)pgm_read_dword(&xy[num][0]);
        } else return xy[num][0];
    }
    TXY Y(int num) {
        if (MODE) {
            if (sizeof(TXY) == 1) return (TXY)pgm_read_byte(&xy[num][1]);
            else if (sizeof(TXY) == 2) return (TXY)pgm_read_word(&xy[num][1]);
            else return (TXY)pgm_read_dword(&xy[num][1]);
        } else return xy[num][1];
    }
    TXY (*xy)[2];
    const uint16_t _size;
};
#endif