/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   DialLarge_png;
    const int            DialLarge_pngSize = 1315184;

    extern const char*   DialLargeSurround_png;
    const int            DialLargeSurround_pngSize = 6358;

    extern const char*   DialSmall_png;
    const int            DialSmall_pngSize = 78644;

    extern const char*   DialSmallSurround_png;
    const int            DialSmallSurround_pngSize = 4035;

    extern const char*   RadioButtonOff_png;
    const int            RadioButtonOff_pngSize = 3118;

    extern const char*   RadioButtonOn_png;
    const int            RadioButtonOn_pngSize = 3290;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 6;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
