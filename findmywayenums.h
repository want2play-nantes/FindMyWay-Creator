
#ifndef EASYPAINTENUMS_H
#define EASYPAINTENUMS_H

/**
 * @brief Enum with instruments names
 *
 */
typedef enum
{
    NONE_INSTRUMENT = 0,
    CURSOR,
    LINE,
    MAGNIFIER,
    RECTANGLE,
    ELLIPSE,


    // Don't use it. (Used to know count of current instrument)
    INSTRUMENTS_COUNT
} InstrumentsEnum;


#endif // EASYPAINTENUMS_H
