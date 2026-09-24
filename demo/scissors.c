/*
 * `libBeresta`
 *
 * scissors.c - Минимально возможный пример
 * ==========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Complex path drawing example
*/

/** ru
  \par Пример отрисовки сложного объекта
*/

#include "brst.h"
#include "handler.h"
#include "cli.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    char* fname = prepare_output(argc, argv);
    if (fname == NULL) {
        print_error("file name too long");
        return 1;
    }

    // Создание объекта документа
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        print_error("cannot create Doc object");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    BRST_Page_Scale(page, BRST_MM, BRST_MM);

    // Отрисовка ножниц
    BRST_Page_MoveTo(page,  30.465f, 50.000f);
    BRST_Page_CurveTo(page, 30.141f, 50.000f, 29.798f, 49.990f, 29.423f, 49.968f);
    BRST_Page_CurveTo(page, 28.366f, 49.907f, 27.900f, 49.808f, 26.917f, 49.437f);
    BRST_Page_CurveTo(page, 25.329f, 48.839f, 24.564f, 48.222f, 23.755f, 46.889f);
    BRST_Page_CurveTo(page, 23.406f, 46.314f, 23.037f, 44.784f, 23.090f, 44.134f);
    BRST_Page_CurveTo(page, 23.124f, 43.730f, 23.874f, 41.793f, 24.162f, 41.368f);
    BRST_Page_CurveTo(page, 24.264f, 41.218f, 24.663f, 40.629f, 25.050f, 40.058f);
    BRST_Page_CurveTo(page, 25.436f, 39.488f, 26.147f, 38.496f, 26.629f, 37.855f);
    BRST_Page_LineTo(page,  27.506f, 36.689f);
    BRST_Page_LineTo(page,  26.897f, 35.455f);
    BRST_Page_CurveTo(page, 26.562f, 34.776f, 26.229f, 34.112f, 26.157f, 33.980f);
    BRST_Page_CurveTo(page, 26.048f, 33.781f, 26.081f, 33.693f, 26.351f, 33.464f);
    BRST_Page_CurveTo(page, 27.099f, 32.830f, 27.112f, 32.831f, 28.127f, 33.606f);
    BRST_Page_CurveTo(page, 28.634f, 33.994f, 29.236f, 34.398f, 29.465f, 34.504f);
    BRST_Page_CurveTo(page, 29.967f, 34.737f, 30.232f, 34.645f, 32.447f, 33.468f);
    BRST_Page_CurveTo(page, 35.268f, 31.969f, 36.495f, 31.004f, 37.510f, 29.486f);
    BRST_Page_CurveTo(page, 38.319f, 28.275f, 38.599f, 27.712f, 39.674f, 25.139f);
    BRST_Page_CurveTo(page, 40.883f, 22.245f, 41.679f, 19.225f, 42.169f, 15.672f);
    BRST_Page_CurveTo(page, 42.283f, 14.846f, 42.487f, 13.372f, 42.624f, 12.396f);
    BRST_Page_CurveTo(page, 42.760f, 11.420f, 42.851f, 10.574f, 42.827f, 10.518f);
    BRST_Page_CurveTo(page, 42.802f, 10.461f, 42.571f, 10.361f, 42.313f, 10.295f);
    BRST_Page_CurveTo(page, 41.971f, 10.208f, 41.675f, 10.228f, 41.227f, 10.370f);
    BRST_Page_CurveTo(page, 40.473f, 10.610f, 40.386f, 10.709f, 38.731f, 13.213f);
    BRST_Page_CurveTo(page, 38.069f, 14.215f, 37.492f, 15.049f, 37.449f, 15.067f);
    BRST_Page_CurveTo(page, 37.350f, 15.107f, 36.315f, 16.274f, 36.281f, 16.384f);
    BRST_Page_CurveTo(page, 36.225f, 16.563f, 34.469f, 18.088f, 33.684f, 18.638f);
    BRST_Page_CurveTo(page, 32.931f, 19.166f, 32.420f, 19.406f, 28.552f, 21.040f);
    BRST_Page_CurveTo(page, 22.660f, 23.531f, 14.339f, 26.641f, 11.423f, 27.442f);
    BRST_Page_CurveTo(page,  9.652f, 27.929f,  8.743f, 28.090f,  6.762f, 28.266f);
    BRST_Page_CurveTo(page,  3.407f, 28.564f,  1.155f, 27.368f,  0.319f, 24.844f);
    BRST_Page_CurveTo(page,  0.032f, 23.977f,  0.000f, 22.817f,  0.060f, 22.151f);
    BRST_Page_CurveTo(page,  0.474f, 20.174f,  2.043f, 17.789f,  3.955f, 16.230f);
    BRST_Page_CurveTo(page,  4.974f, 15.400f,  6.782f, 14.092f,  7.551f, 13.629f);
    BRST_Page_CurveTo(page,  9.988f, 12.162f, 13.826f, 10.284f, 15.641f,  9.671f);
    BRST_Page_CurveTo(page, 19.317f,  8.429f, 20.834f,  8.049f, 24.083f,  7.559f);
    BRST_Page_CurveTo(page, 27.296f,  7.074f, 28.808f,  7.036f, 30.596f,  7.396f);
    BRST_Page_CurveTo(page, 31.634f,  7.605f, 33.379f,  8.366f, 34.047f,  8.901f);
    BRST_Page_CurveTo(page, 35.451f, 10.027f, 36.172f,  9.764f, 38.444f,  7.298f);
    BRST_Page_CurveTo(page, 39.335f,  6.332f, 39.778f,  6.015f, 40.333f,  5.947f);
    BRST_Page_CurveTo(page, 40.580f,  5.917f, 41.350f,  5.820f, 42.042f,  5.731f);
    BRST_Page_CurveTo(page, 42.735f,  5.642f, 43.753f,  5.544f, 44.305f,  5.513f);
    BRST_Page_CurveTo(page, 44.856f,  5.482f, 45.854f,  5.399f, 46.522f,  5.328f);
    BRST_Page_CurveTo(page, 47.189f,  5.258f, 48.209f,  5.164f, 48.788f,  5.119f);
    BRST_Page_LineTo(page,  49.840f,  5.037f);
    BRST_Page_LineTo(page,  54.098f,  3.415f);
    BRST_Page_CurveTo(page, 56.440f,  2.523f, 58.425f,  1.788f, 58.510f,  1.782f);
    BRST_Page_CurveTo(page, 58.594f,  1.775f, 58.655f,  1.824f, 58.645f,  1.889f);
    BRST_Page_CurveTo(page, 58.634f,  1.954f, 58.684f,  2.017f, 58.757f,  2.028f);
    BRST_Page_CurveTo(page, 58.829f,  2.039f, 58.870f,  2.005f, 58.847f,  1.952f);
    BRST_Page_CurveTo(page, 58.825f,  1.900f, 58.961f,  1.708f, 59.150f,  1.526f);
    BRST_Page_CurveTo(page, 59.419f,  1.268f, 60.017f,  0.988f, 62.418f,  0.000f);
    BRST_Page_LineTo(page,  78.349f,  0.000f);
    BRST_Page_CurveTo(page, 72.283f,  2.989f, 70.348f,  3.970f, 70.333f,  4.065f);
    BRST_Page_CurveTo(page, 70.326f,  4.106f, 71.382f,  4.125f, 72.680f,  4.104f);
    BRST_Page_CurveTo(page, 73.977f,  4.084f, 75.746f,  4.069f, 76.611f,  4.071f);
    BRST_Page_CurveTo(page, 79.819f,  4.077f, 81.022f,  4.064f, 83.647f,  3.995f);
    BRST_Page_CurveTo(page, 86.675f,  3.917f, 90.214f,  4.004f, 96.286f,  4.308f);
    BRST_Page_CurveTo(page, 97.169f,  4.352f, 98.348f,  4.407f, 98.906f,  4.429f);
    BRST_Page_CurveTo(page, 99.823f,  4.466f, 99.999f,  4.587f, 99.878f,  4.725f);
    BRST_Page_CurveTo(page, 99.104f,  5.036f, 93.279f,  6.937f, 92.857f,  7.017f);
    BRST_Page_CurveTo(page, 92.549f,  7.075f, 91.532f,  7.301f, 90.596f,  7.520f);
    BRST_Page_CurveTo(page, 87.659f,  8.206f, 80.733f,  9.350f, 76.660f,  9.820f);
    BRST_Page_CurveTo(page, 76.344f,  9.857f, 75.026f, 10.017f, 73.732f, 10.176f);
    BRST_Page_CurveTo(page, 72.438f, 10.335f, 69.153f, 10.727f, 66.433f, 11.047f);
    BRST_Page_LineTo(page,  61.488f, 11.630f);
    BRST_Page_LineTo(page,  61.091f, 11.333f);
    BRST_Page_CurveTo(page, 60.782f, 11.102f, 60.713f, 11.084f, 60.783f, 11.250f);
    BRST_Page_CurveTo(page, 60.903f, 11.534f, 60.734f, 11.828f, 60.420f, 11.885f);
    BRST_Page_CurveTo(page, 60.281f, 11.910f, 58.832f, 12.051f, 57.200f, 12.198f);
    BRST_Page_CurveTo(page, 51.250f, 12.734f, 52.011f, 12.602f, 50.286f, 13.400f);
    BRST_Page_CurveTo(page, 48.683f, 14.142f, 47.803f, 14.679f, 47.412f, 15.152f);
    BRST_Page_CurveTo(page, 46.851f, 15.834f, 46.324f, 17.347f, 45.844f, 19.657f);
    BRST_Page_CurveTo(page, 45.574f, 20.957f, 45.385f, 21.773f, 45.176f, 22.543f);
    BRST_Page_CurveTo(page, 44.953f, 23.362f, 44.388f, 24.874f, 43.413f, 27.265f);
    BRST_Page_CurveTo(page, 42.209f, 30.215f, 41.989f, 30.816f, 41.949f, 31.271f);
    BRST_Page_CurveTo(page, 41.886f, 31.979f, 42.040f, 32.960f, 42.412f, 34.223f);
    BRST_Page_CurveTo(page, 43.087f, 36.511f, 43.136f, 37.293f, 42.737f, 39.421f);
    BRST_Page_CurveTo(page, 42.177f, 42.406f, 39.816f, 45.825f, 36.815f, 47.998f);
    BRST_Page_CurveTo(page, 36.355f, 48.330f, 35.779f, 48.610f, 34.546f, 49.099f);
    BRST_Page_CurveTo(page, 32.916f, 49.746f, 31.871f, 49.993f, 30.465f, 50.000f);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page,  30.858f, 47.955f);
    BRST_Page_CurveTo(page, 31.179f, 47.952f, 31.493f, 47.929f, 31.791f, 47.883f);
    BRST_Page_CurveTo(page, 32.860f, 47.719f, 35.324f, 46.544f, 36.403f, 45.682f);
    BRST_Page_CurveTo(page, 38.238f, 44.218f, 39.768f, 42.111f, 40.526f, 40.003f);
    BRST_Page_CurveTo(page, 41.000f, 38.685f, 41.099f, 37.930f, 40.955f, 36.730f);
    BRST_Page_CurveTo(page, 40.756f, 35.070f, 40.195f, 34.126f, 39.149f, 33.690f);
    BRST_Page_CurveTo(page, 37.875f, 33.160f, 37.280f, 33.303f, 34.956f, 34.703f);
    BRST_Page_CurveTo(page, 32.643f, 36.095f, 27.981f, 39.778f, 27.420f, 40.656f);
    BRST_Page_CurveTo(page, 27.381f, 40.718f, 27.107f, 40.995f, 26.813f, 41.272f);
    BRST_Page_CurveTo(page, 25.901f, 42.129f, 25.509f, 42.820f, 25.437f, 43.701f);
    BRST_Page_CurveTo(page, 25.388f, 44.301f, 25.427f, 44.600f, 25.611f, 45.029f);
    BRST_Page_CurveTo(page, 25.914f, 45.734f, 26.574f, 46.584f, 27.144f, 47.002f);
    BRST_Page_CurveTo(page, 27.957f, 47.598f, 29.469f, 47.968f, 30.858f, 47.955f);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page,   5.880f, 25.801f);
    BRST_Page_CurveTo(page,  6.427f, 25.821f,  6.559f, 25.772f, 12.917f, 23.181f);
    BRST_Page_CurveTo(page, 18.838f, 20.767f, 19.725f, 20.432f, 23.209f, 19.288f);
    BRST_Page_CurveTo(page, 25.306f, 18.600f, 27.793f, 17.806f, 28.735f, 17.524f);
    BRST_Page_CurveTo(page, 29.677f, 17.241f, 30.884f, 16.809f, 31.416f, 16.564f);
    BRST_Page_CurveTo(page, 32.299f, 16.156f, 32.445f, 16.049f, 33.080f, 15.345f);
    BRST_Page_CurveTo(page, 34.067f, 14.253f, 34.254f, 13.347f, 33.740f, 12.148f);
    BRST_Page_CurveTo(page, 33.329f, 11.191f, 32.730f, 10.697f, 31.298f, 10.130f);
    BRST_Page_CurveTo(page, 30.601f,  9.855f, 29.919f,  9.639f, 29.783f,  9.651f);
    BRST_Page_CurveTo(page, 29.647f,  9.663f, 29.521f,  9.636f, 29.501f,  9.591f);
    BRST_Page_CurveTo(page, 29.423f,  9.409f, 26.971f,  9.560f, 25.087f,  9.863f);
    BRST_Page_CurveTo(page, 23.027f, 10.194f, 20.590f, 10.718f, 18.671f, 11.243f);
    BRST_Page_CurveTo(page, 17.337f, 11.608f, 13.164f, 13.352f, 11.295f, 14.327f);
    BRST_Page_CurveTo(page,  9.734f, 15.141f,  6.859f, 16.938f,  6.244f, 17.483f);
    BRST_Page_CurveTo(page,  4.334f, 19.177f,  3.204f, 20.970f,  3.118f, 22.443f);
    BRST_Page_CurveTo(page,  3.008f, 24.350f,  4.150f, 25.740f,  5.880f, 25.801f);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page,   50.480f, 10.650f);
    BRST_Page_CurveTo(page,  50.707f, 10.650f, 50.938f, 10.604f, 51.167f, 10.510f);
    BRST_Page_CurveTo(page,  52.087f, 10.133f, 52.434f,  9.330f, 52.112f,  8.325f);
    BRST_Page_CurveTo(page,  51.904f,  7.678f, 51.493f,  7.332f, 50.812f,  7.231f);
    BRST_Page_CurveTo(page,  50.275f,  7.151f, 50.042f,  7.234f, 50.392f,  7.380f);
    BRST_Page_CurveTo(page,  50.534f,  7.440f, 50.661f,  7.436f, 50.674f,  7.373f);
    BRST_Page_CurveTo(page,  50.710f,  7.205f, 51.327f,  7.571f, 51.618f,  7.932f);
    BRST_Page_CurveTo(page,  51.943f,  8.337f, 52.028f,  8.697f, 51.952f,  9.156f);
    BRST_Page_CurveTo(page,  51.927f,  9.686f, 51.265f,  9.975f, 50.916f, 10.129f);
    BRST_Page_CurveTo(page,  50.489f, 10.313f, 50.307f, 10.332f, 49.963f, 10.227f);
    BRST_Page_CurveTo(page,  49.365f, 10.045f, 49.004f,  9.589f, 48.963f,  8.963f);
    BRST_Page_CurveTo(page,  48.927f,  8.431f, 48.767f,  8.338f, 48.784f,  8.859f);
    BRST_Page_CurveTo(page,  48.804f,  9.504f, 48.863f,  9.695f, 49.141f, 10.014f);
    BRST_Page_CurveTo(page,  49.507f, 10.432f, 49.982f, 10.651f, 50.480f, 10.650f);
    BRST_Page_ClosePath(page);
    BRST_Page_Fill(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
