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

#include <Arduino.h>

#define AP_PGM 1

namespace approxy {

template <typename T, bool MODE>
T read(const T* ptr) {
    if (MODE) {
        T value;
        memcpy_P(&value, ptr, sizeof(T));
        return value;
    }
    return *ptr;
}

}  // namespace approxy

// одномерный массив
template <typename TX, typename TY, bool MODE = 0>
class Approxy {
   public:
    Approxy(const TX* nx, const TY* ny, uint16_t size) : x(nx), y(ny), _size(size) {}

    float get(float val) {
        if (!_size || !x || !y) return 0;
        if (val < X(0)) return Y(0);                         // вышли слева
        if (val >= X(_size - 1)) return Y(_size - 1);        // вышли справа
        for (uint16_t i = 0; i < _size - 1; i++) {           // поиск
            float x1 = X(i + 1);
            if (x1 > val) {
                float x0 = X(i);
                float y0 = Y(i);
                float y1 = Y(i + 1);
                return (val - x0) * (y1 - y0) / (x1 - x0) + y0;
            }
        }
        return Y(_size - 1);
    }

   private:
    TX X(uint16_t num) {
        return approxy::read<TX, MODE>(&x[num]);
    }
    TY Y(uint16_t num) {
        return approxy::read<TY, MODE>(&y[num]);
    }

    const TX* x;
    const TY* y;
    const uint16_t _size;
};

// двумерный массив
template <typename TXY, bool MODE = 0>
class Approxy2D {
   public:
    Approxy2D(const TXY nxy[][2], uint16_t size) : xy(nxy), _size(size) {}

    float get(float val) {
        if (!_size || !xy) return 0;
        if (val < X(0)) return Y(0);                         // вышли слева
        if (val >= X(_size - 1)) return Y(_size - 1);        // вышли справа
        for (uint16_t i = 0; i < _size - 1; i++) {           // поиск
            float x1 = X(i + 1);
            if (x1 > val) {
                float x0 = X(i);
                float y0 = Y(i);
                float y1 = Y(i + 1);
                return (val - x0) * (y1 - y0) / (x1 - x0) + y0;
            }
        }
        return Y(_size - 1);
    }

   private:
    TXY X(uint16_t num) {
        return approxy::read<TXY, MODE>(&xy[num][0]);
    }
    TXY Y(uint16_t num) {
        return approxy::read<TXY, MODE>(&xy[num][1]);
    }

    const TXY (*xy)[2];
    const uint16_t _size;
};
#endif
